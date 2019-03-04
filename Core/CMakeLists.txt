
set(TEMPLATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/templates")
set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

configure_file(
    "${TEMPLATE_DIR}/include/ph/Version.hpp.in"
    "${OUTPUT_DIR}/include/ph/Version.hpp"
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
    ${GLOB_FILES} ${ITEM_FILES}
    Empty.cpp)
set_target_properties(Core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(Core PUBLIC cxx_std_17)
target_include_directories(Core INTERFACE include "${OUTPUT_DIR}/include")

add_library(Physics::Core ALIAS Core)
