import qbs
import qbs.FileInfo

StaticLibrary {
    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Physics" }
    Depends { name: "phcg" }

    name: "QPhysics"

    phcg.script: "../PhysicsCodeGen.py"
    phcg.data: "../PhysicsData.json"

    cpp.includePaths: [
        FileInfo.joinPaths(buildDirectory, "include")
    ]

    files: [
        "include/QPhysics.hpp.ph_gt",
        "QPhysics.cpp.ph_gt",
    ]

    Export {
        Depends { name: "cpp" }
        Depends { name: "Physics" }
        cpp.includePaths: [
            FileInfo.joinPaths(product.buildDirectory, "include")
        ]
    }
}
