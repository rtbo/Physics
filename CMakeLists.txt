
cmake_minimum_required(VERSION 3.12)

project(SI_Units VERSION 1.3.1
                DESCRIPTION "SI Units C++ library"
                LANGUAGES CXX)


option(DISABLE_QT_WIDGETS "Disables the build of the SI_Units Qt widgets" OFF)
option(DISABLE_QT_DESIGNER_PLUGIN "Disables the build of the Qt designer plugin" OFF)

set(EXCLUDED_BASE_DIMS "" CACHE STRING "; separated list of base dimensions to exclude")
set(EXCLUDED_DIMS "" CACHE PATH "File containing a list of dimensions to exclude")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(SI_Units_CodeGen)

find_package(Python3 REQUIRED)
if(NOT ${Python3_FOUND})
    message(FATAL_ERROR "Python3 with Jinja2 is needed for the source code generation")
endif()

execute_process(COMMAND "${Python3_EXECUTABLE}" Dimensions.py
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

add_subdirectory(Core)

if(NOT DISABLE_QT_WIDGETS)
    find_package(Qt5Core)
    find_package(Qt5Widgets)
    if(${Qt5Core_FOUND} AND ${Qt5Widgets_FOUND})

        add_subdirectory(Widgets)

        if(NOT DISABLE_QT_DESIGNER_PLUGIN)
            find_package(Qt5Designer)
            if(${Qt5Designer_FOUND})
                add_subdirectory(DesignerPlugin)
            else()
                message(WARNING "Qt5 Designer package not found - The designer plugin will not be built")
            endif()
        endif()

        add_subdirectory(examples/WidgetApp)

    else()
        message(WARNING "Qt5 libraries not found - The SI_Units Qt widgets will not be built")
    endif()
endif()
