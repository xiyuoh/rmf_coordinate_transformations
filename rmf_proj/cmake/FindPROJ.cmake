
# Find PROJ includes and libraries because problems...
# Reference: https://github.com/OSGeo/PROJ/issues/2546

# Define macros:

# PROJ_FOUND - boolean
# PROJ_INCLUDE_DIRS - include directories
# PROJ_LIBRARIES - libraries
# PROJ_DEFINATIONS - compiler switches for proj


if (PROJ_LIBRARIES AND PROJ_INCLUDE_DIRS)
  # in cache already
  set(PROJ_FOUND TRUE)
else (PROJ_LIBRARIES AND PROJ_INCLUDE_DIRS)

  find_path(PROJ_INCLUDE_DIR
    NAMES
      proj.h
    PATHS
      /usr/include
      /usr/local/include
      ${CMAKE_INSTALL_PREFIX}/include
    PATH_SUFFIXES
        proj4
  )

  find_library(LIBPROJ_LIBRARY
    NAMES
      proj
      proj_6_0
      proj_6_1
      proj_6_2
      proj_6_3
    PATHS
      /usr/lib
      /usr/local/lib
  )

  if (LIBPROJ_LIBRARY)
    set(LIBPROJ_FOUND TRUE)
  endif (LIBPROJ_LIBRARY)

  set(PROJ_INCLUDE_DIRS ${PROJ_INCLUDE_DIR})

  if (LIBPROJ_FOUND)
    set(PROJ_LIBRARIES
      ${PROJ_LIBRARIES}
      ${LIBPROJ_LIBRARY}
    )
  endif (LIBPROJ_FOUND)

  if (PROJ_INCLUDE_DIRS AND PROJ_LIBRARIES)
    set(PROJ_FOUND TRUE)
    set(PROJ_VERSION "8.0.0")
  endif (PROJ_INCLUDE_DIRS AND PROJ_LIBRARIES)

  if (PROJ_FOUND)
    if (NOT PROJ_FIND_QUIETLY)
      message(STATUS "Found PROJ: ${PROJ_LIBRARIES}")
    endif (NOT PROJ_FIND_QUIETLY)
  else (PROJ_FOUND)
    if (PROJ_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find PROJ")
    endif (PROJ_FIND_REQUIRED)
  endif (PROJ_FOUND)

endif (PROJ_LIBRARIES AND PROJ_INCLUDE_DIRS)
