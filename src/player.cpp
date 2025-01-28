#include <iostream>
#include <ncurses.h>
#include "mover.h"
#include "player.h"
#include <string.h>

Player::Player(const char *p){
    int i=strlen(p);
    if(i<11){
	strcpy(Name,p);
    }
    Id='@';
}

//Player::~Player(){delete[] Name;}

char* Player::GetName(){
    return Name;
}
