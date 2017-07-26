import qbs
import qbs.FileInfo

StaticLibrary {
    Depends {name: "cpp"}
    Depends {name: "Qt"; submodules:["core", "widgets"]}
    Depends {name: "Physics"}
    Depends {name: "phcg"}

    name: "QPhysicsUI"

    phcg.script: "../PhysicsCodeGen.py"
    phcg.data: "../PhysicsData.json"

    cpp.includePaths: [
        "include",
        FileInfo.joinPaths(buildDirectory, "include")
    ]
    Properties {
        condition: qbs.toolchain.contains("gcc")
        cpp.cxxFlags: [
            "-Wno-unused-variable"
        ]
    }

    files: [
        "include/QItemLabel.hpp.ph_it",
        "include/QItemSpinBox.hpp.ph_it",
        "QItemLabel.cpp.ph_it",
        "QItemSpinBox.cpp.ph_it",
    ]

    Export {
        Depends {name: "cpp"}
        Depends {name: "Physics"}
        cpp.includePaths: [
            "include",
            FileInfo.joinPaths(product.buildDirectory, "include")
        ]
    }
}
