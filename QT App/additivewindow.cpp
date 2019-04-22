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
}

void additiveWindow::makeSequenceForm()
{
    seqGroup = new QGroupBox(tr("Sorozat"), this);
    seqTextEdit = new QTextEdit(seqGroup);
    seqTextEdit->setReadOnly(true);
    seqLayout = new QGridLayout(seqGroup);
    seqLayout->addWidget(seqTextEdit, 0, 0, 1, 3);
    seqGenButton = new QPushButton("Sorozat generálás", seqGroup);
    seqLayout->addWidget(seqGenButton, 2, 1);
    seqSaveButton = new QPushButton("Sorozat mentése", seqGroup);
    seqLayout->addWidget(seqSaveButton, 2, 2);
    connect(seqGenButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));
    connect(seqSaveButton, SIGNAL(clicked()), this, SLOT(seqSaveButtonClicked()));
}

void additiveWindow::polDegButtonClicked()
{
    bool isPrimeOk;
    const QString prime_text = primeLineEdit->displayText();
    const uint64_t prime = (uint64_t)prime_text.toULongLong(&isPrimeOk);
    if(isPrimeOk)
    {
        const uint64_t deg = additive.GenerateDegree(prime);
        std::stringstream ss;
        ss << deg;
        QString s = QString::fromStdString(ss.str());
        polDegLineEdit->setText(s);
    }
    else
    {
        displayError("Adathiba", "A prímszám mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy szabályos prímszámot.");
    }
}

void additiveWindow::polGenButtonClicked()
{
    bool isDegOk, isPrimeOk;
    const QString deg = polDegLineEdit->displayText();
    const QString modulus = primeLineEdit->displayText();
    const uint64_t m = (uint64_t)modulus.toULongLong(&isPrimeOk);
    const uint32_t d = (uint32_t)deg.toULong(&isDegOk);
    if(isDegOk && isPrimeOk && d > 1 && m >= d)
    {
        const std::set<uint64_t> polynom = GenerateSimpleModPoly(m, d);
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
    else
    {
        if(!isPrimeOk)
        {
            displayError("Adathiba", "A prímszám mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy szabályos prímszámot.");
        }
        else
        {
            displayError("Adathiba", "A fokszám mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy a prímszámnál kisebb, de 1-nél pozitív egész számot.");
        }
    }
}

void additiveWindow::generateButtonClicked()
{
    bool isLengthOk, isPrimeOk, isPolTextOk, isDegOk;
    const QString length_text = lengthEdit->displayText();
    const QString p_text = primeLineEdit->displayText();
    const QString deg_text = polDegLineEdit->displayText();
    const QString polynom_text = polTextEdit->toPlainText();

    const std::string pol_str = polynom_text.toStdString();
    const uint64_t length = (uint64_t)length_text.toULongLong(&isLengthOk);
    const uint64_t p = (uint64_t)p_text.toULongLong(&isPrimeOk);
    const uint32_t d = (uint32_t)deg_text.toULong(&isDegOk);

    isPolTextOk = pol_str.find_first_not_of(' ') != std::string::npos;
    if(isLengthOk && isPrimeOk && isPolTextOk && isDegOk && d > 1 && length > 0 && p > 2)
    {
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
        if(ss.eof() && polynom.size() == d)
        {
            std::vector<bool> sequence = additive.Generate((uint64_t)length_text.toLongLong(), (uint64_t)p_text.toLongLong(), polynom);
            ss.clear();
            ss.str("");
            for(std::vector<bool>::const_iterator it = sequence.begin(); it != sequence.end(); it++)
            {
                ss << *it;
            }
            QString s = QString::fromStdString(ss.str());
            seqTextEdit->setPlainText(s);
        }
        else
        {
            displayError("Adathiba", "A polinom formátuma nem megfelelő! Adjon meg szóközökkel elválasztva, a fokszámmal megegyező számú pozitív egész számot!");
        }
    }
    else
    {
        if(!isLengthOk || length <= 0)
        {
            displayError("Adathiba", "A méret mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy pozitív egész számot!");
        }
        else if(!isPolTextOk)
        {
            displayError("Adathiba", "A polinom mező üres! Adjon meg szóközökkel elválasztva pozitív egész számokat!");
        }
        else if(!isDegOk || d <= 1)
        {
            displayError("Adathiba", "A fokszám mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy 1-nél nagyobb, de a prímszámnál kisebb számot!");
        }
        else
        {
            displayError("Adathiba" , "A prímszám mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy 2-nél nagyobb prímszámot!");
        }
    }
}

void additiveWindow::generatePrimeButtonClicked()
{
    bool isLengthOk;
    const QString length_text = lengthEdit->displayText();
    const uint64_t length = (uint64_t)length_text.toULongLong(&isLengthOk);
    if(isLengthOk && length > 0)
    {
        const uint64_t p = additive.GeneratePrime(length+1);
        std::stringstream ss;
        ss << p;
        QString s = QString::fromStdString(ss.str());
        primeLineEdit->setText(s);
    }
    else
    {
         displayError("Adathiba", "A méret mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy pozitív egész számot.");
    }
}

void additiveWindow::nextPrimeButtonClicked()
{
    bool isPrimeOk;
    const QString prime_text = primeLineEdit->displayText();
    const uint64_t prime = (uint64_t)prime_text.toULongLong(&isPrimeOk);
    if(isPrimeOk)
    {
        const uint64_t p = additive.GeneratePrime(prime+2);
        std::stringstream ss;
        ss << p;
        QString s = QString::fromStdString(ss.str());
        primeLineEdit->setText(s);
    }
    else
    {
        displayError("Adathiba", "A prímszám mezőben nincs adat, vagy nem megfelelő a formátuma! A következő prím kereséséhez adjon meg egy szabályos, pozitív számot!");
    }
}

void additiveWindow::backButtonClicked()
{
    polDegLineEdit->clear();
    lengthEdit->clear();
    primeLineEdit->clear();
    polTextEdit->clear();
    seqTextEdit->clear();
    parentWindow->ChangeMenu(0);
}

void additiveWindow::seqSaveButtonClicked()
{
    std::vector<bool> vec;
    const QString seq = seqTextEdit->toPlainText();
    std::stringstream sstream(seq.toStdString());
    bool l;
    l = sstream.get() - '0';
    while(!sstream.fail())
    {
        vec.push_back(l);
        l = sstream.get() - '0';
    }
    parentWindow->setSavedSeq(vec);
}
