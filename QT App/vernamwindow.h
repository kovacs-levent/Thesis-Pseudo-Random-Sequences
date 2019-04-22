#ifndef VERNAMWINDOW_H
#define VERNAMWINDOW_H
#include "mainwindow.h"
#include <QTextEdit>
#include <string>
#include <QWidget>
#include <QGroupBox>
#include <QString>
#include <QPushButton>
#include <unordered_map>
#include <bitset>

class oneTimePad
{
public:
    oneTimePad();
    void setKey(const std::vector<bool> &newkey)
    {
        key = newkey;
    }
    QString Encrypt(const QString &inputText);
private:
    std::vector<bool> key;
    std::unordered_map<unsigned short, std::bitset<7> > letter_dictionary;
    std::unordered_map<std::string, unsigned short> seq_dictionary;
};

class vernamWindow : public QWidget
{
    Q_OBJECT

public:
    vernamWindow(QWidget *parent = 0);
private slots:
    void oneTimePadButtonClicked();
    void seqLoadButtonClicked();
    void backButtonClicked();
private:
    void makeTextForm();
    void makeBitSeqForm();
    void makeResultForm();
    QGridLayout* mainLayout;
    QGroupBox* inputGroup;
    QGridLayout* inputLayout;
    QTextEdit* inputTextEdit;

    QGroupBox* seqGroup;
    QTextEdit* seqTextEdit;
    QGridLayout* seqLayout;
    QPushButton* seqLoadButton;
    QPushButton* oneTimePadButton;

    QGroupBox* resultGroup;
    QGridLayout* resultLayout;
    QTextEdit* resultTextEdit;

    QPushButton* backButton;
    mainWindow* parentWindow;

    oneTimePad cipher;
};

#endif // VERNAMWINDOW_H
