#ifndef BOT_H
#define BOT_H
#include <QWidget>
#include <QPalette>
#include "misc.h"
#include "AI.h"
#include "player.h"
#include "mainwindow.h"
namespace Ui {
class BOT;
}

class BOT : public QWidget
{
    Q_OBJECT

public:
    //pvp - gametype - переменная, влияющая на вид окна при игре с ботом или игроком
    //значение по умолчанию означает игру с ботом, при параметре *p2=0
    BOT(QWidget *parent = 0,player *mainplayer=0, bool pvp=false,player *p2=0);
    ~BOT();

private slots:
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
    void on_confirmbutton_clicked();
    void on_confirmbutton_2_clicked();
    void on_confirmbutton_3_clicked();
    //игрок 1 сдался
    void on_surrender_clicked();
    //игрок 2 сдался
    void on_surrender_2_clicked();
    void activate_player_dices();
    void activate_player_dices2();
    void deactivate_player_dices();
    void on_applydices_clicked();
    void shake_all_dices();
    //слот первой стадии игры, где осуществляется подсчет первой ставки и банка
    void stage1();
    //слот второй стадии игры, где осуществляется подсчет второй ставки и банка
    void stage2();
    //результат игры
    void gameresult();
    //замена циклу при некорректном вводе ставки при игре с ботом
    //заново активирует ввод ставки
    void bet_error();
    //запуск игры с начальными параметрами зависящими от gametype
    void on_START_clicked();
signals:
    void set_players_dice_active();
    void set_players_dice_active2();
    void set_players_dice_deactivated();
    void shakedices();
    void gamestage1();
    void gamestage2();
    void result();
    void beterror();
private:
    //заливка фона виджета
    QBrush *brush;
    QPalette *palette;
    QPushButton *botdices[5];
    QPushButton *playerdices[5];
    int gamestage=1;
    //имена игроков
    QString playername;
    QString playername2;
    //внутриклассовый объект бот
    computer *bot=new computer(botname);
    //внутриклассовые игроки
    player *gamer;
    player *player2;
    int bank=0;
    //условие при котором ставка первого игрока не сравнивается со вторым
    //при первом нажатии кнопки confirm bet
    bool firsttime;
    //тип игры, изменяет вид окна
    bool gametype;
    //начальные ставки сторон
    int playerbet=0,botbet=0;
    Ui::BOT *ui;
    //проверяет действительно ли ставка попадает
    //в промежуток от 1 до 40% наименьшего золота из двух игроков
    bool check_bet(int bet, int gold);
    //меняет кость игрока/бота в зависимости от type и второго игрока в зависимости от gametype
    void change_dice(int number,bool type,bool gametype=false);
    //находит меньше имеющееся золото из двух игроков
    int lowest_gold(int gold1,int gold2);

};
#endif // BOT_H
