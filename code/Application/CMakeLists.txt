


add_executable(app src/Main.cpp)
set(Core_Inc_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)
target_include_directories(Core PUBLIC ${Core_Inc_DIR})
