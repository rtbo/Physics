import qbs

Product {
    Depends { name: "cpp" }
    name: "Physics"
    cpp.includePaths: "include"

    cpp.cxxLanguageVersion: "c++14"

    files: [
        "include/ph/Acceleration.hpp",
        "include/ph/Area.hpp",
        "include/ph/Energy.hpp",
        "include/ph/Flow.hpp",
        "include/ph/Force.hpp",
        "include/ph/Length.hpp",
        "include/ph/Mass.hpp",
        "include/ph/MolecularMass.hpp",
        "include/ph/Power.hpp",
        "include/ph/Pressure.hpp",
        "include/ph/Quantity.hpp",
        "include/ph/Temperature.hpp",
        "include/ph/Time.hpp",
        "include/ph/Velocity.hpp",
        "include/ph/Volume.hpp",
        "include/ph/VolumicMass.hpp",
        "include/ph/FwdDecl.hpp",
        "include/ph/Operators.hpp",
        "include/ph/Literals.hpp",
        "include/ph/Physics.hpp",
        "include/ph/Constants.hpp",
        "include/ph/Zero.hpp",
        "include/ph/_IncludeAll.hpp",
    ]

    Export {
        Depends {name: "cpp"}
        cpp.includePaths: "include"

        cpp.cxxLanguageVersion: "c++14"
    }
}
