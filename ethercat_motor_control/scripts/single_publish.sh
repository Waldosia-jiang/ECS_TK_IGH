
# 位置模式：1-15 号电机走到 90 度 (π/2 ≈ 1.5708 rad)
ros2 topic pub /low_cmd dro_hg/msg/LowCmd "
{
  header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'base_link'},
  begin: 0,
  end: 14,
  motor_cmd: [
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 1, q: 90.0, dq: 0.0, tau: 0.0, kp: 500.0, kd: 10.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
    {mode: 4, q: 0.0, dq: 0.0, tau: 0.0, kp: 300.0, kd: 40.0, reserve: 1},
  ],
  reserve: [0, 0, 0, 0],
  crc: 0
}
" -r 200



