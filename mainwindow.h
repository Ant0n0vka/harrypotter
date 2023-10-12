#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNextClicked();
    void onFinishClicked();

private:
    Ui::MainWindow *ui;
    int currentQuestionIndex;
    int correctAnswersCount;

    void loadQuestion(int index);
};

#endif // MAINWINDOW_H
