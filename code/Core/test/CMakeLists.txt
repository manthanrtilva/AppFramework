

add_executable(test_property PropertyTest.cpp)
target_include_directories(test_property PUBLIC ${gtest_SOURCE_DIR}/include)
target_include_directories(test_property PUBLIC ${Core_Inc_DIR})
target_link_libraries(test_property Core gtest_main)

add_executable(test_socket SocketTest.cpp)
target_include_directories(test_socket PUBLIC ${gtest_SOURCE_DIR}/include)
target_include_directories(test_socket PUBLIC ${Core_Inc_DIR})
target_link_libraries(test_socket Core gtest_main)
