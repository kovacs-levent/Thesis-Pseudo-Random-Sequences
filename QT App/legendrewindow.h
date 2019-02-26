#ifndef LEGENDREWINDOW_H
#define LEGENDREWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "mainwindow.h"

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
  void makeButtons();
  void setButtonsSize();
  void setButtonsSender();
  QLabel* welcomeMessage;
  QVBoxLayout* mainLayout;
  QGridLayout* buttonLayout;
  QPushButton* legendreButton;
  QPushButton* rc4Button;
  QPushButton* additiveButton;
  QPushButton* chachaButton;
  QPushButton* linearButton;
  QPushButton* measuresButton;
  QPushButton* cryptoButton;
  QPushButton* quitButton;
  mainWindow* parentWindow;
};

#endif // LEGENDREWINDOW_H
