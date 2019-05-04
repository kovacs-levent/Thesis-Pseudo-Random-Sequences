#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    //app.setStyleSheet("QPushButton { background-color: rgb(192, 192, 192); border-style: outset; border-width: 2px; border-radius: 10px; font: 14px; border-color: beige; min-width: 10em; padding: 6px; }");
    mainWindow widget;
    widget.show();
    return app.exec();
}
