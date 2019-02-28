

set(TEMPLATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/templates")
set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

code_gen_glob(
    "${TEMPLATE_DIR}"
    "${OUTPUT_DIR}"
    GLOB_FILES
)

add_library(QPhysicsDesigner SHARED
    ${GLOB_FILES}
    icons.qrc)

target_link_libraries(QPhysicsDesigner QPhysicsUI Qt5::Designer)
