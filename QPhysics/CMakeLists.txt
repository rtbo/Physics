
add_library(QPhysics STATIC
    include/QPhysics.hpp
    QPhysics.cpp)

target_include_directories(QPhysics PUBLIC include)

target_link_libraries(QPhysics Physics Qt5::Core)

if(NOT ${SKIP_PHYSICS_INSTALL})
    install(TARGETS QPhysics
        ARCHIVE DESTINATION lib)
    install(FILES include/QPhysics.hpp DESTINATION include)
endif()
