
add_library(QPhysicsDesigner SHARED
    QPhysicsDesignerPlugin.hpp
    QPhysicsDesignerPlugin.cpp
    icons.qrc)

target_link_libraries(QPhysicsDesigner QPhysicsUI Qt5::Designer)

if(NOT ${SKIP_PHYSICSDESIGNER_INSTALL})
    install(TARGETS QPhysicsDesigner
        RUNTIME DESTINATION plugins/designer)
endif()
