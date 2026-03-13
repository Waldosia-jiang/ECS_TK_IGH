cmake_minimum_required(VERSION 3.10)
project(ethercat_motor_node)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找依赖
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(EtherCAT REQUIRED)
find_package(dro_hg REQUIRED)

# 包含目录
include_directories(
  ${ETHERCAT_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 静态库：math_ops + motor_control
add_library(ethercat_motor_lib STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/math_ops.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/motor_control.c
)
target_link_libraries(ethercat_motor_lib PUBLIC
  EtherLab::ethercat
)

# ROS2 节点
add_executable(ethercat_motor_node
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ethercat_motor_node.cpp
)
ament_target_dependencies(ethercat_motor_node
  rclcpp
  rclcpp_components
  std_msgs
  geometry_msgs
  builtin_interfaces
  dro_hg
)
target_link_libraries(ethercat_motor_node
  ethercat_motor_lib
  pthread
  m
)

# 安装
install(TARGETS
  ethercat_motor_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)
ament_export_libraries(ethercat_motor_lib)
ament_export_dependencies(
  rclcpp
  rclcpp_components
  std_msgs
  geometry_msgs
  builtin_interfaces
  dro_hg
)

ament_package()
