import qbs

StaticLibrary {
    name: "QPhysics"
    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Physics" }

    cpp.includePaths: "include"

    files: [
        "include/QPhysics.hpp",
        "QPhysics.cpp"
    ]

    Export {
        Depends { name: "cpp" }
        Depends { name: "Physics" }
        cpp.includePaths: [
            "include"
        ]
    }
}
