// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from arm_control:msg/LowState.idl
// generated code does not contain a copyright notice

#ifndef ARM_CONTROL__MSG__DETAIL__LOW_STATE__STRUCT_HPP_
#define ARM_CONTROL__MSG__DETAIL__LOW_STATE__STRUCT_HPP_

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
// Member 'motor_state'
#include "arm_control/msg/detail/motor_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__arm_control__msg__LowState __attribute__((deprecated))
#else
# define DEPRECATED__arm_control__msg__LowState __declspec(deprecated)
#endif

namespace arm_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LowState_
{
  using Type = LowState_<ContainerAllocator>;

  explicit LowState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->slave_num = 0;
    }
  }

  explicit LowState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->slave_num = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _slave_num_type =
    uint8_t;
  _slave_num_type slave_num;
  using _motor_state_type =
    rosidl_runtime_cpp::BoundedVector<arm_control::msg::MotorState_<ContainerAllocator>, 14, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<arm_control::msg::MotorState_<ContainerAllocator>>>;
  _motor_state_type motor_state;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__slave_num(
    const uint8_t & _arg)
  {
    this->slave_num = _arg;
    return *this;
  }
  Type & set__motor_state(
    const rosidl_runtime_cpp::BoundedVector<arm_control::msg::MotorState_<ContainerAllocator>, 14, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<arm_control::msg::MotorState_<ContainerAllocator>>> & _arg)
  {
    this->motor_state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    arm_control::msg::LowState_<ContainerAllocator> *;
  using ConstRawPtr =
    const arm_control::msg::LowState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<arm_control::msg::LowState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<arm_control::msg::LowState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      arm_control::msg::LowState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<arm_control::msg::LowState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      arm_control::msg::LowState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<arm_control::msg::LowState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<arm_control::msg::LowState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<arm_control::msg::LowState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__arm_control__msg__LowState
    std::shared_ptr<arm_control::msg::LowState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__arm_control__msg__LowState
    std::shared_ptr<arm_control::msg::LowState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LowState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->slave_num != other.slave_num) {
      return false;
    }
    if (this->motor_state != other.motor_state) {
      return false;
    }
    return true;
  }
  bool operator!=(const LowState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LowState_

// alias to use template instance with default allocator
using LowState =
  arm_control::msg::LowState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace arm_control

#endif  // ARM_CONTROL__MSG__DETAIL__LOW_STATE__STRUCT_HPP_
