// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from arm_control:msg/MotorState.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__MOTOR_STATE__BUILDER_HPP_
#define ARM_CONTROL__MSG__DETAIL__MOTOR_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "arm_control/msg/detail/motor_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace arm_control
{

namespace msg
{

namespace builder
{

class Init_MotorState_motorstate
{
public:
  explicit Init_MotorState_motorstate(::arm_control::msg::MotorState & msg)
  : msg_(msg)
  {}
  ::arm_control::msg::MotorState motorstate(::arm_control::msg::MotorState::_motorstate_type arg)
  {
    msg_.motorstate = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_control::msg::MotorState msg_;
};

class Init_MotorState_current
{
public:
  explicit Init_MotorState_current(::arm_control::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_motorstate current(::arm_control::msg::MotorState::_current_type arg)
  {
    msg_.current = std::move(arg);
    return Init_MotorState_motorstate(msg_);
  }

private:
  ::arm_control::msg::MotorState msg_;
};

class Init_MotorState_dq
{
public:
  explicit Init_MotorState_dq(::arm_control::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_current dq(::arm_control::msg::MotorState::_dq_type arg)
  {
    msg_.dq = std::move(arg);
    return Init_MotorState_current(msg_);
  }

private:
  ::arm_control::msg::MotorState msg_;
};

class Init_MotorState_q
{
public:
  explicit Init_MotorState_q(::arm_control::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_dq q(::arm_control::msg::MotorState::_q_type arg)
  {
    msg_.q = std::move(arg);
    return Init_MotorState_dq(msg_);
  }

private:
  ::arm_control::msg::MotorState msg_;
};

class Init_MotorState_mode
{
public:
  Init_MotorState_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorState_q mode(::arm_control::msg::MotorState::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_MotorState_q(msg_);
  }

private:
  ::arm_control::msg::MotorState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_control::msg::MotorState>()
{
  return arm_control::msg::builder::Init_MotorState_mode();
}

}  // namespace arm_control

#endif  // ARM_CONTROL__MSG__DETAIL__MOTOR_STATE__BUILDER_HPP_
