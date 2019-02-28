
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

add_library(PhysicsCore STATIC ${GLOB_FILES} ${ITEM_FILES})
set_target_properties(PhysicsCore PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(PhysicsCore INTERFACE PUBLIC include "${OUTPUT_DIR}/include")
