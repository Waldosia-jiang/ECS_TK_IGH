// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from arm_control:msg/LowCmd.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__LOW_CMD__BUILDER_HPP_
#define ARM_CONTROL__MSG__DETAIL__LOW_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "arm_control/msg/detail/low_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace arm_control
{

namespace msg
{

namespace builder
{

class Init_LowCmd_motor_cmd
{
public:
  explicit Init_LowCmd_motor_cmd(::arm_control::msg::LowCmd & msg)
  : msg_(msg)
  {}
  ::arm_control::msg::LowCmd motor_cmd(::arm_control::msg::LowCmd::_motor_cmd_type arg)
  {
    msg_.motor_cmd = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_control::msg::LowCmd msg_;
};

class Init_LowCmd_end
{
public:
  explicit Init_LowCmd_end(::arm_control::msg::LowCmd & msg)
  : msg_(msg)
  {}
  Init_LowCmd_motor_cmd end(::arm_control::msg::LowCmd::_end_type arg)
  {
    msg_.end = std::move(arg);
    return Init_LowCmd_motor_cmd(msg_);
  }

private:
  ::arm_control::msg::LowCmd msg_;
};

class Init_LowCmd_begin
{
public:
  explicit Init_LowCmd_begin(::arm_control::msg::LowCmd & msg)
  : msg_(msg)
  {}
  Init_LowCmd_end begin(::arm_control::msg::LowCmd::_begin_type arg)
  {
    msg_.begin = std::move(arg);
    return Init_LowCmd_end(msg_);
  }

private:
  ::arm_control::msg::LowCmd msg_;
};

class Init_LowCmd_header
{
public:
  Init_LowCmd_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LowCmd_begin header(::arm_control::msg::LowCmd::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LowCmd_begin(msg_);
  }

private:
  ::arm_control::msg::LowCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_control::msg::LowCmd>()
{
  return arm_control::msg::builder::Init_LowCmd_header();
}

}  // namespace arm_control

#endif  // ARM_CONTROL__MSG__DETAIL__LOW_CMD__BUILDER_HPP_
