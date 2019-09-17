
set(PHYSICS_CORE_SRC
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
physics_dims_codegen(
    templates/AllDims.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/AllDims.hpp"
)
physics_dims_codegen(
    templates/Config.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Config.hpp"
)
physics_dim_codegen(
    templates/Dimension.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/@Dim@.hpp"
    PHYSICS_CORE_GEN_HPP
)

set(PHYSICS_CORE_HPP
    ${PHYSICS_CORE_SRC}
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/AllDims.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Config.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Version.hpp"
    ${PHYSICS_CORE_GEN_HPP}
)

# generating an empty static lib instead of an INTERFACE target
# otherwise code generation is not triggered
add_library(PhysicsCore STATIC
    ${PHYSICS_CORE_HPP}
    Empty.cpp
)

set_target_properties(PhysicsCore PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(PhysicsCore PUBLIC cxx_std_17)
target_include_directories(PhysicsCore PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include")
set_property(TARGET PhysicsCore PROPERTY PUBLIC_HEADER ${PHYSICS_CORE_HPP})

install(TARGETS PhysicsCore
    PUBLIC_HEADER DESTINATION include/si
    ARCHIVE DESTINATION lib
)

add_library(Physics::Core ALIAS PhysicsCore)

add_subdirectory(tests)
