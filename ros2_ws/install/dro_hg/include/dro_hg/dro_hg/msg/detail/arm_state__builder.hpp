// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dro_hg:msg/ArmState.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__ARM_STATE__BUILDER_HPP_
#define DRO_HG__MSG__DETAIL__ARM_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dro_hg/msg/detail/arm_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dro_hg
{

namespace msg
{

namespace builder
{

class Init_ArmState_motor_state
{
public:
  explicit Init_ArmState_motor_state(::dro_hg::msg::ArmState & msg)
  : msg_(msg)
  {}
  ::dro_hg::msg::ArmState motor_state(::dro_hg::msg::ArmState::_motor_state_type arg)
  {
    msg_.motor_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dro_hg::msg::ArmState msg_;
};

class Init_ArmState_slave_num
{
public:
  explicit Init_ArmState_slave_num(::dro_hg::msg::ArmState & msg)
  : msg_(msg)
  {}
  Init_ArmState_motor_state slave_num(::dro_hg::msg::ArmState::_slave_num_type arg)
  {
    msg_.slave_num = std::move(arg);
    return Init_ArmState_motor_state(msg_);
  }

private:
  ::dro_hg::msg::ArmState msg_;
};

class Init_ArmState_header
{
public:
  Init_ArmState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArmState_slave_num header(::dro_hg::msg::ArmState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ArmState_slave_num(msg_);
  }

private:
  ::dro_hg::msg::ArmState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dro_hg::msg::ArmState>()
{
  return dro_hg::msg::builder::Init_ArmState_header();
}

}  // namespace dro_hg

#endif  // DRO_HG__MSG__DETAIL__ARM_STATE__BUILDER_HPP_
