// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dro_hg:msg/MotorState.idl
// generated code does not contain a copyright notice

#ifndef DRO_HG__MSG__DETAIL__MOTOR_STATE__STRUCT_HPP_
#define DRO_HG__MSG__DETAIL__MOTOR_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__dro_hg__msg__MotorState __attribute__((deprecated))
#else
# define DEPRECATED__dro_hg__msg__MotorState __declspec(deprecated)
#endif

namespace dro_hg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorState_
{
  using Type = MotorState_<ContainerAllocator>;

  explicit MotorState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->q = 0.0f;
      this->dq = 0.0f;
      this->current = 0.0f;
      std::fill<typename std::array<int16_t, 2>::iterator, int16_t>(this->temperature.begin(), this->temperature.end(), 0);
      this->motorstate = 0ul;
    }
  }

  explicit MotorState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : temperature(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->q = 0.0f;
      this->dq = 0.0f;
      this->current = 0.0f;
      std::fill<typename std::array<int16_t, 2>::iterator, int16_t>(this->temperature.begin(), this->temperature.end(), 0);
      this->motorstate = 0ul;
    }
  }

  // field types and members
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _q_type =
    float;
  _q_type q;
  using _dq_type =
    float;
  _dq_type dq;
  using _current_type =
    float;
  _current_type current;
  using _temperature_type =
    std::array<int16_t, 2>;
  _temperature_type temperature;
  using _motorstate_type =
    uint32_t;
  _motorstate_type motorstate;

  // setters for named parameter idiom
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__q(
    const float & _arg)
  {
    this->q = _arg;
    return *this;
  }
  Type & set__dq(
    const float & _arg)
  {
    this->dq = _arg;
    return *this;
  }
  Type & set__current(
    const float & _arg)
  {
    this->current = _arg;
    return *this;
  }
  Type & set__temperature(
    const std::array<int16_t, 2> & _arg)
  {
    this->temperature = _arg;
    return *this;
  }
  Type & set__motorstate(
    const uint32_t & _arg)
  {
    this->motorstate = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dro_hg::msg::MotorState_<ContainerAllocator> *;
  using ConstRawPtr =
    const dro_hg::msg::MotorState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dro_hg::msg::MotorState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dro_hg::msg::MotorState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dro_hg::msg::MotorState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dro_hg::msg::MotorState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dro_hg::msg::MotorState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dro_hg::msg::MotorState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dro_hg::msg::MotorState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dro_hg::msg::MotorState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dro_hg__msg__MotorState
    std::shared_ptr<dro_hg::msg::MotorState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dro_hg__msg__MotorState
    std::shared_ptr<dro_hg::msg::MotorState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorState_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    if (this->q != other.q) {
      return false;
    }
    if (this->dq != other.dq) {
      return false;
    }
    if (this->current != other.current) {
      return false;
    }
    if (this->temperature != other.temperature) {
      return false;
    }
    if (this->motorstate != other.motorstate) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorState_

// alias to use template instance with default allocator
using MotorState =
  dro_hg::msg::MotorState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace dro_hg

#endif  // DRO_HG__MSG__DETAIL__MOTOR_STATE__STRUCT_HPP_
