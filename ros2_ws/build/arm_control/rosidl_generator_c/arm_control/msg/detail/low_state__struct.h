// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from arm_control:msg/LowState.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__LOW_STATE__STRUCT_H_
#define ARM_CONTROL__MSG__DETAIL__LOW_STATE__STRUCT_H_

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
#include "arm_control/msg/detail/motor_state__struct.h"

// constants for array fields with an upper bound
// motor_state
enum
{
  arm_control__msg__LowState__motor_state__MAX_SIZE = 14
};

/// Struct defined in msg/LowState in the package arm_control.
typedef struct arm_control__msg__LowState
{
  std_msgs__msg__Header header;
  /// 序列号 从站的站号
  uint8_t slave_num;
  arm_control__msg__MotorState__Sequence motor_state;
} arm_control__msg__LowState;

// Struct for a sequence of arm_control__msg__LowState.
typedef struct arm_control__msg__LowState__Sequence
{
  arm_control__msg__LowState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_control__msg__LowState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARM_CONTROL__MSG__DETAIL__LOW_STATE__STRUCT_H_
