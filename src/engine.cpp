#include <fstream>
#include <iostream>
#include <ncurses.h>
#include "engine.h"
#include <cstdlib>
#include <ctime>
#include <string.h>

#define MAX_Y 47
#define MAX_X 18

Engine::Engine(){
	score=0;
	numofstones=0;
	gradflag=TRUE;
    winflag=FALSE;
}

void Engine::MapSetup(char **argv){
    char c;
    std::ifstream F;
    F.exceptions (std::ifstream::badbit |std::ifstream::badbit);

    try{
        F.open(argv[1]); 
        while(!F.eof()){
	    F.get(c);
            printw("%c",c);   
        }
        F.close();
    }catch(std::ifstream::failure e){
        std::cerr<<"Exception opening the file\n";
    }
}


	


void Engine::MapInit(Player *A , Monster *B , Monster *C){
    bool found=TRUE;
    bool found1=TRUE;
    bool found2=TRUE;
    int stones=10;
    int randx,randy;	
    std::srand(time(NULL));

    while(stones>0 || found || found1 || found2){
        randx=std::rand()%47-1;
        randy=std::rand()%18-1;
        if(mvinch(randy,randx)==' '){
	    if(stones>0){
	    	mvprintw(randy,randx,"o");
            	stones--;
	    }else if(found){
	    	mvprintw(randy,randx,"%c",A->GetId());
			A->SetPosy(randy);
			A->SetPosx(randx);
			found=FALSE;
	    }else if(found1){
	    	mvprintw(randy,randx,"%c",B->GetId());
			B->SetPosy(randy);
			B->SetPosx(randx);
			found1=FALSE;
	    }else if(found2){
	    	mvprintw(randy,randx,"%c",C->GetId());
			C->SetPosy(randy);
			C->SetPosx(randx);
			found2=FALSE;
	    }
        }
    }
	
    mvprintw(19,0,"Collected:%d\tScore:%d\t  Name:%s",numofstones,score,A->GetName());
   
}

bool Engine::CheckPColision(int y , int x ){
	if(mvinch(y,x)=='*'){
		return FALSE;
	}else if(mvinch(y,x)=='o'){numofstones++;score+=10;RefScore(this);}
	else if(mvinch(y,x)=='$'){score+=100;winflag=TRUE;RefScore(this);}
	return TRUE;
}

void RefScore(Engine *A){
	mvprintw(19,0,"Collected:%d\t",A->numofstones);
	printw("Score:%d",A->score);	
}

void Engine::CheckStone(){
	std::srand(time(NULL));
	int randy,randx;
	if(numofstones==10){
		while(gradflag){
			randx=std::rand()%47-1;
        		randy=std::rand()%18-1;
			if(mvinch(randy,randx)==' ')
			{
				mvprintw(randy,randx,"$");
				gradflag=FALSE;	
			}		
		}
	}
}

void Engine::MoveMonster(Monster *A){
	std::srand(time(NULL));
	int randnum;
	bool moved=FALSE;
	while(!moved){
		randnum=rand()%4+1;
		switch(randnum){
		//top
		case 1:
		if(CheckMColision(A->GetPosy()-1,A->GetPosx())){
		A->MoveTo(A->GetPosy()-1,A->GetPosx());moved=TRUE;}break;
		//right
		case 2:
		if(CheckMColision(A->GetPosy(),A->GetPosx()+1)){
		A->MoveTo(A->GetPosy(),A->GetPosx()+1);moved=TRUE;}break;
		//bottom
		case 3:
		if(CheckMColision(A->GetPosy()+1,A->GetPosx())){
		A->MoveTo(A->GetPosy()+1,A->GetPosx());moved=TRUE;}break;
		//left
		case 4:
		if(CheckMColision(A->GetPosy(),A->GetPosx()-1)){
		A->MoveTo(A->GetPosy(),A->GetPosx()-1);moved=TRUE;}break;
		}
	}
}


bool Engine::CheckMColision(int y , int x){
	char ch;
	ch=mvinch(y,x);
	switch(ch){
		case 'T':
		case 'G':
		case '*':
		case 'o':
		case '$':return FALSE;break;
		default :return TRUE;break;
	}
}




