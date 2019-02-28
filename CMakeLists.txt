
cmake_minimum_required(VERSION 3.1...3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Physics VERSION 1.2.0
                DESCRIPTION "Physics C++ library"
                LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(CodeGen)

find_package(Python)
if (NOT Python_Interpreter_FOUND)
    message(FATAL_ERROR "Python not found but required for code generation")
endif()

set(CODEGEN_SCRIPT "${Physics_SOURCE_DIR}/PhysicsCodeGen.py")
set(CODEGEN_DATA "${Physics_SOURCE_DIR}/PhysicsData.json")

execute_process(COMMAND ${Python_EXECUTABLE} PhysicsCodeGen.py --print-items
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_VARIABLE PHYSICS_ITEMS
                RESULT_VARIABLE PHYSICS_ITEMS_RESULT
                OUTPUT_STRIP_TRAILING_WHITESPACE)

if (NOT PHYSICS_ITEMS_RESULT EQUAL "0")
    message(FATAL_ERROR "Could not list items. Make sure Python 3 is available and that Jinja2 is installed")
endif()

add_subdirectory(Physics)

find_package(Qt5Core)
if(${Qt5Core_FOUND})

    add_subdirectory(QPhysics)

#     find_package(Qt5Widgets)
#     if(${Qt5Widgets_FOUND})

#         add_subdirectory(QPhysicsUI)

#         find_package(Qt5Designer)
#         if(${Qt5Designer_FOUND})
#             add_subdirectory(QPhysicsDesigner)
#         endif()

#     endif()
endif()


