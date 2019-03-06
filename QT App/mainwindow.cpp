#include "mainwindow.h"
#include "qwindow.h"
#include "legendrewindow.h"
#include "rc4window.h"
#include "additivewindow.h"

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
    rc4Window* rc = new rc4Window(this);
    stack->addWidget(rc);
    additiveWindow* aw = new additiveWindow(this);
    stack->addWidget(aw);
    stack->setCurrentIndex(0);
    setLayout(stack);
}
