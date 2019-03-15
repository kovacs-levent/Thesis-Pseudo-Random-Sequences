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
    void nonceGenButtonClicked();
    void backButtonClicked();
private:
    void makeLengthForm();
    void makeKeyForm();
    void makeCounterForm();
    void makeNonceForm();
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

    QGridLayout* counterLayout;
    QGroupBox* counterGroup;
    QLineEdit* counterEdit;

    QGridLayout* nonceLayout;
    QGroupBox* nonceGroup;
    QPushButton* nonceGenButton;
    QTextEdit* nonceEdit;

    QGridLayout* seqLayout;
    QGroupBox* seqGroup;
    QPushButton* seqGenButton;
    QTextEdit* seqTextEdit;

    QPushButton* backButton;
    mainWindow* parentWindow;
};

#endif // CHACHAWINDOW_H
