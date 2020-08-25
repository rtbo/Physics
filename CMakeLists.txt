
cmake_minimum_required(VERSION 3.12)

project(SI_Units VERSION 1.3.0
                DESCRIPTION "SI_Units C++ library"
                LANGUAGES CXX)

set(EXCLUDED_BASE_DIMS "" CACHE STRING "; separated list of base dimensions to exclude")
set(EXCLUDED_DIMS "" CACHE PATH "File containing a list of dimensions to exclude")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(SI_Units_CodeGen)

find_package(Python REQUIRED)

execute_process(COMMAND "${Python_EXECUTABLE}" Dimensions.py
                    --print-dims --excluded-base-dims=${EXCLUDED_BASE_DIMS} --excluded-dims=${EXCLUDED_DIMS}
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                OUTPUT_VARIABLE SI_UNITS_DIMS
                RESULT_VARIABLE SI_UNITS_DIMS_RESULT
                OUTPUT_STRIP_TRAILING_WHITESPACE)

if (NOT SI_UNITS_DIMS_RESULT EQUAL "0")
    message(FATAL_ERROR "Could not list dimensions. Make sure Python 3 is available and that Jinja2 is installed")
endif()

string(REPLACE ":" ";" SI_UNITS_DIM_LIST ${SI_UNITS_DIMS})
# need to cache this for outer projects to use the scripts
set(SI_UNITS_DIMS ${SI_UNITS_DIMS} CACHE INTERNAL "")
set(SI_UNITS_DIM_LIST ${SI_UNITS_DIM_LIST} CACHE INTERNAL "")

find_package(Qt5Core)
set(SI_UNITS_HAVE_QT_CORE ${Qt5Core_FOUND})

add_subdirectory(Core)

find_package(Qt5Widgets)
if(${Qt5Core_FOUND} AND ${Qt5Widgets_FOUND})

    add_subdirectory(Widgets)

    find_package(Qt5Designer)
    if(${Qt5Designer_FOUND})
        add_subdirectory(DesignerPlugin)
    endif()

    add_subdirectory(examples/WidgetApp)

endif()
