# EtherCAT Motor Control

基于 ROS2 的 EtherCAT 电机控制：订阅 `/low_cmd`、发布 `/low_state`（dro_hg 消息）。节点在独立包 `ethercat_motor_node` 中。

## 编译

在包根目录下（即本 README 所在目录）执行。`--paths` 必须包含各包所在目录，否则 `--packages-up-to` 会报 “Package not found”：

```bash
colcon build --paths . src/dro_hg src/ethercat_motor_node --packages-up-to ethercat_motor_node --symlink-install
source install/setup.bash
```

或显式指定包名（可加 `--symlink-install`）：

```bash
colcon build --paths . src/dro_hg src/ethercat_motor_node --symlink-install
source install/setup.bash
```


只编节点包（需已安装并 source 过 dro_hg）：

```bash
colcon build --packages-select ethercat_motor_node
source install/setup.bash
```

**若使用 `--symlink-install` 时报 “existing path cannot be removed: Is a directory”**：先清理再编，例如  
`rm -rf build/dro_hg build/ethercat_motor_node install/dro_hg install/ethercat_motor_node`，然后重新执行上述 `colcon build`。  
**若 WARNING 提示 `install/ethercat_motor_control` 不存在**：该包已移除，可新开终端或先 `unset AMENT_PREFIX_PATH CMAKE_PREFIX_PATH` 再 `source install/setup.bash`。

## 启动

节点需在 root 下运行（EtherCAT 与实时调度）。`sudo -E ros2 run ...` 常因 root 下找不到 `ros2` 而失败，建议先切到 root 再 source 后运行：

```bash
sudo su
source install/setup.bash
ros2 run ethercat_motor_node ethercat_motor_node
```

**使用 launch（同样需在 root 下先 source 再执行）：**

```bash
sudo su
source install/setup.bash
ros2 launch ethercat_motor_node ethercat_motor.launch.py
```

带参数示例：

```bash
ros2 launch ethercat_motor_node ethercat_motor.launch.py slave_num:=3 cycle_time_ms:=1 publish_motor_states:=true
```
