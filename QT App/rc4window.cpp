#include "rc4window.h"
#include <sstream>
#include <vector>
#include <bitset>

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
    seqLayout = new QGridLayout(seqGroup);
    seqLayout->addWidget(seqTextEdit, 0, 0, 1, 3);
    seqGenButton = new QPushButton("Sorozat generálás", seqGroup);
    seqLayout->addWidget(seqGenButton, 2, 1);
    connect(seqGenButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));
}

void rc4Window::generateButtonClicked()
{
    const QString length_text = lengthEdit->displayText();
    const QString key_text = keyEdit->displayText();
    rc.SetKey(key_text.toStdString());
    std::vector<std::bitset<8> > sequence = rc.GenerateStream((uint64_t)length_text.toLongLong());
    std::stringstream ss;
    for(std::vector<std::bitset<8> >::const_iterator it = sequence.begin(); it != sequence.end(); it++)
    {
        ss << it->to_string();
    }
    QString s = QString::fromStdString(ss.str());
    seqTextEdit->setPlainText(s);
}

void rc4Window::backButtonClicked()
{
    lengthEdit->clear();
    keyEdit->clear();
    seqTextEdit->clear();
    parentWindow->getStack()->setCurrentIndex(0);
}
