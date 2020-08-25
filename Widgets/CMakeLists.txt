
si_units_dim_codegen(
    templates/DimLabel.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/siui/@Dim@Label.hpp"
    SI_UNITS_WIDGETS_GEN_HPP
)
si_units_dims_codegen(
    templates/DimLabel.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/DimLabel.cpp"
)
si_units_dim_codegen(
    templates/DimSpinBox.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/siui/@Dim@SpinBox.hpp"
    SI_UNITS_WIDGETS_GEN_HPP
)
si_units_dims_codegen(
    templates/DimSpinBox.cpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/DimSpinBox.cpp"
)

set(SI_UNITS_WIDGETS_HPP
    include/siui/API.hpp
    "${SI_UNITS_WIDGETS_GEN_HPP}"
)

add_library(SI_Units_Widgets STATIC
    "templates/DimLabel.hpp.j2"
    "templates/DimLabel.cpp.j2"
    "templates/DimSpinBox.hpp.j2"
    "templates/DimSpinBox.cpp.j2"

    "${CMAKE_CURRENT_BINARY_DIR}/DimLabel.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/DimSpinBox.cpp"

    ${SI_UNITS_WIDGETS_HPP}
)

target_include_directories(SI_Units_Widgets PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries(SI_Units_Widgets PUBLIC SI_Units::Core Qt5::Widgets)
set_property(TARGET SI_Units_Widgets PROPERTY AUTOMOC ON)
set_property(TARGET SI_Units_Widgets PROPERTY PUBLIC_HEADER ${SI_UNITS_WIDGETS_HPP})

install(TARGETS SI_Units_Widgets
    PUBLIC_HEADER DESTINATION include/siui
    ARCHIVE DESTINATION lib
)

add_library(SI_Units::Widgets ALIAS SI_Units_Widgets)
