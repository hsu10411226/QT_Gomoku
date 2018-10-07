#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include "move.h"

class Board : public QWidget{
    Q_OBJECT

public:
    Board(QWidget *parent = 0);
    ~Board();
    int now;
    int turn;
    int board_status[15][15];
    bool checkWin(int status[][15],int position_x,int position_y,int player);
    void ai_choosemove(int b_status[][15],int player);
    Move miniMax(int board_status[][15],int player);
    QList<Move> generatemove(int board_status[][15]);
    Move lastbestmove;
    void usemove(int *board_status,int player,Move move);
    double min_move(int board_status[][15],int player,int depth,double alpha,double beta);
    double max_move(int board_status[][15],int player,int depth,double alpha,double beta);
    QList<Move> generateusefulmove(int board_status[][15]);
    //QList<int [][15]> generateBoards(int board_status[][15],int player,Move moves);
    void generateBoards(int *board_status,int player,QList<Move> moves);
    double getstatevalue(int board_status[][15],int player);
    double getPointsToAdd(int val);
    bool isStraightFour(QString in, int player);
    QString convertstring(int board_status[][15],int cal,int raw,int which);
    //add
    void aistart();
    void pdown(int x, int y);
    int count = 0;
    bool wins[15][15][700] = {{{false}}};
    void airingGo();
    bool ai = false;
    void aigo();

public slots:
    void newgame();
    void set_turn(int a);
    void force_update();

signals:
    void press(int x,int y,int player);

private:
    void paintEvent(QPaintEvent *);
    QPainter *paint;
    QPoint m_pos;
    bool clicked = false;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    int maxdepth = 4;
    int currentdepth;
    int myWin[700] = {0};
    int airingWin[700] = {0};

};


#endif // BOARD_H
