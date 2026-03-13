// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from arm_control:msg/LowState.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__LOW_STATE__BUILDER_HPP_
#define ARM_CONTROL__MSG__DETAIL__LOW_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "arm_control/msg/detail/low_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace arm_control
{

namespace msg
{

namespace builder
{

class Init_LowState_motor_state
{
public:
  explicit Init_LowState_motor_state(::arm_control::msg::LowState & msg)
  : msg_(msg)
  {}
  ::arm_control::msg::LowState motor_state(::arm_control::msg::LowState::_motor_state_type arg)
  {
    msg_.motor_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_control::msg::LowState msg_;
};

class Init_LowState_slave_num
{
public:
  explicit Init_LowState_slave_num(::arm_control::msg::LowState & msg)
  : msg_(msg)
  {}
  Init_LowState_motor_state slave_num(::arm_control::msg::LowState::_slave_num_type arg)
  {
    msg_.slave_num = std::move(arg);
    return Init_LowState_motor_state(msg_);
  }

private:
  ::arm_control::msg::LowState msg_;
};

class Init_LowState_header
{
public:
  Init_LowState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LowState_slave_num header(::arm_control::msg::LowState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LowState_slave_num(msg_);
  }

private:
  ::arm_control::msg::LowState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_control::msg::LowState>()
{
  return arm_control::msg::builder::Init_LowState_header();
}

}  // namespace arm_control

#endif  // ARM_CONTROL__MSG__DETAIL__LOW_STATE__BUILDER_HPP_
