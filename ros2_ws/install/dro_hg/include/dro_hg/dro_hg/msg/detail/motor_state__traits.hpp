// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dro_hg:msg/MotorState.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__MOTOR_STATE__TRAITS_HPP_
#define DRO_HG__MSG__DETAIL__MOTOR_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "dro_hg/msg/detail/motor_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace dro_hg
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorState & msg,
  std::ostream & out)
{
  out << "{";
  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: q
  {
    out << "q: ";
    rosidl_generator_traits::value_to_yaml(msg.q, out);
    out << ", ";
  }

  // member: dq
  {
    out << "dq: ";
    rosidl_generator_traits::value_to_yaml(msg.dq, out);
    out << ", ";
  }

  // member: current
  {
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
    out << ", ";
  }

  // member: temperature
  {
    if (msg.temperature.size() == 0) {
      out << "temperature: []";
    } else {
      out << "temperature: [";
      size_t pending_items = msg.temperature.size();
      for (auto item : msg.temperature) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: motorstate
  {
    out << "motorstate: ";
    rosidl_generator_traits::value_to_yaml(msg.motorstate, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: q
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "q: ";
    rosidl_generator_traits::value_to_yaml(msg.q, out);
    out << "\n";
  }

  // member: dq
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dq: ";
    rosidl_generator_traits::value_to_yaml(msg.dq, out);
    out << "\n";
  }

  // member: current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
    out << "\n";
  }

  // member: temperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.temperature.size() == 0) {
      out << "temperature: []\n";
    } else {
      out << "temperature:\n";
      for (auto item : msg.temperature) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: motorstate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motorstate: ";
    rosidl_generator_traits::value_to_yaml(msg.motorstate, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorState & msg, bool use_flow_style = false)
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

}  // namespace dro_hg

namespace rosidl_generator_traits
{

[[deprecated("use dro_hg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const dro_hg::msg::MotorState & msg,
  std::ostream & out, size_t indentation = 0)
{
  dro_hg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dro_hg::msg::to_yaml() instead")]]
inline std::string to_yaml(const dro_hg::msg::MotorState & msg)
{
  return dro_hg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<dro_hg::msg::MotorState>()
{
  return "dro_hg::msg::MotorState";
}

template<>
inline const char * name<dro_hg::msg::MotorState>()
{
  return "dro_hg/msg/MotorState";
}

template<>
struct has_fixed_size<dro_hg::msg::MotorState>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<dro_hg::msg::MotorState>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<dro_hg::msg::MotorState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DRO_HG__MSG__DETAIL__MOTOR_STATE__TRAITS_HPP_
