// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from arm_control:msg/MotorState.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__MOTOR_STATE__STRUCT_H_
#define ARM_CONTROL__MSG__DETAIL__MOTOR_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MotorState in the package arm_control.
typedef struct arm_control__msg__MotorState
{
  /// 运动模式 1、位置控制；3、速度控制；4、力控模式；8、csp模式；10、cst模式
  uint8_t mode;
  /// 关节位置，rad
  float q;
  /// 速度，rad/s
  float dq;
  /// 电流
  float current;
  /// 电机错误码
  uint32_t motorstate;
} arm_control__msg__MotorState;

// Struct for a sequence of arm_control__msg__MotorState.
typedef struct arm_control__msg__MotorState__Sequence
{
  arm_control__msg__MotorState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_control__msg__MotorState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARM_CONTROL__MSG__DETAIL__MOTOR_STATE__STRUCT_H_
