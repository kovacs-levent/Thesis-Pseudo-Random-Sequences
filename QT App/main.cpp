#include <QApplication>
#include "qwindow.h"

int main(int argc, char **argv)
{
 QApplication app (argc, argv);
 Window widget;
 widget.show();

 return app.exec();
}
