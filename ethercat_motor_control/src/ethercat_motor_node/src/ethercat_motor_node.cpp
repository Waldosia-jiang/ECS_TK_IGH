#include <rclcpp/rclcpp.hpp>
#include <rclcpp/executors/multi_threaded_executor.hpp>
#include <rclcpp/qos.hpp>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <sched.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <cmath>
#include <cstdio>
#include <string>

#include <rcl_interfaces/msg/parameter_descriptor.hpp>
#include <rcl_interfaces/msg/floating_point_range.hpp>
#include <rcl_interfaces/msg/set_parameters_result.hpp>

#include "ethercat_motor_node/main.h"
#include "dro_hg/msg/leg_cmd.hpp"
#include "dro_hg/msg/leg_state.hpp"

// SSC 网关从站数量（Beckhoff AX58100）
#define SSC_SLAVE_NUM 3
// 物理从站总数（0~16，共 17 个，从站 3~16 为伺服）
#define PHYSICAL_SLAVE_NUM 17
#define SERVO_FIRST 3
#define SERVO_LAST 16

#define AnaInSlavePos 0, 0

// 伺服 PDO 在 domain 中的字节偏移（用于 3~16 号泰科伺服状态机，参考 ros2_ws/igh_ethercat）
struct ServoPdoOffsets {
    size_t control_word;         // 0x6040
    size_t status_word;          // 0x6041
    size_t target_position;      // 0x607A
    size_t position_actual_value;// 0x6064
    size_t mode_of_operation;    // 0x6060
};
static constexpr size_t INVALID_SERVO_OFFSET = static_cast<size_t>(-1);
#define Beckhoff_AX58100  0x00000009, 0x26483052

// 为泰科伺服（Vendor 0x00000c48, Product 0x00030924）配置 RW 模板 CSP 模式 PDO（参考 ros2_ws/igh_ethercat）
static int configure_servo_pdo(ec_slave_config_t* slave)
{
    const uint16_t rx_pdo = 0x1607;
    const uint16_t tx_pdo = 0x1a07;

    // 清除并重新分配 SM2/SM3
    ecrt_slave_config_pdo_assign_clear(slave, 2);
    ecrt_slave_config_pdo_assign_clear(slave, 3);
    if (ecrt_slave_config_pdo_assign_add(slave, 2, rx_pdo) != 0) return -1;
    if (ecrt_slave_config_pdo_assign_add(slave, 3, tx_pdo) != 0) return -1;

    // 清空 PDO 映射
    ecrt_slave_config_pdo_mapping_clear(slave, rx_pdo);
    ecrt_slave_config_pdo_mapping_clear(slave, tx_pdo);

    // RxPDO: 6040 + 6060 + 607A + 60FF + 6071 + 60B2
    if (ecrt_slave_config_pdo_mapping_add(slave, rx_pdo, 0x6040, 0x00, 16) != 0) return -1; // 控制字
    if (ecrt_slave_config_pdo_mapping_add(slave, rx_pdo, 0x6060, 0x00, 8)  != 0) return -1; // 运行模式
    if (ecrt_slave_config_pdo_mapping_add(slave, rx_pdo, 0x607A, 0x00, 32) != 0) return -1; // 目标位置
    if (ecrt_slave_config_pdo_mapping_add(slave, rx_pdo, 0x60FF, 0x00, 32) != 0) return -1; // 目标速度
    if (ecrt_slave_config_pdo_mapping_add(slave, rx_pdo, 0x6071, 0x00, 16) != 0) return -1; // 目标转矩
    if (ecrt_slave_config_pdo_mapping_add(slave, rx_pdo, 0x60B2, 0x00, 16) != 0) return -1; // 转矩偏移

    // TxPDO: 6041 + 6061 + 6064 + 606C + 6077
    if (ecrt_slave_config_pdo_mapping_add(slave, tx_pdo, 0x6041, 0x00, 16) != 0) return -1; // 状态字
    if (ecrt_slave_config_pdo_mapping_add(slave, tx_pdo, 0x6061, 0x00, 8)  != 0) return -1; // 运行模式显示
    if (ecrt_slave_config_pdo_mapping_add(slave, tx_pdo, 0x6064, 0x00, 32) != 0) return -1; // 实际位置
    if (ecrt_slave_config_pdo_mapping_add(slave, tx_pdo, 0x606C, 0x00, 32) != 0) return -1; // 实际速度
    if (ecrt_slave_config_pdo_mapping_add(slave, tx_pdo, 0x6077, 0x00, 16) != 0) return -1; // 实际转矩

    return 0;
}

using namespace std::chrono_literals;

class EthercatMotorNode : public rclcpp::Node
{
public:
    EthercatMotorNode() : Node("ethercat_motor_node")
    {
        // 声明参数
        this->declare_parameter<int>("slave_num", 3);
        this->declare_parameter<int>("cycle_time_ms", 5);
        this->declare_parameter<bool>("publish_motor_states", true);
        this->declare_parameter<int>("zero_current_update_timeout_ms", 100);
        // dq 低通滤波系数，支持 ROS2 parameter reconfigure，范围 [0,1]，1.0 表示不过滤
        {
            rcl_interfaces::msg::ParameterDescriptor desc;
            desc.description = "dq 低通滤波系数 [0,1]，1 表示不过滤";
            rcl_interfaces::msg::FloatingPointRange range;
            range.from_value = 0.0;
            range.to_value = 1.0;
            range.step = 0.01;
            desc.floating_point_range.push_back(range);
            this->declare_parameter<double>("dq_lowpass_alpha", 0.5, desc);
        }
        this->declare_parameter<int>("temperature_limit_deg", 90);  // 温度保护阈值(℃)，超过则进零电流模式

        slave_num_ = this->get_parameter("slave_num").as_int();
        cycle_time_ms_ = this->get_parameter("cycle_time_ms").as_int();
        publish_states_ = this->get_parameter("publish_motor_states").as_bool();
        zero_current_update_timeout_ms_ = this->get_parameter("zero_current_update_timeout_ms").as_int();
        dq_lowpass_alpha_ = this->get_parameter("dq_lowpass_alpha").as_double();
        temperature_limit_deg_ = this->get_parameter("temperature_limit_deg").as_int();

        // 动态参数回调：支持运行时通过 ros2 param set / Reconfigure 修改 dq_lowpass_alpha
        param_callback_handle_ = this->add_on_set_parameters_callback(
            [this](const std::vector<rclcpp::Parameter> & params)
            {
                rcl_interfaces::msg::SetParametersResult result;
                result.successful = true;
                for (const auto & p : params)
                {
                    if (p.get_name() == "dq_lowpass_alpha")
                    {
                        double v = 0.0;
                        try
                        {
                            v = p.as_double();
                        }
                        catch (const rclcpp::ParameterTypeException &)
                        {
                            result.successful = false;
                            result.reason = "dq_lowpass_alpha 类型必须为 double";
                            return result;
                        }
                        if (v < 0.0 || v > 1.0)
                        {
                            result.successful = false;
                            result.reason = "dq_lowpass_alpha 应在 [0,1] 范围内";
                            return result;
                        }
                        dq_lowpass_alpha_ = v;
                    }
                }
                return result;
            });

        // 发布腿部状态 leg_state（dro_hg）
        leg_state_pub_ = this->create_publisher<dro_hg::msg::LegState>(
            "leg_state", 10);

        // 订阅 dro_hg 腿部控制指令（/leg_cmd），使用默认 QoS（可靠传输）
        leg_cmd_sub_ = this->create_subscription<dro_hg::msg::LegCmd>(
            "leg_cmd", 10,
            std::bind(&EthercatMotorNode::leg_cmd_callback, this, std::placeholders::_1));
        
        RCLCPP_INFO(this->get_logger(), "Subscribed to /leg_cmd (dro_hg), publishing /leg_state");

        // 初始化 EtherCAT
        if (init_ethercat() != 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to initialize EtherCAT master");
            rclcpp::shutdown();
            return;
        }

        // 锁定内存
        if (mlockall(MCL_CURRENT | MCL_FUTURE) == -1)
        {
            RCLCPP_WARN(this->get_logger(), "mlockall() failed: %s", strerror(errno));
        }

        // 创建实时线程
        running_ = true;
        rt_thread_ = std::thread(&EthercatMotorNode::real_time_task, this);

        // 创建定时器用于发布 leg_state
        if (publish_states_)
        {
            timer_ = this->create_wall_timer(
                std::chrono::milliseconds(1),  // 1000Hz
                std::bind(&EthercatMotorNode::publish_leg_state, this));
        }

        // 零电流模式更新状态：未收到 /leg_cmd 时周期性下发零电流指令（电流控制 cur=0，ack_status=1）以持续获取反馈
        apply_zero_current_cmd();
        zero_current_update_timer_ = this->create_wall_timer(
            std::chrono::milliseconds(50),
            std::bind(&EthercatMotorNode::zero_current_update_tick, this));

        RCLCPP_INFO(this->get_logger(), "EtherCAT Motor Node started (zero-current state update when no leg_cmd, timeout %d ms)", zero_current_update_timeout_ms_);
    }

    ~EthercatMotorNode()
    {
        running_ = false;
        if (rt_thread_.joinable())
        {
            rt_thread_.join();
        }
        if (master)
        {
            ecrt_release_master(master);
        }
    }

private:
    // motor_id(1-15) -> slave_idx, passage(1-6)
    // 电机 ID → 从站/通道：ID 1-6 从站0 通道1-6，ID 7-12 从站2 通道1-6，ID 13-15 从站1 通道1-3
    static void motor_id_to_slave_passage(uint16_t motor_id, int& slave_idx, int& passage)
    {
        slave_idx = -1;
        passage = 0;
        if (motor_id >= 1 && motor_id <= 6) { slave_idx = 0; passage = static_cast<int>(motor_id); }
        else if (motor_id >= 7 && motor_id <= 12) { slave_idx = 2; passage = static_cast<int>(motor_id - 6); }   // 从站2 通道1-6
        else if (motor_id >= 13 && motor_id <= 15) { slave_idx = 1; passage = static_cast<int>(motor_id - 12); } // 从站1 通道1-3
    }

    void leg_cmd_callback(const dro_hg::msg::LegCmd::SharedPtr msg)
    {
        const uint8_t begin = msg->begin;
        const uint8_t end = msg->end;
        const size_t n = msg->motor_cmd.size();
        constexpr uint16_t default_cur = 40;
        constexpr uint8_t default_ack = 1;  // 返回报文类型 1（位置+速度+电流一帧）
        constexpr uint16_t pos_mode_spd = 1000;   // 100 rpm 速度限制
        constexpr uint16_t pos_mode_cur = 100;     // 5 A 电流限制
        constexpr uint8_t pos_mode_ack = 1;       // 返回报文类型 1（不修改，保持 ack=1）

        // 在临时缓冲区处理，避免长时间持锁阻塞 RT 线程
        EtherCAT_Msg tx_pending[SSC_SLAVE_NUM];
        memset(tx_pending, 0, sizeof(tx_pending));

        // 先按 [begin,end] 标记使用的通道，未在范围内的通道清空
        bool used_channels[SSC_SLAVE_NUM][6] = {false};
        for (uint8_t i = begin; i <= end && i < n; i++)
        {
            if (msg->motor_cmd[i].mode == 0) continue;
            int slave_idx = -1, passage = 0;
            motor_id_to_slave_passage(static_cast<uint16_t>(i + 1), slave_idx, passage);
            if (slave_idx >= 0 && slave_idx < SSC_SLAVE_NUM && passage >= 1 && passage <= 6)
                used_channels[slave_idx][passage - 1] = true;
        }
        for (int slave = 0; slave < SSC_SLAVE_NUM; slave++)
            for (int i = 0; i < 6; i++)
                if (!used_channels[slave][i])
                    memset(&tx_pending[slave].motor[i], 0, sizeof(Motor_Msg));

        int processed = 0;
        double now_s = this->get_clock()->now().seconds();
        bool do_kpkd_log = (now_s - last_kpkd_log_time_ >= 1.0);
        std::string kpkd_log_line;  // 汇总所有 mode4 的 motor_id/kp/kd，与 Reconfigure 的 motor_id、kp_motors、kd_motors 一致

        for (uint8_t i = begin; i <= end && i < n; i++)
        {
            const auto& cmd = msg->motor_cmd[i];
            if (cmd.mode == 0) continue;
            uint16_t motor_id = static_cast<uint16_t>(i + 1);
            int slave_idx = -1, passage = 0;
            motor_id_to_slave_passage(motor_id, slave_idx, passage);
            if (slave_idx < 0 || slave_idx >= SSC_SLAVE_NUM || passage < 1 || passage > 6) continue;

            switch (cmd.mode)
            {
            case 1:
                set_motor_position(&tx_pending[slave_idx], static_cast<uint8_t>(passage), motor_id,
                    static_cast<float>(cmd.q), pos_mode_spd, pos_mode_cur, pos_mode_ack);
                break;
            case 2:
                set_motor_speed(&tx_pending[slave_idx], static_cast<uint8_t>(passage), motor_id,
                    cmd.dq, default_cur, default_ack);
                break;
            case 4:
                send_motor_ctrl_cmd(&tx_pending[slave_idx], static_cast<uint8_t>(passage), motor_id,
                    static_cast<float>(cmd.kp), static_cast<float>(cmd.kd), static_cast<float>(cmd.q),
                    static_cast<float>(cmd.dq), static_cast<float>(cmd.tau));
                if (do_kpkd_log)
                {
                    char buf[64];
                    snprintf(buf, sizeof(buf), " [%u:kp=%.2f kd=%.2f]", motor_id,
                        static_cast<double>(cmd.kp), static_cast<double>(cmd.kd));
                    kpkd_log_line += buf;
                }
                break;
            default:
                RCLCPP_DEBUG(this->get_logger(), "leg_cmd joint %d mode %d ignored", i, cmd.mode);
                break;
            }
            processed++;
        }

        // 每 1 秒打印一次所有 mode4 电机的 kp/kd，与 motor_freq_response_test 的 motor_id、kp_motors、kd_motors 一致
        if (do_kpkd_log && !kpkd_log_line.empty())
        {
            last_kpkd_log_time_ = now_s;
            RCLCPP_INFO(this->get_logger(), "low_cmd mode4 kp/kd (motor_id 1-15):%s", kpkd_log_line.c_str());
        }

        for (int slave = 0; slave < SSC_SLAVE_NUM; slave++)
        {
            int count = 0;
            for (int i = 0; i < 6; i++) if (tx_pending[slave].motor[i].id != 0) count++;
            tx_pending[slave].motor_num = count;
        }

        // 仅持锁拷贝，最小化阻塞 RT 线程
        {
            std::lock_guard<std::mutex> lock(cmd_mutex_);
            memcpy(tx_msg, tx_pending, sizeof(EtherCAT_Msg) * SSC_SLAVE_NUM);
            last_leg_cmd_ns_.store(std::chrono::steady_clock::now().time_since_epoch().count());
        }
        // leg_cmd 日志限频：约 1 秒一次（复用前面获取的 now_s）
        if ((now_s - last_leg_cmd_log_time_) >= 1.0)
        {
            last_leg_cmd_log_time_ = now_s;
            RCLCPP_INFO(this->get_logger(), "leg_cmd: begin=%u end=%u 处理 %d 条, motor_num [%d,%d,%d]",
                begin, end, processed, tx_pending[0].motor_num, tx_pending[1].motor_num, tx_pending[2].motor_num);
        }
    }

    // 零电流模式：对 15 个电机下发电流控制 cur=0、ack_status=1，仅请求反馈、不输出力矩，用于持续更新 /leg_state
    void apply_zero_current_cmd()
    {
        std::lock_guard<std::mutex> lock(cmd_mutex_);
        constexpr uint8_t ctrl_status = 0;  // 电流控制
        constexpr int16_t cur_tor = 0;      // 零电流
        constexpr uint8_t ack_status = 1;   // 返回报文类型 1
        for (int slave = 0; slave < SSC_SLAVE_NUM; slave++)
            for (int i = 0; i < 6; i++)
                memset(&tx_msg[slave].motor[i], 0, sizeof(Motor_Msg));
        for (uint16_t motor_id = 1; motor_id <= 15; motor_id++)
        {
            int slave_idx = -1, passage = 0;
            motor_id_to_slave_passage(motor_id, slave_idx, passage);
            if (slave_idx >= 0 && slave_idx < SSC_SLAVE_NUM && passage >= 1 && passage <= 6)
                set_motor_cur_tor(&tx_msg[slave_idx], static_cast<uint8_t>(passage), motor_id, cur_tor, ctrl_status, ack_status);
        }
        for (int slave = 0; slave < SSC_SLAVE_NUM; slave++)
        {
            int count = 0;
            for (int i = 0; i < 6; i++) if (tx_msg[slave].motor[i].id != 0) count++;
            tx_msg[slave].motor_num = count;
        }
    }

    void zero_current_update_tick()
    {
        const int64_t now_ns = std::chrono::steady_clock::now().time_since_epoch().count();
        const int64_t last = last_leg_cmd_ns_.load(std::memory_order_relaxed);
        const int64_t timeout_ns = static_cast<int64_t>(zero_current_update_timeout_ms_) * 1'000'000;
        if (last == 0 || (now_ns - last) > timeout_ns)
            apply_zero_current_cmd();
    }

    void publish_leg_state()
    {
        // 至少完成一次 EtherCAT 周期后再发布，避免启动瞬间发布全零
        if (!ec_first_cycle_done_.load(std::memory_order_relaxed))
            return;

        std::lock_guard<std::mutex> lock(state_mutex_);

        // 收到数据更新链：do_ec_task() -> ethercat_data_get() -> rx_msg -> RV_can_data_repack_all() -> rv_motor_msg -> 此处发布 LegState
        // 配置：OD_Motor_Msg (motor_msg) 到 dro_hg MotorState (/leg_state) 的字段映射：
        //   motor_msg->angle_actual_rad      -> st.q            (关节位置 rad)
        //   motor_msg->speed_actual_rad      -> st.dq           (速度 rad/s，无回传时用位置差分)
        //   motor_msg->current_actual_float  -> st.current      (电流估计)
        //   motor_msg->temperature           -> st.temperature[0] (绕组温度)
        //   motor_msg->motor_id              -> st.mode (motor_control.c:514，uint16 取低 8 位)
        double now_s = this->get_clock()->now().seconds();
        double dt_s = (last_publish_time_ > 0.0) ? (now_s - last_publish_time_) : 0.0;
        const double min_dt = 1e-6;

        // 从站掉线：已进入零力矩时限频打印（约 1 秒一次）
        if (zero_torque_due_to_slave_offline_.load(std::memory_order_relaxed) && (now_s - last_slave_offline_log_time_) >= 1.0)
        {
            last_slave_offline_log_time_ = now_s;
            RCLCPP_WARN(this->get_logger(), "从站掉线(预期 %d 个，当前 %u 个响应)，已进入零力矩模式，请检查 EtherCAT 链路与从站供电。", PHYSICAL_SLAVE_NUM, last_slaves_responding_);
        }
        if (OfflineDetectionEnabled)
        {
            // 因掉线进入零力矩模式时，限频打印触发的掉线电机 ID（约 1 秒一次）
            if (zero_torque_due_to_offline_.load(std::memory_order_relaxed) && (now_s - last_offline_log_time_) >= 1.0)
            {
                last_offline_log_time_ = now_s;
                std::string ids;
                uint32_t bits = offline_trigger_motor_bits_;
                for (int i = 0; i < 15; i++)
                    if (bits & (1u << i))
                        ids += (ids.empty() ? "" : ", ") + std::to_string(i + 1);
                RCLCPP_WARN(this->get_logger(), "电机掉线(连续%d次无反馈)，已进入零力矩模式，停止接收 /leg_cmd，持续零力矩。掉线电机 ID: [%s]", OfflineThreshold, ids.empty() ? "(无)" : ids.c_str());
            }
            // 正常控制过程中监控电机在线状态：有电机无反馈时限频打印（约 1 秒一次）
            if (offline_detection_enabled_ && !zero_torque_due_to_offline_.load(std::memory_order_relaxed) && (now_s - last_online_status_log_time_) >= 1.0)
            {
                std::string ids;
                std::string counts;
                int num_missing = 0;
                for (int i = 0; i < 15; i++)
                {
                    if (motor_offline_count_[i] > 0)
                    {
                        if (num_missing) { ids += ", "; counts += ", "; }
                        ids += std::to_string(i + 1);
                        counts += std::to_string(static_cast<int>(motor_offline_count_[i]));
                        num_missing++;
                    }
                }
                if (num_missing > 0)
                {
                    last_online_status_log_time_ = now_s;
                    RCLCPP_WARN(this->get_logger(), "电机在线监控: 无反馈 电机 ID [%s] 连续次数 [%s] (满 %d 次将进入零力矩)", ids.c_str(), counts.c_str(), OfflineThreshold);
                }
            }
        }
        // 温度保护：已进入零电流模式时限频打印（约 1 秒一次），与 OfflineDetectionEnabled 无关
        if (zero_torque_due_to_temperature_.load(std::memory_order_relaxed) && (now_s - last_temperature_log_time_) >= 1.0)
        {
            last_temperature_log_time_ = now_s;
            std::string ids;
            uint32_t bits = temperature_trigger_motor_bits_;
            for (int i = 0; i < 15; i++)
                if (bits & (1u << i))
                    ids += (ids.empty() ? "" : ", ") + std::to_string(i + 1);
            RCLCPP_WARN(this->get_logger(), "电机温度超过 %d℃，已进入零电流模式，持续零力矩。超温电机 ID: [%s]", temperature_limit_deg_, ids.empty() ? "(无)" : ids.c_str());
        }

        dro_hg::msg::LegState msg;
        msg.header.stamp = this->get_clock()->now();
        msg.slave_num = static_cast<uint8_t>(SSC_SLAVE_NUM);

        // /leg_state 的 motor_state 按电机 ID 1-15 顺序填充（与 motor_id_to_slave_passage 映射一致）
        msg.motor_state.reserve(15);
        for (uint16_t motor_id = 1; motor_id <= 15; motor_id++)
        {
            int slave_idx = -1, passage = 0;
            motor_id_to_slave_passage(motor_id, slave_idx, passage);
            if (slave_idx < 0 || slave_idx >= SSC_SLAVE_NUM || passage < 1 || passage > 6)
                continue;
            const OD_Motor_Msg& m = rv_motor_msg[slave_idx][passage - 1];
            dro_hg::msg::MotorState st;
            st.mode = static_cast<uint8_t>(m.motor_id & 0xFF);   // motor_id -> mode (motor_control.c:514)
            st.q = m.angle_actual_rad;                           // angle_actual_rad -> q
            if (m.speed_actual_rad != 0.0f)
                st.dq = m.speed_actual_rad;                      // speed_actual_rad -> dq
            else if (dt_s >= min_dt)
                st.dq = static_cast<float>((m.angle_actual_rad - last_q_[slave_idx][passage - 1]) / dt_s);
            else
                st.dq = 0.0f;
            last_q_[slave_idx][passage - 1] = m.angle_actual_rad;

            // 对 dq 做一阶低通滤波：dq_f = alpha * dq_raw + (1-alpha) * dq_f_prev
            double alpha = dq_lowpass_alpha_;
            if (alpha < 0.0) alpha = 0.0;
            if (alpha > 1.0) alpha = 1.0;
            float raw_dq = st.dq;
            if (alpha < 1.0)
            {
                float& dq_prev = last_dq_filtered_[slave_idx][passage - 1];
                dq_prev = static_cast<float>(alpha * raw_dq + (1.0 - alpha) * dq_prev);
                st.dq = dq_prev;
            }
            else
            {
                // alpha == 1 表示不过滤，仍然更新历史值避免后续切回 <1 时跳变过大
                last_dq_filtered_[slave_idx][passage - 1] = raw_dq;
            }

            st.current = m.current_actual_float;                         // current_actual_float -> current
            st.temperature[0] = static_cast<int16_t>(m.temperature);     // temperature -> temperature[0]
            st.temperature[1] = 0;
            st.motorstate = static_cast<uint32_t>(m.error);
            msg.motor_state.push_back(st);
        }
        last_publish_time_ = now_s;

        leg_state_pub_->publish(msg);
    }

    void real_time_task()
    {
        // 强制设置实时调度 - 必须成功，否则退出
        struct sched_param param;
        int policy = SCHED_FIFO;
        int max_priority = sched_get_priority_max(policy);
        int min_priority = sched_get_priority_min(policy);
        
        // 设置高优先级（接近最大值）
        param.sched_priority = max_priority - 1;  // 使用高优先级，留一点余量
        
        // 尝试设置实时优先级
        int ret = pthread_setschedparam(pthread_self(), policy, &param);
        if (ret != 0)
        {
            // 如果失败，尝试中等优先级
            param.sched_priority = (max_priority + min_priority) / 2;
            ret = pthread_setschedparam(pthread_self(), policy, &param);
            
            if (ret != 0)
            {
                // 如果还是失败，尝试最低实时优先级
                param.sched_priority = min_priority + 1;
                ret = pthread_setschedparam(pthread_self(), policy, &param);
                
                if (ret != 0)
                {
                    // 必须设置实时优先级，失败则退出
                    RCLCPP_ERROR(this->get_logger(), 
                        "CRITICAL: Failed to set real-time priority (errno: %d, %s). "
                        "Real-time scheduling is REQUIRED for EtherCAT communication. "
                        "Node will exit. Solutions:\n"
                        "1. Run with root: sudo -E ros2 run ethercat_motor_node ethercat_motor_node\n"
                        "2. Set capabilities: sudo setcap cap_sys_nice+ep <executable>\n"
                        "3. Configure limits.conf: add 'username soft rtprio 99' and 'username hard rtprio 99'",
                        errno, strerror(errno));
                    
                    running_ = false;
                    return;
                }
                else
                {
                    RCLCPP_INFO(this->get_logger(), 
                        "Set SCHED_FIFO priority to %d (minimum real-time priority)", param.sched_priority);
                }
            }
            else
            {
                RCLCPP_INFO(this->get_logger(), 
                    "Set SCHED_FIFO priority to %d (medium priority)", param.sched_priority);
            }
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), 
                "Successfully set SCHED_FIFO priority to %d (high priority)", param.sched_priority);
        }

        period_info pinfo{};
        periodic_task_init(&pinfo);

        while (rclcpp::ok() && running_)
        {
            do_ec_task();
            wait_rest_of_period(&pinfo);
        }
    }

    int init_ethercat()
    {
        for (int i = 0; i < PHYSICAL_SLAVE_NUM; i++)
        {
            servo_pdo_offsets_[i].control_word = servo_pdo_offsets_[i].status_word =
                servo_pdo_offsets_[i].target_position = servo_pdo_offsets_[i].position_actual_value =
                servo_pdo_offsets_[i].mode_of_operation = INVALID_SERVO_OFFSET;
        }
        init_pdo_entries(slave_0_pdo_entries_out, slave_0_pdo_entries_in);
        init_domain_regs(domain_regs_in);

        ec_slave_config_t* sc[SSC_SLAVE_NUM];
        master = ecrt_request_master(0);
        if (!master)
        {
            return -1;
        }
        ec_master_info_t master_info;
        if (ecrt_master(master, &master_info) != 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to get master info");
            ecrt_release_master(master);
            return -1;
        }
        const unsigned int slave_count = master_info.slave_count;
        if (slave_count < static_cast<unsigned int>(PHYSICAL_SLAVE_NUM))
        {
            RCLCPP_ERROR(this->get_logger(),
                "当前扫描到 %u 个从站，预期至少 %d 个。请确认 EtherCAT 已启动且网线连接正常: sudo /etc/init.d/ethercat start",
                slave_count, PHYSICAL_SLAVE_NUM);
            ecrt_release_master(master);
            return -1;
        }
        domain = ecrt_master_create_domain(master);
        if (!domain)
        {
            return -1;
        }
        // 配置 0~2 号 SSC 网关从站（Beckhoff AX58100）
        for (int slave = 0; slave < SSC_SLAVE_NUM; slave++)
        {
            if (!((sc[slave] = ecrt_master_slave_config(master, 0, slave, Beckhoff_AX58100))))
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to get slave %d configuration", slave);
                return -1;
            }
            RCLCPP_INFO(this->get_logger(), "Configuring PDOs for SSC gateway slave %d...", slave);
            if (ecrt_slave_config_pdos(sc[slave], EC_END, slave_0_syncs))
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to configure PDOs for slave %d", slave);
                return -1;
            }
        }

        // 为 3~16 号泰科伺服添加 PDO 配置（参考 ros2_ws/igh_ethercat）
        for (int slave = 3; slave <= 16; ++slave)
        {
            ec_slave_info_t info{};
            if (ecrt_master_get_slave(master, slave, &info) != 0)
            {
                RCLCPP_WARN(this->get_logger(), "Failed to get info for slave %d, skip PDO config.", slave);
                continue;
            }

            if (!(info.vendor_id == 0x00000c48 && info.product_code == 0x00030924))
            {
                // 非泰科伺服，从站保持默认配置
                continue;
            }

            ec_slave_config_t* servo_sc =
                ecrt_master_slave_config(master, 0, slave, info.vendor_id, info.product_code);
            if (!servo_sc)
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to get slave %d configuration (servo).", slave);
                return -1;
            }

            RCLCPP_INFO(this->get_logger(), "Configuring PDOs (CSP RW template) for servo slave %d...", slave);
            if (configure_servo_pdo(servo_sc) != 0)
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to configure PDOs for servo slave %d", slave);
                return -1;
            }
        }

        // 先注册 SSC 从站 PDO 列表，再注册伺服 PDO 条目（IgH 要求先 domain list）
        if (ecrt_domain_reg_pdo_entry_list(domain, domain_regs_in))
        {
            RCLCPP_ERROR(this->get_logger(), "PDO entry registration failed!");
            return -1;
        }

        // 将伺服 PDO 条目注册到 domain（须在 domain list 之后、activate 之前）
        for (int slave = 3; slave <= 16; ++slave)
        {
            ec_slave_info_t info{};
            if (ecrt_master_get_slave(master, slave, &info) != 0) continue;
            if (info.vendor_id != 0x00000c48 || info.product_code != 0x00030924) continue;
            ec_slave_config_t* servo_sc = ecrt_master_slave_config(master, 0, slave, info.vendor_id, info.product_code);
            if (!servo_sc) continue;
            ServoPdoOffsets& o = servo_pdo_offsets_[slave];
            o.control_word = o.status_word = o.target_position = o.position_actual_value = o.mode_of_operation = INVALID_SERVO_OFFSET;
            unsigned int bp = 0;
            if (ecrt_slave_config_reg_pdo_entry(servo_sc, 0x6040, 0x00, domain, &bp) == 0) o.control_word = static_cast<size_t>(bp) / 8;
            if (ecrt_slave_config_reg_pdo_entry(servo_sc, 0x6041, 0x00, domain, &bp) == 0) o.status_word = static_cast<size_t>(bp) / 8;
            if (ecrt_slave_config_reg_pdo_entry(servo_sc, 0x6060, 0x00, domain, &bp) == 0) o.mode_of_operation = static_cast<size_t>(bp) / 8;
            if (ecrt_slave_config_reg_pdo_entry(servo_sc, 0x607A, 0x00, domain, &bp) == 0) o.target_position = static_cast<size_t>(bp) / 8;
            if (ecrt_slave_config_reg_pdo_entry(servo_sc, 0x6064, 0x00, domain, &bp) == 0) o.position_actual_value = static_cast<size_t>(bp) / 8;
        }

        RCLCPP_INFO(this->get_logger(), "Activating master...");
        if (ecrt_master_activate(master))
        {
            return -1;
        }
        if (!((domain_pd = ecrt_domain_data(domain))))
        {
            return -1;
        }

        // 启动时检测从站数量：预期 PHYSICAL_SLAVE_NUM 个在线，不符合则提示并退出
        for (int i = 0; i < 50; i++)
        {
            ecrt_master_receive(master);
            ecrt_master_send(master);
            usleep(1000);  // 1ms，给主站发现从站的时间
        }
        ecrt_master_state(master, &master_state);
        if (master_state.slaves_responding != PHYSICAL_SLAVE_NUM)
        {
            RCLCPP_ERROR(this->get_logger(),
                "从站数量不符合预期(预期 %d 个，实际 %d 个)。请检查:\n"
                "  1) EtherCAT 已启动: sudo /etc/init.d/ethercat start\n"
                "  2) 设置开机自启: sudo update-rc.d ethercat defaults\n"
                "  3) 检查网线连接和从站供电",
                PHYSICAL_SLAVE_NUM, master_state.slaves_responding);
            ecrt_release_master(master);
            return -1;
        }
        RCLCPP_INFO(this->get_logger(), "从站检测通过: %d 个从站在线", PHYSICAL_SLAVE_NUM);

        return 0;
    }

    // EtherCAT 相关函数（从原 main.cpp 移植）
    static void inc_period(period_info* pinfo)
    {
        pinfo->next_period.tv_nsec += pinfo->period_ns;
        while (pinfo->next_period.tv_nsec >= 1000000000)
        {
            pinfo->next_period.tv_sec++;
            pinfo->next_period.tv_nsec -= 1000000000;
        }
    }

    static void periodic_task_init(period_info* pinfo)
    {
        pinfo->period_ns = 1000000; // 1ms
        clock_gettime(CLOCK_MONOTONIC, &(pinfo->next_period));
    }

    static void wait_rest_of_period(period_info* pinfo)
    {
        inc_period(pinfo);
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &pinfo->next_period, nullptr);
    }

    static void ethercat_data_get(void)
    {
        for (int slave = 0; slave < SSC_SLAVE_NUM; slave++)
        {
            rx_msg[slave].can_ide = EC_READ_U8(domain_pd + pdo_struct[slave].IN_MOTOR_IDE);
            rx_msg[slave].motor_num = EC_READ_U8(domain_pd + pdo_struct[slave].IN_MOTOR_NUM);

            for (int i = 0; i < 6; i++)
            {
                rx_msg[slave].motor[i].id = EC_READ_U32(domain_pd + pdo_struct[slave].IN_MOTOR[i].ID);
                rx_msg[slave].motor[i].rtr = EC_READ_U8(domain_pd + pdo_struct[slave].IN_MOTOR[i].RTR);
                rx_msg[slave].motor[i].dlc = EC_READ_U8(domain_pd + pdo_struct[slave].IN_MOTOR[i].DLC);

                for (int j = 0; j < 8; j++)
                {
                    rx_msg[slave].motor[i].data[j] = EC_READ_U8(domain_pd + pdo_struct[slave].IN_MOTOR[i].DATA[j]);
                }
            }
        }
    }

    static void ethercat_data_set(void)
    {
        for (int slave = 0; slave < SSC_SLAVE_NUM; slave++)
        {
            EC_WRITE_U8(domain_pd + pdo_struct[slave].OUT_CAN_IDE, tx_msg[slave].can_ide);
            EC_WRITE_U8(domain_pd + pdo_struct[slave].OUT_NOTOR_NUM, tx_msg[slave].motor_num);

            for (int i = 0; i < 6; i++)
            {
                EC_WRITE_U32(domain_pd + pdo_struct[slave].OUT_MOTOR[i].ID, tx_msg[slave].motor[i].id);
                EC_WRITE_U8(domain_pd + pdo_struct[slave].OUT_MOTOR[i].RTR, tx_msg[slave].motor[i].rtr);
                EC_WRITE_U8(domain_pd + pdo_struct[slave].OUT_MOTOR[i].DLC, tx_msg[slave].motor[i].dlc);

                for (int j = 0; j < 8; j++)
                {
                    EC_WRITE_U8(domain_pd + pdo_struct[slave].OUT_MOTOR[i].DATA[j], tx_msg[slave].motor[i].data[j]);
                }
            }
        }
    }

    // 伺服故障恢复（参考 ros2_ws motion_fault_recovery）
    static void servo_fault_recovery(int slave)
    {
        if (slave < SERVO_FIRST || slave > SERVO_LAST) return;
        const ServoPdoOffsets& ofs = servo_pdo_offsets_[slave];
        if (ofs.status_word == INVALID_SERVO_OFFSET) return;

        uint16_t sw = EC_READ_U16(domain_pd + ofs.status_word);
        if (sw & 0x0008)  // 故障位
        {
            if (!servo_last_fault_state_[slave])
            {
                servo_last_fault_state_[slave] = 1;
                servo_fault_recovery_attempts_[slave] = 0;
                servo_fault_recovery_wait_[slave] = 0;
            }
            servo_fault_recovery_wait_[slave]++;
            if (servo_fault_recovery_wait_[slave] >= SERVO_FAULT_RECOVERY_INTERVAL_CYCLES)
            {
                servo_fault_recovery_attempts_[slave]++;
                servo_fault_recovery_wait_[slave] = 0;
                if (servo_fault_recovery_attempts_[slave] <= 5 && ofs.control_word != INVALID_SERVO_OFFSET)
                    EC_WRITE_U16(domain_pd + ofs.control_word, 0x0080);  // 清除故障
            }
        }
        else
        {
            servo_last_fault_state_[slave] = 0;
        }
    }

    // 伺服上电状态机（参考 ros2_ws motion_power_state_machine）
    static void servo_power_state_machine(int slave, int is_on)
    {
        if (slave < SERVO_FIRST || slave > SERVO_LAST) return;
        const ServoPdoOffsets& ofs = servo_pdo_offsets_[slave];
        if (ofs.status_word == INVALID_SERVO_OFFSET || ofs.control_word == INVALID_SERVO_OFFSET) return;

        uint16_t sw = EC_READ_U16(domain_pd + ofs.status_word);
        int32_t actual_pos = (ofs.position_actual_value != INVALID_SERVO_OFFSET) ? EC_READ_S32(domain_pd + ofs.position_actual_value) : 0;

        if (sw == 0x0000)
        {
            if (!servo_zero_status_warning_[slave])
                servo_zero_status_warning_[slave] = 1;
        }
        else
            servo_zero_status_warning_[slave] = 0;

        if (is_on)
        {
            unsigned char status_low = sw & 0x0f;
            if (status_low == 0x00)
            {
                if (servo_is_power_on_[slave] && sw == 0x0000)
                    EC_WRITE_U16(domain_pd + ofs.control_word, 0x0f);
                else
                    EC_WRITE_U16(domain_pd + ofs.control_word, 0x06);
                if (ofs.target_position != INVALID_SERVO_OFFSET)
                    EC_WRITE_S32(domain_pd + ofs.target_position, actual_pos);
            }
            else if (status_low == 0x01)
            {
                if (servo_is_power_on_[slave])
                    EC_WRITE_U16(domain_pd + ofs.control_word, 0x07);
                else
                    EC_WRITE_U16(domain_pd + ofs.control_word, 0x07);
                if (ofs.target_position != INVALID_SERVO_OFFSET)
                    EC_WRITE_S32(domain_pd + ofs.target_position, actual_pos);
            }
            else if (status_low == 0x03)
            {
                EC_WRITE_U16(domain_pd + ofs.control_word, 0x0f);
                if (ofs.target_position != INVALID_SERVO_OFFSET)
                    EC_WRITE_S32(domain_pd + ofs.target_position, actual_pos);
            }
            else if (status_low == 0x07)
            {
                EC_WRITE_U16(domain_pd + ofs.control_word, 0x0f);
                servo_is_power_on_[slave] = 1;
                if (ofs.target_position != INVALID_SERVO_OFFSET)
                {
                    EC_WRITE_S32(domain_pd + ofs.target_position, actual_pos);  // 每周期保持目标=实际
                    if (!servo_initial_target_set_[slave])
                        servo_initial_target_set_[slave] = 1;
                }
            }
            else
            {
                EC_WRITE_U16(domain_pd + ofs.control_word, 0x80);
                if (ofs.target_position != INVALID_SERVO_OFFSET)
                    EC_WRITE_S32(domain_pd + ofs.target_position, actual_pos);
            }
            if (ofs.mode_of_operation != INVALID_SERVO_OFFSET)
                EC_WRITE_U8(domain_pd + ofs.mode_of_operation, 8);  // CSP
        }
        else
        {
            EC_WRITE_U16(domain_pd + ofs.control_word, 0x00);
            servo_is_power_on_[slave] = 0;
        }
    }

    static void check_domain_state()
    {
        ec_domain_state_t ds;
        ecrt_domain_state(domain, &ds);

        if (!(ds.working_counter && ds.wc_state))
            return;

        if (ds.working_counter != domain_state.working_counter)
        {
            // RCLCPP_DEBUG can be used here if needed
        }
        if (ds.wc_state != domain_state.wc_state)
        {
            // RCLCPP_DEBUG can be used here if needed
        }

        domain_state = ds;
    }

    static void check_master_state()
    {
        ec_master_state_t ms;
        ecrt_master_state(master, &ms);

        if (ms.slaves_responding != master_state.slaves_responding)
        {
            // RCLCPP_DEBUG can be used here if needed
        }
        if (ms.al_states != master_state.al_states)
        {
            // RCLCPP_DEBUG can be used here if needed
        }
        if (ms.link_up != master_state.link_up)
        {
            // RCLCPP_DEBUG can be used here if needed
        }

        master_state = ms;
    }

    void do_ec_task()
    {
        {
            std::lock_guard<std::mutex> lock(cmd_mutex_);

            ecrt_master_receive(master);
            ecrt_domain_process(domain);

            ethercat_data_get();

            // 伺服 3~16 状态机（上电 + 故障恢复，参考 ros2_ws）
            for (int s = SERVO_FIRST; s <= SERVO_LAST; s++)
            {
                if (servo_pdo_offsets_[s].status_word == INVALID_SERVO_OFFSET)
                    continue;
                servo_fault_recovery(s);
                servo_power_state_machine(s, 1);
            }

            check_domain_state();
            check_master_state();
            
            // 从站掉线检测：预期 PHYSICAL_SLAVE_NUM 个从站，主站报告响应数不足则累计，连续超过阈值则进入零力矩
            {
                uint16_t responding = master_state.slaves_responding;
                if (responding < static_cast<uint16_t>(PHYSICAL_SLAVE_NUM))
                {
                    slave_offline_cycles_++;
                    if (slave_offline_cycles_ >= SlaveOfflineThreshold)
                    {
                        const bool first_enter = !zero_torque_due_to_slave_offline_.load(std::memory_order_relaxed);
                        if (first_enter)
                            RCLCPP_WARN(rclcpp::get_logger("ethercat_motor_node"),
                                "从站掉线：预期 %d 个从站，当前 %u 个响应，进入零力矩模式。请检查网线、从站供电与 EtherCAT 链路。", PHYSICAL_SLAVE_NUM, responding);
                        zero_torque_due_to_slave_offline_.store(true, std::memory_order_relaxed);
                    }
                }
                else
                    slave_offline_cycles_ = 0;
            }

            {
                std::lock_guard<std::mutex> state_lock(state_mutex_);

                last_slaves_responding_ = master_state.slaves_responding;

                // 仅将各槽位 motor_id 置 0，本周期未收到反馈的槽位 repack 后仍为 0；其余字段保留上一周期数据
                for (int s = 0; s < SSC_SLAVE_NUM; s++)
                    for (int i = 0; i < 6; i++)
                        rv_motor_msg[s][i].motor_id = 0;
                RV_can_data_repack_all(rx_msg, comm_ack, rv_motor_msg, SSC_SLAVE_NUM, 0);

                // 温度保护：任一电机温度超过阈值则进零电流模式（一旦进入不自动恢复）
                {
                    bool any_over_temp = false;
                    uint32_t temp_bits = 0;
                    const int limit = temperature_limit_deg_;
                    for (uint16_t mid = 1; mid <= 15; mid++)
                    {
                        int slave_idx = -1, passage = 0;
                        motor_id_to_slave_passage(mid, slave_idx, passage);
                        if (slave_idx < 0 || slave_idx >= SSC_SLAVE_NUM || passage < 1 || passage > 6)
                            continue;
                        const OD_Motor_Msg& m = rv_motor_msg[slave_idx][passage - 1];
                        if (m.motor_id != 0 && static_cast<int>(m.temperature) > limit)
                        {
                            any_over_temp = true;
                            temp_bits |= (1u << (mid - 1));
                        }
                    }
                    if (any_over_temp)
                    {
                        const bool first_enter = !zero_torque_due_to_temperature_.load(std::memory_order_relaxed);
                        if (first_enter)
                        {
                            temperature_trigger_motor_bits_ = temp_bits;
                            std::string ids;
                            for (int i = 0; i < 15; i++)
                                if (temp_bits & (1u << i))
                                    ids += (ids.empty() ? "" : ", ") + std::to_string(i + 1);
                            RCLCPP_WARN(rclcpp::get_logger("ethercat_motor_node"),
                                "电机温度超过 %d℃，进入零电流模式，超温电机 ID: [%s]", temperature_limit_deg_, ids.c_str());
                        }
                        zero_torque_due_to_temperature_.store(true, std::memory_order_relaxed);
                    }
                }

                if (OfflineDetectionEnabled)
                {
                    // 主站稳定判定：连续 StableCyclesThreshold 个周期 15 个电机均有反馈，再启用在线检测
                    bool all_15_have_feedback = true;
                    for (uint16_t mid = 1; mid <= 15; mid++)
                    {
                        int slave_idx = -1, passage = 0;
                        motor_id_to_slave_passage(mid, slave_idx, passage);
                        if (slave_idx < 0 || slave_idx >= SSC_SLAVE_NUM || passage < 1 || passage > 6)
                            continue;
                        if (rv_motor_msg[slave_idx][passage - 1].motor_id == 0)
                        {
                            all_15_have_feedback = false;
                            break;
                        }
                    }
                    if (all_15_have_feedback)
                    {
                        stable_cycles_count_++;
                        if (stable_cycles_count_ >= StableCyclesThreshold && !offline_detection_enabled_)
                        {
                            offline_detection_enabled_ = true;
                            RCLCPP_INFO(rclcpp::get_logger("ethercat_motor_node"),
                                "主站运行稳定（连续 %d 周期收到全部电机数据），已启用电机在线检测，连续 %d 次无反馈将进入零力矩", StableCyclesThreshold, OfflineThreshold);
                        }
                    }
                    else
                        stable_cycles_count_ = 0;
                    // 根据反馈判断掉线：对应槽位 motor_id==0 表示本周期无反馈
                    if (offline_detection_enabled_)
                    {
                        for (uint16_t mid = 1; mid <= 15; mid++)
                        {
                            int slave_idx = -1, passage = 0;
                            motor_id_to_slave_passage(mid, slave_idx, passage);
                            if (slave_idx < 0 || slave_idx >= SSC_SLAVE_NUM || passage < 1 || passage > 6)
                                continue;
                            if (rv_motor_msg[slave_idx][passage - 1].motor_id == 0)
                                motor_offline_count_[mid - 1]++;
                            else
                                motor_offline_count_[mid - 1] = 0;
                        }
                    }
                    // 任意电机连续 OfflineThreshold 次无反馈则进入零力矩模式；一旦进入不主动恢复
                    bool any_offline = false;
                    uint32_t trigger_bits = 0;
                    if (offline_detection_enabled_)
                    {
                        for (int i = 0; i < 15; i++)
                            if (motor_offline_count_[i] >= OfflineThreshold)
                            {
                                any_offline = true;
                                trigger_bits |= (1u << i);
                            }
                    }
                    if (any_offline)
                    {
                        const bool first_enter = !zero_torque_due_to_offline_.load(std::memory_order_relaxed);
                        if (first_enter)
                        {
                            offline_trigger_motor_bits_ = trigger_bits;
                            std::string ids;
                            for (int i = 0; i < 15; i++)
                                if (trigger_bits & (1u << i))
                                    ids += (ids.empty() ? "" : ", ") + std::to_string(i + 1);
                            RCLCPP_WARN(rclcpp::get_logger("ethercat_motor_node"),
                                "电机掉线(连续%d次无反馈)，进入零力矩模式，掉线电机 ID: [%s]", OfflineThreshold, ids.c_str());
                        }
                        zero_torque_due_to_offline_.store(true, std::memory_order_relaxed);
                    }
                }
                // 因从站掉线、电机掉线或温度保护进入零力矩后：停止下发 leg_cmd 内容，仅下发零电流
                if (zero_torque_due_to_slave_offline_.load(std::memory_order_relaxed) || zero_torque_due_to_offline_.load(std::memory_order_relaxed) || zero_torque_due_to_temperature_.load(std::memory_order_relaxed))
                {
                    constexpr uint8_t ctrl_status = 0;
                    constexpr int16_t cur_tor = 0;
                    constexpr uint8_t ack_status = 1;
                    for (int s = 0; s < SSC_SLAVE_NUM; s++)
                        for (int i = 0; i < 6; i++)
                            memset(&tx_msg[s].motor[i], 0, sizeof(Motor_Msg));
                    for (uint16_t motor_id = 1; motor_id <= 15; motor_id++)
                    {
                        int slave_idx = -1, passage = 0;
                        motor_id_to_slave_passage(motor_id, slave_idx, passage);
                        if (slave_idx >= 0 && slave_idx < SSC_SLAVE_NUM && passage >= 1 && passage <= 6)
                            set_motor_cur_tor(&tx_msg[slave_idx], static_cast<uint8_t>(passage), motor_id, cur_tor, ctrl_status, ack_status);
                    }
                    for (int s = 0; s < SSC_SLAVE_NUM; s++)
                    {
                        int count = 0;
                        for (int i = 0; i < 6; i++) if (tx_msg[s].motor[i].id != 0) count++;
                        tx_msg[s].motor_num = count;
                    }
                }
            }
            ec_first_cycle_done_.store(true, std::memory_order_relaxed);

            ethercat_data_set();
            ecrt_domain_queue(domain);
            ecrt_master_send(master);
        }
    }

    // 静态成员变量（从原 main.cpp 移植）
    static ec_pdo_entry_info_t slave_0_pdo_entries_out[68];
    static ec_pdo_entry_info_t slave_0_pdo_entries_in[68];
    static ec_pdo_entry_info_t slave_0_pdo_entries_out_pdo[9];
    static ec_pdo_info_t slave_0_pdos[3];
    static ec_sync_info_t slave_0_syncs[5];
    static EtherCAT_Msg tx_msg[SSC_SLAVE_NUM];
    static EtherCAT_Msg rx_msg[SSC_SLAVE_NUM];
    static OD_Motor_Msg rv_motor_msg[SSC_SLAVE_NUM][6];
    static PDO_Struct pdo_struct[SSC_SLAVE_NUM];
    static ec_pdo_entry_reg_t domain_regs_in[68 * 2 * SSC_SLAVE_NUM + 1];

    // 伺服 3~16 的 PDO 偏移与状态机状态（参考 ros2_ws/igh_ethercat motion.c）
    static ServoPdoOffsets servo_pdo_offsets_[PHYSICAL_SLAVE_NUM];
    static uint16_t servo_status_word_[PHYSICAL_SLAVE_NUM];
    static uint8_t servo_is_power_on_[PHYSICAL_SLAVE_NUM];
    static int servo_last_fault_state_[PHYSICAL_SLAVE_NUM];
    static int servo_fault_recovery_attempts_[PHYSICAL_SLAVE_NUM];
    static int servo_fault_recovery_wait_[PHYSICAL_SLAVE_NUM];
    static int servo_zero_status_warning_[PHYSICAL_SLAVE_NUM];
    static int servo_initial_target_set_[PHYSICAL_SLAVE_NUM];
    static constexpr int SERVO_FAULT_RECOVERY_INTERVAL_CYCLES = 1000;  // 约 1 秒（1ms 周期）

    static void init_pdo_entries(ec_pdo_entry_info_t* pdo_entries_out, ec_pdo_entry_info_t* pdo_entries_in)
    {
        for (int i = 0; i < 68; i++)
        {
            int subindex = (i + 1);
            int bit_length = (i - 2) % 11 ? 8 : 32;

            pdo_entries_out[i] = (ec_pdo_entry_info_t){0x7010, static_cast<uint8_t>(subindex), static_cast<uint8_t>(bit_length)};
            pdo_entries_in[i] = (ec_pdo_entry_info_t){0x6000, static_cast<uint8_t>(subindex), static_cast<uint8_t>(bit_length)};
        }
    }

    static void init_domain_regs(ec_pdo_entry_reg_t* domain_regs)
    {
        int i = 0;

        for (uint16_t slave = 0; slave < SSC_SLAVE_NUM; slave++)
        {
            domain_regs[i++] = (ec_pdo_entry_reg_t){
                0, slave, Beckhoff_AX58100, 0x7010, 1, &pdo_struct[slave].OUT_NOTOR_NUM
            };
            domain_regs[i++] = (ec_pdo_entry_reg_t){
                0, slave, Beckhoff_AX58100, 0x7010, 2, &pdo_struct[slave].OUT_CAN_IDE
            };

            for (int motor = 0; motor < 6; motor++)
            {
                domain_regs[i++] = (ec_pdo_entry_reg_t){
                    0, slave, Beckhoff_AX58100, 0x7010, static_cast<uint8_t>(3 + motor * 11), &pdo_struct[slave].OUT_MOTOR[motor].ID
                };
                domain_regs[i++] = (ec_pdo_entry_reg_t){
                    0, slave, Beckhoff_AX58100, 0x7010, static_cast<uint8_t>(4 + motor * 11), &pdo_struct[slave].OUT_MOTOR[motor].RTR
                };
                domain_regs[i++] = (ec_pdo_entry_reg_t){
                    0, slave, Beckhoff_AX58100, 0x7010, static_cast<uint8_t>(5 + motor * 11), &pdo_struct[slave].OUT_MOTOR[motor].DLC
                };
                for (int data_idx = 0; data_idx < 8; data_idx++)
                {
                    domain_regs[i++] = (ec_pdo_entry_reg_t){
                        0, slave, Beckhoff_AX58100, 0x7010, static_cast<uint8_t>(6 + data_idx + motor * 11),
                        &pdo_struct[slave].OUT_MOTOR[motor].DATA[data_idx]
                    };
                }
            }
        }
        for (uint16_t slave = 0; slave < SSC_SLAVE_NUM; slave++)
        {
            domain_regs[i++] = (ec_pdo_entry_reg_t){0, slave, Beckhoff_AX58100, 0x6000, 1, &pdo_struct[slave].IN_MOTOR_NUM};
            domain_regs[i++] = (ec_pdo_entry_reg_t){0, slave, Beckhoff_AX58100, 0x6000, 2, &pdo_struct[slave].IN_MOTOR_IDE};

            for (int motor = 0; motor < 6; motor++)
            {
                domain_regs[i++] = (ec_pdo_entry_reg_t){
                    0, slave, Beckhoff_AX58100, 0x6000, static_cast<uint8_t>(3 + motor * 11), &pdo_struct[slave].IN_MOTOR[motor].ID
                };
                domain_regs[i++] = (ec_pdo_entry_reg_t){
                    0, slave, Beckhoff_AX58100, 0x6000, static_cast<uint8_t>(4 + motor * 11), &pdo_struct[slave].IN_MOTOR[motor].RTR
                };
                domain_regs[i++] = (ec_pdo_entry_reg_t){
                    0, slave, Beckhoff_AX58100, 0x6000, static_cast<uint8_t>(5 + motor * 11), &pdo_struct[slave].IN_MOTOR[motor].DLC
                };
                for (int data_idx = 0; data_idx < 8; data_idx++)
                {
                    domain_regs[i++] = (ec_pdo_entry_reg_t){
                        0, slave, Beckhoff_AX58100, 0x6000, static_cast<uint8_t>(6 + data_idx + motor * 11),
                        &pdo_struct[slave].IN_MOTOR[motor].DATA[data_idx]
                    };
                }
            }
        }

        domain_regs[i] = (ec_pdo_entry_reg_t){0xff};
    }

    rclcpp::Publisher<dro_hg::msg::LegState>::SharedPtr leg_state_pub_;
    rclcpp::Subscription<dro_hg::msg::LegCmd>::SharedPtr leg_cmd_sub_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr zero_current_update_timer_;
    rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr param_callback_handle_;

    int slave_num_;
    int cycle_time_ms_;
    bool publish_states_;
    int zero_current_update_timeout_ms_;
    double dq_lowpass_alpha_{1.0};  // dq 速度低通滤波系数 [0,1]，1 表示不过滤
    std::atomic<int64_t> last_leg_cmd_ns_{0};
    bool running_;
    std::atomic<bool> ec_first_cycle_done_{false};  // 至少一次 EC 周期后再发布状态
    // 从站掉线检测：预期 PHYSICAL_SLAVE_NUM 个从站，主站 slaves_responding 持续低于则进入零力矩
    static constexpr int SlaveOfflineThreshold = 10;  // 连续 N 个周期 slaves_responding < PHYSICAL_SLAVE_NUM 则判为从站掉线
    int slave_offline_cycles_{0};                     // 当前连续“从站响应数不足”的周期数
    std::atomic<bool> zero_torque_due_to_slave_offline_{false};  // 因从站掉线进入零力矩模式
    uint16_t last_slaves_responding_{0};             // 最近一次主站报告的从站响应数（在 state_mutex_ 下更新，供发布线程安全读取）
    double last_slave_offline_log_time_{0};          // 从站掉线报警限频

    // 电机掉线检测：主站运行稳定（连续收到所有电机数据）后启用（设为 false 可屏蔽整个机制）
    static constexpr bool OfflineDetectionEnabled = true;   // 设为 false 可屏蔽掉线检测
    static constexpr int StableCyclesThreshold = 50;  // 连续 N 个周期 15 个电机均有反馈，认为主站稳定
    static constexpr int OfflineThreshold = 100;       // 连续 N 个周期无反馈则判为掉线，进入零力矩
    int stable_cycles_count_{0};  // 当前连续“15 个电机均有反馈”的周期数
    bool offline_detection_enabled_{false};           // 主站稳定后为 true，才进行掉线判断
    uint8_t motor_offline_count_[15]{};              // 电机 1-15 连续无反馈的周期数（index 0 = 电机 1）
    std::atomic<bool> zero_torque_due_to_offline_{false};  // 因掉线进入零力矩模式
    uint32_t offline_trigger_motor_bits_{0};  // 进入零力矩时触发的掉线电机 ID 位图（bit i = 电机 i+1），用于持续报警时打印
    double last_offline_log_time_{0};  // 上次打印掉线信息的时间（限频）
    // 温度保护：任一电机温度超过阈值则进零电流模式（不自动恢复）
    int temperature_limit_deg_{80};
    std::atomic<bool> zero_torque_due_to_temperature_{false};
    uint32_t temperature_trigger_motor_bits_{0};  // 触发的超温电机 ID 位图，用于报警打印
    double last_temperature_log_time_{0};
    double last_online_status_log_time_{0};  // 正常控制时电机在线状态打印限频
    double last_leg_cmd_log_time_{0};  // leg_cmd 日志限频（约 1s 一次）
    double last_kpkd_log_time_{0};     // kp / kd 日志限频（约 1s 一次）
    // 用于 dq 差分：驱动器未回传速度时用 (q - q_prev)/dt 保证 dq 必须更新
    float last_q_[SSC_SLAVE_NUM][6]{};
    // dq 低通滤波历史值：按从站/通道存储
    float last_dq_filtered_[SSC_SLAVE_NUM][6]{};
    double last_publish_time_{0.0};
    std::thread rt_thread_;
    static std::mutex cmd_mutex_;
    static std::mutex state_mutex_;
};

// 静态成员定义
ec_pdo_entry_info_t EthercatMotorNode::slave_0_pdo_entries_out[68];
ec_pdo_entry_info_t EthercatMotorNode::slave_0_pdo_entries_in[68];
ec_pdo_entry_info_t EthercatMotorNode::slave_0_pdo_entries_out_pdo[9] = {
    {0x6020, 0x01,  1},
    {0x6020, 0x02,  1},
    {0x6020, 0x03,  2},
    {0x6020, 0x05,  2},
    {0x0000, 0x00,  8},
    {0x1802, 0x07,  1},
    {0x1802, 0x09,  1},
    {0x6020, 0x0b, 16},
    {0x6020, 0x0c, 16},
};
ec_pdo_info_t EthercatMotorNode::slave_0_pdos[3] = {
    {0x1601, 68, slave_0_pdo_entries_out},
    {0x1a00, 68, slave_0_pdo_entries_in},
    {0x1a02, 9, slave_0_pdo_entries_out_pdo},
};
ec_sync_info_t EthercatMotorNode::slave_0_syncs[5] = {
    {0, EC_DIR_OUTPUT, 0, nullptr, EC_WD_DISABLE},
    {1, EC_DIR_INPUT , 0, nullptr, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, slave_0_pdos, EC_WD_ENABLE},
    {3, EC_DIR_INPUT , 2, slave_0_pdos + 1, EC_WD_DISABLE},
    {0xff}
};
EtherCAT_Msg EthercatMotorNode::tx_msg[SSC_SLAVE_NUM];
EtherCAT_Msg EthercatMotorNode::rx_msg[SSC_SLAVE_NUM];
OD_Motor_Msg EthercatMotorNode::rv_motor_msg[SSC_SLAVE_NUM][6];
PDO_Struct EthercatMotorNode::pdo_struct[SSC_SLAVE_NUM];
ec_pdo_entry_reg_t EthercatMotorNode::domain_regs_in[68 * 2 * SSC_SLAVE_NUM + 1];
ServoPdoOffsets EthercatMotorNode::servo_pdo_offsets_[PHYSICAL_SLAVE_NUM];
uint16_t EthercatMotorNode::servo_status_word_[PHYSICAL_SLAVE_NUM] = {0};
uint8_t EthercatMotorNode::servo_is_power_on_[PHYSICAL_SLAVE_NUM] = {0};
int EthercatMotorNode::servo_last_fault_state_[PHYSICAL_SLAVE_NUM] = {0};
int EthercatMotorNode::servo_fault_recovery_attempts_[PHYSICAL_SLAVE_NUM] = {0};
int EthercatMotorNode::servo_fault_recovery_wait_[PHYSICAL_SLAVE_NUM] = {0};
int EthercatMotorNode::servo_zero_status_warning_[PHYSICAL_SLAVE_NUM] = {0};
int EthercatMotorNode::servo_initial_target_set_[PHYSICAL_SLAVE_NUM] = {0};
std::mutex EthercatMotorNode::cmd_mutex_;
std::mutex EthercatMotorNode::state_mutex_;

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    
    auto node = std::make_shared<EthercatMotorNode>();
    
    // 使用多线程executor确保回调能被及时处理
    rclcpp::executors::MultiThreadedExecutor executor(rclcpp::ExecutorOptions(), 2);
    executor.add_node(node);
    
    // 在单独的线程中spin，避免阻塞实时任务
    std::thread spin_thread([&executor]() {
        executor.spin();
    });
    
    spin_thread.join();
    
    rclcpp::shutdown();
    return 0;
}
