

add_executable(sample_property Property.cpp)
target_include_directories(sample_property PUBLIC ${Core_Inc_DIR})
target_link_libraries(sample_property Core)
