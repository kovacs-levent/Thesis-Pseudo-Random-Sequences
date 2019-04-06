#include "vernamwindow.h"
#include <sstream>
#include <bitset>

vernamWindow::vernamWindow(QWidget *parent) : QWidget(parent)
{
    parentWindow = (mainWindow*)parent;
    mainLayout = new QGridLayout(this);

    makeTextForm();
    makeBitSeqForm();
    makeResultForm();

    mainLayout->addWidget(inputGroup, 0, 0, 1, 4);
    mainLayout->addWidget(seqGroup, 1, 0, 2, 4);
    mainLayout->addWidget(resultGroup, 3, 0, 1, 4);
    backButton = new QPushButton(tr("Vissza"), this);
    mainLayout->addWidget(backButton, 4, 3);
    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
}

void vernamWindow::makeTextForm()
{
    inputGroup = new QGroupBox(tr("Titkosítandó szöveg"), this);
    inputLayout = new QGridLayout(inputGroup);
    inputTextEdit = new QTextEdit(inputGroup);
    inputLayout->addWidget(inputTextEdit, 0, 0);
}

void vernamWindow::makeBitSeqForm()
{
    seqGroup = new QGroupBox(tr("Sorozat"), this);
    seqTextEdit = new QTextEdit(seqGroup);
    seqLayout = new QGridLayout(seqGroup);
    seqLayout->addWidget(seqTextEdit, 0, 0, 1, 4);
    seqLoadButton = new QPushButton("Sorozat betöltése", seqGroup);
    oneTimePadButton = new QPushButton("Szöveg titkosítása", seqGroup);
    connect(seqLoadButton, SIGNAL(clicked()), this, SLOT(seqLoadButtonClicked()));
    connect(oneTimePadButton, SIGNAL(clicked()), this, SLOT(oneTimePadButtonClicked()));
    seqLayout->addWidget(seqLoadButton, 1, 1);
    seqLayout->addWidget(oneTimePadButton, 1, 2);
}

void vernamWindow::makeResultForm()
{
    resultGroup = new QGroupBox(tr("A titkosított szöveg"), this);
    resultLayout = new QGridLayout(resultGroup);
    resultTextEdit = new QTextEdit(resultGroup);
    resultTextEdit->setReadOnly(true);
    resultLayout->addWidget(resultTextEdit, 0, 0);
}

void vernamWindow::oneTimePadButtonClicked()
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
    const QString message = inputTextEdit->toPlainText();
    const QString cipheredText = vernamCipher(vec, message);
    resultTextEdit->setText(cipheredText);
}

QString vernamWindow::vernamCipher(const std::vector<bool> &key, const QString &inputText)
{
    std::string str = inputText.toStdString();
    std::string encryptedText = "";
    for(size_t i = 0; i < str.size(); ++i)
    {
        std::bitset<CHAR_BIT> byte = str[i];
        std::bitset<CHAR_BIT> byteXOR;
        for(int j = 0; j < CHAR_BIT; j++)
        {
            byteXOR[j] = key[i*CHAR_BIT+j];
        }
        byte ^= byteXOR;
        encryptedText.push_back((char)(byte.to_ulong()));
    }
    return QString::fromStdString(encryptedText);
}

void vernamWindow::backButtonClicked()
{
    inputTextEdit->clear();
    resultTextEdit->clear();
    seqTextEdit->clear();
    parentWindow->getStack()->setCurrentIndex(0);
}

void vernamWindow::seqLoadButtonClicked()
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
