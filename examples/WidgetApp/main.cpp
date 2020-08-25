
#include "widget.h"

#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };
    Widget widget;

    widget.setWindowTitle("SI_Units Widget App");
    widget.showNormal();

    return app.exec();
}
