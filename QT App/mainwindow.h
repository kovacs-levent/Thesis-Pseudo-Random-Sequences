#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_MAINWINDOW_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QStackedLayout>

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    mainWindow(QWidget *parent = 0);
    QStackedLayout* getStack()
    {
        return stack;
    }
private:
    QStackedLayout* stack;
    QVBoxLayout* mainLayout;
};

#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_MAINWINDOW_H
