cmake_minimum_required(VERSION 3.3)

project(sushi)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

set (BOOST_ROOT /usr/local/opt/boost)
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package (Boost 1.59.0 REQUIRED COMPONENTS system filesystem thread regex date_time unit_test_framework)
if (Boost_FOUND)
    message(STATUS "-- Found Boost Libaray: ${Boost_LIBRARIES}")
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
else()
    message(FATAL_ERROR "-- Boost Libaray Not Found")
endif ()

enable_testing(true)

include_directories(.)

add_subdirectory(timer)
add_subdirectory(daytime)
# add_subdirectory(server)
add_subdirectory(test)
