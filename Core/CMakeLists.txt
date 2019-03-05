
set(TEMPLATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/templates")
set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

configure_file(
    "${TEMPLATE_DIR}/include/ph/Version.hpp.in"
    "${OUTPUT_DIR}/include/ph/Version.hpp"
)

set(HAND_WRITTEN_SRC
    include/ph/Constants.hpp
    include/ph/Operators.hpp
    include/ph/Physics.hpp
    include/ph/Zero.hpp
)

set(TEMPLATES_SRC
    templates/include/ph/_IncludeAll.hpp.glob.in
    templates/include/ph/FwdDecl.hpp.glob.in
    templates/include/ph/Item.hpp.item.in
    templates/include/ph/Literals.hpp.glob.in
    templates/include/ph/Version.hpp.in
)

code_gen_glob(
    "${TEMPLATE_DIR}"
    "${OUTPUT_DIR}"
    GLOB_FILES
)

code_gen_item(
    "${TEMPLATE_DIR}"
    "${OUTPUT_DIR}"
    ITEM_FILES
)

# generating an empty static lib instead of an INTERFACE target
# otherwise code generation is not triggered
add_library(Core STATIC
    ${HAND_WRITTEN_SRC} ${TEMPLATES_SRC} ${GLOB_FILES} ${ITEM_FILES}
    Empty.cpp)
set_target_properties(Core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(Core PUBLIC cxx_std_17)
target_include_directories(Core INTERFACE include "${OUTPUT_DIR}/include")

add_library(Physics::Core ALIAS Core)
