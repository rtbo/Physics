
set(PHYSICS_CORE_SRC
    include/ph/Constants.hpp
    include/ph/Operators.hpp
    include/ph/Physics.hpp
    include/ph/Zero.hpp

    templates/Config.hpp.in
    templates/_IncludeAll.hpp.j2
    templates/FwdDecl.hpp.j2
    templates/Item.hpp.j2
    templates/Literals.hpp.j2
    templates/Version.hpp.in
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

# generating an empty static lib instead of an INTERFACE target
# otherwise code generation is not triggered
add_library(Core STATIC
    ${PHYSICS_CORE_SRC}
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/Config.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/Version.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/_IncludeAll.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/FwdDecl.hpp"
    "${CMAKE_CURRENT_BINARY_DIR}/include/ph/Literals.hpp"
    ${PHYSICS_CORE_ITEMS}
    Empty.cpp)

set_target_properties(Core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(Core PUBLIC cxx_std_17)
target_include_directories(Core PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include")
if(${Qt5Core_FOUND})
    target_link_libraries(Core PUBLIC Qt5::Core)
endif()

add_library(Physics::Core ALIAS Core)

