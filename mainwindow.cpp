#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <QMessageBox>
#include <time.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    on_actionNew_Game_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int GetRandomNumber(int min, int max)
{
  // Установить генератор случайных чисел
  srand(time(NULL));

  // Получить случайное число - формула
  int num = min + rand() % (max - min + 1);

  return num;
}

bool isExist(QString a, QString c)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == c)
            return true;
    }
    return false;
}

void MainWindow::on_actionNew_Game_triggered()
{
    ui->answer->setText("");
    srand(time(NULL));
    int count = 0;
    random_string_.clear();
    while(random_string_.size() != 4)
    {
        int a;
        if (count == 0)
            a = GetRandomNumber(1, 9);
        else
            a = GetRandomNumber(0, 9);
        QString s = QString::number(a);
        if (!isExist(random_string_, s))
            random_string_.push_back(s);
    }
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}


void MainWindow::on_OkButton_clicked()
{
    qDebug() << random_string_;
    QString readText = ui->textEdit->toPlainText();
    if (readText.size() != 4)
    {
        QMessageBox::warning(this, "Предупреждение", "Введите четырехзначное число с неповторяющимися числами");
        ui->textEdit->clear();
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                if (readText[i] == readText[j])
                {
                    QMessageBox::warning(this, "Предупреждение", "Введите четырехзначное число с неповторяющимися числами");
                    return;
                }
            }
        }
        numberOfGuess++;
        int cows = 0, bulls = 0;
        for (int i = 0; i < readText.size() && i < random_string_.size(); i++)
        {
            for (int j = 0; j < readText.size() && j < random_string_.size(); j++)
            {
                if (readText[i] == random_string_[j] && (i == j))
                    bulls++;
                if (readText[i] == random_string_[j] && (i != j))
                    cows++;
            }
        }
        QMessageBox::warning(this, "Попытка " + QString::number(numberOfGuess),
                             "Коровы " + QString::number(cows) + ", быки " + QString::number(bulls));
        if (bulls == 4)
        {
            QMessageBox::warning(this, "Поздравляем!", "Вы выиграли");
            on_actionNew_Game_triggered();
        }
    }
}
