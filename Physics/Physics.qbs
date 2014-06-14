import qbs

StaticLibrary {
    Depends { name: "cpp" }
    name: "Physics"
    cpp.includePaths: "include"

    Properties {
        condition: qbs.toolchain.contains("gcc")
        cpp.cxxFlags: "-std=c++1y"
    }
    Properties {
        condition: qbs.toolchain.contains("msvc")
        cpp.cxxFlags: "/FS"
    }

    files: [
        "include/ph/Acceleration.hpp",
        "include/ph/Area.hpp",
        "include/ph/Energy.hpp",
        "include/ph/Flow.hpp",
        "include/ph/Force.hpp",
        "include/ph/Length.hpp",
        "include/ph/Mass.hpp",
        "include/ph/MolecularMass.hpp",
        "include/ph/Pressure.hpp",
        "include/ph/Quantity.hpp",
        "include/ph/Temperature.hpp",
        "include/ph/Time.hpp",
        "include/ph/Velocity.hpp",
        "include/ph/Volume.hpp",
        "include/ph/VolumicMass.hpp",
        "include/ph/Config.hpp",
        "include/ph/FwdDecl.hpp",
        "include/ph/Operators.hpp",
        "include/ph/Literals.hpp",
        "include/ph/Physics.hpp",
        "include/ph/Constants.hpp",
        "include/ph/_IncludeAll.hpp",
        "Zero.cpp"
    ]

    Export {
        Depends {name: "cpp"}
        cpp.includePaths: "include"

        Properties {
            condition: qbs.toolchain.contains("gcc")
            cpp.cxxFlags: "-std=c++1y"
        }
        Properties {
            condition: qbs.toolchain.contains("msvc")
            cpp.cxxFlags: "/FS"
        }
    }
}
