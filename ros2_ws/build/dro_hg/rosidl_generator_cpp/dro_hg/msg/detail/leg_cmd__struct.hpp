// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dro_hg:msg/LegCmd.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__LEG_CMD__STRUCT_HPP_
#define DRO_HG__MSG__DETAIL__LEG_CMD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'motor_cmd'
#include "dro_hg/msg/detail/motor_cmd__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__dro_hg__msg__LegCmd __attribute__((deprecated))
#else
# define DEPRECATED__dro_hg__msg__LegCmd __declspec(deprecated)
#endif

namespace dro_hg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LegCmd_
{
  using Type = LegCmd_<ContainerAllocator>;

  explicit LegCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->begin = 0;
      this->end = 0;
    }
  }

  explicit LegCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->begin = 0;
      this->end = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _begin_type =
    uint8_t;
  _begin_type begin;
  using _end_type =
    uint8_t;
  _end_type end;
  using _motor_cmd_type =
    rosidl_runtime_cpp::BoundedVector<dro_hg::msg::MotorCmd_<ContainerAllocator>, 15, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<dro_hg::msg::MotorCmd_<ContainerAllocator>>>;
  _motor_cmd_type motor_cmd;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__begin(
    const uint8_t & _arg)
  {
    this->begin = _arg;
    return *this;
  }
  Type & set__end(
    const uint8_t & _arg)
  {
    this->end = _arg;
    return *this;
  }
  Type & set__motor_cmd(
    const rosidl_runtime_cpp::BoundedVector<dro_hg::msg::MotorCmd_<ContainerAllocator>, 15, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<dro_hg::msg::MotorCmd_<ContainerAllocator>>> & _arg)
  {
    this->motor_cmd = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dro_hg::msg::LegCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const dro_hg::msg::LegCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dro_hg::msg::LegCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dro_hg::msg::LegCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dro_hg::msg::LegCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dro_hg::msg::LegCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dro_hg::msg::LegCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dro_hg::msg::LegCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dro_hg::msg::LegCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dro_hg::msg::LegCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dro_hg__msg__LegCmd
    std::shared_ptr<dro_hg::msg::LegCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dro_hg__msg__LegCmd
    std::shared_ptr<dro_hg::msg::LegCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LegCmd_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->begin != other.begin) {
      return false;
    }
    if (this->end != other.end) {
      return false;
    }
    if (this->motor_cmd != other.motor_cmd) {
      return false;
    }
    return true;
  }
  bool operator!=(const LegCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LegCmd_

// alias to use template instance with default allocator
using LegCmd =
  dro_hg::msg::LegCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace dro_hg

#endif  // DRO_HG__MSG__DETAIL__LEG_CMD__STRUCT_HPP_
