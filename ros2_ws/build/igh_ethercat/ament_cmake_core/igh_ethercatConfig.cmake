# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_igh_ethercat_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED igh_ethercat_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(igh_ethercat_FOUND FALSE)
  elseif(NOT igh_ethercat_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(igh_ethercat_FOUND FALSE)
  endif()
  return()
endif()
set(_igh_ethercat_CONFIG_INCLUDED TRUE)

# output package information
if(NOT igh_ethercat_FIND_QUIETLY)
  message(STATUS "Found igh_ethercat: 0.0.1 (${igh_ethercat_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'igh_ethercat' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${igh_ethercat_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(igh_ethercat_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${igh_ethercat_DIR}/${_extra}")
endforeach()
