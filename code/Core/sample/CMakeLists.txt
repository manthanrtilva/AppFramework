
add_executable(sample_property Property.cpp)
target_include_directories(sample_property PUBLIC ${Core_Inc_DIR})
target_link_libraries(sample_property Core)

add_executable(sample_socket Socket.cpp)
target_include_directories(sample_socket PUBLIC ${Core_Inc_DIR})
target_link_libraries(sample_socket Core)

add_executable(sample_component Component.cpp)
target_include_directories(sample_component PUBLIC ${Core_Inc_DIR})
target_link_libraries(sample_component Core)

add_executable(sample_commandline CommandLine.cpp)
target_include_directories(sample_commandline PUBLIC ${Core_Inc_DIR})
# target_link_libraries(sample_commandline)

link_directories(${Boost_LIBRARY_DIRS})

AddPlugin(plugin1 plugin1.cpp)
target_include_directories(plugin1 PUBLIC ${Boost_INCLUDE_DIRS})
AddPlugin(plugin2 plugin2.cpp)
target_include_directories(plugin2 PUBLIC ${Boost_INCLUDE_DIRS})

AddPlugin(SinWaveGenerator SinWaveGenerator.cpp)
target_include_directories(SinWaveGenerator PUBLIC ${Boost_INCLUDE_DIRS})

add_executable(sample_pluginrunner PluginRunner.cpp)
target_include_directories(sample_pluginrunner PUBLIC ${Core_Inc_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(sample_pluginrunner Core ${Boost_LIBRARIES})

add_executable(sample_sinewaverunner SineWaveRunner.cpp)
target_include_directories(sample_sinewaverunner PUBLIC ${Core_Inc_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(sample_sinewaverunner Core ${Boost_LIBRARIES})
