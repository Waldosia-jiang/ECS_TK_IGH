#include <stdio.h>
#include "ecrt.h"
#include "ethercat_motor_node/servo_pdo_set.h"

// 清除并重新分配 RW 模板 PDO（0x1607/0x1A07）
static void pdo_set_clear_pdo_assign(ec_slave_config_t *slave,
                                     int slave_index,
                                     uint16_t rx_pdo,
                                     uint16_t tx_pdo)
{
    printf("清除从站 %d 的默认PDO分配（RW模板）...\n", slave_index);
    ecrt_slave_config_pdo_assign_clear(slave, 2);
    ecrt_slave_config_pdo_assign_clear(slave, 3);

    if (ecrt_slave_config_pdo_assign_add(slave, 2, rx_pdo) != 0) {
        printf("从站 %d: 分配SM2 RxPDO失败 (0x%04X)，可能导致PDO配置错误\n", slave_index, rx_pdo);
    }
    if (ecrt_slave_config_pdo_assign_add(slave, 3, tx_pdo) != 0) {
        printf("从站 %d: 分配SM3 TxPDO失败 (0x%04X)，可能导致PDO配置错误\n", slave_index, tx_pdo);
    }
}

// 添加 PDO 映射条目
static int pdo_set_add_pdo_mapping(ec_slave_config_t *slave,
                                   uint16_t pdo_index,
                                   uint16_t index,
                                   uint8_t subindex,
                                   uint8_t bit_length,
                                   const char *entry_name)
{
    if (ecrt_slave_config_pdo_mapping_add(slave, pdo_index, index, subindex, bit_length) == 0) {
        printf("将%s(0x%04X)添加到PDO 0x%04X\n", entry_name, index, pdo_index);
        return 0;
    } else {
        printf("向PDO 0x%04X添加%s失败\n", pdo_index, entry_name);
        return -1;
    }
}

// RW 模板 CST 模式配置（与 ros2_ws 中 CST 分支保持一致）
static int pdo_set_configure_rw_template_cst(ec_slave_config_t *slave,
                                             ec_domain_t *domain,
                                             int slave_index,
                                             struct pdo_offset *offset,
                                             uint16_t rx_pdo,
                                             uint16_t tx_pdo)
{
    printf("从站 %d: RW模板配置CST模式PDO映射 (RX=0x%04X, TX=0x%04X)\n", slave_index, rx_pdo, tx_pdo);

    // 通过 SDO 先将从站设置到 CST 模式（4）
    ecrt_slave_config_sdo8(slave, 0x6060, 0x00, 4);

    // RxPDO: 6040 + 6060 + 607A + 6071
    pdo_set_add_pdo_mapping(slave, rx_pdo, 0x6040, 0x00, 16, "控制字");
    pdo_set_add_pdo_mapping(slave, rx_pdo, 0x6060, 0x00, 8,  "运行模式");
    pdo_set_add_pdo_mapping(slave, rx_pdo, 0x607a, 0x00, 32, "目标位置");
    pdo_set_add_pdo_mapping(slave, rx_pdo, 0x6071, 0x00, 16, "目标转矩");

    // TxPDO: 6041 + 6061 + 6064 + 6077
    pdo_set_add_pdo_mapping(slave, tx_pdo, 0x6041, 0x00, 16, "状态字");
    pdo_set_add_pdo_mapping(slave, tx_pdo, 0x6061, 0x00, 8,  "运行模式显示");
    pdo_set_add_pdo_mapping(slave, tx_pdo, 0x6064, 0x00, 32, "实际位置值");
    pdo_set_add_pdo_mapping(slave, tx_pdo, 0x6077, 0x00, 16, "实际转矩值");

    // 注册 PDO 条目到域
    offset[slave_index].control_word =
        ecrt_slave_config_reg_pdo_entry(slave, 0x6040, 0x00, domain, NULL);
    offset[slave_index].mode_of_operation =
        ecrt_slave_config_reg_pdo_entry(slave, 0x6060, 0x00, domain, NULL);
    offset[slave_index].target_position =
        ecrt_slave_config_reg_pdo_entry(slave, 0x607a, 0x00, domain, NULL);
    offset[slave_index].target_torque =
        ecrt_slave_config_reg_pdo_entry(slave, 0x6071, 0x00, domain, NULL);

    offset[slave_index].target_velocity = (unsigned int)-1;

    offset[slave_index].status_word =
        ecrt_slave_config_reg_pdo_entry(slave, 0x6041, 0x00, domain, NULL);
    offset[slave_index].mode_of_operation_display =
        ecrt_slave_config_reg_pdo_entry(slave, 0x6061, 0x00, domain, NULL);
    offset[slave_index].position_actual_value =
        ecrt_slave_config_reg_pdo_entry(slave, 0x6064, 0x00, domain, NULL);
    offset[slave_index].torque_actual_value =
        ecrt_slave_config_reg_pdo_entry(slave, 0x6077, 0x00, domain, NULL);

    // CST 模式其它未用字段置为无效
    offset[slave_index].velocity_feedforward = (unsigned int)-1;
    offset[slave_index].torque_offset        = (unsigned int)-1;
    offset[slave_index].digital_outputs      = (unsigned int)-1;
    offset[slave_index].velocity_actual_value= (unsigned int)-1;
    offset[slave_index].velocity_demand_value= (unsigned int)-1;
    offset[slave_index].torque_demand_value  = (unsigned int)-1;
    offset[slave_index].digital_inputs       = (unsigned int)-1;

    if ((int)offset[slave_index].control_word < 0 ||
        (int)offset[slave_index].target_torque < 0 ||
        (int)offset[slave_index].status_word < 0) {
        printf("从站 %d: RW模板CST模式PDO条目注册失败（offset为负）\n", slave_index);
        return -1;
    }

    printf("为伺服从站 %d 配置的PDO映射(CST模式):\n", slave_index);
    printf("  控制字偏移量: %d\n", offset[slave_index].control_word);
    printf("  运行模式偏移量: %d\n", offset[slave_index].mode_of_operation);
    printf("  目标位置(0x607A)偏移量: %d\n", offset[slave_index].target_position);
    printf("  目标转矩(0x6071)偏移量: %d\n", offset[slave_index].target_torque);
    printf("  状态字偏移量: %d\n", offset[slave_index].status_word);
    printf("  运行模式显示偏移量: %d\n", offset[slave_index].mode_of_operation_display);
    if ((int)offset[slave_index].position_actual_value >= 0) {
        printf("  实际位置偏移量: %d\n", offset[slave_index].position_actual_value);
    }
    if ((int)offset[slave_index].torque_actual_value >= 0) {
        printf("  实际转矩偏移量: %d\n", offset[slave_index].torque_actual_value);
    }

    return 0;
}

// 对外接口：配置从站 PDO（RW 模板 0x1607/0x1A07），当前实现总是走 CST 路径
int pdo_set_configure_slave_pdo(int slave_index,
                                ec_slave_config_t *slave,
                                ec_domain_t *domain,
                                struct pdo_offset *offset,
                                int pdo_choice,
                                int target_velocity_cnt,
                                int target_torque)
{
    (void)target_velocity_cnt; // 当前实现未使用

    uint16_t rx_pdo = (uint16_t)(0x1600 + pdo_choice);
    uint16_t tx_pdo = (uint16_t)(0x1a00 + pdo_choice);

    // 清除并重新分配 RW 模板 PDO
    pdo_set_clear_pdo_assign(slave, slave_index, rx_pdo, tx_pdo);
    printf("为从站 %d 使用PDO: RX=0x%04X, TX=0x%04X (CST)\n",
           slave_index, rx_pdo, tx_pdo);

    // 清除默认映射
    ecrt_slave_config_pdo_mapping_clear(slave, rx_pdo);
    ecrt_slave_config_pdo_mapping_clear(slave, tx_pdo);

    // 始终配置 CST 模式（如果调用者传入 target_torque==0，则这里强制设置为一个非零值）
    if (target_torque == 0) {
        target_torque = 1;
    }
    (void)target_torque;

    return pdo_set_configure_rw_template_cst(slave, domain, slave_index, offset, rx_pdo, tx_pdo);
}

