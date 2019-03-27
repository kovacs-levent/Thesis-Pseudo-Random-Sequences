#include "mainwindow.h"
#include "qwindow.h"
#include "legendrewindow.h"
#include "rc4window.h"
#include "additivewindow.h"
#include "chachawindow.h"
#include "measurewindow.h"

void displayError(const std::string &errorTitle, const std::string &errorMessage)
{
    QMessageBox* error = new QMessageBox;
    error->setAttribute(Qt::WA_DeleteOnClose, true);
    const QString title(errorTitle.c_str());
    const QString message(errorMessage.c_str());
    error->setWindowTitle(title);
    error->setText(message);
    error->show();
}

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(850, 400);
    setWindowTitle(tr("Pszeudovéletlen sorozatok mértékei és konstrukciói"));
    layoutWidget = new QWidget(this);
    stack = new QStackedLayout(layoutWidget);
    Window* main_menu = new Window(this);
    stack->addWidget(main_menu);
    legendreWindow* leg = new legendreWindow(this);
    stack->addWidget(leg);
    rc4Window* rc = new rc4Window(this);
    stack->addWidget(rc);
    additiveWindow* aw = new additiveWindow(this);
    stack->addWidget(aw);
    chachaWindow* cw = new chachaWindow(this);
    stack ->addWidget(cw);
    measureWindow* mw = new measureWindow(this);
    stack->addWidget(mw);
    stack->setCurrentIndex(0);
    setCentralWidget(layoutWidget);
}
