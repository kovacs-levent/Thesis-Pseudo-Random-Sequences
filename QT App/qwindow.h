#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class Window : public QWidget
{
    Q_OBJECT

 public:
  Window(QWidget *parent = 0);
 private slots:
  void legendreButtonClicked();
  void rc4ButtonClicked();
  void additiveButtonClicked();
  void chachaButtonClicked();
  void linearButtonClicked();
  void measuresButtonClicked();
  void cryptoButtonClicked();
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
};

#endif // WINDOW_H
