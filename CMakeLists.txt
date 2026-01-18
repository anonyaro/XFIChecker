# Copyright (C) 2026 anonyaro (github.com/anonyaro)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# --- MANDATORY ATTRIBUTION NOTICE ---
# In accordance with Section 7(b) of the GNU AGPLv3, the following
# appropriate legal notices must be preserved and displayed in the
# user interface of any work incorporating this software:
#
# Author: anonyaro (github.com/anonyaro)
# Project: XFIChecker (https://github.com/anonyaro/XFIChecker)
# Support: https://dalink.to/xenyaro

cmake_minimum_required (VERSION 3.15)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
endif()

project ("xfichecker")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(XFICHECKER_SOURCES "xfichecker.cpp")

# --- build testing switch ---
option(BUILD_TESTING "Build unit tests" ON)

# --- lib type ---
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(MY_LIB_TYPE SHARED)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    set(MY_LIB_TYPE STATIC)
endif()

# --- compiler flags ---
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(MSVC)
    add_compile_options(/permissive- /Zc:__cplusplus)
endif()

# --- msvc config ---
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "$<IF:$<CONFIG:Debug>,MultiThreadedDebugDLL,MultiThreaded>")
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<CONFIG:Debug,RelWithDebInfo>,EditAndContinue,ProgramDatabase>")
endif()

# --- logic lib ---
add_library(xfichecker_libs ${MY_LIB_TYPE} 
    "core/xfiler.cpp" 
    "CliUI/cli.cpp"
    "HashUtils/hashing.cpp"
)

target_include_directories(xfichecker_libs PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/CliUI"
    "${CMAKE_CURRENT_SOURCE_DIR}/HashUtils"
    "${CMAKE_CURRENT_SOURCE_DIR}/modules"
)

# --- main app ---
if(WIN32)
    list(APPEND XFICHECKER_SOURCES "resources/res.rc")
endif()

add_executable (XFIChecker ${XFICHECKER_SOURCES})
target_link_libraries(XFIChecker PRIVATE xfichecker_libs)

if(UNIX AND NOT APPLE AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_options(XFIChecker PRIVATE "-static-libgcc" "-static-libstdc++")
endif()

# --- gtest ---
if(BUILD_TESTING)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/externals/googletest/CMakeLists.txt")
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        add_subdirectory("externals/googletest")
        
        add_executable(xfichecker_unit_tests "unit_tests/unit_test.cpp")
        target_link_libraries(xfichecker_unit_tests PRIVATE xfichecker_libs gtest_main gtest)
        
        enable_testing()
        include(GoogleTest)
        gtest_discover_tests(xfichecker_unit_tests)
        message(STATUS "GTests enabled")
    else()
        message(WARNING "GTest not found")
    endif()
endif()

# --- NOTICE ---
add_custom_command(TARGET XFIChecker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/NOTICE"
        "$<TARGET_FILE_DIR:XFIChecker>/NOTICE"
    COMMENT "Copying NOTICE to executable directory"
    VERBATIM
)

source_group("Legal Documents" FILES NOTICE LICENSE)

install(TARGETS XFIChecker DESTINATION bin)
install(FILES NOTICE LICENSE DESTINATION bin)
