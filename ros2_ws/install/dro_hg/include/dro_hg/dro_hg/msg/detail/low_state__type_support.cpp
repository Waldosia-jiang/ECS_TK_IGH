// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from dro_hg:msg/LowState.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "dro_hg/msg/detail/low_state__struct.hpp"
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

void LowState_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) dro_hg::msg::LowState(_init);
}

void LowState_fini_function(void * message_memory)
{
  auto typed_message = static_cast<dro_hg::msg::LowState *>(message_memory);
  typed_message->~LowState();
}

size_t size_function__LowState__motor_state(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<dro_hg::msg::MotorState> *>(untyped_member);
  return member->size();
}

const void * get_const_function__LowState__motor_state(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<dro_hg::msg::MotorState> *>(untyped_member);
  return &member[index];
}

void * get_function__LowState__motor_state(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<dro_hg::msg::MotorState> *>(untyped_member);
  return &member[index];
}

void fetch_function__LowState__motor_state(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const dro_hg::msg::MotorState *>(
    get_const_function__LowState__motor_state(untyped_member, index));
  auto & value = *reinterpret_cast<dro_hg::msg::MotorState *>(untyped_value);
  value = item;
}

void assign_function__LowState__motor_state(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<dro_hg::msg::MotorState *>(
    get_function__LowState__motor_state(untyped_member, index));
  const auto & value = *reinterpret_cast<const dro_hg::msg::MotorState *>(untyped_value);
  item = value;
}

void resize_function__LowState__motor_state(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<dro_hg::msg::MotorState> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember LowState_message_member_array[3] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dro_hg::msg::LowState, header),  // bytes offset in struct
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
    offsetof(dro_hg::msg::LowState, slave_num),  // bytes offset in struct
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
    29,  // array size
    true,  // is upper bound
    offsetof(dro_hg::msg::LowState, motor_state),  // bytes offset in struct
    nullptr,  // default value
    size_function__LowState__motor_state,  // size() function pointer
    get_const_function__LowState__motor_state,  // get_const(index) function pointer
    get_function__LowState__motor_state,  // get(index) function pointer
    fetch_function__LowState__motor_state,  // fetch(index, &value) function pointer
    assign_function__LowState__motor_state,  // assign(index, value) function pointer
    resize_function__LowState__motor_state  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers LowState_message_members = {
  "dro_hg::msg",  // message namespace
  "LowState",  // message name
  3,  // number of fields
  sizeof(dro_hg::msg::LowState),
  LowState_message_member_array,  // message members
  LowState_init_function,  // function to initialize message memory (memory has to be allocated)
  LowState_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t LowState_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &LowState_message_members,
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
get_message_type_support_handle<dro_hg::msg::LowState>()
{
  return &::dro_hg::msg::rosidl_typesupport_introspection_cpp::LowState_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, dro_hg, msg, LowState)() {
  return &::dro_hg::msg::rosidl_typesupport_introspection_cpp::LowState_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
