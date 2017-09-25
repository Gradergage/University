#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QInputDialog>
#include <QWidget>
#include <QMessageBox>
#include <QPalette>
#include <QBrush>
#include "bot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //кнопка выхода

    //показывает автора
    void on_actionAuthor_triggered();
    //вызов игры типа игрок против игрока
    void on_menupvp_clicked();
    //вызов игры против компьютера
    void on_menubot_clicked();
    //смена имени главного игрока
    void on_actionMain_player_triggered();
    //смена имени дополнительного игрока
    void on_actionSecond_player_triggered();

    void on_pushButton_clicked();

signals:
    void pvp_clicked();
    void bot_clicked();
private:
    //заливка фона виджета
    Ui::MainWindow *ui;
    QBrush *brush;
    QPalette *palette;
};

#endif // MAINWINDOW_H
