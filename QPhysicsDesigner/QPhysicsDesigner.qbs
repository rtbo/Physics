import qbs
import qbs.FileInfo

DynamicLibrary {
    Depends {name: "cpp"}
    Depends {name: "QPhysicsUI"}
    Depends {name: "Qt"; submodules:["core", "gui", "widgets", "designer"]}
    Depends {name: "phcg"}

    name: "QPhysicsDesigner"

    phcg.script: "../PhysicsCodeGen.py"
    phcg.data: "../PhysicsData.json"

    cpp.includePaths: [
        buildDirectory
    ]

    files: [
        "icons.qrc",
        "QPhysicsDesignerPlugin.hpp.ph_gt",
        "QPhysicsDesignerPlugin.cpp.ph_gt",
    ]

//    Group {
//        qbs.install: true
//        qbs.installDir: FileInfo.joinPaths(Qt.core.pluginPath, "designer")
//        fileTagsFilter: product.type
//    }
}
