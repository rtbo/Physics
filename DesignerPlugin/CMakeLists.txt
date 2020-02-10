
option(BUILD_DESIGNER_ICONS "Whether to generate SVG then PNG icons for Qt Designer plugin" OFF)

if (BUILD_DESIGNER_ICONS)

    find_program(INKSCAPE inkscape)

    if(NOT INKSCAPE)
        message(FATAL_ERROR "Inkscape not found! Cannot generate png icons")
    endif()

    set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
    include(SvgToPng)

    set(PHYSICS_DESIGNER_QRC "${CMAKE_CURRENT_BINARY_DIR}/icons.qrc")

    physics_dim_codegen(
        templates/Label.svg.j2
        "${CMAKE_CURRENT_BINARY_DIR}/icons/@Dim@Label.svg"
        PHYSICS_DESIGNER_SVG
    )
    physics_dim_codegen(
        templates/SpinBox.svg.j2
        "${CMAKE_CURRENT_BINARY_DIR}/icons/@Dim@SpinBox.svg"
        PHYSICS_DESIGNER_SVG
    )
    foreach(Svg ${PHYSICS_DESIGNER_SVG})
        svg_to_png("${Svg}" "${CMAKE_CURRENT_BINARY_DIR}/icons" PHYSICS_DESIGNER_PNG)
    endforeach()

    physics_dims_codegen(
        templates/icons.qrc.j2
        ${PHYSICS_DESIGNER_QRC}
        "${PHYSICS_DESIGNER_PNG}"
    )

    set(HAVE_ICONS_QRC 1)
else()
    unset(HAVE_ICONS_QRC)
endif()

configure_file(
    templates/Config.hpp.in
    "${CMAKE_CURRENT_BINARY_DIR}/Config.hpp"
)

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
    "${CMAKE_CURRENT_BINARY_DIR}/Config.hpp"
    ${PHYSICS_DESIGNER_PNG}
    ${PHYSICS_DESIGNER_QRC}
    )
set_property(TARGET PhysicsDesigner APPEND PROPERTY AUTOGEN_TARGET_DEPENDS ${PHYSICS_DESIGNER_PNG})

target_link_libraries(PhysicsDesigner Physics::Widgets Qt5::Designer)
set_property(TARGET PhysicsDesigner PROPERTY AUTOMOC ON)
set_property(TARGET PhysicsDesigner PROPERTY AUTORCC ON)

install(TARGETS PhysicsDesigner
    LIBRARY DESTINATION bin/plugins/designer
    RUNTIME DESTINATION bin/plugins/designer
)

add_library(Physics::DesignerPlugin ALIAS PhysicsDesigner)
