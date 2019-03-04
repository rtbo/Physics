
set(TEMPLATE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/templates")
set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

code_gen_item(
    "${TEMPLATE_DIR}"
    "${OUTPUT_DIR}"
    ITEM_FILES
)

add_library(QPhysicsUI STATIC
    "include/QPhysicsUI_API.hpp"
    ${ITEM_FILES})

target_include_directories(QPhysicsUI PUBLIC include "${OUTPUT_DIR}/include")
target_link_libraries(QPhysicsUI QPhysics Qt5::Widgets)
set_property(TARGET QPhysicsUI PROPERTY AUTOMOC ON)
