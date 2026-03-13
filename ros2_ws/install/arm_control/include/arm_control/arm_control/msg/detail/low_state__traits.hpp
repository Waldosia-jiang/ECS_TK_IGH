// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from arm_control:msg/LowState.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__LOW_STATE__TRAITS_HPP_
#define ARM_CONTROL__MSG__DETAIL__LOW_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "arm_control/msg/detail/low_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'motor_state'
#include "arm_control/msg/detail/motor_state__traits.hpp"

namespace arm_control
{

namespace msg
{

inline void to_flow_style_yaml(
  const LowState & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: slave_num
  {
    out << "slave_num: ";
    rosidl_generator_traits::value_to_yaml(msg.slave_num, out);
    out << ", ";
  }

  // member: motor_state
  {
    if (msg.motor_state.size() == 0) {
      out << "motor_state: []";
    } else {
      out << "motor_state: [";
      size_t pending_items = msg.motor_state.size();
      for (auto item : msg.motor_state) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LowState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: slave_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "slave_num: ";
    rosidl_generator_traits::value_to_yaml(msg.slave_num, out);
    out << "\n";
  }

  // member: motor_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.motor_state.size() == 0) {
      out << "motor_state: []\n";
    } else {
      out << "motor_state:\n";
      for (auto item : msg.motor_state) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LowState & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace arm_control

namespace rosidl_generator_traits
{

[[deprecated("use arm_control::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const arm_control::msg::LowState & msg,
  std::ostream & out, size_t indentation = 0)
{
  arm_control::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use arm_control::msg::to_yaml() instead")]]
inline std::string to_yaml(const arm_control::msg::LowState & msg)
{
  return arm_control::msg::to_yaml(msg);
}

template<>
inline const char * data_type<arm_control::msg::LowState>()
{
  return "arm_control::msg::LowState";
}

template<>
inline const char * name<arm_control::msg::LowState>()
{
  return "arm_control/msg/LowState";
}

template<>
struct has_fixed_size<arm_control::msg::LowState>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<arm_control::msg::LowState>
  : std::integral_constant<bool, has_bounded_size<arm_control::msg::MotorState>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<arm_control::msg::LowState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ARM_CONTROL__MSG__DETAIL__LOW_STATE__TRAITS_HPP_
