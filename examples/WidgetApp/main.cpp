
#include <siui/VolumeSpinBox.hpp>
#include <siui/PressureSpinBox.hpp>
#include <siui/EnergyLabel.hpp>

#include <QtWidgets>

int main (int argc, char *argv[])
{
    QApplication app { argc, argv };
    QWidget window;

    window.setWindowTitle("Physics Widget App");
    auto *layout = new QBoxLayout{ QBoxLayout::LeftToRight, &window };

    auto *vol = new siui::VolumeSpinBox{ &window };
    vol->setUnit(si::volume::Unit::meter3);
    vol->setVolume(si::meter3_t{ 12 });

    auto *pre = new siui::PressureSpinBox{ &window };
    pre->setUnit(si::pressure::Unit::bar);
    pre->setPressure(si::bar_t{ 4 });

    auto *enr = new siui::EnergyLabel{ &window };
    enr->setUnit(si::energy::Unit::kilojoule);


    auto *lbl1 = new QLabel{ " at ", &window };
    auto *lbl2 = new QLabel{ " represent ", &window };

    layout->insertWidget(0, vol);
    layout->insertWidget(1, lbl1);
    layout->insertWidget(2, pre);
    layout->insertWidget(3, lbl2);
    layout->insertWidget(4, enr);

    auto update = [&] () {
        enr->setEnergy( vol->volume() * pre->pressure() );
    };

    QObject::connect(vol, &siui::VolumeSpinBox::volumeChanged, update);
    QObject::connect(pre, &siui::PressureSpinBox::pressureChanged, update);
    update();

    window.showNormal();

    return app.exec();
}
