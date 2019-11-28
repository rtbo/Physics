
add_executable(TestPhysicsCore
    catch.hpp

    main.cpp

    Conversion.cpp
    MolarMass.cpp
    Output.cpp
    Temperature.cpp
    Trigo.cpp
    Units.cpp
)
target_link_libraries(TestPhysicsCore PRIVATE Physics::Core)

add_test(NAME "Physics::Core" COMMAND TestPhysicsCore)
