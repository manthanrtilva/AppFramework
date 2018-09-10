
macro(AddPlugin name files)
  add_library(${name} SHARED ${files})
  set_target_properties(${name} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugin")
  set_target_properties(${name} PROPERTIES SUFFIX ".plug")
  target_include_directories(${name} PUBLIC ${Core_Inc_DIR})
  target_link_libraries(${name} Core ${Boost_LIBRARIES})
endmacro(AddPlugin)
