#include "game.h"
#include "ui_game.h"
#include <ctime>
Game::Game(QWidget *parent,bool type,player *p1,player *p2) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(520,330);
    QBrush *brush = new QBrush;
    QPalette *palette = new QPalette;
    brush->setTextureImage(QImage(":/textures/BackgroundGame.jpg"));
    palette->setBrush(QPalette::Window, *brush);
    this->setPalette(*palette);
    QObject::connect(this, SIGNAL(startGamestage1()),this, SLOT(gamestage1()));
    QObject::connect(this, SIGNAL(startGamestage2()),this, SLOT(gamestage2()));
    QObject::connect(this, SIGNAL(setdeactivated1(bool)),this, SLOT(deactivate1(bool)));
    QObject::connect(this, SIGNAL(setdeactivated2(bool)),this, SLOT(deactivate2(bool)));
    QObject::connect(this, SIGNAL(result()),this, SLOT(gameresult()));
    QObject::connect(this, SIGNAL(isbeterror(bool)),this, SLOT(beterror(bool)));
    gametype=type;
    ui->messageDisplay->clear();
    ui->score_1->setText(QString::number(SCORE1));
    ui->score_2->setText(QString::number(SCORE2));
    PLAYER1=p1;
    PLAYER1->make_dice(0,ui->dice11);
    PLAYER1->make_dice(1,ui->dice12);
    PLAYER1->make_dice(2,ui->dice13);
    PLAYER1->make_dice(3,ui->dice14);
    PLAYER1->make_dice(4,ui->dice15);
    ui->player1name->setText(PLAYER1->get_name());
    ui->bet1->setDisabled(true);
    ui->bet2->setDisabled(true);
    ui->confirm1->setDisabled(true);
    ui->confirm2->setDisabled(true);
    ui->surrender1->setDisabled(true);
    ui->surrender2->setDisabled(true);
    ui->apply->setDisabled(true);
    emit setdeactivated1(true);
    emit setdeactivated2(true);

    if(gametype)
    {
        PLAYER2=p2;
        ui->player2name->setText(PLAYER2->get_name());
        PLAYER2->make_dice(0,ui->dice21);
        PLAYER2->make_dice(1,ui->dice22);
        PLAYER2->make_dice(2,ui->dice23);
        PLAYER2->make_dice(3,ui->dice24);
        PLAYER2->make_dice(4,ui->dice25);
        ui->botbet->hide();
        ui->botstatus->hide();
        ui->sign_botbet->hide();
    }
    else
    {
        ui->botbet->show();
        ui->sign_botbet->show();
        ui->bet2->hide();
        ui->confirm2->hide();
        ui->surrender2->hide();
        ui->player2name->setText(BOT->get_name());
        ui->botstatus->clear();
        BOT->make_dice(0,ui->dice21);
        BOT->make_dice(1,ui->dice22);
        BOT->make_dice(2,ui->dice23);
        BOT->make_dice(3,ui->dice24);
        BOT->make_dice(4,ui->dice25);
    }
    srand(time(0));
}

Game::~Game()
{
    delete ui;
}

int Game::betRange()
{
    if(gametype)
    {
        if(PLAYER1->get_gold()<PLAYER2->get_gold())
        {
             return PLAYER1->get_gold()*20/100;
        }
        else
        {
             return PLAYER2->get_gold()*20/100;
        }
    }
    else
    {
        if(PLAYER1->get_gold()<BOT->get_gold())
        {
             return PLAYER1->get_gold()*20/100;
        }
        else
        {
             return BOT->get_gold()*20/100;
        }
    }
}
void Game::winnerbox(bool win1)
{
    QString result;
    if(win1)
    {
        PLAYER1->edit_gold(BANK);
        result=PLAYER1->get_name()+" won! His gold now "+QString::number(PLAYER1->get_gold());
    }
    else
    {
        if(gametype&&!win1)
        {
           PLAYER2->edit_gold(BANK);
           result=PLAYER2->get_name()+" won! His gold now "+QString::number(PLAYER2->get_gold());
        }
        else
        {
           BOT->edit_gold(BANK);
           result=BOT->get_name()+" won! His gold now "+QString::number(BOT->get_gold());
        }
    }
    QMessageBox::information(0, "Result", result);
    Game::close();
}
void Game::shakealldices()
{
    for(int i=0;i<5;i++)
    {
        int rad=rand()%6+1;
        PLAYER1->change_dice(rad,i);
    }
    if(gametype)
    {
        for(int i=0;i<5;i++)
        {
            int rad=rand()%6+1;
            PLAYER2->change_dice(rad,i);
        }
    }
    else
    {
        for(int i=0;i<5;i++)
        {
            int rad=rand()%6+1;
            BOT->change_dice(rad,i);
        }
    }
}
void Game::controlBet(bool enable,bool player)
{
   if(enable)
   {
       if(player)
       {
           ui->bet1->setEnabled(true);
           ui->confirm1->setEnabled(true);
       }
       else
       {
           ui->bet2->setEnabled(true);
           ui->confirm2->setEnabled(true);
       }
   }
   else
   {
       if(player)
       {
           ui->bet1->setDisabled(true);
           ui->confirm1->setDisabled(true);
       }
       else
       {
           ui->bet2->setDisabled(true);
           ui->confirm2->setDisabled(true);
       }
   }
}
void Game::message(int type)
{
    switch(type)
    {
    case 1:
        ui->messageDisplay->setText("Make bet from 1 to "+QString::number(betRange()));
        break;

    case 2:
        ui->messageDisplay->setText("Error, make bet from 1 to "+QString::number(betRange()));
        break;

    case 3:
        ui->messageDisplay->setText("Lesser bet, try again");
        break;
    }
}

void Game::betConfirmation(bool player,int &rate1, int &rate2)
{
    int gold=betRange();
    if(player)
    {
        rate1=(ui->bet1->text()).toInt();
    }
    else
    {
        rate1=(ui->bet2->text()).toInt();
    }

    controlBet(false,player);
    if(rate1>gold || rate1<1)
    {
        emit isbeterror(player);
        message(2);
    }
    else
    {
        if(rate1!=rate2)
        {
            if(rate1<rate2)
            {

                        message(3);
                        emit isbeterror(player);
                        if(!gametype || !firsttime)
                        {
                            message(3);
                        }
                        firsttime=false;


            }
            else
            {

                if(gametype)
                {
                    controlBet(true,!player);
                }
                else
                {
                    rate2=rate1;
                    ui->botbet->setText(QString::number(rate2));
                    switch(gamestage)
                    {
                    case 1: emit gamestage1(); break;
                    case 2: emit gamestage2(); break;
                    }
                }

            }
        }
        else
        {
                    switch(gamestage)
                    {
                    case 1: emit gamestage1(); break;
                    case 2: emit gamestage2(); break;
                    }
        }
    }
}

void Game::beterror(bool player)
{
    controlBet(true,player);
}

//--------------------------------------

void Game::on_START_clicked()
{
    ui->START->hide();
    ui->bet1->clear();
    ui->surrender1->setEnabled(true);
    firsttime=true;
    if(gametype)
    {
        ui->bet2->clear();
        ui->surrender2->setEnabled(true);
    }
    else
    {
        ui->botbet->clear();
        BET2=rand()%betRange()+1;
        ui->botstatus->clear();
        ui->botbet->setText(QString::number(BET2));
    }
    controlBet(true,true);
    message(1);
    ui->dice11->setText("?");
    ui->dice12->setText("?");
    ui->dice13->setText("?");
    ui->dice14->setText("?");
    ui->dice15->setText("?");
    ui->dice21->setText("?");
    ui->dice22->setText("?");
    ui->dice23->setText("?");
    ui->dice24->setText("?");
    ui->dice25->setText("?");


}

void Game::on_confirm1_clicked()
{
    betConfirmation(true,BET1,BET2);
}

void Game::on_confirm2_clicked()
{
    betConfirmation(false,BET2,BET1);
}

void Game::on_apply_clicked()
{
    deactivate1(true);
    if(gametype)
    {
           deactivate2(true);
    }
    ui->apply->setDisabled(true);
    gamestage++;
    message(1);
    controlBet(true,true);

    if(gamestage==3)
    {
        emit result();
    }
    else
    {
        if(!gametype)
       {
            BET2=BOT->make_bet();
            ui->botbet->setText(QString::number(BET2));
        }

    }
}

void Game::on_surrender1_clicked()
{
    winnerbox(false);
    Game::close();
}

void Game::on_surrender2_clicked()
{
    winnerbox(true);
    Game::close();
}

void Game::gamestage1()
{

    BANK+=BET1+BET2;
    ui->bankDisplay->setText(QString::number(BANK));
    PLAYER1->edit_gold(-BET1);
    ui->bet1->clear();
    ui->bet2->clear();
    if(gametype)
    {
        PLAYER2->edit_gold(-BET2);
    }
    else
    {
        BOT->edit_gold(-BET2);
    }
    BET1=0;
    BET2=0;
    shakealldices();
    ui->apply->setEnabled(true);
}

void Game::gamestage2()
{
    BANK+=BET1+BET2;
    PLAYER1->edit_gold(-BET1);
    if(gametype)
    {
        PLAYER2->edit_gold(-BET2);
    }
    else
    {
        BOT->edit_gold(-BET2);
    }
    BET1=0;
    BET2=0;
    setdeactivated1(false);
    if(gametype)
    {
        setdeactivated2(false);
    }
    if(!gametype)
    {
        QString status="Rethrowed: ";
        BOT->get_combination();
        for(int i=0;i<5;i++)
        {
            if(BOT->if_havent_pair(i))
            {
                int rad=rand()%6+1;
                BOT->change_dice(rad,i);
                status+=QString::number(i+1)+" ";
            }

        }
        ui->botstatus->setText(status);
    }
    ui->apply->setEnabled(true);
}

void Game::gameresult()
{

    if(gametype)
    {
        if(PLAYER1->get_combination()>PLAYER2->get_combination())
        {
            SCORE1++;
            ui->score_1->setText(QString::number(SCORE1));
        }
        else
        {
            SCORE2++;
            ui->score_2->setText(QString::number(SCORE2));
        }
    }
    else
    {
        if(PLAYER1->get_combination()>BOT->get_combination())
        {
            SCORE1++;
            ui->score_1->setText(QString::number(SCORE1));
        }
        else
        {
            SCORE2++;
            ui->score_2->setText(QString::number(SCORE2));
        }
    }
    if(SCORE1>1)
    {
        winnerbox(true);
    }
        else
        {
           if(SCORE2>1)
           {
                winnerbox(false);
           }
           else
           {
                QMessageBox::information(0, "Chapter","Next round!");
           }
    }
    gamestage=1;
    emit ui->START->clicked();
}

void Game::deactivate1(bool disable)
{
    ui->dice11->setDisabled(disable);
    ui->dice12->setDisabled(disable);
    ui->dice13->setDisabled(disable);
    ui->dice14->setDisabled(disable);
    ui->dice15->setDisabled(disable);
}

void Game::deactivate2(bool disable)
{
    ui->dice21->setDisabled(disable);
    ui->dice22->setDisabled(disable);
    ui->dice23->setDisabled(disable);
    ui->dice24->setDisabled(disable);
    ui->dice25->setDisabled(disable);
}
void Game::on_dice11_clicked()
{
    int rad=rand()%6+1;
    PLAYER1->change_dice(rad,0);
    ui->dice11->setDisabled(true);
}
void Game::on_dice12_clicked()
{
    int rad=rand()%6+1;
    PLAYER1->change_dice(rad,1);
    ui->dice12->setDisabled(true);
}
void Game::on_dice13_clicked()
{
    int rad=rand()%6+1;
    PLAYER1->change_dice(rad,2);
    ui->dice13->setDisabled(true);
}
void Game::on_dice14_clicked()
{
    int rad=rand()%6+1;
    PLAYER1->change_dice(rad,3);
    ui->dice14->setDisabled(true);
}
void Game::on_dice15_clicked()
{
    int rad=rand()%6+1;
    PLAYER1->change_dice(rad,4);
    ui->dice15->setDisabled(true);
}
void Game::on_dice21_clicked()
{
    int rad=rand()%6+1;
    PLAYER2->change_dice(rad,0);
    ui->dice21->setDisabled(true);
}
void Game::on_dice22_clicked()
{
    int rad=rand()%6+1;
    PLAYER2->change_dice(rad,1);
    ui->dice22->setDisabled(true);
}
void Game::on_dice23_clicked()
{
    int rad=rand()%6+1;
    PLAYER2->change_dice(rad,2);
    ui->dice23->setDisabled(true);
}
void Game::on_dice24_clicked()
{
    int rad=rand()%6+1;
    PLAYER2->change_dice(rad,3);
    ui->dice24->setDisabled(true);
}
void Game::on_dice25_clicked()
{
    int rad=rand()%6+1;
    PLAYER2->change_dice(rad,4);
    ui->dice25->setDisabled(true);
}

