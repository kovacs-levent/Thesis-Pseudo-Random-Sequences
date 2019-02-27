#include "legendrewindow.h"
#include <QString>
#include <sstream>
#include <set>
#include <bitset>
#include "../Arithmetics/PrimeArithmetic.h"

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
    makeSequenceForm();
    mainLayout->addWidget(lengthFormGroup, 0, 0);
    mainLayout->addWidget(primeGroup, 0, 1);
    mainLayout->addWidget(polDegGroup, 1, 0);
    mainLayout->addWidget(polGroup, 1, 1);
    mainLayout->addWidget(seqGroup, 2, 0, 3, 2);

    backButton = new QPushButton(tr("Vissza"), this);
    mainLayout->addWidget(backButton, 5, 1);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
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

void legendreWindow::makeSequenceForm()
{
    seqGroup = new QGroupBox(tr("Sorozat"), this);
    seqTextEdit = new QTextEdit(this);
    seqLayout = new QGridLayout(this);
    seqLayout->addWidget(seqTextEdit, 0, 0, 1, 3);
    seqGenButton = new QPushButton("Sorozat generálás", this);
    seqLayout->addWidget(seqGenButton, 2, 1);
    connect(seqGenButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));
    seqGroup->setLayout(seqLayout);
}

void legendreWindow::polDegButtonClicked()
{
    const QString prime = primeLineEdit->displayText();
    const uint64_t deg = legendre.GenerateDegree(prime.toLongLong());
    std::stringstream ss;
    ss << deg;
    QString s = QString::fromStdString(ss.str());
    polDegLineEdit->setText(s);
}

void legendreWindow::polGenButtonClicked()
{
    const QString deg = polDegLineEdit->displayText();
    const QString modulus = primeLineEdit->displayText();
    const std::set<uint64_t> polynom = GenerateSimpleModPoly(modulus.toLongLong(), deg.toUInt());
    std::stringstream ss;
    std::set<uint64_t>::const_iterator it = polynom.begin();
    ss << *it;
    it++;
    while(it != polynom.end())
    {
        ss << " " << *it;
        it++;
    }
    QString s = QString::fromStdString(ss.str());
    polTextEdit->setText(s);
}

void legendreWindow::generateButtonClicked()
{
    const QString length_text = lengthEdit->displayText();
    const QString p_text = primeLineEdit->displayText();
    const QString polynom_text = polTextEdit->toPlainText();
    std::set<uint64_t> polynom;
    std::stringstream ss;
    ss.str(polynom_text.toStdString());
    uint64_t tmp;
    ss >> tmp;
    while(!ss.fail())
    {
        polynom.insert(tmp);
        ss >> tmp;
    }
    std::vector<std::bitset<8> > sequence = legendre.Generate((uint64_t)length_text.toLongLong(), (uint64_t)p_text.toLongLong(), polynom);
    ss.clear();
    ss.str("");
    for(std::vector<std::bitset<8> >::const_iterator it = sequence.begin(); it != sequence.end(); it++)
    {
        ss << it->to_string();
    }
    QString s = QString::fromStdString(ss.str());
    seqTextEdit->setPlainText(s);
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

void legendreWindow::backButtonClicked()
{
    parentWindow->getStack()->setCurrentIndex(0);
}
