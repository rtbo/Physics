import qbs

Application {
    Depends {name: "cpp"}
    Depends {name: "Physics"}

    name: "Physics tests"

    consoleApplication: true

    files: [
        "main.cpp",
        "Temperature.cpp",
        "VolumicMass.cpp",
        "MolecularMass.cpp",
        "Zero.cpp",

        "catch.hpp"
    ]
}
