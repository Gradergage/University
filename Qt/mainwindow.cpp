#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    brush = new QBrush;
    palette = new QPalette;
    brush->setTextureImage(QImage(":/textures/BackgroundMenu.jpg"));
    palette->setBrush(QPalette::Window, *brush);
    this->setPalette(*palette);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(400,300);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionAuthor_triggered()
{
    QMessageBox::information(NULL,QObject::tr("Author"),tr("Pokatilo Pavel, SPBSTU: group 13501/4"));
}
//запуск игры с игроком
void MainWindow::on_menupvp_clicked()
{
    player *player1=new player(name1);
    player *player2=new player(name2);
    BOT *bot = new BOT(0,player1,true,player2);
    bot->setWindowFlags(Qt::FramelessWindowHint);
    bot->show();
}
//запуск игры с ботом
void MainWindow::on_menubot_clicked()
{

    player *player1=new player(name1);
    BOT *bot = new BOT(0,player1,false);
    bot->setWindowFlags(Qt::FramelessWindowHint);
    bot->show();
}

void MainWindow::on_actionMain_player_triggered()
{
    bool check;
    name1=QInputDialog::getText(0,"Change name","Enter new name",QLineEdit::Normal,name1,&check);
}

void MainWindow::on_actionSecond_player_triggered()
{
    bool check;
    name2=QInputDialog::getText(0,"Change name","Enter new name",QLineEdit::Normal,name2,&check);
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow::close();
}
