
cmake_minimum_required(VERSION 3.12)

project(Physics VERSION 1.2.0
                DESCRIPTION "Physics C++ library"
                LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(PhysicsCodeGen)

find_package(Python REQUIRED)

execute_process(COMMAND "${Python_EXECUTABLE}" PhysicsCodeGen.py --print-items
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                OUTPUT_VARIABLE PHYSICS_ITEMS
                RESULT_VARIABLE PHYSICS_ITEMS_RESULT
                OUTPUT_STRIP_TRAILING_WHITESPACE)

if (NOT PHYSICS_ITEMS_RESULT EQUAL "0")
    message(FATAL_ERROR "Could not list items. Make sure Python 3 is available and that Jinja2 is installed")
endif()

find_package(Qt5Core)
set(PHYSICS_HAVE_QT_CORE ${Qt5Core_FOUND})

add_subdirectory(Core)

find_package(Qt5Widgets)
if(${Qt5Core_FOUND} AND ${Qt5Widgets_FOUND})

    add_subdirectory(Widgets)

    find_package(Qt5Designer)
    if(${Qt5Designer_FOUND})
        add_subdirectory(DesignerPlugin)
    endif()

endif()
