import qbs
import qbs.FileInfo

Product {
    Depends {name: "cpp"}
    Depends {name: "QPhysicsUI"}
    Depends {name: "Qt"; submodules:["core", "gui", "widgets", "designer"]}
    Depends {name: "phcg"}
    name: "QPhysicsDesigner"

    type: ["dynamiclibrary", "generated_glob_hpp", "generated_item_hpp"]
    phcg.script: "../PhysicsCodeGen.py"
    phcg.data: "../PhysicsData.json"

    cpp.includePaths: [
        buildDirectory
    ]

    Group {
        name: "Header template"
        files: ["QPhysicsDesignerPlugin.hpp.template"]
        fileTags: ["glob_hpp_template"]
    }
    Group {
        name: "Source template"
        files: ["QPhysicsDesignerPlugin.cpp.template"]
        fileTags: ["glob_cpp_template"]
    }
    Group {
        name: "Resource"
        files: ["icons.qrc"]
    }

//    Group {
//        qbs.install: true
//        qbs.installDir: FileInfo.joinPaths(Qt.core.pluginPath, "designer")
//        fileTagsFilter: product.type
//    }
}
