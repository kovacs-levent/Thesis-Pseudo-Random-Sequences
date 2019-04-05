#ifndef RC4WINDOW_H
#define RC4WINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QTextEdit>
#include "mainwindow.h"
#include "../RC4/RC4_PRG.h"

class rc4Window : public QWidget
{
    Q_OBJECT

public:
    rc4Window(QWidget *parent = 0);
private slots:
    void generateButtonClicked();
    void seqSaveButtonClicked();
    void backButtonClicked();
private:
    void makeLengthForm();
    void makeKeyForm();
    void makeSequenceForm();

    RC4_PRG rc;
    QGridLayout* mainLayout;

    QGridLayout* lengthLayout;
    QGroupBox* lengthFormGroup;
    QLineEdit* lengthEdit;

    QGridLayout* keyLayout;
    QGroupBox* keyGroup;
    QLineEdit* keyEdit;

    QGridLayout* seqLayout;
    QGroupBox* seqGroup;
    QPushButton* seqGenButton;
    QTextEdit* seqTextEdit;
    QPushButton* seqSaveButton;

    QPushButton* backButton;
    mainWindow* parentWindow;
};

#endif // RC4WINDOW_H
