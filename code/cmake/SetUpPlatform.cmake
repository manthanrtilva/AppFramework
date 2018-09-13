
if (UNIX)
    add_definitions(-DUNIX)
elseif (MSVC)
    add_definitions(-DMSVC)
endif (UNIX)
