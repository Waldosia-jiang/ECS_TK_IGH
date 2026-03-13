cmake_minimum_required(VERSION 3.5)
project(igh_ethercat)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(dro_hg REQUIRED)

# 显式使用与系统已安装 IgH EtherCAT 匹配的头文件和库
set(ETHERCAT_INCLUDE_DIRS
  /home/p30039115276/ethercat-stable-1.6/include
  /usr/local/etherlab/include
  /usr/local/include
)

find_library(ETHERCAT_LIB
  ethercat
  HINTS
    /usr/local/lib
    /usr/local/etherlab/lib
)

add_library(igh_core STATIC
  src/igh_example.c
  src/motion.c
  src/pdo_set.c
  src/trajectory_planning.c
  src/dc.c
)

target_compile_definitions(igh_core PRIVATE IGH_EXAMPLE_NO_MAIN=1 USE_GNU_THREAD=1)

target_include_directories(igh_core PUBLIC
  ${ETHERCAT_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(ETHERCAT_LIB)
  target_link_libraries(igh_core ${ETHERCAT_LIB})
else()
  message(WARNING "EtherCAT library 'ethercat' not found, linking may fail")
endif()

add_executable(igh_ethercat_node
  src/igh_ethercat_node.cpp
)

target_include_directories(igh_ethercat_node PRIVATE
  ${ETHERCAT_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

ament_target_dependencies(igh_ethercat_node
  rclcpp
  dro_hg
)

target_link_libraries(igh_ethercat_node
  igh_core
)

install(TARGETS
  igh_ethercat_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

