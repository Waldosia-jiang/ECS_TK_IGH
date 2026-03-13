# ethercat_motor_node

与 `motor_freq_response_test` 同级的**独立 ROS2 包**，将 EtherCAT 电机控制节点、`math_ops`、`motor_control` 及头文件合并在一起，可单独构建与运行。

## 功能

- 订阅 **/low_cmd**（`dro_hg/msg/LowCmd`），下发电机控制（位置/速度/力位混合等）
- 发布 **/low_state**（`dro_hg/msg/LowState`），反馈电机状态
- 实时 EtherCAT 通信（1 ms 周期）、零电流状态更新、电机掉线检测与零力矩保护
- 依赖 **dro_hg** 消息包，与 `motor_freq_response_test` 共用同一消息定义

## 与仓库根目录文件的对应关系

仓库根目录（`EC_ethercat_igh_c++/`）下的 `config.h`、`main.h`、`math_ops.h`、`math_ops.c`、`motor_control.h`、`motor_control.c`、`main.cpp`、`CMakeLists.txt` 与本包对应关系如下：

| 根目录文件 | 本包中是否包含 | 说明 |
|------------|----------------|------|
| **config.h** | ✅ 有 | `include/ethercat_motor_node/config.h`，内容一致（EtherCAT_Msg、Motor_Msg）。 |
| **main.h** | ✅ 有 | `include/ethercat_motor_node/main.h`，内容一致（仅 include 改为 `ethercat_motor_node/config.h`、`motor_control.h`）。 |
| **math_ops.h / math_ops.c** | ✅ 有 | 功能一致；根目录版在 C++ 下不声明 fmaxf/fminf 以免与 std 冲突，本包版未做该区分，一般无影响。 |
| **motor_control.h / motor_control.c** | ✅ 有 | API 与实现一致，仅头文件 include 路径改为本包命名空间。 |
| **main.cpp** | ⚠️ 部分 | 根目录 `main.cpp` 是**无 ROS 的独立程序**（CMake 生成 `master_stack_test`），本包对应的是 **ethercat_motor_node.cpp**（ROS2 节点）。<br>• **已包含**：EtherCAT 初始化、PDO 配置（init_pdo_entries、init_domain_regs）、ethercat_data_get/set、do_ec_task、周期实时任务（1 ms）、RV_can_data_repack_all、check_domain_state、check_master_state、电机控制 API 调用等。<br>• **未包含**：根目录独有的**文件日志**——`log_motor_data()`、`g_data_file`（motor_data_q_tau.csv）、`g_motor_current_file`（motor_current_log.csv）及 do_ec_task 内对 motor 4 的电流估算写文件。若需“无 ROS 的纯 EtherCAT 测试 + 写 CSV”，需单独编译运行根目录的 `master_stack_test`。 |
| **CMakeLists.txt** | ✅ 对应 | 根目录用于构建 `master_stack_test`；本包 CMakeLists 构建 ROS2 节点与静态库 `ethercat_motor_lib`（math_ops + motor_control），并安装 launch。 |

结论：除根目录 `main.cpp` 里的**文件日志**（写 CSV）外，上述头文件与 C 库的功能在本包中均已包含；本包在此基础上增加了 ROS2 接口（/low_cmd、/low_state）、零电流更新与掉线保护等。

## 依赖

- ROS2 (Humble/Iron/Jazzy)
- IgH EtherCAT Master
- CMake 3.10+、C++17
- **dro_hg**（需先在同一工作空间中构建）

## 目录结构（类 motor_freq_response_test）

```
ethercat_motor_node/
├── CMakeLists.txt
├── package.xml
├── README.md
├── resource/
│   └── ethercat_motor_node
├── include/
│   └── ethercat_motor_node/
│       ├── config.h
│       ├── main.h
│       ├── math_ops.h
│       └── motor_control.h
├── src/
│   ├── ethercat_motor_node.cpp
│   ├── math_ops.c
│   └── motor_control.c
└── launch/
    └── ethercat_motor.launch.py
```

## 构建

在包含 `dro_hg` 与本包的工作空间中（例如与 `motor_freq_response_test` 相同方式）：

```bash
cd /path/to/ethercat_motor_control
colcon build --paths . src/dro_hg src/ethercat_motor_node
source install/setup.bash
```

或只编本包（需已安装并 source 过 dro_hg）：

```bash
colcon build --packages-select ethercat_motor_node
source install/setup.bash
```

## 参数

| 参数 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| slave_num | int | 3 | EtherCAT 从站数量 |
| cycle_time_ms | int | 1 | 控制周期 (ms) |
| publish_motor_states | bool | true | 是否发布 /low_state |
| zero_current_update_timeout_ms | int | 100 | 未收到 low_cmd 时零电流状态更新超时 (ms) |
| dq_lowpass_alpha | double | 0.7 | dq 低通滤波系数 [0,1]，1 表示不过滤 |

## 话题

- **订阅**：`/low_cmd`（`dro_hg/msg/LowCmd`）
- **发布**：`/low_state`（`dro_hg/msg/LowState`）

## 故障排除

- **root 与普通用户间无法订阅**：可执行 `source /etc/profile.d/ros2-fastdds-no-shm.sh` 或设置 `FASTDDS_BUILTIN_TRANSPORTS=UDPv4`，与主包 README 中说明一致。
- **实时优先级失败**：需使用 `sudo -E ros2 run ethercat_motor_node ethercat_motor_node` 或配置 `limits.conf` / `setcap`。
- **从站数量不符**：确认 EtherCAT 已启动、网线与从站供电正常。

## 许可证

MIT License
