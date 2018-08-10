cmake_minimum_required(VERSION  3.0.0)

project(AppFramework VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

option(ENABLE_TESTS "Enable unit testing using googletest" OFF)

if(ENABLE_TESTS)
  include(SetUpGoogleTest)
endif(ENABLE_TESTS)

include_directories(${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(Core)
