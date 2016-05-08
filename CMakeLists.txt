
if(${CMAKE_CXX_STANDARD} LESS 11)
    set(CMAKE_CXX_STANDARD 11)
endif()
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Designer)

add_subdirectory(Physics)

if(${Qt5Core_FOUND})
    add_subdirectory(QPhysics)
    if(${Qt5Widgets_FOUND})
        add_subdirectory(QPhysicsUI)
        if(${Qt5Designer_FOUND})
            add_subdirectory(QPhysicsDesigner)
        endif()
    endif()
endif()


