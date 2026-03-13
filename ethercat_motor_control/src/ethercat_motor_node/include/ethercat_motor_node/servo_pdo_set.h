#pragma once

#include "ecrt.h"

// 与 ros2_ws/igh_ethercat 中 struct pdo_offset 保持一致
struct pdo_offset {
    unsigned int control_word;
    unsigned int mode_of_operation;
    unsigned int target_position;
    unsigned int target_velocity;
    unsigned int target_torque;
    unsigned int velocity_feedforward;
    unsigned int torque_offset;
    unsigned int digital_outputs;

    unsigned int status_word;
    unsigned int mode_of_operation_display;
    unsigned int position_actual_value;
    unsigned int velocity_actual_value;
    unsigned int velocity_demand_value;
    unsigned int torque_actual_value;
    unsigned int torque_demand_value;
    unsigned int digital_inputs;
};

#ifdef __cplusplus
extern "C" {
#endif

// RW 模板 0x1607/0x1A07 PDO 配置与偏移注册（最小实现：总是走 CST 分支）
int pdo_set_configure_slave_pdo(int slave_index,
                                ec_slave_config_t *slave,
                                ec_domain_t *domain,
                                struct pdo_offset *offset,
                                int pdo_choice,
                                int target_velocity_cnt,
                                int target_torque);

#ifdef __cplusplus
}
#endif

