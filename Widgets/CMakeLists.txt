
physics_item_codegen(
    templates/QItemLabel.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/Q@Item@Label.hpp"
    PHYSICS_WIDGETS_ITEMS
)
physics_item_codegen(
    templates/QItemLabel.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/Q@Item@Label.cpp"
    PHYSICS_WIDGETS_ITEMS
)
physics_item_codegen(
    templates/QItemSpinBox.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/Q@Item@SpinBox.hpp"
    PHYSICS_WIDGETS_ITEMS
)
physics_item_codegen(
    templates/QItemSpinBox.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/Q@Item@SpinBox.cpp"
    PHYSICS_WIDGETS_ITEMS
)

add_library(PhysicsWidgets STATIC
    "include/QPhysicsUI_API.hpp"
    "templates/QItemLabel.hpp.j2"
    "templates/QItemSpinBox.hpp.j2"
    "templates/QItemLabel.cpp.j2"
    "templates/QItemSpinBox.cpp.j2"
    ${PHYSICS_WIDGETS_ITEMS})

target_include_directories(PhysicsWidgets PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries(PhysicsWidgets PUBLIC Physics::Core Qt5::Widgets)
set_property(TARGET PhysicsWidgets PROPERTY AUTOMOC ON)

add_library(Physics::Widgets ALIAS PhysicsWidgets)
