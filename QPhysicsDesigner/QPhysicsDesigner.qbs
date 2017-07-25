import qbs
import qbs.FileInfo

DynamicLibrary {
    Depends {name: "cpp"}
    Depends {name: "QPhysicsUI"}
    Depends {name: "Qt"; submodules:["core", "gui", "widgets", "designer"]}
    name: "QPhysicsDesigner"
    files: [
        "icons.qrc"
    ]
//    Group {
//        qbs.install: true
//        qbs.installDir: FileInfo.joinPaths(Qt.core.pluginPath, "designer")
//        fileTagsFilter: product.type
//    }
}
