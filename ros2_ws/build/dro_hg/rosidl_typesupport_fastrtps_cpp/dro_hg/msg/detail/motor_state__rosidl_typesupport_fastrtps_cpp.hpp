// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from dro_hg:msg/MotorState.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__MOTOR_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define DRO_HG__MSG__DETAIL__MOTOR_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "dro_hg/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "dro_hg/msg/detail/motor_state__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace dro_hg
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dro_hg
cdr_serialize(
  const dro_hg::msg::MotorState & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dro_hg
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  dro_hg::msg::MotorState & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dro_hg
get_serialized_size(
  const dro_hg::msg::MotorState & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dro_hg
max_serialized_size_MotorState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace dro_hg

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dro_hg
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, dro_hg, msg, MotorState)();

#ifdef __cplusplus
}
#endif

#endif  // DRO_HG__MSG__DETAIL__MOTOR_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
