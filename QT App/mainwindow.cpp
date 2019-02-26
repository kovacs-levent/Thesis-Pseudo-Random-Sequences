#include "mainwindow.h"
#include "qwindow.h"
#include "legendrewindow.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(850, 400);
    setBaseSize(850,400);
    setWindowTitle(tr("Pszeudovéletlen sorozatok mértékei és konstrukciói"));
    stack = new QStackedLayout(this);
    Window* main_menu = new Window(this);
    stack->addWidget(main_menu);
    legendreWindow* leg = new legendreWindow(this);
    stack->addWidget(leg);
    stack->setCurrentIndex(0);
    setLayout(stack);
}
