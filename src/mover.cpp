#include <iostream>
#include <ncurses.h>
#include "mover.h"

void Mover::MoveTo(int newy , int newx){
    mvprintw(this->Posy , this->Posx , " ");
    this->Posx=newx;
    this->Posy=newy;

    mvprintw(newy , newx , "%c", this->Id);
    move(newy,newx);
}

void Mover::SetId(char A){
	Id=A;
}


