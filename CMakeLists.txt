#
# @brief The MIT License (MIT)
# @copyright © 2017 David Dumke, (strike5150@gmail.com)
# @ref https://www.linkedin.com/in/davidtjdumke/
#
# Permission  is  hereby  granted, free  of  charge, to  any person  obtaining
# a copy of this software and associated documentation files (the “Software”),
# to deal in the Software  without restriction,  including  without limitation
# the rights to  use,  copy,  modify,  merge, publish, distribute, sublicense,
# and/or sell  copies of the  Software,  and  to  permit  persons  to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice  and this permission  notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS  PROVIDED “AS IS”,  WITHOUT WARRANTY  OF ANY  KIND,  EXPRESS
# OR IMPLIED,  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR  PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR  COPYRIGHT HOLDERS BE  LIABLE FOR ANY  CLAIM,  DAMAGES  OR  OTHER
# LIABILITY,  WHETHER IN  AN ACTION  OF CONTRACT,  TORT OR  OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#

#
# "determine required cmake here (use 'sudo snap install cmake') to get the 
# latest and greatest version, (regardless of platform)" -- Matt Williams, 2021
#
cmake_minimum_required(VERSION 3.21)

#
# NOTE: Include our own cmake scripts, and the CPM package manager
#
include(cmake/CPM.cmake)
include(cmake/print.cmake)
include(cmake/utils.cmake)
include(cmake/Find32or64bit.cmake)
extras_cpp_get_version()
project(
  extras_cpp
  VERSION ${EXTRAS_CPP_VERSION}
  LANGUAGES CXX
)

FIND_PACKAGE (Threads)

#
# NOTE: Set our source and include directory variables for use through the build
#
set(SOURCES "${PROJECT_SOURCE_DIR}/src")
set(INCLUDES "${PROJECT_SOURCE_DIR}/include")

#
# NOTE: Prevent in source builds (can't build in src/ or in project root)
#
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR OR PROJECT_BINARY_DIR STREQUAL SOURCES)
  print(
    FATAL_ERROR
    "In source builds are not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()
print(STATUS "Building ${PROJECT_NAME}-${PROJECT_VERSION}")

#
# NOTE: bring in standard cmake includes
#
include(CMakeDependentOption)
include(GNUInstallDirs)
include(CheckIPOSupported)

#
# NOTE: Export compile_commands.json file to support clang tooling
#
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# NOTE: Set C/C++ parameters for all targets in this CMakeLists.txt
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic --std=c++17 -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -fPIC")

#
# NOTE: add additional project options
#
option(EXTRAS_CPP_PRODUCTION "Production build" OFF)

#
# MAKE_EXTRAS_CPP_LIBRARY_ONLY
#
# Quite often when you include a library from a github project, (via CPM)
# all you are interested in are the shared library files. When you use this
# flag you have to set it on any executables (see below) that you setup
# and/or wish to make optional. Mind you, this option has not been fully
# tested for use with EXTRAS_CPP_PRODUCTION flag. So, there might be 
# a hiccup in here that needs to be worked out, (reader beware).
#
# see also MAKE_EXTRAS_CPP_LIBRARY_TOOLS
#
# This second flag will allow both the shared libraries and any executatbles
# (but not the unit tests) to be compiled.
#
# Using these flags speeds up the CPM inclusions in other projects significantly.
#

message(STATUS "MAKE_EXTRAS_CPP_LIBRARY_ONLY is ${MAKE_EXTRAS_CPP_LIBRARY_ONLY}")
if(MAKE_EXTRAS_CPP_LIBRARY_ONLY)
  option(BUILD_TESTS "Build tests" OFF)
  option(DEBUG "Debug Build" OFF)
  set(EXTRAS_CPP_TESTS OFF)
  message(STATUS "BUILD_TESTS is ${BUILD_TESTS}")
  message(STATUS "DEBUG is ${DEBUG}")
else()
  option(BUILD_TESTS "Build tests" ON)
  option(DEBUG "Debug Build" ON)
  message(STATUS "BUILD_TESTS is ${BUILD_TESTS}")
  message(STATUS "DEBUG is ${DEBUG}")

  #
  # NOTE: Build defaults to production, cmake -DEXTRAS_CPP_PRODUCTION=OFF will build debug with tests
  #
  if(NOT EXTRAS_CPP_PRODUCTION)
    print(STATUS "Building ${PROJECT_NAME}-${PROJECT_VERSION} [DEBUG]")
    set(CMAKE_BUILD_TYPE Debug)
    set(EXTRAS_CPP_TESTS ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
  else()
    print(STATUS "Building ${PROJECT_NAME}-${PROJECT_VERSION} [RELEASE]")
    set(EXTRAS_CPP_TESTS OFF)
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
  endif()

endif()

#
# NOTE: Output build param information
#
print(STATUS "edit your ~/.bashrc and set")
print(STATUS "export LD_LIBRARY_PATH=/usr/local/lib")
print(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
print(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")

#
# NOTE: "Include 3rd party libraries, Perry and I maintain an open-source extras C++ library, which
# is used extensively in extras_cpp, it comes bundled with spdlog, cpr, and nlohmann json. extras has
# project options that allow us to control how other libraries it includes are built. for example we
# can tell extras to build spdlog as a static library (for faster compile times) by settings
# MAKE_SPDLOG_SHARED OFF" -- Matt Williams, October, 2021
#
if (MAKE32BITONLY)
set(EXTRAS_32_64_MODE "MAKE32BITONLY")
elseif(MAKE64BITONLY)
set(EXTRAS_32_64_MODE "MAKE64BITONLY")
else()
set(EXTRAS_32_64_MODE "MAKEBOTH32AND64")
endif()

CPMAddPackage(
  NAME injections
  GITHUB_REPOSITORY perriera/injections
  VERSION 1.1.8
  OPTIONS "MAKE_SPDLOG_SHARED OFF"
  OPTIONS "MAKE_EXTRAS_LIBRARY_ONLY ON"
  OPTIONS "MAKE_INJECTIONS_LIBRARY_ONLY ON"
#  OPTIONS "MAKE_INJECTIONS_LIBRARY_TOOLS ON"
  OPTIONS "${EXTRAS_32_64_MODE} ON"
)

if(injections_ADDED)
  #
  # NOTE:  enable c++11 to avoid compilation errors, and force spdlog into release build
  #
  print(STATUS "Configuring injections build properties")
  # set_target_properties(injections PROPERTIES CMAKE_BUILD_TYPE Release)
else()
  print(WARNING "injections was not configured properly")
endif()

#
# HACK: glob src files and header files
#
file(GLOB_RECURSE EXTRAS_CPP_HEADERS CONFIGURE_DEPENDS "${INCLUDES}/${PROJECT_NAME}/*.hpp")
file(GLOB_RECURSE EXTRAS_CPP_SOURCE CONFIGURE_DEPENDS "${SOURCES}/*.cpp")

#
# NOTE: declare libraries here all source should be placed into a single library, (whether they be
# shared or static)
#

# 
# EXTRAS_CPP_THIRD_PARTY_LIBRARIES
#
# list here any 3rd party libraries that you want that were
# installed using sudo apt install ....
#
# set(EXTRAS_CPP_THIRD_PARTY_LIBRARIES ldap gcrypt gnutls uuid microhttpd)
set(EXTRAS_CPP_LIBS_COMMON stdc++fs ${EXTRAS_CPP_THIRD_PARTY_LIBRARIES} Threads::Threads)

if (MAKE32BIT)
set(EXTRAS_CPP_LIBS_NEEDED_i386 extras_i386 injections_i386 ${EXTRAS_CPP_LIBS_COMMON})
add_library(${PROJECT_NAME}_i386 SHARED ${EXTRAS_CPP_HEADERS} ${EXTRAS_CPP_SOURCE})
set_target_properties(${PROJECT_NAME}_i386 PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME}_i386 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" ${ORACLE_INCLUDE})
target_link_libraries(${PROJECT_NAME}_i386 PRIVATE ${EXTRAS_CPP_LIBS_NEEDED_i386})
target_compile_options(${PROJECT_NAME}_i386 PUBLIC -m32)
target_link_options(${PROJECT_NAME}_i386 PRIVATE -m32)
endif()

if (MAKE64BIT)
set(EXTRAS_CPP_LIBS_NEEDED extras injections ${EXTRAS_CPP_LIBS_COMMON})
add_library(${PROJECT_NAME} SHARED ${EXTRAS_CPP_HEADERS} ${EXTRAS_CPP_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" ${ORACLE_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTRAS_CPP_LIBS_NEEDED})
endif()

#
# NOTE: declare unit test cases here all source should have adequate test cases whether they be mock
# or unit tests, (or both)
#

#
# ${ORACLE_INCLUDE} is included below even though there may not be any .cmake file under the current
# cmake/ folder to define this macro. It is kept in place here for your future reference should you
# decide to add either your own Oracle macro or another 3rd party library
#

if (NOT MAKE_EXTRAS_CPP_LIBRARY_ONLY)
  if(EXTRAS_CPP_TESTS)
    print(STATUS "Building tests")
    file(GLOB_RECURSE EXTRAS_CPP_TESTS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/interfaces/*.cpp")
    set(TEST_EXEC "run-unittests-${PROJECT_NAME}")

    if (MAKE32BIT)
      add_executable(${TEST_EXEC}_i386 ${EXTRAS_CPP_TESTS})
      target_include_directories(${TEST_EXEC}_i386 PUBLIC ${INCLUDES} ${ORACLE_INCLUDE})
      target_link_libraries(${TEST_EXEC}_i386 ${PROJECT_NAME}_i386 ${EXTRAS_CPP_LIBS_NEEDED_i386})
      target_compile_options(${TEST_EXEC}_i386 PUBLIC -m32)
      target_link_options(${TEST_EXEC}_i386 PRIVATE -m32)
    endif()
    if (MAKE64BIT)
      add_executable(${TEST_EXEC} ${EXTRAS_CPP_TESTS})
      target_include_directories(${TEST_EXEC} PUBLIC ${INCLUDES} ${ORACLE_INCLUDE})
      target_link_libraries(${TEST_EXEC} PRIVATE ${PROJECT_NAME} ${EXTRAS_CPP_LIBS_NEEDED})
    endif()

  endif()
endif()

#
# TODO: declare example client usage application code here, this is where regression tests should
# ultimately be written. as well, this make file uses a GLOB_RECURSE macro which automatically 
# includes ALL headers and sources under include/ and src/. So, to keep two or more main() 
# declarations seperate, we place any sources that have a main() in the instances/ folder
#
if( NOT MAKE_EXTRAS_CPP_LIBRARY_ONLY OR MAKE_EXTRAS_CPP_LIBRARY_TOOLS)

  #
  # extras_cpp_app
  #
  if (MAKE32BIT)
    add_executable(extras_cpp_app_i386 instances/extras_cpp_app.cpp) 
    target_include_directories(extras_cpp_app_i386 PUBLIC ${INCLUDES} ${ORACLE_INCLUDE})
    target_link_libraries(extras_cpp_app_i386 PRIVATE ${PROJECT_NAME}_i386 ${EXTRAS_CPP_LIBS_NEEDED_i386})
    target_compile_options(extras_cpp_app_i386 PUBLIC -m32)
    target_link_options(extras_cpp_app_i386 PRIVATE -m32)
  endif()
  if (MAKE64BIT)
    add_executable(extras_cpp_app instances/extras_cpp_app.cpp) 
    target_include_directories(extras_cpp_app PUBLIC ${INCLUDES} ${ORACLE_INCLUDE})
    target_link_libraries(extras_cpp_app PRIVATE ${PROJECT_NAME} ${EXTRAS_CPP_LIBS_NEEDED})
  endif()

  # #
  # # your_app_here (or use the one above)
  # #
  # if (MAKE32BIT)
  #   add_executable(your_app_here_i386 instances/your_app_here.cpp) 
  #   target_include_directories(extras_cpp_app_i386 PUBLIC ${INCLUDES} ${ORACLE_INCLUDE})
  #   target_link_libraries(extras_cpp_app_i386 PRIVATE ${PROJECT_NAME}_i386 ${EXTRAS_CPP_LIBS_NEEDED_i386})
  #   target_compile_options(extras_cpp_app_i386 PUBLIC -m32)
  #   target_link_options(extras_cpp_app_i386 PRIVATE -m32)
  # endif()
  # if (MAKE64BIT)
  #   add_executable(your_app_here instances/your_app_here.cpp) 
  #   target_include_directories(extras_cpp_app PUBLIC ${INCLUDES} ${ORACLE_INCLUDE})
  #   target_link_libraries(extras_cpp_app PRIVATE ${PROJECT_NAME} ${EXTRAS_CPP_LIBS_NEEDED})
  # endif()

endif()

#
# NOTE: Install all shared libraries
#
# install(TARGETS ${PROJECT_NAME}_i386 LIBRARY DESTINATION lib)
if (MAKE32BIT||MAKE64BIT)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
endif()
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

#
#     #
#     # NOTE: Install all shared libraries & executables, (sample)
#     #
#     install(TARGETS 
#          parcel
#          socketpool_client socketpool_server
#          uploader_client uploader_server 
#          vendor_client vendor_server 
#          downloader_client downloader_server 
#          ${PROJECT_NAME}
#          LIBRARY DESTINATION lib
#          RUNTIME DESTINATION bin)
#     install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
#

#
# NOTE: if the compiler supports iter-procedural optimization, turn it on
#
check_ipo_supported(RESULT result OUTPUT output)
if(result)
  print(STATUS "Building ${PROJECT_NAME} with Interprocedural Optimization")
  if (MAKE32BIT||MAKE64BIT)
    set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()
else()
  print(WARNING "IPO is not supported: ${output}")
endif()

if (MAKE32BIT)
  set_target_properties(
    ${PROJECT_NAME}_i386 
    PROPERTIES VERSION 
    ${${PROJECT_NAME}_VERSION} SOVERSION
    ${${PROJECT_NAME}_VERSION_MAJOR}
  )
endif()

if (MAKE64BIT)
  set_target_properties(
    ${PROJECT_NAME} 
    PROPERTIES VERSION 
    ${${PROJECT_NAME}_VERSION} SOVERSION
    ${${PROJECT_NAME}_VERSION_MAJOR}
  )
endif()
