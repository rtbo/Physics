import qbs

StaticLibrary {
    name: "QPhysics"
    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Physics" }

    cpp.includePaths: "include"
    cpp.cxxFlags: "-std=c++11"

    files: [
        "include/QPhysics.hpp",
        "QPhysics.cpp"
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [
            "include"
        ]
    }
}
