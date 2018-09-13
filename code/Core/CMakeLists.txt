

add_library(Core SHARED src/Property.cpp src/Socket.cpp src/Component.cpp)
target_include_directories(Core PUBLIC ${Core_Inc_DIR} ${Boost_INCLUDE_DIRS})
if (UNIX)
    target_link_libraries(Core pthread dl)
elseif(MSVC)
  target_compile_definitions(Core PRIVATE EXPORT_API=1)
endif (UNIX)
add_subdirectory(sample)
if(ENABLE_TESTS)
  add_subdirectory(test)
endif(ENABLE_TESTS)
