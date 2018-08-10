
add_executable(sample_property Property.cpp)
target_include_directories(sample_property PUBLIC ${Core_Inc_DIR})
target_link_libraries(sample_property Core)

add_executable(sample_socket Socket.cpp)
target_include_directories(sample_socket PUBLIC ${Core_Inc_DIR})
target_link_libraries(sample_socket Core)

add_executable(sample_component Component.cpp)
target_include_directories(sample_component PUBLIC ${Core_Inc_DIR})
target_link_libraries(sample_component Core)
