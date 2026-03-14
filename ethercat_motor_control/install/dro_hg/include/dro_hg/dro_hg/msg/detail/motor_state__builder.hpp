// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dro_hg:msg/MotorState.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__MOTOR_STATE__BUILDER_HPP_
#define DRO_HG__MSG__DETAIL__MOTOR_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dro_hg/msg/detail/motor_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dro_hg
{

namespace msg
{

namespace builder
{

class Init_MotorState_motorstate
{
public:
  explicit Init_MotorState_motorstate(::dro_hg::msg::MotorState & msg)
  : msg_(msg)
  {}
  ::dro_hg::msg::MotorState motorstate(::dro_hg::msg::MotorState::_motorstate_type arg)
  {
    msg_.motorstate = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dro_hg::msg::MotorState msg_;
};

class Init_MotorState_temperature
{
public:
  explicit Init_MotorState_temperature(::dro_hg::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_motorstate temperature(::dro_hg::msg::MotorState::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return Init_MotorState_motorstate(msg_);
  }

private:
  ::dro_hg::msg::MotorState msg_;
};

class Init_MotorState_current
{
public:
  explicit Init_MotorState_current(::dro_hg::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_temperature current(::dro_hg::msg::MotorState::_current_type arg)
  {
    msg_.current = std::move(arg);
    return Init_MotorState_temperature(msg_);
  }

private:
  ::dro_hg::msg::MotorState msg_;
};

class Init_MotorState_dq
{
public:
  explicit Init_MotorState_dq(::dro_hg::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_current dq(::dro_hg::msg::MotorState::_dq_type arg)
  {
    msg_.dq = std::move(arg);
    return Init_MotorState_current(msg_);
  }

private:
  ::dro_hg::msg::MotorState msg_;
};

class Init_MotorState_q
{
public:
  explicit Init_MotorState_q(::dro_hg::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_dq q(::dro_hg::msg::MotorState::_q_type arg)
  {
    msg_.q = std::move(arg);
    return Init_MotorState_dq(msg_);
  }

private:
  ::dro_hg::msg::MotorState msg_;
};

class Init_MotorState_num
{
public:
  explicit Init_MotorState_num(::dro_hg::msg::MotorState & msg)
  : msg_(msg)
  {}
  Init_MotorState_q num(::dro_hg::msg::MotorState::_num_type arg)
  {
    msg_.num = std::move(arg);
    return Init_MotorState_q(msg_);
  }

private:
  ::dro_hg::msg::MotorState msg_;
};

class Init_MotorState_mode
{
public:
  Init_MotorState_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorState_num mode(::dro_hg::msg::MotorState::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_MotorState_num(msg_);
  }

private:
  ::dro_hg::msg::MotorState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dro_hg::msg::MotorState>()
{
  return dro_hg::msg::builder::Init_MotorState_mode();
}

}  // namespace dro_hg

#endif  // DRO_HG__MSG__DETAIL__MOTOR_STATE__BUILDER_HPP_
