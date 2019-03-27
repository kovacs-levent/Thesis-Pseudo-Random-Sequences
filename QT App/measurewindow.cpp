#include "measurewindow.h"
#include <QString>
#include <QMessageBox>
#include <sstream>
#include <set>
#include <bitset>
#include "../Measurements/measure.h"

measureWindow::measureWindow(QWidget *parent) : QWidget(parent)
{
    parentWindow = (mainWindow*)parent;
    mainLayout = new QGridLayout(this);
    makeSequenceForm();
    makeDistrForm();
    makeNormalityForm();
    makeCorrelationForm();
    mainLayout->addWidget(sequenceGroup, 0, 0, 1, 2);
    mainLayout->addWidget(distrGroup, 1, 0);
    mainLayout->addWidget(normalityGroup, 1, 1);
    mainLayout->addWidget(correlationGroup, 2, 0);

    backButton = new QPushButton(tr("Vissza"), this);
    mainLayout->addWidget(backButton, 2, 1);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
}

void measureWindow::makeSequenceForm()
{
    sequenceGroup = new QGroupBox(tr("Sorozat"), this);
    seqTextEdit = new QTextEdit(sequenceGroup);
    sequenceLayout = new QGridLayout(sequenceGroup);
    sequenceLayout->addWidget(seqTextEdit, 0, 0, 1, 3);
    seqLoadButton = new QPushButton("Sorozat betöltése", sequenceGroup);
    sequenceLayout->addWidget(seqLoadButton, 2, 1);
    connect(seqLoadButton, SIGNAL(clicked()), this, SLOT(loadSequenceButtonClicked()));
}

void measureWindow::makeDistrForm()
{
    distrGroup = new QGroupBox(tr("Jól-eloszlás"), this);
    distrLineEdit = new QLineEdit(distrGroup);
    distrLayout = new QGridLayout(distrGroup);
    distrLayout->addWidget(distrLineEdit, 0, 0, 1, 3);
    distrCalculateButton = new QPushButton("Számolás", distrGroup);
    distrLayout->addWidget(distrCalculateButton, 2, 1);
    connect(distrCalculateButton, SIGNAL(clicked()), this, SLOT(calculateDistributionButtonClicked()));
}

void measureWindow::makeNormalityForm()
{
    normalityGroup = new QGroupBox(tr("Normalitás"), this);
    normalityLineEdit = new QLineEdit(normalityGroup);
    normalityLayout = new QGridLayout(normalityGroup);
    normalityLayout->addWidget(normalityLineEdit, 0, 0, 1, 3);
    normalityCalculateButton = new QPushButton("Számolás", normalityGroup);
    normalityLayout->addWidget(normalityCalculateButton, 2, 1);
    connect(normalityCalculateButton, SIGNAL(clicked()), this, SLOT(calculateNormalityButtonClicked()));
}

void measureWindow::makeCorrelationForm()
{
    correlationGroup = new QGroupBox(tr("Korreláció"), this);
    correlationLineEdit = new QLineEdit(correlationGroup);
    correlationLayout = new QGridLayout(correlationGroup);
    correlationLayout->addWidget(correlationLineEdit, 0, 0, 1, 3);
    correlationCalculateButton = new QPushButton("Számolás", correlationGroup);
    correlationLayout->addWidget(correlationCalculateButton, 2, 1);
    connect(correlationCalculateButton, SIGNAL(clicked()), this, SLOT(calculateCorrelationButtonClicked()));
}

void measureWindow::calculateDistributionButtonClicked()
{
    const QString sequence = seqTextEdit->toPlainText();
    std::stringstream ss(sequence.toStdString());
    std::vector<bool> vec;
    bool l;
    l = ss.get() - '0';
    while(!ss.fail())
    {
        vec.push_back(l);
        l = ss.get() - '0';
    }
    uint64_t result = wellDistributionMeasure(vec);
    QString s = QString::number(result);
    distrLineEdit->setText(s);
}

void measureWindow::calculateNormalityButtonClicked()
{
    const QString sequence = seqTextEdit->toPlainText();
    std::stringstream ss(sequence.toStdString());
    std::vector<bool> vec;
    bool l;
    l = ss.get() - '0';
    while(!ss.fail())
    {
        vec.push_back(l);
        l = ss.get() - '0';
    }
    long double result = normalityMeasure(vec);
    ss.str("");
    ss.clear();
    ss << result;
    QString s = QString::fromStdString(ss.str());
    normalityLineEdit->setText(s);
}

void measureWindow::loadSequenceButtonClicked()
{

}

void measureWindow::calculateCorrelationButtonClicked()
{
    const QString sequence = seqTextEdit->toPlainText();
    std::stringstream ss(sequence.toStdString());
    std::vector<bool> vec;
    bool l;
    l = ss.get() - '0';
    while(!ss.fail())
    {
        vec.push_back(l);
        l = ss.get() - '0';
    }
    uint64_t result = correlationMeasure(vec);
    QString s = QString::number(result);
    correlationLineEdit->setText(s);
}

/*void measureWindow::generateButtonClicked()
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
        ss.str(pol_str);
        uint64_t tmp;
        ss >> tmp;
        while(!ss.fail())
        {
            polynom.insert(tmp);
            ss >> tmp;
        }
        if(ss.eof() && polynom.size() == d)
        {
            std::vector<bool> sequence = legendre.Generate(length, p, polynom);
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

void measureWindow::generatePrimeButtonClicked()
{
    bool isLengthOk;
    const QString len = lengthEdit->displayText();
    const uint64_t length = (uint64_t)len.toULongLong(&isLengthOk);
    if(isLengthOk && length > 0)
    {
        const uint64_t p = legendre.GenerateValidPrime(length*2+1);
        std::stringstream ss;
        ss << p;
        QString s = QString::fromStdString(ss.str());
        primeLineEdit->setText(s);
    }
    else
    {
        displayError("Adathiba", "A méret mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy pozitív egész számot!");
    }
}

void measureWindow::nextPrimeButtonClicked()
{
    bool isPrimeOk;
    const QString prime = primeLineEdit->displayText();
    const uint64_t tmp = (uint64_t)prime.toULongLong(&isPrimeOk);
    if(isPrimeOk)
    {
        const uint64_t p = legendre.GenerateValidPrime(tmp+2);
        std::stringstream ss;
        ss << p;
        QString s = QString::fromStdString(ss.str());
        primeLineEdit->setText(s);
    }
    else
    {
        displayError("Adathiba", "A prímszám mezőben nincs adat, vagy nem megfelelő a formátuma! A következő prím kereséséhez adjon meg egy szabályos, pozitív számot!");
    }
}*/

void measureWindow::backButtonClicked()
{
    seqTextEdit->clear();
    distrLineEdit->clear();
    normalityLineEdit->clear();
    correlationLineEdit->clear();
    parentWindow->getStack()->setCurrentIndex(0);
}
