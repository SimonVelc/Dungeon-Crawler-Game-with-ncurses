#include <iostream>
#include <ncurses.h>
#include "mover.h"
#include "monster.h"
#include <string.h>

Monster::Monster(char S){
	Id=S;
}

char Monster::GetId(){
	return Id;
}
