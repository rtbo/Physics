
add_executable(SI_Units_CoreTest
    catch.hpp

    main.cpp

    Conversion.cpp
    MolarMass.cpp
    Output.cpp
    Temperature.cpp
    Trigo.cpp
    Units.cpp
)
target_link_libraries(SI_Units_CoreTest PRIVATE SI_Units::Core)

add_test(NAME "SI_Units::Core" COMMAND SI_Units_CoreTest)
