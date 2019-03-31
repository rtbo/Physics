
physics_dim_codegen(
    templates/DimLabel.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/siui/@Dim@Label.hpp"
    PHYSICS_WIDGETS_FILES
)
physics_dims_codegen(
    templates/DimLabel.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/DimLabel.cpp"
)
physics_dim_codegen(
    templates/DimSpinBox.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/siui/@Dim@SpinBox.hpp"
    PHYSICS_WIDGETS_FILES
)
physics_dims_codegen(
    templates/DimSpinBox.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/DimSpinBox.cpp"
)

add_library(PhysicsWidgets STATIC
    "include/siui/API.hpp"
    "templates/DimLabel.hpp.j2"
    "templates/DimLabel.cpp.j2"
    "templates/DimSpinBox.hpp.j2"
    "templates/DimSpinBox.cpp.j2"

    "${CMAKE_CURRENT_BINARY_DIR}/DimLabel.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/DimSpinBox.cpp"

    ${PHYSICS_WIDGETS_FILES})

target_include_directories(PhysicsWidgets PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries(PhysicsWidgets PUBLIC Physics::Core Qt5::Widgets)
set_property(TARGET PhysicsWidgets PROPERTY AUTOMOC ON)

add_library(Physics::Widgets ALIAS PhysicsWidgets)
