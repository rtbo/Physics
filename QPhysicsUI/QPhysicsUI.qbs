import qbs

StaticLibrary {
    Depends {name: "cpp"}
    Depends {name: "Qt"; submodules:["core", "widgets"]}
    Depends {name: "Physics"}
    name: "QPhysicsUI"
    cpp.includePaths: "include"
    files: [
        "include/QAccelerationLabel.hpp",
        "include/QAreaLabel.hpp",
        "include/QEnergyLabel.hpp",
        "include/QFlowLabel.hpp",
        "include/QForceLabel.hpp",
        "include/QLengthLabel.hpp",
        "include/QMassLabel.hpp",
        "include/QMolecularMassLabel.hpp",
        "include/QPowerLabel.hpp",
        "include/QPressureLabel.hpp",
        "include/QQuantityLabel.hpp",
        "include/QTemperatureLabel.hpp",
        "include/QTimeLabel.hpp",
        "include/QVelocityLabel.hpp",
        "include/QVolumeLabel.hpp",
        "include/QVolumicMassLabel.hpp",
        "QAccelerationLabel.cpp",
        "QAreaLabel.cpp",
        "QEnergyLabel.cpp",
        "QFlowLabel.cpp",
        "QForceLabel.cpp",
        "QLengthLabel.cpp",
        "QMassLabel.cpp",
        "QMolecularMassLabel.cpp",
        "QPowerLabel.cpp",
        "QPressureLabel.cpp",
        "QQuantityLabel.cpp",
        "QTemperatureLabel.cpp",
        "QTimeLabel.cpp",
        "QVelocityLabel.cpp",
        "QVolumeLabel.cpp",
        "QVolumicMassLabel.cpp",

        "include/QAccelerationSpinBox.hpp",
        "include/QAreaSpinBox.hpp",
        "include/QEnergySpinBox.hpp",
        "include/QFlowSpinBox.hpp",
        "include/QForceSpinBox.hpp",
        "include/QLengthSpinBox.hpp",
        "include/QMassSpinBox.hpp",
        "include/QMolecularMassSpinBox.hpp",
        "include/QPowerSpinBox.hpp",
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
        "QPowerSpinBox.cpp",
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
