
add_library(Physics INTERFACE)

target_include_directories(Physics INTERFACE include)

if(NOT ${SKIP_PHYSICS_INSTALL})
    install(DIRECTORY include/ph DESTINATION include)
endif()

