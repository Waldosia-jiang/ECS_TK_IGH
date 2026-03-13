// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dro_hg:msg/ArmState.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__ARM_STATE__STRUCT_H_
#define DRO_HG__MSG__DETAIL__ARM_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'motor_state'
#include "dro_hg/msg/detail/motor_state__struct.h"

// constants for array fields with an upper bound
// motor_state
enum
{
  dro_hg__msg__ArmState__motor_state__MAX_SIZE = 14
};

/// Struct defined in msg/ArmState in the package dro_hg.
typedef struct dro_hg__msg__ArmState
{
  std_msgs__msg__Header header;
  /// 序列号 从站的站号
  uint8_t slave_num;
  dro_hg__msg__MotorState__Sequence motor_state;
} dro_hg__msg__ArmState;

// Struct for a sequence of dro_hg__msg__ArmState.
typedef struct dro_hg__msg__ArmState__Sequence
{
  dro_hg__msg__ArmState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dro_hg__msg__ArmState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRO_HG__MSG__DETAIL__ARM_STATE__STRUCT_H_
