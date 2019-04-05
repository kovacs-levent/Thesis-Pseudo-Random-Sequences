#ifndef VERNAMWINDOW_H
#define VERNAMWINDOW_H
#include "mainwindow.h"
#include <QTextEdit>
#include <QWidget>
#include <QGroupBox>
#include <QPushButton>

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
};

#endif // VERNAMWINDOW_H
