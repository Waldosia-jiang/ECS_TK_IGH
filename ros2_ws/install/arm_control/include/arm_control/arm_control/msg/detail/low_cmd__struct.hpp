// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from arm_control:msg/LowCmd.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__LOW_CMD__STRUCT_HPP_
#define ARM_CONTROL__MSG__DETAIL__LOW_CMD__STRUCT_HPP_

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
#include "arm_control/msg/detail/motor_cmd__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__arm_control__msg__LowCmd __attribute__((deprecated))
#else
# define DEPRECATED__arm_control__msg__LowCmd __declspec(deprecated)
#endif

namespace arm_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LowCmd_
{
  using Type = LowCmd_<ContainerAllocator>;

  explicit LowCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->begin = 0;
      this->end = 0;
    }
  }

  explicit LowCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    rosidl_runtime_cpp::BoundedVector<arm_control::msg::MotorCmd_<ContainerAllocator>, 14, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<arm_control::msg::MotorCmd_<ContainerAllocator>>>;
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
    const rosidl_runtime_cpp::BoundedVector<arm_control::msg::MotorCmd_<ContainerAllocator>, 14, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<arm_control::msg::MotorCmd_<ContainerAllocator>>> & _arg)
  {
    this->motor_cmd = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    arm_control::msg::LowCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const arm_control::msg::LowCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<arm_control::msg::LowCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<arm_control::msg::LowCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      arm_control::msg::LowCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<arm_control::msg::LowCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      arm_control::msg::LowCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<arm_control::msg::LowCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<arm_control::msg::LowCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<arm_control::msg::LowCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__arm_control__msg__LowCmd
    std::shared_ptr<arm_control::msg::LowCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__arm_control__msg__LowCmd
    std::shared_ptr<arm_control::msg::LowCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LowCmd_ & other) const
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
  bool operator!=(const LowCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LowCmd_

// alias to use template instance with default allocator
using LowCmd =
  arm_control::msg::LowCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace arm_control

#endif  // ARM_CONTROL__MSG__DETAIL__LOW_CMD__STRUCT_HPP_
