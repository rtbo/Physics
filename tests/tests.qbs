import qbs

Application {
    Depends {name: "cpp"}
    Depends {name: "Physics"}

    name: "Physics tests"

    consoleApplication: true

    cpp.cxxLanguageVersion: "c++17"

    files: [
        "main.cpp",
        "Temperature.cpp",
        "VolumicMass.cpp",
        "MolecularMass.cpp",
        "Zero.cpp",

        "catch.hpp"
    ]
}
