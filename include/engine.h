#ifndef engine_h
#define engine_h
#include "player.h"
#include "monster.h"

class Engine
{
    int score;//player score
    int numofstones;//stones collected
    bool winflag;//turns true when player wins
    bool gradflag;//Sets when the parchment appears
public:
    Engine();
    void MapSetup(char **argv);//to read the map 
    void MapInit(Player *A,Monster *B,Monster *C);//Adjusts the position of the player and monsters on the map
    bool CheckPColision(int y , int x);//Checks if the player can move to a specific position
    friend void RefScore(Engine *A);
    void CheckStone();//Checks if 10 stones have been collected for the parchment to appear
    void MoveMonster(Monster *A);//moves a monster at random
    bool CheckMColision(int y , int x);//Checks if the monster can move to a certain position
    int GetScore(){return score;}; 
    bool GetWin(){return winflag;};
};

#endif
