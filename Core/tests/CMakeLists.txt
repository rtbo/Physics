
add_executable(TestPhysicsCore
    catch.hpp

    main.cpp

    Units.cpp
)
target_link_libraries(TestPhysicsCore PRIVATE Physics::Core)

add_test(NAME "Physics::Core" COMMAND TestPhysicsCore)
