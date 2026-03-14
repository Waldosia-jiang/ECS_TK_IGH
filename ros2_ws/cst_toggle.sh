#!/usr/bin/env bash

# 循环次数，设为 1000 基本等于无限，可按需调整
LOOP=1000

while true; do
  echo "==== cycle $((i+1)): q=0 ===="
  timeout 4s ros2 topic pub /arm_cmd dro_hg/msg/ArmCmd "
{
  header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'base_link'},
  begin: 0,
  end: 13,
  motor_cmd: [
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0}
  ]
}" -r 50

  # q 为弧度，节点按 (q+12.5)*65535/25-32768 转为编码器；下列弧度与不修改前编码器 -5070,30841,-33997,31709,30193,-132,984,7662,-33611,30869,-34209,-32316,71,381 一一对应
  echo "==== cycle $((i+1)): q=target rad (equiv to original encoder) ===="
  timeout 4s ros2 topic pub /arm_cmd dro_hg/msg/ArmCmd "
{
  header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'base_link'},
  begin: 0,
  end: 13,
  motor_cmd: [
    {mode: 4, q: -1.9348, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 11.767, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: -12.9688, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 12.1047, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 11.5245, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: -0.0473, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.3775, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 2.9268, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: -12.8216, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 11.7773, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: -12.5497, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: -12.3276, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.0304, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0},
    {mode: 4, q: 0.1462, dq: 0.0, tau: 0.0, kp: 10.0, kd: 2.0}
  ]
}" -r 50
done

