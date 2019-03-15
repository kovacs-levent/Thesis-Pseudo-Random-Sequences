#include "additivewindow.h"
#include <QString>
#include <sstream>
#include <set>
#include <bitset>
#include "../Arithmetics/PrimeArithmetic.h"

additiveWindow::additiveWindow(QWidget *parent) : QWidget(parent)
{
    parentWindow = (mainWindow*)parent;
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
    setLayout(mainLayout);
}

void additiveWindow::makeLengthForm()
{
    lengthFormGroup = new QGroupBox(tr("Sorozat mérete"), this);
    lengthFormLayout = new QGridLayout(lengthFormGroup);
    lengthEdit = new QLineEdit(lengthFormGroup);
    lengthEdit->setPlaceholderText("...");
    lengthEdit->setFocus();
    lengthFormLayout->addWidget(lengthEdit, 0, 0, 0, 1);
}

void additiveWindow::makePrimeForm()
{
    primeGroup = new QGroupBox(tr("Prímszám"), this);
    primeLayout = new QGridLayout(primeGroup);
    primeLineEdit = new QLineEdit(primeGroup);
    primeLineEdit->setPlaceholderText("...");
    primeLayout->addWidget(primeLineEdit, 0, 0, 0, 1);
    primeGenButton = new QPushButton("Generálás", primeGroup);
    primeLayout->addWidget(primeGenButton, 0, 2);
    primeNextButton = new QPushButton("Következő", primeGroup);
    primeLayout->addWidget(primeNextButton, 0, 3);
    connect(primeGenButton, SIGNAL(clicked()), this, SLOT(generatePrimeButtonClicked()));
    connect(primeNextButton, SIGNAL(clicked()), this, SLOT(nextPrimeButtonClicked()));
    primeGroup->setLayout(primeLayout);
}

void additiveWindow::makePolDeg()
{
    polDegGroup = new QGroupBox(tr("Polinom fokszáma"), this);
    polDegLineEdit = new QLineEdit(polDegGroup);
    polDegLineEdit->setPlaceholderText("...");
    polDegLayout = new QGridLayout(polDegGroup);
    polDegLayout->addWidget(polDegLineEdit, 0, 0, 0, 1);
    polDegGenButton = new QPushButton("Fokszám generálás", polDegGroup);
    polDegLayout->addWidget(polDegGenButton, 0, 2);
    connect(polDegGenButton, SIGNAL(clicked()), this, SLOT(polDegButtonClicked()));
    polDegGroup->setLayout(polDegLayout);
}

void additiveWindow::makePolForm()
{
    polGroup = new QGroupBox(tr("Polinom"), this);
    polTextEdit = new QTextEdit(polGroup);
    polTextEdit->setPlaceholderText("...");
    polLayout = new QGridLayout(polGroup);
    polLayout->addWidget(polTextEdit, 0, 0, 0, 1);
    polGenButton = new QPushButton("Polinom generálás", polGroup);
    polLayout->addWidget(polGenButton, 0, 2);
    connect(polGenButton, SIGNAL(clicked()), this, SLOT(polGenButtonClicked()));
    polGroup->setLayout(polLayout);
}

void additiveWindow::makeSequenceForm()
{
    seqGroup = new QGroupBox(tr("Sorozat"), this);
    seqTextEdit = new QTextEdit(seqGroup);
    seqLayout = new QGridLayout(seqGroup);
    seqLayout->addWidget(seqTextEdit, 0, 0, 1, 3);
    seqGenButton = new QPushButton("Sorozat generálás", seqGroup);
    seqLayout->addWidget(seqGenButton, 2, 1);
    connect(seqGenButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));
    seqGroup->setLayout(seqLayout);
}

void additiveWindow::polDegButtonClicked()
{
    const QString prime = primeLineEdit->displayText();
    const uint64_t deg = additive.GenerateDegree(prime.toLongLong());
    std::stringstream ss;
    ss << deg;
    QString s = QString::fromStdString(ss.str());
    polDegLineEdit->setText(s);
}

void additiveWindow::polGenButtonClicked()
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

void additiveWindow::generateButtonClicked()
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
    std::vector<std::bitset<8> > sequence = additive.Generate((uint64_t)length_text.toLongLong(), (uint64_t)p_text.toLongLong(), polynom);
    ss.clear();
    ss.str("");
    for(std::vector<std::bitset<8> >::const_iterator it = sequence.begin(); it != sequence.end(); it++)
    {
        ss << it->to_string();
    }
    QString s = QString::fromStdString(ss.str());
    seqTextEdit->setPlainText(s);
}

void additiveWindow::generatePrimeButtonClicked()
{
    const QString len = lengthEdit->displayText();
    const uint64_t p = additive.GeneratePrime(len.toLongLong()*8+1);
    std::stringstream ss;
    ss << p;
    QString s = QString::fromStdString(ss.str());
    primeLineEdit->setText(s);
}

void additiveWindow::nextPrimeButtonClicked()
{
    const QString prime = primeLineEdit->displayText();
    const uint64_t p = additive.GeneratePrime(prime.toLongLong()+2);
    std::stringstream ss;
    ss << p;
    QString s = QString::fromStdString(ss.str());
    primeLineEdit->setText(s);
}

void additiveWindow::backButtonClicked()
{
    polDegLineEdit->clear();
    lengthEdit->clear();
    primeLineEdit->clear();
    polTextEdit->clear();
    seqTextEdit->clear();
    parentWindow->getStack()->setCurrentIndex(0);
}
