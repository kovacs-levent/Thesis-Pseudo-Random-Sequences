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
    QString vernamCipher(const std::vector<bool> &key, const QString &inputText);
    void makeTextForm();
    void makeBitSeqForm();
    void makeResultForm();
    void makeDictionary();
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

    std::unordered_map<unsigned short, std::bitset<7> > letter_dictionary;
    std::unordered_map<std::string, unsigned short> seq_dictionary;
};

#endif // VERNAMWINDOW_H
