
option(BUILD_DESIGNER_ICONS "Whether to generate SVG then PNG icons for Qt Designer plugin" OFF)

if (BUILD_DESIGNER_ICONS)

    find_program(INKSCAPE inkscape)

    if(NOT INKSCAPE)
        message(FATAL_ERROR "Inkscape not found! Cannot generate png icons")
    endif()

    set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
    include(SvgToPng)

    set(SI_UNITS_DESIGNER_QRC "${CMAKE_CURRENT_BINARY_DIR}/icons.qrc")

    si_units_dim_codegen(
        templates/Label.svg.j2
        "${CMAKE_CURRENT_BINARY_DIR}/icons/@Dim@Label.svg"
        SI_UNITS_DESIGNER_SVG
    )
    si_units_dim_codegen(
        templates/SpinBox.svg.j2
        "${CMAKE_CURRENT_BINARY_DIR}/icons/@Dim@SpinBox.svg"
        SI_UNITS_DESIGNER_SVG
    )
    foreach(Svg ${SI_UNITS_DESIGNER_SVG})
        svg_to_png("${Svg}" "${CMAKE_CURRENT_BINARY_DIR}/icons" SI_UNITS_DESIGNER_PNG)
    endforeach()

    si_units_dims_codegen(
        templates/icons.qrc.j2
        ${SI_UNITS_DESIGNER_QRC}
        "${SI_UNITS_DESIGNER_PNG}"
    )

    set(HAVE_ICONS_QRC 1)
else()
    unset(HAVE_ICONS_QRC)
endif()

configure_file(
    templates/Config.hpp.in
    "${CMAKE_CURRENT_BINARY_DIR}/Config.hpp"
)

si_units_dims_codegen(
    templates/SI_Units_DesignerPlugin.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/SI_Units_DesignerPlugin.hpp"
)
si_units_dims_codegen(
    templates/SI_Units_DesignerPlugin.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/SI_Units_DesignerPlugin.cpp"
)
add_library(SI_Units_Designer SHARED
    templates/SI_Units_DesignerPlugin.hpp.j2
    templates/SI_Units_DesignerPlugin.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/SI_Units_DesignerPlugin.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/SI_Units_DesignerPlugin.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/Config.hpp"
    ${SI_UNITS_DESIGNER_PNG}
    ${SI_UNITS_DESIGNER_QRC}
    )
set_property(TARGET SI_Units_Designer APPEND PROPERTY AUTOGEN_TARGET_DEPENDS ${SI_UNITS_DESIGNER_PNG})

target_link_libraries(SI_Units_Designer SI_Units::Widgets Qt5::Designer)
set_property(TARGET SI_Units_Designer PROPERTY AUTOMOC ON)
set_property(TARGET SI_Units_Designer PROPERTY AUTORCC ON)

install(TARGETS SI_Units_Designer
    LIBRARY DESTINATION bin/plugins/designer
    RUNTIME DESTINATION bin/plugins/designer
)

add_library(SI_Units::DesignerPlugin ALIAS SI_Units_Designer)
