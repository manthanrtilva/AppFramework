# cmake -DENABLE_TESTS=ON -DBOOST_ROOT=D:\Download\Compressed\boost_1_67_0 ..\code\
cmake_minimum_required(VERSION  3.0.0)

project(AppFramework VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

option(ENABLE_TESTS "Enable unit testing using googletest" OFF)

if(ENABLE_TESTS)
  include(SetUpGoogleTest)
endif(ENABLE_TESTS)
include(SetUpJsonCpp)
include(AddPlugin)
find_package(Boost REQUIRED system)

include_directories(${CMAKE_CURRENT_LIST_DIR})
set(Core_Inc_DIR ${CMAKE_CURRENT_LIST_DIR}/Core/inc)
if (WIN32)
add_definitions(-D__FUNC__=__FUNCTION__)
endif()
add_subdirectory(Core)
add_subdirectory(Application)
