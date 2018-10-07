#include "move.h"

Move::Move(){

}

Move::Move(int x,int y,int player)
{
    this->x_position = x;
    this->y_position = y;
    this->color = player;
}

void Move::setmove(int x, int y, int player){
    this->x_position = x;
    this->y_position = y;
    this->color = player;
}
