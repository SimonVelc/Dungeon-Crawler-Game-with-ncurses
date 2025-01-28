#ifndef Player_h
#define Player_h
#include "mover.h"


class Player : public Mover
{
    char Name[11];//max name length is 10
public:
    Player(const char *p);
    Player(){Id='@';};
    //~Player();
    char GetId(){return Id;};
    char* GetName();
};

#endif
