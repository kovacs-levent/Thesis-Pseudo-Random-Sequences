#include "legendrewindow.h"
#include <QString>
#include <sstream>

legendreWindow::legendreWindow(QWidget *parent) : QWidget(parent)
{
    parentWindow = (mainWindow*)parent;
    setMinimumSize(850, 400);
    setBaseSize(850,400);
    setWindowTitle(tr("Pszeudovéletlen sorozatok mértékei és konstrukciói"));
    mainLayout = new QGridLayout(this);
    makeLengthForm();
    makePrimeForm();
    makePolDeg();
    makePolForm();
    mainLayout->addWidget(lengthFormGroup, 0, 0);
    mainLayout->addWidget(primeGroup, 0, 1);
    mainLayout->addWidget(polDegGroup, 1, 0);
    mainLayout->addWidget(polGroup, 1, 1);
    //setLayout(mainLayout);
}

void legendreWindow::makeLengthForm()
{
    lengthFormLayout = new QGridLayout(this);
    lengthFormGroup = new QGroupBox(tr("Sorozat mérete"), this);
    lengthEdit = new QLineEdit(this);
    lengthEdit->setPlaceholderText("...");
    lengthEdit->setFocus();
    lengthFormLayout->addWidget(lengthEdit, 0, 0, 0, 1);
    lengthFormGroup->setLayout(lengthFormLayout);
}

void legendreWindow::makePrimeForm()
{
    primeLayout = new QGridLayout(this);
    primeGroup = new QGroupBox(tr("Prímszám"), this);
    primeLineEdit = new QLineEdit(this);
    primeLineEdit->setPlaceholderText("...");
    primeLayout->addWidget(primeLineEdit, 0, 0, 0, 1);
    primeGenButton = new QPushButton("Generálás", this);
    primeLayout->addWidget(primeGenButton, 0, 2);
    primeNextButton = new QPushButton("Következő", this);
    primeLayout->addWidget(primeNextButton, 0, 3);
    connect(primeGenButton, SIGNAL(clicked()), this, SLOT(generatePrimeButtonClicked()));
    connect(primeNextButton, SIGNAL(clicked()), this, SLOT(nextPrimeButtonClicked()));
    primeGroup->setLayout(primeLayout);
}

void legendreWindow::makePolDeg()
{
    polDegGroup = new QGroupBox(tr("Polinom fokszáma"), this);
    polDegLineEdit = new QLineEdit(this);
    polDegLineEdit->setPlaceholderText("...");
    polDegLayout = new QGridLayout(this);
    polDegLayout->addWidget(polDegLineEdit, 0, 0, 0, 1);
    polDegGenButton = new QPushButton("Fokszám generálás", this);
    polDegLayout->addWidget(polDegGenButton, 0, 2);
    connect(polDegGenButton, SIGNAL(clicked()), this, SLOT(polDegButtonClicked()));
    polDegGroup->setLayout(polDegLayout);
}

void legendreWindow::makePolForm()
{
    polGroup = new QGroupBox(tr("Polinom"), this);
    polTextEdit = new QTextEdit(this);
    polTextEdit->setPlaceholderText("...");
    polLayout = new QGridLayout(this);
    polLayout->addWidget(polTextEdit, 0, 0, 0, 1);
    polGenButton = new QPushButton("Polinom generálás", this);
    polLayout->addWidget(polGenButton, 0, 2);
    connect(polGenButton, SIGNAL(clicked()), this, SLOT(polGenButtonClicked()));
    polGroup->setLayout(polLayout);
}

void legendreWindow::polDegButtonClicked()
{
}

void legendreWindow::polGenButtonClicked()
{

}

void legendreWindow::generateButtonClicked()
{

}

void legendreWindow::generatePrimeButtonClicked()
{
    const QString len = lengthEdit->displayText();
    const uint64_t p = legendre.GenerateValidPrime(len.toLongLong()*16+1);
    std::stringstream ss;
    ss << p;
    QString s = QString::fromStdString(ss.str());
    primeLineEdit->setText(s);
}

void legendreWindow::nextPrimeButtonClicked()
{
    const QString prime = primeLineEdit->displayText();
    const uint64_t p = legendre.GenerateValidPrime(prime.toLongLong()+2);
    std::stringstream ss;
    ss << p;
    QString s = QString::fromStdString(ss.str());
    primeLineEdit->setText(s);
}
