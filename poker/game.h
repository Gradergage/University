#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QMessageBox>
#include <QPalette>
#include "AI.h"
namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0,bool type=false,player *p1=0,player *p2=0);
    ~Game();

private slots:

    void on_START_clicked();
    void on_confirm1_clicked();
    void on_confirm2_clicked();
    void on_surrender1_clicked();
    void on_surrender2_clicked();
    void gamestage1();
    void gamestage2();
    void gameresult();
    void on_dice11_clicked();
    void on_dice12_clicked();
    void on_dice13_clicked();
    void on_dice14_clicked();
    void on_dice15_clicked();
    void on_dice21_clicked();
    void on_dice22_clicked();
    void on_dice23_clicked();
    void on_dice24_clicked();
    void on_dice25_clicked();
    void deactivate1(bool disable);
    void deactivate2(bool disable);
    void beterror(bool player);
    void on_apply_clicked();

signals:
    void startGamestage1();
    void startGamestage2();
    void result();
    //активирует/деактивирует кости 1/2 игрока
    void setdeactivated1(bool disable);
    void setdeactivated2(bool disable);
    void isbeterror(bool player);
private:
    Ui::Game *ui;

    bool gametype;
    bool firsttime=true;
    int gamestage=1;
    computer *BOT=new computer("Lucky Traveller");
    player *PLAYER1;
    player *PLAYER2;

    int BET1=0;
    int BET2=0;
    int BANK=0;
    int SCORE1=0;
    int SCORE2=0;

    //встряхивает кости
    void shakealldices();
    //окно победителя (true первый/false -второй либо бот)
    void winnerbox(bool win1);
    //контроль окошек ввода ставки включить/выключить, игрок1/игрок2(бот)
    void controlBet(bool enable,bool player);
    //границы ставок
    int betRange();
    //сообщение какого-либо из 3х типов
    void message(int type);
    //подтверждение ставки, функция для кнопок подтверждения
    void betConfirmation(bool player,int &rate1, int &rate2);
};

#endif // GAME_H
