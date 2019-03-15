#ifndef CHACHAWINDOW_H
#define CHACHAWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QTextEdit>
#include "mainwindow.h"
#include "../ChaCha20/ChaCha20Construction.h"

class chachaWindow : public QWidget
{
    Q_OBJECT

public:
    chachaWindow(QWidget *parent = 0);
private slots:
    void generateButtonClicked();
    void keyGenButtonClicked();
    void backButtonClicked();
private:
    void makeLengthForm();
    void makeKeyForm();
    void makeCounterForm();
    void makeNounceForm();
    void makeSequenceForm();

    ChaCha20Construction chacha;
    QGridLayout* mainLayout;

    QGridLayout* lengthLayout;
    QGroupBox* lengthFormGroup;
    QLineEdit* lengthEdit;

    QGridLayout* keyLayout;
    QGroupBox* keyGroup;
    QPushButton* keyGenButton;
    QTextEdit* keyEdit;

    QGridLayout* seqLayout;
    QGroupBox* seqGroup;
    QPushButton* seqGenButton;
    QTextEdit* seqTextEdit;

    QPushButton* backButton;
    mainWindow* parentWindow;
};

#endif // CHACHAWINDOW_H
