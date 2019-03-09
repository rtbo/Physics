
physics_glob_codegen(
    templates/QPhysicsDesignerPlugin.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/QPhysicsDesignerPlugin.hpp"
)
physics_glob_codegen(
    templates/QPhysicsDesignerPlugin.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/QPhysicsDesignerPlugin.cpp"
)

add_library(PhysicsDesigner SHARED
    "${CMAKE_CURRENT_BINARY_DIR}/QPhysicsDesignerPlugin.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/QPhysicsDesignerPlugin.cpp"
    icons.qrc)

target_link_libraries(PhysicsDesigner Physics::Widgets Qt5::Designer)
set_property(TARGET PhysicsDesigner PROPERTY AUTOMOC ON)

add_library(Physics::DesignerPlugin ALIAS PhysicsDesigner)
