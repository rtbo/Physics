import qbs

StaticLibrary {
    Depends {name: "cpp"}
    Depends {name: "Qt"; submodules:["core", "widgets"]}
    Depends {name: "Physics"}
    name: "QPhysicsUI"
    cpp.includePaths: "include"
    files: [
    ]

    Export {
        Depends {name: "cpp"}
        Depends {name: "Physics"}
        cpp.includePaths: "include"
    }
}
