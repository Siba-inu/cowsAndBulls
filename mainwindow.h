#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_Game_triggered();

    void on_actionQuit_triggered();

    void on_OkButton_clicked();

private:
    Ui::MainWindow *ui;
    QString random_string_;
    int numberOfGuess = 0;
};
#endif // MAINWINDOW_H
