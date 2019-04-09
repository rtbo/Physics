
physics_dim_codegen(
    templates/DimLabel.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/siui/@Dim@Label.hpp"
    PHYSICS_WIDGETS_GEN_HPP
)
physics_dims_codegen(
    templates/DimLabel.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/DimLabel.cpp"
)
physics_dim_codegen(
    templates/DimSpinBox.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/siui/@Dim@SpinBox.hpp"
    PHYSICS_WIDGETS_GEN_HPP
)
physics_dims_codegen(
    templates/DimSpinBox.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/DimSpinBox.cpp"
)

set(PHYSICS_WIDGETS_HPP
    include/siui/API.hpp
    "${PHYSICS_WIDGETS_GEN_HPP}"
)

add_library(PhysicsWidgets STATIC
    "templates/DimLabel.hpp.j2"
    "templates/DimLabel.cpp.j2"
    "templates/DimSpinBox.hpp.j2"
    "templates/DimSpinBox.cpp.j2"

    "${CMAKE_CURRENT_BINARY_DIR}/DimLabel.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/DimSpinBox.cpp"

    ${PHYSICS_WIDGETS_HPP}
)

target_include_directories(PhysicsWidgets PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries(PhysicsWidgets PUBLIC Physics::Core Qt5::Widgets)
set_property(TARGET PhysicsWidgets PROPERTY AUTOMOC ON)
set_property(TARGET PhysicsWidgets PROPERTY PUBLIC_HEADER ${PHYSICS_WIDGETS_HPP})

install(TARGETS PhysicsWidgets
    PUBLIC_HEADER DESTINATION include/siui
    LIBRARY DESTINATION lib
)

add_library(Physics::Widgets ALIAS PhysicsWidgets)
