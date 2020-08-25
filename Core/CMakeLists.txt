
set(SI_UNITS_CORE_SRC
    include/si/Constants.hpp
    include/si/Conversion.hpp
    include/si/Dim.hpp
    include/si/Trigo.hpp
    include/si/Unit.hpp
    include/si/Value.hpp
    include/si/Physics.hpp

    templates/AllDims.hpp.j2
    templates/Config.hpp.j2
    templates/Dimension.hpp.j2
)

configure_file(
    templates/Version.hpp.in
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Version.hpp"
)
si_units_dims_codegen(
    templates/AllDims.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/AllDims.hpp"
)
si_units_dims_codegen(
    templates/Config.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Config.hpp"
)
si_units_dim_codegen(
    templates/Dimension.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/@Dim@.hpp"
    SI_UNITS_CORE_GEN_HPP
)

set(SI_UNITS_CORE_HPP
    ${SI_UNITS_CORE_SRC}
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/AllDims.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Config.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Version.hpp"
    ${SI_UNITS_CORE_GEN_HPP}
)

# generating an empty static lib instead of an INTERFACE target
# otherwise code generation is not triggered
add_library(SI_Units_Core STATIC
    ${SI_UNITS_CORE_HPP}
    Empty.cpp
)

set_target_properties(SI_Units_Core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(SI_Units_Core PUBLIC cxx_std_17)
target_include_directories(SI_Units_Core PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include")
set_property(TARGET SI_Units_Core PROPERTY PUBLIC_HEADER ${SI_UNITS_CORE_HPP})

install(TARGETS SI_Units_Core
    PUBLIC_HEADER DESTINATION include/si
    ARCHIVE DESTINATION lib
)

add_library(SI_Units::Core ALIAS SI_Units_Core)

add_subdirectory(tests)
