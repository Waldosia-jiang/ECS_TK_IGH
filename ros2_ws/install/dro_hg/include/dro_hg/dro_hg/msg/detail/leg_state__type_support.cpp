// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from dro_hg:msg/LegState.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "dro_hg/msg/detail/leg_state__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace dro_hg
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void LegState_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) dro_hg::msg::LegState(_init);
}

void LegState_fini_function(void * message_memory)
{
  auto typed_message = static_cast<dro_hg::msg::LegState *>(message_memory);
  typed_message->~LegState();
}

size_t size_function__LegState__motor_state(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<dro_hg::msg::MotorState> *>(untyped_member);
  return member->size();
}

const void * get_const_function__LegState__motor_state(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<dro_hg::msg::MotorState> *>(untyped_member);
  return &member[index];
}

void * get_function__LegState__motor_state(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<dro_hg::msg::MotorState> *>(untyped_member);
  return &member[index];
}

void fetch_function__LegState__motor_state(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const dro_hg::msg::MotorState *>(
    get_const_function__LegState__motor_state(untyped_member, index));
  auto & value = *reinterpret_cast<dro_hg::msg::MotorState *>(untyped_value);
  value = item;
}

void assign_function__LegState__motor_state(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<dro_hg::msg::MotorState *>(
    get_function__LegState__motor_state(untyped_member, index));
  const auto & value = *reinterpret_cast<const dro_hg::msg::MotorState *>(untyped_value);
  item = value;
}

void resize_function__LegState__motor_state(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<dro_hg::msg::MotorState> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember LegState_message_member_array[3] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dro_hg::msg::LegState, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "slave_num",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dro_hg::msg::LegState, slave_num),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "motor_state",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<dro_hg::msg::MotorState>(),  // members of sub message
    true,  // is array
    15,  // array size
    true,  // is upper bound
    offsetof(dro_hg::msg::LegState, motor_state),  // bytes offset in struct
    nullptr,  // default value
    size_function__LegState__motor_state,  // size() function pointer
    get_const_function__LegState__motor_state,  // get_const(index) function pointer
    get_function__LegState__motor_state,  // get(index) function pointer
    fetch_function__LegState__motor_state,  // fetch(index, &value) function pointer
    assign_function__LegState__motor_state,  // assign(index, value) function pointer
    resize_function__LegState__motor_state  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers LegState_message_members = {
  "dro_hg::msg",  // message namespace
  "LegState",  // message name
  3,  // number of fields
  sizeof(dro_hg::msg::LegState),
  LegState_message_member_array,  // message members
  LegState_init_function,  // function to initialize message memory (memory has to be allocated)
  LegState_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t LegState_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &LegState_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace dro_hg


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<dro_hg::msg::LegState>()
{
  return &::dro_hg::msg::rosidl_typesupport_introspection_cpp::LegState_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, dro_hg, msg, LegState)() {
  return &::dro_hg::msg::rosidl_typesupport_introspection_cpp::LegState_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
