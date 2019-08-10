#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    auto update = [&]() {
        ui->energyLabel->setEnergy(ui->volumeSpinBox->volume() *
                                   ui->pressureSpinBox->pressure());
    };

    QObject::connect(ui->volumeSpinBox, &siui::VolumeSpinBox::volumeChanged,
                     update);
    QObject::connect(ui->pressureSpinBox,
                     &siui::PressureSpinBox::pressureChanged, update);
    update();
}

Widget::~Widget()
{
    delete ui;
}
