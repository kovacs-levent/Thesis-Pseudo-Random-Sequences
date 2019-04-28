#include "rc4window.h"
#include <sstream>
#include <vector>
rc4Window::rc4Window(QWidget *parent) : QWidget(parent)
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

void rc4Window::makeLengthForm()
{
    lengthFormGroup = new QGroupBox(tr("Sorozat mérete"), this);
    lengthLayout = new QGridLayout(lengthFormGroup);
    lengthEdit = new QLineEdit(lengthFormGroup);
    lengthEdit->setPlaceholderText("...");
    lengthEdit->setFocus();
    lengthLayout->addWidget(lengthEdit, 0, 0, 0, 1);
}

void rc4Window::makeKeyForm()
{
    keyGroup = new QGroupBox(tr("Kulcs"), this);
    keyLayout = new QGridLayout(keyGroup);
    keyEdit = new QLineEdit(keyGroup);
    keyEdit->setPlaceholderText("...");
    keyLayout->addWidget(keyEdit, 0, 0);
}

void rc4Window::makeSequenceForm()
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

void rc4Window::generateButtonClicked()
{
    bool isKeyOk, isLengthOk;
    const QString length_text = lengthEdit->displayText();
    const QString key_text = keyEdit->displayText();
    const uint64_t length = (uint64_t)length_text.toULongLong(&isLengthOk);
    const std::string key = key_text.toStdString();
    isKeyOk = key.length() >= 5 && key.length() <= 256;
    if(isLengthOk && isKeyOk && length > 0)
    {
        rc.SetKey(key);
        std::vector<bool> sequence = rc.GenerateStream(length);
        std::stringstream ss;
        for(std::vector<bool>::const_iterator it = sequence.begin(); it != sequence.end(); it++)
        {
            ss << *it;
        }
        QString s = QString::fromStdString(ss.str());
        seqTextEdit->setPlainText(s);
    }
    else
    {
        if(!isLengthOk || length <= 0)
        {
            displayError("Adathiba", "A méret mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy pozitív egész számot.");
        }
        else
        {
            displayError("Adathiba", "A kulcs mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy legalább 5, maximum 256 karakter hosszúságú szöveget!");
        }
    }
}

void rc4Window::backButtonClicked()
{
    lengthEdit->clear();
    keyEdit->clear();
    seqTextEdit->clear();
    parentWindow->setWindowTitle(tr("Pszeudovéletlen sorozatok mértékei és konstrukciói"));
    parentWindow->ChangeMenu(0);
}

void rc4Window::seqSaveButtonClicked()
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
