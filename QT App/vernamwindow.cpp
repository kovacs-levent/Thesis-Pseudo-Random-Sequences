#include "vernamwindow.h"
#include <sstream>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QCoreApplication>

vernamWindow::vernamWindow(QWidget *parent) : QWidget(parent), cipher()
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
    if(vec.size() >= message.size()*7)
    {
        cipher.setKey(vec);
        const QString cipheredText = cipher.Encrypt(message);
        resultTextEdit->setText(cipheredText);
    }
    else
    {
         displayError("Adathiba", "A sorozat mezőben nincs adat, vagy formátuma nem megfelelő! Adjon meg egy szabályos bitsorozatot, mely legalább olyan hosszú mint a bemeneti szöveg bitekben vett hossza!");
    }
}

void vernamWindow::backButtonClicked()
{
    inputTextEdit->clear();
    resultTextEdit->clear();
    seqTextEdit->clear();
    parentWindow->ChangeMenu(0);
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

oneTimePad::oneTimePad()
{
    QFile file("dictionary.txt");
    file.open(QFile::ReadOnly);
    QTextStream in(&file);
    in.setCodec("UTF-8");
    while(!in.atEnd())
    {
       std::cout << "hi";
       QString line = in.readLine();
       QTextStream line_str(&line);
       line_str.setCodec("UTF-8");
       QChar tmp;
       QString tmp2;
       std::bitset<7> seq;
       line_str >> tmp >> tmp2;
       int count = 6;
       for(int i = 0; i < tmp2.size(); i++)
       {
           seq[count] = tmp2[i].unicode() == 49;
           --count;
       }
       std::cout <<  std::endl << tmp.unicode() << " " << seq.to_string() << std::endl;
       letter_dictionary[tmp.unicode()] = seq;
       seq_dictionary[seq.to_string()] = tmp.unicode();
    }
    QChar whitespace(' ');
    std::bitset<7> lastseq("1111111");
    letter_dictionary[whitespace.unicode()] = lastseq;
    seq_dictionary[lastseq.to_string()] = whitespace.unicode();
    std::unordered_map<unsigned short, std::bitset<7> >::iterator it = letter_dictionary.begin();
    std::ofstream logger("log.txt");
    while(it != letter_dictionary.end())
    {
        logger << it->first << " " << it->second.to_string() << std::endl;
        it++;
    }
    std::unordered_map<std::string, unsigned short>::iterator it2 = seq_dictionary.begin();
    while(it2 != seq_dictionary.end())
    {
        logger << it2->first << " " << it2->second << std::endl;
        it2++;
    }
}

QString oneTimePad::Encrypt(const QString &inputText)
{
    std::string inText = inputText.toStdString();
    QString encryptedText;
    for(int i = 0; i < inputText.size(); i++)
    {
        std::bitset<7> byte;
        try
        {
            byte = letter_dictionary.at(inputText[i].unicode());

        }
        catch(std::out_of_range e)
        {
            //std::cout << "char error: " << inputText[i] << " "<< i << std::endl;
            throw(e);
        }
        std::stringstream sstr;
        for(int j = 0; j < 7; j++)
        {
            sstr << key[i*7+j];
        }
        std::bitset<7> byteXOR(sstr.str());
        byte ^= byteXOR;
        try
        {
            QChar c(seq_dictionary.at(byte.to_string()));
            encryptedText.append(c);
        }
        catch(std::out_of_range e)
        {
            //std::cout << "seq error: " << byte << std::endl;
            throw e;
        }
    }
    return encryptedText;
}
