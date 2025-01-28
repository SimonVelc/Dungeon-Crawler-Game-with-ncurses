#ifndef Monster_h
#define Monster_h
#include "mover.h"

class Monster : public Mover
{
    char ch;//to save monsters' symbol
public:
    Monster(char S);
    char GetId();
};

#endif
