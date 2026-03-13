// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dro_hg:msg/LegCmd.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__LEG_CMD__STRUCT_H_
#define DRO_HG__MSG__DETAIL__LEG_CMD__STRUCT_H_

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
  dro_hg__msg__LegCmd__motor_cmd__MAX_SIZE = 15
};

/// Struct defined in msg/LegCmd in the package dro_hg.
typedef struct dro_hg__msg__LegCmd
{
  std_msgs__msg__Header header;
  /// 起始关节
  uint8_t begin;
  /// 终止关节
  uint8_t end;
  /// 0-5左腿（ID:1-6），6-11右腿（ID:7-12）12-14腰（ID:13-15）
  dro_hg__msg__MotorCmd__Sequence motor_cmd;
} dro_hg__msg__LegCmd;

// Struct for a sequence of dro_hg__msg__LegCmd.
typedef struct dro_hg__msg__LegCmd__Sequence
{
  dro_hg__msg__LegCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dro_hg__msg__LegCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRO_HG__MSG__DETAIL__LEG_CMD__STRUCT_H_
