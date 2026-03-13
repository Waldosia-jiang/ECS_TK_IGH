// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from dro_hg:msg/LowState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "dro_hg/msg/detail/low_state__rosidl_typesupport_introspection_c.h"
#include "dro_hg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "dro_hg/msg/detail/low_state__functions.h"
#include "dro_hg/msg/detail/low_state__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `motor_state`
#include "dro_hg/msg/motor_state.h"
// Member `motor_state`
#include "dro_hg/msg/detail/motor_state__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  dro_hg__msg__LowState__init(message_memory);
}

void dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_fini_function(void * message_memory)
{
  dro_hg__msg__LowState__fini(message_memory);
}

size_t dro_hg__msg__LowState__rosidl_typesupport_introspection_c__size_function__LowState__motor_state(
  const void * untyped_member)
{
  const dro_hg__msg__MotorState__Sequence * member =
    (const dro_hg__msg__MotorState__Sequence *)(untyped_member);
  return member->size;
}

const void * dro_hg__msg__LowState__rosidl_typesupport_introspection_c__get_const_function__LowState__motor_state(
  const void * untyped_member, size_t index)
{
  const dro_hg__msg__MotorState__Sequence * member =
    (const dro_hg__msg__MotorState__Sequence *)(untyped_member);
  return &member->data[index];
}

void * dro_hg__msg__LowState__rosidl_typesupport_introspection_c__get_function__LowState__motor_state(
  void * untyped_member, size_t index)
{
  dro_hg__msg__MotorState__Sequence * member =
    (dro_hg__msg__MotorState__Sequence *)(untyped_member);
  return &member->data[index];
}

void dro_hg__msg__LowState__rosidl_typesupport_introspection_c__fetch_function__LowState__motor_state(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const dro_hg__msg__MotorState * item =
    ((const dro_hg__msg__MotorState *)
    dro_hg__msg__LowState__rosidl_typesupport_introspection_c__get_const_function__LowState__motor_state(untyped_member, index));
  dro_hg__msg__MotorState * value =
    (dro_hg__msg__MotorState *)(untyped_value);
  *value = *item;
}

void dro_hg__msg__LowState__rosidl_typesupport_introspection_c__assign_function__LowState__motor_state(
  void * untyped_member, size_t index, const void * untyped_value)
{
  dro_hg__msg__MotorState * item =
    ((dro_hg__msg__MotorState *)
    dro_hg__msg__LowState__rosidl_typesupport_introspection_c__get_function__LowState__motor_state(untyped_member, index));
  const dro_hg__msg__MotorState * value =
    (const dro_hg__msg__MotorState *)(untyped_value);
  *item = *value;
}

bool dro_hg__msg__LowState__rosidl_typesupport_introspection_c__resize_function__LowState__motor_state(
  void * untyped_member, size_t size)
{
  dro_hg__msg__MotorState__Sequence * member =
    (dro_hg__msg__MotorState__Sequence *)(untyped_member);
  dro_hg__msg__MotorState__Sequence__fini(member);
  return dro_hg__msg__MotorState__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_message_member_array[3] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dro_hg__msg__LowState, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "slave_num",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dro_hg__msg__LowState, slave_num),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    29,  // array size
    true,  // is upper bound
    offsetof(dro_hg__msg__LowState, motor_state),  // bytes offset in struct
    NULL,  // default value
    dro_hg__msg__LowState__rosidl_typesupport_introspection_c__size_function__LowState__motor_state,  // size() function pointer
    dro_hg__msg__LowState__rosidl_typesupport_introspection_c__get_const_function__LowState__motor_state,  // get_const(index) function pointer
    dro_hg__msg__LowState__rosidl_typesupport_introspection_c__get_function__LowState__motor_state,  // get(index) function pointer
    dro_hg__msg__LowState__rosidl_typesupport_introspection_c__fetch_function__LowState__motor_state,  // fetch(index, &value) function pointer
    dro_hg__msg__LowState__rosidl_typesupport_introspection_c__assign_function__LowState__motor_state,  // assign(index, value) function pointer
    dro_hg__msg__LowState__rosidl_typesupport_introspection_c__resize_function__LowState__motor_state  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_message_members = {
  "dro_hg__msg",  // message namespace
  "LowState",  // message name
  3,  // number of fields
  sizeof(dro_hg__msg__LowState),
  dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_message_member_array,  // message members
  dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_init_function,  // function to initialize message memory (memory has to be allocated)
  dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_message_type_support_handle = {
  0,
  &dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dro_hg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dro_hg, msg, LowState)() {
  dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dro_hg, msg, MotorState)();
  if (!dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_message_type_support_handle.typesupport_identifier) {
    dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &dro_hg__msg__LowState__rosidl_typesupport_introspection_c__LowState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
