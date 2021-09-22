cmake_minimum_required(VERSION 3.5.0)

project(rmf_proj VERSION 0.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

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

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(ament_cmake_catch2 QUIET)
find_package(rmf_utils REQUIRED)
find_package(rmf_cmake_uncrustify QUIET)
find_package(PROJ REQUIRED)

# ===== rmf_proj library
file(GLOB lib_srcs
  "src/rmf_proj/*.cpp"
)

add_library(rmf_proj SHARED
  ${lib_srcs}
)

target_include_directories(rmf_proj
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    ${rmf_utils_INCLUDE_DIRS}
)

target_link_libraries(rmf_proj
  rmf_utils::rmf_utils
  ${PROJ_LIBRARIES}
)

if(BUILD_TESTING AND ament_cmake_catch2_FOUND AND rmf_cmake_uncrustify_FOUND)
  file(GLOB_RECURSE unit_test_srcs "test/*.cpp")

  ament_add_catch2(
    test_rmf_proj test/main.cpp ${unit_test_srcs}
    TIMEOUT 300)
  target_link_libraries(test_rmf_proj
      rmf_proj
      # ${PROJ_LIBRARIES}
  )

  target_include_directories(test_rmf_proj
    PRIVATE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/>
      ${rmf_utils_INCLUDE_DIRS}
  )

  find_file(uncrustify_config_file
    NAMES "rmf_code_style.cfg"
    PATHS "${rmf_utils_DIR}/../../../share/rmf_utils/")

  rmf_uncrustify(
    ARGN include src test
    CONFIG_FILE ${uncrustify_config_file}
    MAX_LINE_LENGTH 80
  )
endif()

install(
  DIRECTORY include/rmf_proj
  DESTINATION include
)

export(PACKAGE rmf_proj)
