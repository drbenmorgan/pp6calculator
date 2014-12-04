# - Main CMake script for pp6calculator
# Comments in CMake begin with a '#' just like shell and python scripts
#
# - Require latest generation of CMake
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# - Declare the project
project(pp6calculator)

# - Use standard flag set when using the GNU/Clang compiler
# Use CMake builtin to check for available flags
# run "cmake --help-module CheckCXXCompilerFlag" for more information
include(CheckCXXCompilerFlag)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Set default flag set for GNU/Clang
  set(CMAKE_CXX_FLAGS "-pedantic-errors -Wall -Wextra -Werror -Wfatal-errors -Wwrite-strings -Woverloaded-virtual  -fno-gnu-keywords -fstrict-aliasing")

  # Extra GNU only flag
  if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-nonansi-builtins")
  endif()

  # Check for libc++ which it's best to use on Apple
  check_cxx_compiler_flag(-stdlib=libc++ HAS_LIBCXX)
  if(HAS_LIBCXX AND APPLE)
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
  endif()

  # - Check for and use best available standard up to C++11
  check_cxx_compiler_flag(-std=c++11 HAS_GNUSTYLE_CPP11)
  check_cxx_compiler_flag(-std=c++0x HAS_GNUSTYLE_CPP0X)

  if(HAS_GNUSTYLE_CPP11)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
  elseif(HAS_GNUSTYLE_CPP0X)
    set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "-std=c++98 ${CMAKE_CXX_FLAGS}")
  endif()
endif()

# - Tell compiler where to find headers
include_directories(FileReader)
include_directories(PP6Lib)

# - Add the PP6Lib and FileReader libraries
add_subdirectory(PP6Lib)
add_subdirectory(FileReader)

# - Add the pp6calculator program
add_executable(pp6calculator pp6calculator.cpp)

# - Link pp6calculator to pp6lib and FileReader library
target_link_libraries(pp6calculator pp6lib FileReader)

# - Install pp6calculator to the bin subdirectory of CMAKE_INSTALL_PREFIX
install(TARGETS pp6calculator DESTINATION bin)

# - Copy PDG text DB to build directory so it's immediately available
configure_file(pdg.dbt ${PROJECT_BINARY_DIR}/pdg.dbt COPYONLY)

# - Package pp6calculator sources and executable
include(CPack)

