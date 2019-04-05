#ifndef ADDITIVEWINDOW_H
#define ADDITIVEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QTextEdit>
#include "mainwindow.h"
#include "../AdditiveConstruction/AdditiveConstruction.h"

class additiveWindow : public QWidget
{
    Q_OBJECT

 public:
  additiveWindow(QWidget *parent = 0);
 private slots:
  void polDegButtonClicked();
  void polGenButtonClicked();
  void generateButtonClicked();
  void generatePrimeButtonClicked();
  void nextPrimeButtonClicked();
  void seqSaveButtonClicked();
  void backButtonClicked();
 private:
  void makeLengthForm();
  void makePolDeg();
  void makePrimeForm();
  void makePolForm();
  void makeSequenceForm();

  AdditiveConstruction additive;
  QLabel* welcomeMessage;
  QGridLayout* mainLayout;
  QGridLayout* polDegLayout;
  QGroupBox* polDegGroup;
  QPushButton* polDegGenButton;
  QLineEdit* polDegLineEdit;

  QGridLayout* lengthFormLayout;
  QGroupBox* lengthFormGroup;
  QLineEdit* lengthEdit;

  QGridLayout* primeLayout;
  QGroupBox* primeGroup;
  QPushButton* primeGenButton;
  QPushButton* primeNextButton;
  QLineEdit* primeLineEdit;

  QGridLayout* polLayout;
  QGroupBox* polGroup;
  QPushButton* polGenButton;
  QTextEdit* polTextEdit;

  QGridLayout* seqLayout;
  QGroupBox* seqGroup;
  QPushButton* seqGenButton;
  QTextEdit* seqTextEdit;
  QPushButton* seqSaveButton;

  QPushButton* backButton;
  mainWindow* parentWindow;
};

#endif // ADDITIVEWINDOW_H
