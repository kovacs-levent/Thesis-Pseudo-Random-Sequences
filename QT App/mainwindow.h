#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_MAINWINDOW_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QStackedLayout>
#include <QMessageBox>

void displayError(const std::string &errorTitle, const std::string &errorMessage);

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
    QWidget* layoutWidget;
    QVBoxLayout* mainLayout;
};

#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_MAINWINDOW_H
