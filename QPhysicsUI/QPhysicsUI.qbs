import qbs

StaticLibrary {
    Depends {name: "cpp"}
    Depends {name: "Qt"; submodules:["core", "widgets"]}
    Depends {name: "Physics"}
    name: "QPhysicsUI"
    cpp.includePaths: "include"
    Properties {
        condition: qbs.toolchain.contains("gcc")
        cpp.cxxFlags: [
            "-std=c++11"
        ]
    }
    files: [
        "include/QAccelerationSpinBox.hpp",
        "include/QAreaSpinBox.hpp",
        "include/QEnergySpinBox.hpp",
        "include/QFlowSpinBox.hpp",
        "include/QForceSpinBox.hpp",
        "include/QLengthSpinBox.hpp",
        "include/QMassSpinBox.hpp",
        "include/QMolecularMassSpinBox.hpp",
        "include/QPressureSpinBox.hpp",
        "include/QQuantitySpinBox.hpp",
        "include/QTemperatureSpinBox.hpp",
        "include/QTimeSpinBox.hpp",
        "include/QVelocitySpinBox.hpp",
        "include/QVolumeSpinBox.hpp",
        "include/QVolumicMassSpinBox.hpp",
        "QAccelerationSpinBox.cpp",
        "QAreaSpinBox.cpp",
        "QEnergySpinBox.cpp",
        "QFlowSpinBox.cpp",
        "QForceSpinBox.cpp",
        "QLengthSpinBox.cpp",
        "QMassSpinBox.cpp",
        "QMolecularMassSpinBox.cpp",
        "QPressureSpinBox.cpp",
        "QQuantitySpinBox.cpp",
        "QTemperatureSpinBox.cpp",
        "QTimeSpinBox.cpp",
        "QVelocitySpinBox.cpp",
        "QVolumeSpinBox.cpp",
        "QVolumicMassSpinBox.cpp",
    ]

    Export {
        Depends {name: "cpp"}
        Depends {name: "Physics"}
        cpp.includePaths: "include"
    }
}
