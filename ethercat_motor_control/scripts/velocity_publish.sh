#!/bin/bash

# 速度模式：1-15 号电机，目标 30 转/分钟 (rpm)
# mode: 2 速度控制，dq 单位与 set_motor_speed 一致为 rpm

# 获取脚本所在目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Source ROS2环境（如果未设置）
if [ -z "$ROS_DISTRO" ]; then
    if [ -f "/opt/ros/humble/setup.bash" ]; then
        source /opt/ros/humble/setup.bash
    fi
fi

# Source ROS2工作空间
USER_HOME="${HOME}"
if [ -n "$SUDO_USER" ]; then
    USER_HOME=$(getent passwd "$SUDO_USER" 2>/dev/null | cut -d: -f6)
fi
if [ "$(id -u)" = 0 ] && [ ! -f "$USER_HOME/ros2_ws/install/setup.bash" ]; then
    PARENT=$(dirname "$SCRIPT_DIR")
    if [ -f "$PARENT/ros2_ws/install/setup.bash" ]; then
        USER_HOME="$PARENT"
    fi
fi
ROS2_WS_SETUP="$USER_HOME/ros2_ws/install/setup.bash"
if [ -f "$ROS2_WS_SETUP" ]; then
    source "$ROS2_WS_SETUP"
elif [ -f "$HOME/ros2_ws/install/setup.bash" ]; then
    source "$HOME/ros2_ws/install/setup.bash"
elif [ -f "$SCRIPT_DIR/dro_hg/install/setup.bash" ]; then
    source "$SCRIPT_DIR/dro_hg/install/setup.bash"
else
    echo "错误: 找不到ROS2工作空间setup文件（已尝试: $ROS2_WS_SETUP 等）"
    exit 1
fi

# 速度模式：dq=30 rpm，1-15 号电机。持续发布（20 Hz），否则约 100ms 后零电流更新会覆盖指令导致电机停
# 按 Ctrl+C 停止发布并停止电机（随后节点会下发零电流）
ros2 topic pub /leg_cmd dro_hg/msg/LegCmd "
{
  header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'base_link'},
  begin: 0,
  end: 14,
  motor_cmd: [
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
  ],
}
" -r 50

ros2 topic pub /leg_cmd dro_hg/msg/LegCmd "
{
  header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'base_link'},
  begin: 0,
  end: 14,
  motor_cmd: [
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
    {mode: 2, q: 0.0, dq: 30.0, tau: 0.0, kp: 0.0, kd: 0.0},
  ],
}
" -r 50

ros2 topic pub /leg_cmd dro_hg/msg/LegCmd "
{
  header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'base_link'},
  begin: 0,
  end: 1,
  motor_cmd: [
    {mode: 4, q: 0.2, dq: 0.0, tau: 0.0, kp: 40.0, kd: 30.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 0.0, kd: 0.0},
  ],
}
" -r 50

ros2 topic pub /leg_cmd dro_hg/msg/LegCmd "
{
  header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'base_link'},
  begin: 0,
  end: 14,
  motor_cmd: [
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
  ],
}
" -r 50

ros2 topic pub /leg_cmd dro_hg/msg/LegCmd "
{
  header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'base_link'},
  begin: 0,
  end: 3,
  motor_cmd: [
    {mode: 1, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 1, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 1, q: 0.0, dq: 0.0, tau: 0.0, kp: 100.0, kd: 5.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 200.0, kd: 5.0},
  ],
}
" -r 50


