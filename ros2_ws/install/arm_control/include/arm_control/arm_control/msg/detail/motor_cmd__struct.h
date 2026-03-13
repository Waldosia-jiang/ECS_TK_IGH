// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from arm_control:msg/MotorCmd.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__MOTOR_CMD__STRUCT_H_
#define ARM_CONTROL__MSG__DETAIL__MOTOR_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MotorCmd in the package arm_control.
typedef struct arm_control__msg__MotorCmd
{
  /// 运动模式 1、位置控制；3、速度控制；4、力位混控；8、csp模式；10、cst模式
  uint8_t mode;
  /// 期望弧度位置
  float q;
  /// 期望速度rad/s
  float dq;
  /// 前馈力矩，Nm
  float tau;
  /// 位置刚度系数
  float kp;
  /// 速度阻尼系数
  float kd;
} arm_control__msg__MotorCmd;

// Struct for a sequence of arm_control__msg__MotorCmd.
typedef struct arm_control__msg__MotorCmd__Sequence
{
  arm_control__msg__MotorCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_control__msg__MotorCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARM_CONTROL__MSG__DETAIL__MOTOR_CMD__STRUCT_H_
