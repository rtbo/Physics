
set(PHYSICS_SRC
    include/ph/Acceleration.hpp
    include/ph/Area.hpp
    include/ph/Energy.hpp
    include/ph/Flow.hpp
    include/ph/Force.hpp
    include/ph/Length.hpp
    include/ph/Mass.hpp
    include/ph/MolecularMass.hpp
    include/ph/Pressure.hpp
    include/ph/Quantity.hpp
    include/ph/Temperature.hpp
    include/ph/Time.hpp
    include/ph/Velocity.hpp
    include/ph/Volume.hpp
    include/ph/VolumicMass.hpp
    include/ph/FwdDecl.hpp
    include/ph/Operators.hpp
    include/ph/Literals.hpp
    include/ph/Physics.hpp
    include/ph/Constants.hpp
    include/ph/Zero.hpp
    include/ph/_IncludeAll.hpp)

add_library(Physics INTERFACE)

target_include_directories(Physics INTERFACE include)
#target_sources(Physics INTERFACE ${PHYSICS_SRC})

if(NOT ${SKIP_PHYSICS_INSTALL})
    install(DIRECTORY include/ph DESTINATION include)
endif()

