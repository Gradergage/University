#include "mainwindow.h"
#include "bot.h"
#include "AI.h"
#include "ui_bot.h"
#include <QMessageBox>
#include <ctime>
//pvp - показатель типа игры true - игрок, false - бот
BOT::BOT(QWidget *parent, player *mainplayer,bool pvp,player *p2) :
    QWidget(parent),
    ui(new Ui::BOT)
{
    ui->setupUi(this);
    this->setFixedSize(500,340);
    brush = new QBrush;
    palette = new QPalette;
    brush->setTextureImage(QImage(":/textures/BackgroundGame.jpg"));
    palette->setBrush(QPalette::Window, *brush);
    this->setPalette(*palette);

    setAttribute(Qt::WA_DeleteOnClose, true);

    QObject::connect(this, SIGNAL(set_players_dice_active()),this, SLOT(activate_player_dices()));
    QObject::connect(this, SIGNAL(set_players_dice_active2()),this, SLOT(activate_player_dices2()));
    QObject::connect(this, SIGNAL(set_players_dice_deactivated()),this, SLOT(deactivate_player_dices()));
    QObject::connect(this, SIGNAL(shakedices()),this, SLOT(shake_all_dices()));
    QObject::connect(this, SIGNAL(gamestage1()),this, SLOT(stage1()));
    QObject::connect(this, SIGNAL(gamestage2()),this, SLOT(stage2()));
    QObject::connect(this, SIGNAL(result()),this, SLOT(gameresult()));
    QObject::connect(this, SIGNAL(beterror()),this, SLOT(bet_error()));

    gametype=pvp;
    if(gametype)
    {
        player2=p2;
        ui->Bet2->hide();
        ui->computername->setText(player2->get_name());
        ui->label_3->hide();


    }
    else
    {
        ui->confirmbutton_2->hide();
        ui->surrender_2->hide();
        ui->Bet1_2->hide();
        ui->computername->setText(botname);
        botbet=rand()%(bot->get_gold())*40/100+1;
    }
    //массивы кнопок костей
    botdices[0]=ui->dice21;
    botdices[1]=ui->dice22;
    botdices[2]=ui->dice23;
    botdices[3]=ui->dice24;
    botdices[4]=ui->dice25;
    playerdices[0]=ui->dice11;
    playerdices[1]=ui->dice12;
    playerdices[2]=ui->dice13;
    playerdices[3]=ui->dice14;
    playerdices[4]=ui->dice15;

    gamer=mainplayer;
    playername=gamer->get_name();

    ui->playername->setText(mainplayer->get_name());
    ui->bankdisplay->setText(QString::number(bank));
    ui->errordisplay->clear();
    ui->botstatus->clear();

    firsttime=true;

    srand(time(0));
}

BOT::~BOT()
{
    delete ui;
}
//Меняет кости в зависимости от типа( true - игрок, false - бот)
void BOT::change_dice(int number,bool type,bool gametype)
{
    if(type)
  {
    int index=rand() % 5+0;
    playerdices[number]->setText(models[index]);
    gamer->change_dice(index+1,number);
    playerdices[number]->setDisabled(true);
  }
  else
  {
    int index=rand() % 5+0;
    botdices[number]->setText(models[index]);
    if(gametype)
    {
        player2->change_dice(index+1,number);
    }
    else
    {
        bot->change_dice(index+1,number);
    }
    botdices[number]->setDisabled(true);
  }
}
//сверяет, действительно ли ставка меньше чем сорок процентов данного золота
bool BOT::check_bet(int bet, int gold)
{
    if(bet<=0 ||bet>(double)gold*0,4)
    {
        return false;
    }
    return true;
}
//запуск, скрытие-раскрытие соответствующих интерфейсов для игры бот/игрок
void BOT::on_START_clicked()
{\
   // ui->START->setIcon(QIcon(":textures/skull.jpg")); //addAction(QIcon(":textures/skull.jpg"), "Started");
    ui->errordisplay->setText("Make your first bet from 1 to "+QString::number(lowest_gold(bot->get_gold(),gamer->get_gold())*40/100));
    ui->START->hide();



    if(!gametype)
    {
        botbet=rand()%(bot->get_gold())*40/100+1;
        ui->Bet2->setText(QString::number(botbet));
        ui->surrender->setEnabled(true);
        ui->confirmbutton_3->hide();
        ui->confirmbutton->setEnabled(true);
        ui->Bet1->setEnabled(true);

    }
    else
    {
        ui->confirmbutton->hide();
        ui->Bet1_2->setDisabled(true);
        ui->Bet1->setEnabled(true);
        ui->surrender->setEnabled(true);
        ui->surrender_2->setEnabled(true);
        ui->confirmbutton_3->setEnabled(true);

    }


}
//завершение хода игрока, работает и для общего случая с двумя игроками
void BOT::on_applydices_clicked()
{
    gamestage++;
    firsttime=true;
    ui->Bet1->clear();
    ui->Bet1_2->clear();
    ui->applydices->setDisabled(true);
    if(gamestage==2)
    {
        ui->errordisplay->setText("Make your second bet from 1 to "+QString::number(lowest_gold(bot->get_gold(),gamer->get_gold())*40/100));
    }
    if(gamestage==3)
    {
        emit gameresult();
    }
    else
    {
        if(!gametype)
        {
            botbet=bot->make_bet();
            ui->confirmbutton->setEnabled(true);
            ui->Bet1->setEnabled(true);
            ui->Bet2->setText(QString::number(botbet));
        }
        else
        {
            ui->confirmbutton_3->setEnabled(true);
            ui->Bet1->setEnabled(true);
        }
    }

    emit set_players_dice_deactivated();

}
//подтверждение ставки второго игрока в pvp
void BOT::on_confirmbutton_2_clicked()
{
    int gold=lowest_gold(bot->get_gold(),gamer->get_gold())*40/100;
    ui->errordisplay->clear();
    botbet=(ui->Bet1_2->text()).toInt();
    ui->confirmbutton_2->setDisabled(true);
    ui->Bet1_2->setDisabled(true);
    if(botbet!=playerbet)
    {
        ui->confirmbutton_3->setEnabled(true);
        ui->Bet1->setEnabled(true);

            ui->errordisplay->setText("Error! Try higher or equal bet!");

    }
    else
    {
    if(playerbet>gold||playerbet<=0||botbet>gold||botbet<=0)
    {
        ui->confirmbutton_3->setEnabled(true);
        ui->Bet1->setEnabled(true);
        ui->errordisplay->setText("Error! Bet is not in 1 to "+QString::number(lowest_gold(bot->get_gold(),gamer->get_gold())*40/100)+" borders");
    }
    else
    {
        if(gamestage==1)
        {
            ui->Bet1_2->clear();
            ui->Bet1->clear();
          emit gamestage1();
        }
        if(gamestage==2)
        {
            ui->Bet1_2->clear();
            ui->Bet1->clear();
          emit gamestage2();
        }
    }
    }

}
//подтверждение ставки 1го игрока в pvp
void BOT::on_confirmbutton_3_clicked()
{
    int gold=lowest_gold(bot->get_gold(),gamer->get_gold())*40/100;
    ui->errordisplay->clear();
    playerbet=(ui->Bet1->text()).toInt();
    ui->confirmbutton_3->setDisabled(true);
    ui->Bet1->setDisabled(true);
    if(botbet!=playerbet)
    {
        ui->confirmbutton_2->setEnabled(true);
        ui->Bet1_2->setEnabled(true);
         if(!firsttime)
        {
             ui->errordisplay->setText("Error! Try higher or equal bet!");

        }
         firsttime=false;
    }
    else
    {
    if(playerbet>gold||playerbet<=0||botbet>gold||botbet<=0)
    {
        ui->confirmbutton_2->setEnabled(true);
        ui->Bet1_2->setEnabled(true);
        ui->errordisplay->setText("Error! Bet is not in 1 to "+QString::number(lowest_gold(bot->get_gold(),gamer->get_gold())*40/100)+" borders");
    }
    else
    {
        if(gamestage==1)
        {
            ui->Bet1_2->clear();
            ui->Bet1->clear();
          emit gamestage1();
        }
        if(gamestage==2)
        {
            ui->Bet1_2->clear();
            ui->Bet1->clear();
          emit gamestage2();
        }
    }
    }

}
//подтверждение ставки при игре с ботом
void BOT::on_confirmbutton_clicked()
{
   ui->Bet1->setDisabled(true);
   ui->errordisplay->clear();
   ui->surrender->setEnabled(true);
   ui->surrender_2->setEnabled(true);
   ui->Bet2->setText(QString::number(botbet));
   ui->confirmbutton->setDisabled(true);
   int gold;
   gold=lowest_gold(bot->get_gold(),gamer->get_gold())*40/100;
   playerbet=(ui->Bet1->text()).toInt();
   ui->Bet1->clear();
   ui->Bet1_2->clear();
   if(playerbet>gold||playerbet<=0||botbet>gold||botbet<=0)
   {
       ui->Bet1->clear();
       ui->errordisplay->setText("Error! Bet is not in 1 to "+QString::number(lowest_gold(bot->get_gold(),gamer->get_gold())*40/100)+" borders");
       emit beterror();

   }
   else
   {
       if(playerbet>botbet)
       {
               botbet=playerbet;
                 ui->Bet2->setText(QString::number(botbet));
                 if(gamestage==1)
                 {
                   emit gamestage1();
                 }
                 if(gamestage==2)
                 {
                   emit gamestage2();
                 }
        //  }
       }
       else
       {
          if(playerbet<botbet)
         {
           ui->errordisplay->setText("Low bet, enter equal or surrender");
            emit beterror();
          }
         else
         {
              if(gamestage==1)
               {
                 emit gamestage1();
               }
                 if(gamestage==2)
               {
                emit gamestage2();
                }
         }
       }
   }


}
//первая стадия после первой ставки, все кости бросаются на стол
void BOT::stage1()
{

     bank=bank+playerbet+botbet;
     ui->bankdisplay->setText(QString::number(bank));
     if(gametype)
     {
         player2->edit_gold(-botbet);
     }
     else
     {
         bot->edit_gold(-botbet);
     }
     botbet=0; playerbet=0;
     gamer->edit_gold(-playerbet);
     emit shake_all_dices();
     ui->applydices->setEnabled(true);

}
//вторая стадия, после второй ставки - активируется переброс костей для 1/2 игроков
void BOT::stage2()
{
   bank=bank+playerbet+botbet;
   ui->bankdisplay->setText(QString::number(bank));
   if(gametype)
   {
       player2->edit_gold(-botbet);
       emit set_players_dice_active2();
   }
   else
   {
       bot->edit_gold(-botbet);
   }
   gamer->edit_gold(-playerbet);
   emit set_players_dice_active();


   if(!gametype)
   {
       bot->get_combination();
       QString status="Rethrowed: ";
       for(int i=0;i<5;i++)
       {
         if(bot->if_havent_pair(i))
         {
            change_dice(i,false);
            status+= QString::number(i+1)+" ";
         }
       }
       ui->botstatus->setText(status);
   }
   ui->applydices->setEnabled(true);
}
//по сути третья стадия, вычисление и объявление победителя с последующим закрытием окна игры
void BOT::gameresult()
{
   if(!gametype)
   {
       if(bot->get_combination()<gamer->get_combination())
    {
        BOT::setDisabled(true);
        QString result; result=gamer->get_name()+" won the game! His gold now "+QString::number(bank+gamer->get_gold());
        QMessageBox::information(0, "Result", result);
        BOT::close();
    }
    else
    {

        BOT::setDisabled(true);
        QString result; result=bot->get_name()+" won the game! His gold now "+QString::number(bank+bot->get_gold());
        QMessageBox::information(0, "Result", result);
        BOT::close();
    }
   }
   else
   {
       if(player2->get_combination()<gamer->get_combination())
    {
        BOT::setDisabled(true);
        QString result; result=gamer->get_name()+" won the game! His gold now "+QString::number(bank+gamer->get_gold());
        QMessageBox::information(0, "Result", result);
        BOT::close();
    }
    else
    {

        BOT::setDisabled(true);
        QString result; result=player2->get_name()+" won the game! His gold now "+QString::number(bank+player2->get_gold());
        QMessageBox::information(0, "Result", result);
        BOT::close();
    }
   }
}
//вычисление наименьшего из переданных
int BOT::lowest_gold(int gold1,int gold2)
{
    if(gold1<gold2)
    {
        return gold1;
    }
    else
    {
        return gold2;
    }
}
//переброс всех костей на доске
void BOT::shake_all_dices()
{
   for(int i=0;i<5;i++)
   {
        change_dice(i,true);
   }

   for(int i=0;i<5;i++)
   {
        change_dice(i,false,gametype);
   }
}
//ошибка ставки, активирует заново кнопку утверждения ставки
void BOT::bet_error()
{
    ui->confirmbutton->setEnabled(true);
    ui->Bet1->setEnabled(true);
}
//кнопка "сдаться" для 1 игрока
void BOT::on_surrender_clicked()
{
    if(!gametype)
   {
        BOT::setDisabled(true);
        QString result; result=bot->get_name()+" won the game! His gold now "+QString::number(bank+bot->get_gold());
        QMessageBox::information(0, "Result", result);
        BOT::close();
   }
    else
    {
        BOT::setDisabled(true);
        QString result; result=player2->get_name()+" won the game! His gold now "+QString::number(bank+player2->get_gold());
        QMessageBox::information(0, "Result", result);
        BOT::close();
    }
}
//кнопка "сдаться" для 2го игрока
void BOT::on_surrender_2_clicked()
{
    BOT::setDisabled(true);
    QString result; result=gamer->get_name()+" won the game! His gold now "+QString::number(bank+gamer->get_gold());
    QMessageBox::information(0, "Result", result);
    BOT::close();
}
//активирует кости 1 игрока
void BOT::activate_player_dices()
{
    for(int i=0;i<5;i++)
    {
        playerdices[i]->setEnabled(true);
    }

}
//активирует кости 2 игрока
void BOT::activate_player_dices2()
{
    for(int i=0;i<5;i++)
    {
        botdices[i]->setEnabled(true);
    }

}
//деактивирует все кости
void BOT::deactivate_player_dices()
{
    for(int i=0;i<5;i++)
    {
        playerdices[i]->setDisabled(true);
        botdices[i]->setDisabled(true);
    }
}
//слоты клика по кнопкам для их переброса
void BOT::on_dice11_clicked()
{
    change_dice(0,true);
}
void BOT::on_dice12_clicked()
{
    change_dice(1,true);
}
void BOT::on_dice13_clicked()
{
    change_dice(2,true);
}
void BOT::on_dice14_clicked()
{
    change_dice(3,true);
}
void BOT::on_dice15_clicked()
{
    change_dice(4,true);
}



void BOT::on_dice21_clicked()
{
    change_dice(0,false,gametype);
}

void BOT::on_dice22_clicked()
{
    change_dice(1,false,gametype);
}

void BOT::on_dice23_clicked()
{
    change_dice(2,false,gametype);
}

void BOT::on_dice24_clicked()
{
    change_dice(3,false,gametype);
}

void BOT::on_dice25_clicked()
{
    change_dice(4,false,gametype);
}
