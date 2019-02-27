#ifndef LEGENDREWINDOW_H
#define LEGENDREWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QTextEdit>
#include "mainwindow.h"
#include "../LegendreConstruction/LegendreConstruction.h"

class legendreWindow : public QWidget
{
    Q_OBJECT

 public:
  legendreWindow(QWidget *parent = 0);
 private slots:
  void polDegButtonClicked();
  void polGenButtonClicked();
  void generateButtonClicked();
  void generatePrimeButtonClicked();
  void nextPrimeButtonClicked();
 private:
  void makeLengthForm();
  void makePolDeg();
  void makePrimeForm();
  void makePolForm();
  void setButtonsSize();
  void setButtonsSender();
  LegendreConstruction legendre;
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

  QPushButton* backButton;
  mainWindow* parentWindow;
};

#endif // LEGENDREWINDOW_H
