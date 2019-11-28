
physics_dims_codegen(
    templates/PhysicsDesignerPlugin.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/PhysicsDesignerPlugin.hpp"
)
physics_dims_codegen(
    templates/PhysicsDesignerPlugin.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/PhysicsDesignerPlugin.cpp"
)

add_library(PhysicsDesigner SHARED
    templates/PhysicsDesignerPlugin.hpp.j2
    templates/PhysicsDesignerPlugin.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/PhysicsDesignerPlugin.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/PhysicsDesignerPlugin.cpp"
    icons.qrc)

target_link_libraries(PhysicsDesigner Physics::Widgets Qt5::Designer)
set_property(TARGET PhysicsDesigner PROPERTY AUTOMOC ON)
set_property(TARGET PhysicsDesigner PROPERTY AUTORCC ON)

install(TARGETS PhysicsDesigner
    LIBRARY DESTINATION bin/plugins/designer
    RUNTIME DESTINATION bin/plugins/designer
)

add_library(Physics::DesignerPlugin ALIAS PhysicsDesigner)
