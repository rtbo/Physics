import qbs
import qbs.FileInfo

Product {
    name: "QPhysics"
    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Physics" }
    Depends { name: "phcg" }

    type: ["staticlibrary", "generated_glob_hpp", "generated_item_hpp"]

    phcg.script: "../PhysicsCodeGen.py"
    phcg.data: "../PhysicsData.json"

    cpp.includePaths: [
        FileInfo.joinPaths(buildDirectory, "include")
    ]

    Group {
        name: "Header template"
        files: ["include/QPhysics.hpp.template"]
        fileTags: ["glob_hpp_template"]
    }
    Group {
        name: "Source template"
        files: ["QPhysics.cpp.template"]
        fileTags: ["glob_cpp_template"]
    }

    Export {
        Depends { name: "cpp" }
        Depends { name: "Physics" }
        cpp.includePaths: [
            FileInfo.joinPaths(product.buildDirectory, "include")
        ]
    }
}
