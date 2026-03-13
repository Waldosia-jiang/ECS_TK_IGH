// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from arm_control:msg/LowCmd.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__LOW_CMD__STRUCT_H_
#define ARM_CONTROL__MSG__DETAIL__LOW_CMD__STRUCT_H_

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
// Member 'motor_cmd'
#include "arm_control/msg/detail/motor_cmd__struct.h"

// constants for array fields with an upper bound
// motor_cmd
enum
{
  arm_control__msg__LowCmd__motor_cmd__MAX_SIZE = 14
};

/// Struct defined in msg/LowCmd in the package arm_control.
typedef struct arm_control__msg__LowCmd
{
  std_msgs__msg__Header header;
  /// 起始关节
  uint8_t begin;
  /// 终止关节
  uint8_t end;
  /// 0-6左臂，7-13右臂
  arm_control__msg__MotorCmd__Sequence motor_cmd;
} arm_control__msg__LowCmd;

// Struct for a sequence of arm_control__msg__LowCmd.
typedef struct arm_control__msg__LowCmd__Sequence
{
  arm_control__msg__LowCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_control__msg__LowCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARM_CONTROL__MSG__DETAIL__LOW_CMD__STRUCT_H_
