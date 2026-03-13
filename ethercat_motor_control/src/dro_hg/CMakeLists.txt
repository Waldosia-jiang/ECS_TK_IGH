cmake_minimum_required(VERSION 3.5)
project(dro_hg)

# 默认使用 C++14（如果后续添加 C++ 代码时有用）
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)

set(msg_files
  "msg/MotorCmd.msg"
  "msg/MotorState.msg"
  "msg/ArmCmd.msg"
  "msg/ArmState.msg"
  "msg/LegCmd.msg"
  "msg/LegState.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES std_msgs sensor_msgs builtin_interfaces
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()

