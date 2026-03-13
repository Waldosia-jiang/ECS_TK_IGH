#!/bin/bash
# 向 /low_cmd 发布一条 dro_hg/LowCmd（示例：0-14 号关节速度模式 dq=2.0 rad/s）
# mode: 0=无控制 1=位置 2=速度 4=力矩

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PKG_DIR="$(dirname "$SCRIPT_DIR")"

if [ -z "$ROS_DISTRO" ]; then
    [ -f /opt/ros/humble/setup.bash ] && source /opt/ros/humble/setup.bash
fi
if [ -f "$PKG_DIR/install/setup.bash" ]; then
    source "$PKG_DIR/install/setup.bash"
else
    echo "错误: 未找到 $PKG_DIR/install/setup.bash，请先 colcon build（含 dro_hg）"
    exit 1
fi

ros2 topic pub /low_cmd dro_hg/msg/LowCmd "
{
  header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'base_link'},
  begin: 0,
  end: 14,
  motor_cmd: [
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
    {mode: 2, q: 0.0, dq: 2.0, tau: 0.0, kp: 100.0, kd: 10.0, reserve: 1},
  ],
  reserve: [0, 0, 0, 0],
  crc: 0
}
" --once
