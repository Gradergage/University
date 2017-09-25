#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include "game.h"
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
    void on_exit_clicked();

    void on_gamePlayer_clicked();

    void on_gameBot_clicked();

    void on_settings_clicked();

    void on_confirm1_clicked();

    void on_confirm2_clicked();

    void on_Done_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
