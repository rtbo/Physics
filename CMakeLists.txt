
cmake_minimum_required(VERSION 3.12)

project(Physics VERSION 1.3.0
                DESCRIPTION "Physics C++ library"
                LANGUAGES CXX)

set(EXCLUDED_BASE_DIMS "" CACHE STRING "; separated list of base dimensions to exclude")
set(EXCLUDED_DIMS "" CACHE PATH "File containing a list of dimensions to exclude")

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

execute_process(COMMAND "${Python_EXECUTABLE}" Dimensions.py
                    --print-dims --excluded-base-dims=${EXCLUDED_BASE_DIMS} --excluded-dims=${EXCLUDED_DIMS}
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                OUTPUT_VARIABLE PHYSICS_DIMS
                RESULT_VARIABLE PHYSICS_DIMS_RESULT
                OUTPUT_STRIP_TRAILING_WHITESPACE)

if (NOT PHYSICS_DIMS_RESULT EQUAL "0")
    message(FATAL_ERROR "Could not list dimensions. Make sure Python 3 is available and that Jinja2 is installed")
endif()

find_package(Qt5Core)
set(PHYSICS_HAVE_QT_CORE ${Qt5Core_FOUND})

add_subdirectory(Core)

find_package(Qt5Widgets)
if(${Qt5Core_FOUND} AND ${Qt5Widgets_FOUND})

    add_subdirectory(Widgets)

    find_package(Qt5Designer)
    if(${Qt5Designer_FOUND})
        #add_subdirectory(DesignerPlugin)
    endif()

endif()
