#include "chachawindow.h"
#include "../GeneralPRNG/SeedGenerator.h"
#include <sstream>
#include <vector>
#include <bitset>
#include <sstream>

chachaWindow::chachaWindow(QWidget *parent) : QWidget(parent)
{
    parentWindow = (mainWindow*)parent;
    mainLayout = new QGridLayout(this);
    makeLengthForm();
    makeKeyForm();
    makeSequenceForm();
    mainLayout->addWidget(lengthFormGroup, 0, 0);
    mainLayout->addWidget(keyGroup, 0, 1);
    mainLayout->addWidget(seqGroup, 1, 0, 2, 3);

    backButton = new QPushButton(tr("Vissza"), this);
    mainLayout->addWidget(backButton, 3, 1);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
}

void chachaWindow::makeLengthForm()
{
    lengthFormGroup = new QGroupBox(tr("Sorozat mérete"), this);
    lengthLayout = new QGridLayout(lengthFormGroup);
    lengthEdit = new QLineEdit(lengthFormGroup);
    lengthEdit->setPlaceholderText("...");
    lengthEdit->setFocus();
    lengthLayout->addWidget(lengthEdit, 0, 0, 0, 1);
}

void chachaWindow::makeKeyForm()
{
    keyGroup = new QGroupBox(tr("Kulcs"), this);
    keyLayout = new QGridLayout(keyGroup);
    keyEdit = new QTextEdit(keyGroup);
    keyGenButton = new QPushButton("Generálás", keyGroup);
    connect(keyGenButton, SIGNAL(clicked()), this, SLOT(keyGenButtonClicked()));
    keyEdit->setPlaceholderText("...");
    keyLayout->addWidget(keyEdit, 0, 0);
    keyLayout->addWidget(keyGenButton, 1, 0);
}

void chachaWindow::makeSequenceForm()
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

void chachaWindow::generateButtonClicked()
{

}

void chachaWindow::backButtonClicked()
{
    parentWindow->getStack()->setCurrentIndex(0);

}

void chachaWindow::keyGenButtonClicked()
{
    std::seed_seq seq = GenerateRandomSeed();
    std::vector<uint32_t> key(8);
    seq.generate(key.begin(), key.end());
    std::stringstream ss;
    ss << key[0];
    for(size_t i = 1; i < key.size(); i++)
    {
        ss <<  " " << key[i];
    }
    QString s = QString::fromStdString(ss.str());
    keyEdit->setText(s);
}
