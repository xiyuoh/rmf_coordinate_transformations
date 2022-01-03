cmake_minimum_required(VERSION 3.8)
project(rmf_proj_python)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

find_package(ament_cmake REQUIRED)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(NOT CMAKE_BUILD_TYPE)
  # Use the Release build type by default if the user has not specified one
  set(CMAKE_BUILD_TYPE Release)
endif()

include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(rmf_proj REQUIRED)
find_package(rmf_utils REQUIRED)

include_directories(
  include
  ${rmf_proj_INCLUDE_DIRS}
)

find_package(pybind11_vendor REQUIRED)
find_package(pybind11 REQUIRED)

pybind11_add_module(rmf_transform SHARED
  src/transform.cpp
)

target_include_directories(rmf_transform
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    ${rmf_utils_INCLUDE_DIRS}
)

target_link_libraries(rmf_transform PRIVATE
  rmf_proj::rmf_proj)

# Locate ament_package template files.
set(PYTHON_INSTALL_DIR "lib/python${PYTHON_MAJOR_MINOR}/site-packages")

# Install library for actual use
install(TARGETS rmf_transform
  DESTINATION "${PYTHON_INSTALL_DIR}"
)

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
#   ament_lint_auto_find_test_dependencies()
endif()

ament_package()
