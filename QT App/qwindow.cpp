#include "qwindow.h"

Window::Window(QWidget *parent) : QWidget(parent)
 {
    parentWindow = (mainWindow*)parent;
    mainLayout = new QVBoxLayout(this);
    welcomeMessage = new QLabel("Ez a program az ELTE programtervező informatikus BSc szakának szakdolgozataként készült.\n"
                                "A programhoz tartozó dokumentáció ajánlott az alkalmazásban szereplő konstrukciók ismertetéséhez. \n"
                                "A kipróbálásához válasszon az alábbi opciók közül.\n"
                                "Készítette: Kovács Levente");
    QFont font("Arial", 10, QFont::Bold);
    welcomeMessage->setFont(font);
    mainLayout->addWidget(welcomeMessage);

    buttonLayout = new QGridLayout();
    makeButtons();

    mainLayout->addLayout(buttonLayout);
}

void Window::makeButtons()
{
    legendreButton = new QPushButton("Legendre konstrukció", this);
    rc4Button = new QPushButton("RC4 konstrukció", this);
    additiveButton = new QPushButton("Additív karakteres konstrukció", this);
    chachaButton = new QPushButton("ChaCha20 konstrukció", this);
    measuresButton = new QPushButton("Mértékek", this);
    cryptoButton = new QPushButton("One-time pad titkosítás", this);
    quitButton = new QPushButton("Kilépés", this);
    setButtonsSize();
    setButtonsSender();
    buttonLayout->addWidget(legendreButton, 0, 0, 1, 2);
    buttonLayout->addWidget(rc4Button, 0, 2, 1, 2);
    buttonLayout->addWidget(additiveButton, 1, 0, 1, 2);
    buttonLayout->addWidget(chachaButton, 1, 2, 1, 2);
    buttonLayout->addWidget(measuresButton, 2, 0, 1, 2);
    buttonLayout->addWidget(cryptoButton, 2, 2, 1, 2);
    buttonLayout->addWidget(quitButton, 3, 1, 1, 2);

    for(int i = 0; i < buttonLayout->rowCount(); ++i)
    {
        buttonLayout->setRowMinimumHeight(i, 50);
    }
}

void Window::setButtonsSize()
{
    legendreButton->setMinimumSize(150, 50);
    legendreButton->setBaseSize(150, 50);
    rc4Button->setMinimumSize(150, 50);
    rc4Button->setBaseSize(150,50);
    additiveButton->setMinimumSize(150, 50);
    additiveButton->setBaseSize(150,50);
    chachaButton->setMinimumSize(150, 50);
    chachaButton->setBaseSize(150,50);
    measuresButton->setMinimumSize(150, 50);
    measuresButton->setBaseSize(150, 50);
    cryptoButton->setMinimumSize(150, 50);
    cryptoButton->setBaseSize(150, 50);
    quitButton->setMinimumSize(150, 50);
    quitButton->setBaseSize(150, 50);
}

void Window::setButtonsSender()
{
    connect(legendreButton, SIGNAL(clicked()), this, SLOT(legendreButtonClicked()));
    connect(rc4Button, SIGNAL(clicked()), this, SLOT(rc4ButtonClicked()));
    connect(additiveButton, SIGNAL(clicked()), this, SLOT(additiveButtonClicked()));
    connect(chachaButton, SIGNAL(clicked()), this, SLOT(chachaButtonClicked()));
    connect(measuresButton, SIGNAL(clicked()), this, SLOT(measuresButtonClicked()));
    connect(cryptoButton, SIGNAL(clicked()), this, SLOT(cryptoButtonClicked()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitButtonClicked()));
}
/*
QVBoxLayout* Window::getLayout()
{
    return mainLayout;
}
*/
void Window::legendreButtonClicked()
{
    parentWindow->setWindowTitle(tr("Legendre konstrukció"));
    parentWindow->ChangeMenu(1);
}

void Window::rc4ButtonClicked()
{
    parentWindow->setWindowTitle(tr("RC4 konstrukció"));
    parentWindow->ChangeMenu(2);
}

void Window::additiveButtonClicked()
{
    parentWindow->setWindowTitle(tr("Additív karakteres konstrukció"));
    parentWindow->ChangeMenu(3);
}

void Window::chachaButtonClicked()
{
    parentWindow->setWindowTitle(tr("ChaCha20 konstrukció"));
    parentWindow->ChangeMenu(4);
}

void Window::measuresButtonClicked()
{
    parentWindow->setWindowTitle(tr("Mértékek"));
    parentWindow->ChangeMenu(5);
}

void Window::cryptoButtonClicked()
{
    parentWindow->setWindowTitle(tr("One-time pad titkosítás"));
    parentWindow->ChangeMenu(6);
}

void Window::quitButtonClicked()
{
    close();
    parentWindow->close();
}
