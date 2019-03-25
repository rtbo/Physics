
set(PHYSICS_CORE_SRC
    include/si/Constants.hpp
    include/si/Dim.hpp
    include/si/Operations.hpp
    include/si/Unit.hpp
    include/si/Value.hpp

    templates/Config.hpp.j2
    templates/Dimension.hpp.j2
)

configure_file(
    templates/Version.hpp.in
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Version.hpp"
)
physics_dims_codegen(
    templates/Config.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Config.hpp"
)
physics_dim_codegen(
    templates/Dimension.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/@Dim@.hpp"
    PHYSICS_CORE_DIMS
)

# generating an empty static lib instead of an INTERFACE target
# otherwise code generation is not triggered
add_library(Core STATIC
    ${PHYSICS_CORE_SRC}
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Config.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/si/Version.hpp"
    ${PHYSICS_CORE_DIMS}

    Empty.cpp)

set_target_properties(Core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(Core PUBLIC cxx_std_17)
target_include_directories(Core PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include")

add_library(Physics::Core ALIAS Core)

add_subdirectory(tests)
