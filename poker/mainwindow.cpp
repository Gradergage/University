#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(400,300);
    QBrush *brush = new QBrush;
    QPalette *palette = new QPalette;
    brush->setTextureImage(QImage(":/textures/BackgroundMenu.jpg"));
    palette->setBrush(QPalette::Window, *brush);
    this->setPalette(*palette);
    ui->changename1->hide();
    ui->changename2->hide();
    ui->confirm1->hide();
    ui->confirm2->hide();
    ui->Done->hide();
    ui->label1->hide();
    ui->label2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_clicked()
{
    MainWindow::close();
}

void MainWindow::on_gamePlayer_clicked()
{
    player *player1=new player(name1);
    player *player2=new player(name2);
    Game *pvp=new Game(0,true,player1,player2);
    pvp->show();
}

void MainWindow::on_gameBot_clicked()
{
    player *player1=new player(name1);
    Game *pvc=new Game(0,false,player1);
    pvc->show();
}

void MainWindow::on_settings_clicked()
{
    ui->gamePlayer->setDisabled(true);
    ui->gameBot->setDisabled(true);
    ui->settings->setDisabled(true);
    ui->exit->setDisabled(true);
    ui->changename1->show();
    ui->changename2->show();
    ui->confirm1->show();
    ui->confirm2->show();
    ui->Done->show();
    ui->label1->show();
    ui->label2->show();

}

void MainWindow::on_confirm1_clicked()
{
    name1=ui->changename1->text();
}

void MainWindow::on_confirm2_clicked()
{
    name2=ui->changename2->text();
}

void MainWindow::on_Done_clicked()
{
    ui->gamePlayer->setEnabled(true);
    ui->gameBot->setEnabled(true);
    ui->settings->setEnabled(true);
    ui->exit->setEnabled(true);
    ui->changename1->hide();
    ui->changename2->hide();
    ui->confirm1->hide();
    ui->confirm2->hide();
    ui->label1->hide();
    ui->label2->hide();
    ui->Done->hide();
}
