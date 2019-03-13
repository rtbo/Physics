
set(PHYSICS_CORE_SRC
    include/ph/Constants.hpp
    include/ph/Operators.hpp
    include/ph/Physics.hpp
    include/ph/Zero.hpp

    templates/_IncludeAll.hpp.j2
    templates/FwdDecl.hpp.j2
    templates/Item.hpp.j2
    templates/Literals.hpp.j2

    templates/Config.hpp.in
    templates/Version.hpp.in
)

set(SI_CORE_SRC
    include/si/Dim.hpp
    include/si/Operations.hpp
    include/si/Unit.hpp
    include/si/Value.hpp

    templates/Dimension.hpp.j2
)

configure_file(
    templates/Config.hpp.in
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/Config.hpp"
)
configure_file(
    templates/Version.hpp.in
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/Version.hpp"
)

physics_glob_codegen(
    templates/_IncludeAll.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/_IncludeAll.hpp"
)
physics_glob_codegen(
    templates/FwdDecl.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/FwdDecl.hpp"
)
physics_glob_codegen(
    templates/Literals.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/Literals.hpp"
)
physics_item_codegen(
    templates/Item.hpp.j2
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/@Item@.hpp"
    PHYSICS_CORE_ITEMS
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
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/_IncludeAll.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/FwdDecl.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/Literals.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/Config.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/Version.hpp"
    ${PHYSICS_CORE_ITEMS}

    ${SI_CORE_SRC}
    ${PHYSICS_CORE_DIMS}

    Empty.cpp)

set_target_properties(Core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(Core PUBLIC cxx_std_17)
target_include_directories(Core PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include")
if(${Qt5Core_FOUND})
    target_link_libraries(Core PUBLIC Qt5::Core)
endif()

add_library(Physics::Core ALIAS Core)

add_subdirectory(tests)
