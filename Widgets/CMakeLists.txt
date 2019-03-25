
physics_dim_codegen(
    templates/DimLabel.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/siui/@Dim@Label.hpp"
    PHYSICS_WIDGETS_ITEMS
)
physics_dim_codegen(
    templates/DimLabel.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/@Dim@Label.cpp"
    PHYSICS_WIDGETS_ITEMS
)
# physics_item_codegen(
#     templates/ItemSpinBox.hpp.j2
#     "${CMAKE_CURRENT_BINARY_DIR}/include/siui/@Dim@SpinBox.hpp"
#     PHYSICS_WIDGETS_ITEMS
# )
# physics_item_codegen(
#     templates/ItemSpinBox.cpp.j2
#     "${CMAKE_CURRENT_BINARY_DIR}/@Dim@SpinBox.cpp"
#     PHYSICS_WIDGETS_ITEMS
# )
#     "templates/ItemSpinBox.hpp.j2"
#     "templates/ItemSpinBox.cpp.j2"

add_library(PhysicsWidgets STATIC
    "include/siui/API.hpp"
    "templates/DimLabel.hpp.j2"
    "templates/DimLabel.cpp.j2"
    ${PHYSICS_WIDGETS_ITEMS})

target_include_directories(PhysicsWidgets PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries(PhysicsWidgets PUBLIC Physics::Core Qt5::Widgets)
set_property(TARGET PhysicsWidgets PROPERTY AUTOMOC ON)

add_library(Physics::Widgets ALIAS PhysicsWidgets)
