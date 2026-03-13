// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from dro_hg:msg/MotorState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "dro_hg/msg/detail/motor_state__rosidl_typesupport_introspection_c.h"
#include "dro_hg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "dro_hg/msg/detail/motor_state__functions.h"
#include "dro_hg/msg/detail/motor_state__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  dro_hg__msg__MotorState__init(message_memory);
}

void dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_fini_function(void * message_memory)
{
  dro_hg__msg__MotorState__fini(message_memory);
}

size_t dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__size_function__MotorState__temperature(
  const void * untyped_member)
{
  (void)untyped_member;
  return 2;
}

const void * dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__get_const_function__MotorState__temperature(
  const void * untyped_member, size_t index)
{
  const int16_t * member =
    (const int16_t *)(untyped_member);
  return &member[index];
}

void * dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__get_function__MotorState__temperature(
  void * untyped_member, size_t index)
{
  int16_t * member =
    (int16_t *)(untyped_member);
  return &member[index];
}

void dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__fetch_function__MotorState__temperature(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int16_t * item =
    ((const int16_t *)
    dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__get_const_function__MotorState__temperature(untyped_member, index));
  int16_t * value =
    (int16_t *)(untyped_value);
  *value = *item;
}

void dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__assign_function__MotorState__temperature(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int16_t * item =
    ((int16_t *)
    dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__get_function__MotorState__temperature(untyped_member, index));
  const int16_t * value =
    (const int16_t *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_message_member_array[6] = {
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dro_hg__msg__MotorState, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "q",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dro_hg__msg__MotorState, q),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "dq",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dro_hg__msg__MotorState, dq),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dro_hg__msg__MotorState, current),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "temperature",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    2,  // array size
    false,  // is upper bound
    offsetof(dro_hg__msg__MotorState, temperature),  // bytes offset in struct
    NULL,  // default value
    dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__size_function__MotorState__temperature,  // size() function pointer
    dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__get_const_function__MotorState__temperature,  // get_const(index) function pointer
    dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__get_function__MotorState__temperature,  // get(index) function pointer
    dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__fetch_function__MotorState__temperature,  // fetch(index, &value) function pointer
    dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__assign_function__MotorState__temperature,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motorstate",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dro_hg__msg__MotorState, motorstate),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_message_members = {
  "dro_hg__msg",  // message namespace
  "MotorState",  // message name
  6,  // number of fields
  sizeof(dro_hg__msg__MotorState),
  dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_message_member_array,  // message members
  dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_init_function,  // function to initialize message memory (memory has to be allocated)
  dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_message_type_support_handle = {
  0,
  &dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dro_hg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dro_hg, msg, MotorState)() {
  if (!dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_message_type_support_handle.typesupport_identifier) {
    dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &dro_hg__msg__MotorState__rosidl_typesupport_introspection_c__MotorState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
