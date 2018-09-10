

add_executable(app src/Main.cpp)
target_include_directories(app PUBLIC ${Core_Inc_DIR} ${JSONCPP_INC_DIR})
target_link_libraries(app jsoncpp_lib_static Core)
