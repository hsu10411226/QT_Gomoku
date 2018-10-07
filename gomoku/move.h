#ifndef MOVE_H
#define MOVE_H


class Move
{
public:
    Move(int,int,int);
    Move();
    int x_position = -1;
    int y_position = -1;
    int color = -1;
    void setmove(int x,int y,int player);

};

#endif // MOVE_H
