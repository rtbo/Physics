
set(TEMPLATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/templates")
set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

code_gen_glob(
    "${TEMPLATE_DIR}"
    "${OUTPUT_DIR}"
    GLOB_FILES
)

add_library(QPhysics STATIC ${GLOB_FILES})
target_include_directories(QPhysics PUBLIC "${OUTPUT_DIR}/include")
target_link_libraries(QPhysics Physics::Core Qt5::Core)
set_property(TARGET QPhysics PROPERTY AUTOMOC ON)
