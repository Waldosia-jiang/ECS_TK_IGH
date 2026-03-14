// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dro_hg:msg/MotorState.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__MOTOR_STATE__STRUCT_H_
#define DRO_HG__MSG__DETAIL__MOTOR_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MotorState in the package dro_hg.
typedef struct dro_hg__msg__MotorState
{
  /// 运动模式 1、位置控制；3、速度控制；4、力控模式；8、csp模式；10、cst模式
  uint8_t mode;
  /// 从站的站号
  uint8_t num;
  /// 关节位置，rad
  float q;
  /// 速度，rad/s
  float dq;
  /// 电流
  float current;
  /// 电机绕组温度和驱动器温度
  int16_t temperature[2];
  /// 电机错误码
  uint32_t motorstate;
} dro_hg__msg__MotorState;

// Struct for a sequence of dro_hg__msg__MotorState.
typedef struct dro_hg__msg__MotorState__Sequence
{
  dro_hg__msg__MotorState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dro_hg__msg__MotorState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRO_HG__MSG__DETAIL__MOTOR_STATE__STRUCT_H_
