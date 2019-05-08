#include "measurewindow.h"
#include <QString>
#include <QMessageBox>
#include <sstream>
#include <set>
#include "../Measurements/measure.h"

measureWindow::measureWindow(QWidget *parent) : QWidget(parent)
{
    parentWindow = (mainWindow*)parent;
    mainLayout = new QGridLayout(this);
    makeSequenceForm();
    makeDistrForm();
    makeNormalityForm();
    makeCorrelationForm();
    mainLayout->addWidget(sequenceGroup, 0, 0, 1, 6);
    mainLayout->addWidget(distrGroup, 1, 0, 1, 3);
    mainLayout->addWidget(normalityGroup, 1, 3, 1, 3);
    mainLayout->addWidget(correlationGroup, 2, 0, 1, 6);

    backButton = new QPushButton(tr("Vissza"), this);
    mainLayout->addWidget(backButton, 3, 4, 1, 2);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
}

void measureWindow::makeSequenceForm()
{
    sequenceGroup = new QGroupBox(tr("Sorozat"), this);
    seqTextEdit = new QTextEdit(sequenceGroup);
    sequenceLayout = new QGridLayout(sequenceGroup);
    sequenceLayout->addWidget(seqTextEdit, 0, 0, 1, 6);
    seqLoadButton = new QPushButton("Sorozat betöltése", sequenceGroup);
    sequenceLayout->addWidget(seqLoadButton, 2, 2, 1, 2);
    connect(seqLoadButton, SIGNAL(clicked()), this, SLOT(loadSequenceButtonClicked()));
}

void measureWindow::makeDistrForm()
{
    distrGroup = new QGroupBox(tr("Jól-eloszlás"), this);
    distrLineEdit = new QLineEdit(distrGroup);
    distrLineEdit->setReadOnly(true);
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
    normalityLineEdit->setReadOnly(true);
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
    correlationLineEdit->setPlaceholderText("Eredmény");
    correlationLineEdit->setReadOnly(true);
    correlationDegLineEdit = new QLineEdit(correlationGroup);
    correlationDegLineEdit->setPlaceholderText("Rend");
    correlationRoundsLineEdit = new QLineEdit(correlationGroup);
    correlationRoundsLineEdit->setPlaceholderText("Menetek");
    correlationLayout = new QGridLayout(correlationGroup);
    correlationLayout->addWidget(correlationLineEdit, 0, 4, 1, 2);
    correlationLayout->addWidget(correlationDegLineEdit, 0, 0, 1, 2);
    correlationLayout->addWidget(correlationRoundsLineEdit, 0, 2, 1, 2);
    correlationCalculateButton = new QPushButton("Számolás", correlationGroup);
    correlationLayout->addWidget(correlationCalculateButton, 1, 2, 1, 2);
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
    std::vector<bool> seq = parentWindow->getSavedSeq();
    std::stringstream ss;
    for(size_t i = 0; i < seq.size(); ++i)
    {
        ss << seq[i];
    }
    QString sequenceText = QString::fromStdString(ss.str());
    seqTextEdit->setText(sequenceText);
}

void measureWindow::calculateCorrelationButtonClicked()
{
    bool isOrderOk, isRoundsOk;
    const QString sequence = seqTextEdit->toPlainText();
    const QString orderText = correlationDegLineEdit->displayText();
    const QString roundsText = correlationRoundsLineEdit->displayText();

    const uint32_t order = (uint32_t)orderText.toULongLong(&isOrderOk);
    const uint32_t rounds = (uint32_t)roundsText.toULongLong(&isRoundsOk);
    isOrderOk = isOrderOk && order > 0;
    isRoundsOk = isRoundsOk && round > 0;
    if(isOrderOk && isRoundsOk)
    {
        std::stringstream ss(sequence.toStdString());
        std::vector<bool> vec;
        bool l;
        l = ss.get() - '0';
        while(!ss.fail())
        {
            vec.push_back(l);
            l = ss.get() - '0';
        }
        uint64_t result = kCorrelationApprox(vec, order, rounds);
        QString s = QString::number(result);
        correlationLineEdit->setText(s);
    }
    else
    {
        if(!isOrderOk)
        {
            displayError("Adathiba", "A rend mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy pozitív egész számot!");
        }
        else
        {
            displayError("Adathiba", "A menet mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy pozitív egész számot!");
        }
    }
}

void measureWindow::backButtonClicked()
{
    seqTextEdit->clear();
    distrLineEdit->clear();
    normalityLineEdit->clear();
    correlationLineEdit->clear();
    correlationDegLineEdit->clear();
    correlationRoundsLineEdit->clear();
    parentWindow->setWindowTitle(tr("Pszeudovéletlen sorozatok mértékei és konstrukciói"));
    parentWindow->ChangeMenu(0);
}
