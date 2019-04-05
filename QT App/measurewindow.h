#ifndef MEASUREWINDOW_H
#define MEASUREWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QTextEdit>
#include "mainwindow.h"

class measureWindow : public QWidget
{
    Q_OBJECT

 public:
  measureWindow(QWidget *parent = 0);
 private slots:
  void loadSequenceButtonClicked();
  void calculateDistributionButtonClicked();
  void calculateNormalityButtonClicked();
  void calculateCorrelationButtonClicked();
  void backButtonClicked();
 private:
  void makeSequenceForm();
  void makeDistrForm();
  void makeNormalityForm();
  void makeCorrelationForm();

  QLabel* welcomeMessage;
  QGridLayout* mainLayout;
  QGridLayout* sequenceLayout;
  QGroupBox* sequenceGroup;
  QPushButton* seqLoadButton;
  QTextEdit* seqTextEdit;

  QGridLayout* distrLayout;
  QGroupBox* distrGroup;
  QPushButton* distrCalculateButton;
  QLineEdit* distrLineEdit;


  QGridLayout* normalityLayout;
  QGroupBox* normalityGroup;
  QPushButton* normalityCalculateButton;
  QLineEdit* normalityLineEdit;

  QGridLayout* correlationLayout;
  QGroupBox* correlationGroup;
  QPushButton* correlationCalculateButton;
  QLineEdit* correlationLineEdit;
  QLineEdit* correlationDegLineEdit;
  QLineEdit* correlationRoundsLineEdit;

  QPushButton* backButton;
  mainWindow* parentWindow;
};

#endif // MEASUREWINDOW_H
