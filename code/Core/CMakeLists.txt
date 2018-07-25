

add_library(Core STATIC src/Property.cpp)
set(Core_Inc_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)
target_include_directories(Core PUBLIC ${Core_Inc_DIR})

add_subdirectory(sample)
add_subdirectory(test)
