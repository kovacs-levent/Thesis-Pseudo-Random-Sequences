#include "chachawindow.h"
#include "../GeneralPRNG/SeedGenerator.h"
#include <sstream>
#include <vector>
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
    seqTextEdit->setReadOnly(true);
    seqLayout = new QGridLayout(seqGroup);
    seqLayout->addWidget(seqTextEdit, 0, 0, 1, 3);
    seqGenButton = new QPushButton("Sorozat generálás", seqGroup);
    seqLayout->addWidget(seqGenButton, 2, 1);
    seqSaveButton = new QPushButton("Sorozat mentése", seqGroup);
    seqLayout->addWidget(seqSaveButton, 2, 2);
    connect(seqSaveButton, SIGNAL(clicked()), this, SLOT(seqSaveButtonClicked()));
    connect(seqGenButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));
}

void chachaWindow::generateButtonClicked()
{
    bool isLengthOk;
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

    const uint64_t length = length_text.toULongLong(&isLengthOk);
    if(isLengthOk)
    {
        std::stringstream ss;
        ss.str(key_text.toStdString());
        uint32_t tmp;
        ss >> tmp;
        while(!ss.fail())
        {
            state.push_back(tmp);
            ss >> tmp;
        }
        if(ss.eof() && state.size() == 12)
        {
            bool isCounterOk;
            const uint32_t counter = (uint32_t)counter_text.toULong(&isCounterOk);
            if(isCounterOk)
            {
                state.push_back(counter);
                ss.clear();
                ss.str(nonce_text.toStdString());
                ss >> tmp;
                while(!ss.fail())
                {
                    state.push_back(tmp);
                    ss >> tmp;
                }
                if(ss.eof() && state.size() == 16)
                {
                    ss.clear();
                    ss.str("");
                    chacha.Seed(state);
                    std::vector<bool> sequence = chacha.GenerateStream(length);
                    for(std::vector<bool>::const_iterator it = sequence.begin(); it != sequence.end(); it++)
                    {
                        ss << *it;
                    }
                    QString s = QString::fromStdString(ss.str());
                    seqTextEdit->setPlainText(s);
                }
                else
                {
                    displayError("Adathiba", "Az egyszeri kulcs mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg szóközökkel elválasztva 3 pozitív egész számot!");
                }
            }
            else
            {
                displayError("Adathiba", "A számlaló mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy pozitív egész számot!");
            }
        }
        else
        {
            displayError("Adathiba", "A kulcs mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg szóközökkel elválasztva 8 pozitív egész számot!");
        }
    }
    else
    {
        displayError("Adathiba", "A méret mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy pozitív egész számot!");
    }
}

void chachaWindow::backButtonClicked()
{
    lengthEdit->clear();
    keyEdit->clear();
    counterEdit->clear();
    nonceEdit->clear();
    seqTextEdit->clear();
    parentWindow->setWindowTitle(tr("Pszeudovéletlen sorozatok mértékei és konstrukciói"));
    parentWindow->ChangeMenu(0);
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

void chachaWindow::seqSaveButtonClicked()
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
