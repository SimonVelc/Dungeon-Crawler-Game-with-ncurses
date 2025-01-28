#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "engine.h"
#include "player.h"
#include "monster.h"
#include "highscore.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <cstring>

bool CheckIfDead(Player *A );
void messageL();
void messageW();

int main(int argc , char **argv){
    char buff[50];
	//for input 
    int ch;
	//machine initialization
    Engine engine;
	//initialisation of the score
    HiScore HS(argv[2]);
	//accept a name up to 10 characters
	do{
		std::cout << "Enter your Name challenger :";
    	std::cin >> buff;
		if(strlen(buff)<11)break;
	}while(1);
	//We passed the name to the player's initials
    Player *B=new Player(buff);
	//initialization of the two monsters 
    Monster *Mon1=new Monster('G');
    Monster *Mon2=new Monster('T');

    initscr();			
    noecho();
    refresh();
	//to read characters like arrows
    keypad(stdscr,TRUE);
	//we print the playing paper
    engine.MapSetup(argv);
	//we put the monsters and the player inside 
    engine.MapInit(B,Mon1,Mon2);
    
    //central loop
    //27 is the escape character
    while((ch=getch())!=27 && CheckIfDead(B)){
	switch (ch){
		//when we press the upper arrow the character moves upwards 
		case KEY_UP:
		if(engine.CheckPColision(B->GetPosy()-1,B->GetPosx()))
				B->MoveTo(B->GetPosy()-1,B->GetPosx());
				engine.MoveMonster(Mon1);
				engine.MoveMonster(Mon2);
				move(B->GetPosy(),B->GetPosx());
		break;
		//the same for the left
		case KEY_LEFT:
			if(engine.CheckPColision(B->GetPosy(),B->GetPosx()-1))
				B->MoveTo(B->GetPosy(),B->GetPosx()-1);
			engine.MoveMonster(Mon1);
			engine.MoveMonster(Mon2);
			move(B->GetPosy(),B->GetPosx());
		break;
		//Right
		case KEY_RIGHT:
			/*
				checkpcolision checks the player's next position and returns positive 
				if the next place it finds is an empty space, e.g. stone or boulder, 
				and returns FALSE if it is a wall, in which case it does not move.
			*/
			if(engine.CheckPColision(B->GetPosy(),B->GetPosx()+1))		
				B->MoveTo(B->GetPosy(),B->GetPosx()+1);
			engine.MoveMonster(Mon1);
			engine.MoveMonster(Mon2);
			move(B->GetPosy(),B->GetPosx());
		break;
		//Dwon
		case KEY_DOWN:
			if(engine.CheckPColision(B->GetPosy()+1,B->GetPosx()))
				B->MoveTo(B->GetPosy()+1,B->GetPosx());
			engine.MoveMonster(Mon1);
			engine.MoveMonster(Mon2);
			move(B->GetPosy(),B->GetPosx());
		break;
		//incase of a SPACE_KEY 
		case ' ':
			engine.MoveMonster(Mon1);
			engine.MoveMonster(Mon2);
			move(B->GetPosy(),B->GetPosx());		
		break;
		default:break;	
		
	}
	//If we have collected all 10 stones, then the pearl appears.
	engine.CheckStone();
	//When the winflag shuts down, we get out of the loop.
	if(engine.GetWin())break;
    }
    //the overloaded printout in the scores.bin file
    HS<<B->GetName()<<engine.GetScore();
    clear();
    refresh();
	//If the winflag has been mothballed, we have the corresponding message.	 
	if(engine.GetWin()){
		messageW();
	}else{
		messageL();	
	}					
    getch();
    endwin();	
    
    return 0;
}
//check right, top, left and bottom of the player to see if there's a monster, if so, he's dead.
bool CheckIfDead(Player *A ){

	
	if(mvinch(A->GetPosy(),A->GetPosx())=='G' || mvinch(A->GetPosy(),A->GetPosx())=='T'){
		return FALSE;
	//on top
	}else if(mvinch(A->GetPosy()-1,A->GetPosx())=='G' || mvinch(A->GetPosy()-1,A->GetPosx())=='T'){
		return FALSE;
	//right
	}else if(mvinch(A->GetPosy(),A->GetPosx()+1)=='G' || mvinch(A->GetPosy(),A->GetPosx()+1)=='T'){
		return FALSE;
	//bottom
	}else if(mvinch(A->GetPosy()+1,A->GetPosx())=='G' || mvinch(A->GetPosy()+1,A->GetPosx())=='T'){
		return FALSE;
	//left
	}else if(mvinch(A->GetPosy(),A->GetPosx()-1)=='G' || mvinch(A->GetPosy(),A->GetPosx()-1)=='T'){
		return FALSE;
	}else{return TRUE;}
	
}

void messageW(){
	clear();
	refresh();
	mvprintw(10,10,"###      YOU WIN :D      ###");
}

void messageL(){
	clear();
	refresh();
	mvprintw(10,10,"---      YOU LOSE   :(      ---");
}



