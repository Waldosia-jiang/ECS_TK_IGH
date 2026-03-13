// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dro_hg:msg/ArmCmd.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__ARM_CMD__STRUCT_H_
#define DRO_HG__MSG__DETAIL__ARM_CMD__STRUCT_H_

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
#include "dro_hg/msg/detail/motor_cmd__struct.h"

// constants for array fields with an upper bound
// motor_cmd
enum
{
  dro_hg__msg__ArmCmd__motor_cmd__MAX_SIZE = 14
};

/// Struct defined in msg/ArmCmd in the package dro_hg.
typedef struct dro_hg__msg__ArmCmd
{
  std_msgs__msg__Header header;
  /// 起始关节
  uint8_t begin;
  /// 终止关节
  uint8_t end;
  /// 0-6左臂，7-13右臂
  dro_hg__msg__MotorCmd__Sequence motor_cmd;
} dro_hg__msg__ArmCmd;

// Struct for a sequence of dro_hg__msg__ArmCmd.
typedef struct dro_hg__msg__ArmCmd__Sequence
{
  dro_hg__msg__ArmCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dro_hg__msg__ArmCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRO_HG__MSG__DETAIL__ARM_CMD__STRUCT_H_
