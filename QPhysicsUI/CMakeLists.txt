
set(QPHYSICSUI_H
    include/QAccelerationLabel.hpp
    include/QAreaLabel.hpp
    include/QEnergyLabel.hpp
    include/QFlowLabel.hpp
    include/QForceLabel.hpp
    include/QLengthLabel.hpp
    include/QMassLabel.hpp
    include/QMolecularMassLabel.hpp
    include/QPressureLabel.hpp
    include/QQuantityLabel.hpp
    include/QTemperatureLabel.hpp
    include/QTimeLabel.hpp
    include/QVelocityLabel.hpp
    include/QVolumeLabel.hpp
    include/QVolumicMassLabel.hpp
    include/QAccelerationSpinBox.hpp
    include/QAreaSpinBox.hpp
    include/QEnergySpinBox.hpp
    include/QFlowSpinBox.hpp
    include/QForceSpinBox.hpp
    include/QLengthSpinBox.hpp
    include/QMassSpinBox.hpp
    include/QMolecularMassSpinBox.hpp
    include/QPressureSpinBox.hpp
    include/QQuantitySpinBox.hpp
    include/QTemperatureSpinBox.hpp
    include/QTimeSpinBox.hpp
    include/QVelocitySpinBox.hpp
    include/QVolumeSpinBox.hpp
    include/QVolumicMassSpinBox.hpp)

set(QPHYSICSUI_SRC
    QAccelerationLabel.cpp
    QAreaLabel.cpp
    QEnergyLabel.cpp
    QFlowLabel.cpp
    QForceLabel.cpp
    QLengthLabel.cpp
    QMassLabel.cpp
    QMolecularMassLabel.cpp
    QPressureLabel.cpp
    QQuantityLabel.cpp
    QTemperatureLabel.cpp
    QTimeLabel.cpp
    QVelocityLabel.cpp
    QVolumeLabel.cpp
    QVolumicMassLabel.cpp
    QAccelerationSpinBox.cpp
    QAreaSpinBox.cpp
    QEnergySpinBox.cpp
    QFlowSpinBox.cpp
    QForceSpinBox.cpp
    QLengthSpinBox.cpp
    QMassSpinBox.cpp
    QMolecularMassSpinBox.cpp
    QPressureSpinBox.cpp
    QQuantitySpinBox.cpp
    QTemperatureSpinBox.cpp
    QTimeSpinBox.cpp
    QVelocitySpinBox.cpp
    QVolumeSpinBox.cpp
    QVolumicMassSpinBox.cpp)

add_library(QPhysicsUI STATIC
    ${QPHYSICSUI_H}
    ${QPHYSICSUI_SRC})

target_include_directories(QPhysicsUI PUBLIC include)

target_link_libraries(QPhysicsUI QPhysics Qt5::Widgets)

if(NOT ${SKIP_PHYSICS_INSTALL})
    install(TARGETS QPhysicsUI ARCHIVE DESTINATION lib)
    install(FILES ${QPHYSICSUI_H} DESTINATION include)
endif()
