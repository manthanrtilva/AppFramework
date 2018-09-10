

add_library(Core STATIC src/Property.cpp src/Socket.cpp src/Component.cpp)
target_include_directories(Core PUBLIC ${Core_Inc_DIR})
add_subdirectory(sample)
if(ENABLE_TESTS)
  add_subdirectory(test)
endif(ENABLE_TESTS)
