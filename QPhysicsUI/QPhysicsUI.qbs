import qbs
import qbs.FileInfo

Product {
    Depends {name: "cpp"}
    Depends {name: "Qt"; submodules:["core", "widgets"]}
    Depends {name: "Physics"}
    Depends {name: "phcg"}

    name: "QPhysicsUI"

    type: ["staticlibrary", "generated_glob", "generated_item"]

    phcg.script: "../PhysicsCodeGen.py"
    phcg.data: "../PhysicsData.json"

    cpp.includePaths: [
        "include",
        FileInfo.joinPaths(buildDirectory, "include")
    ]

    Group {
        name: "Header templates"
        files: [
            "include/QItemLabel.hpp.template",
            "include/QItemSpinBox.hpp.template",
        ]
        fileTags: ["item_template"]
    }
    Group {
        name: "Source templates"
        files: [
            "QItemLabel.cpp.template",
            "QItemSpinBox.cpp.template",
        ]
        fileTags: ["item_template"]
    }

    Export {
        Depends {name: "cpp"}
        Depends {name: "Physics"}
        cpp.includePaths: [
            "include",
            FileInfo.joinPaths(product.buildDirectory, "include")
        ]
    }
}
