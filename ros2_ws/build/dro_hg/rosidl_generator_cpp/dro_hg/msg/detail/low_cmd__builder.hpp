// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dro_hg:msg/LowCmd.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__LOW_CMD__BUILDER_HPP_
#define DRO_HG__MSG__DETAIL__LOW_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dro_hg/msg/detail/low_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dro_hg
{

namespace msg
{

namespace builder
{

class Init_LowCmd_motor_cmd
{
public:
  explicit Init_LowCmd_motor_cmd(::dro_hg::msg::LowCmd & msg)
  : msg_(msg)
  {}
  ::dro_hg::msg::LowCmd motor_cmd(::dro_hg::msg::LowCmd::_motor_cmd_type arg)
  {
    msg_.motor_cmd = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dro_hg::msg::LowCmd msg_;
};

class Init_LowCmd_end
{
public:
  explicit Init_LowCmd_end(::dro_hg::msg::LowCmd & msg)
  : msg_(msg)
  {}
  Init_LowCmd_motor_cmd end(::dro_hg::msg::LowCmd::_end_type arg)
  {
    msg_.end = std::move(arg);
    return Init_LowCmd_motor_cmd(msg_);
  }

private:
  ::dro_hg::msg::LowCmd msg_;
};

class Init_LowCmd_begin
{
public:
  explicit Init_LowCmd_begin(::dro_hg::msg::LowCmd & msg)
  : msg_(msg)
  {}
  Init_LowCmd_end begin(::dro_hg::msg::LowCmd::_begin_type arg)
  {
    msg_.begin = std::move(arg);
    return Init_LowCmd_end(msg_);
  }

private:
  ::dro_hg::msg::LowCmd msg_;
};

class Init_LowCmd_header
{
public:
  Init_LowCmd_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LowCmd_begin header(::dro_hg::msg::LowCmd::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LowCmd_begin(msg_);
  }

private:
  ::dro_hg::msg::LowCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dro_hg::msg::LowCmd>()
{
  return dro_hg::msg::builder::Init_LowCmd_header();
}

}  // namespace dro_hg

#endif  // DRO_HG__MSG__DETAIL__LOW_CMD__BUILDER_HPP_
