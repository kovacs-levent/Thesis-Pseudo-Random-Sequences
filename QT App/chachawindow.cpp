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
    makeCounterForm();
    makeNonceForm();
    makeSequenceForm();
    mainLayout->addWidget(lengthFormGroup, 0, 0, 1, 2);
    mainLayout->addWidget(counterGroup, 0, 2, 1, 2);
    mainLayout->addWidget(keyGroup, 1, 0, 2, 2);
    mainLayout->addWidget(nonceGroup, 1, 2, 2, 2);
    mainLayout->addWidget(seqGroup, 3, 0, 2, 4);

    backButton = new QPushButton(tr("Vissza"), this);
    mainLayout->addWidget(backButton, 5, 3);
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

void chachaWindow::makeCounterForm()
{
    counterGroup = new QGroupBox(tr("Számláló"), this);
    counterLayout = new QGridLayout(counterGroup);
    counterEdit = new QLineEdit(counterGroup);
    counterEdit->setPlaceholderText("...");
    counterLayout->addWidget(counterEdit, 0, 0);
}

void chachaWindow::makeNonceForm()
{
    nonceGroup = new QGroupBox(tr("Egyszer használatos kulcs"), this);
    nonceLayout = new QGridLayout(nonceGroup);
    nonceEdit = new QTextEdit(nonceGroup);
    nonceGenButton = new QPushButton("Generálás", nonceGroup);
    connect(nonceGenButton, SIGNAL(clicked()), this, SLOT(nonceGenButtonClicked()));
    nonceEdit->setPlaceholderText("...");
    nonceLayout->addWidget(nonceEdit, 0 , 0);
    nonceLayout->addWidget(nonceGenButton, 1, 0);
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
}

void chachaWindow::generateButtonClicked()
{
    std::vector<uint32_t> state;
    state.resize(4);
    state[0] = 0x61707865;
    state[1] = 0x3320646e;
    state[2] = 0x79622d32;
    state[3] = 0x6b206574;
    const QString length_text = lengthEdit->displayText();
    const QString counter_text = counterEdit->displayText();
    const QString key_text = keyEdit->toPlainText();
    const QString nonce_text = nonceEdit->toPlainText();
    std::stringstream ss;
    ss.str(key_text.toStdString());
    uint32_t tmp;
    ss >> tmp;
    while(!ss.fail())
    {
        state.push_back(tmp);
        ss >> tmp;
    }
    state.push_back((uint32_t)counter_text.toLong());
    ss.clear();
    ss.str(nonce_text.toStdString());
    ss >> tmp;
    while(!ss.fail())
    {
        state.push_back(tmp);
        ss >> tmp;
    }
    ss.clear();
    ss.str("");
    chacha.Seed(state);
    std::vector<std::bitset<8> > sequence = chacha.GenerateStream((uint64_t)length_text.toLongLong());
    for(std::vector<std::bitset<8> >::const_iterator it = sequence.begin(); it != sequence.end(); it++)
    {
        ss << it->to_string();
    }
    QString s = QString::fromStdString(ss.str());
    seqTextEdit->setPlainText(s);
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

void chachaWindow::nonceGenButtonClicked()
{
    std::seed_seq seq = GenerateRandomSeed();
    std::vector<uint32_t> key(3);
    seq.generate(key.begin(), key.end());
    std::stringstream ss;
    ss << key[0];
    for(size_t i = 1; i < key.size(); i++)
    {
        ss <<  " " << key[i];
    }
    QString s = QString::fromStdString(ss.str());
    nonceEdit->setText(s);
}
