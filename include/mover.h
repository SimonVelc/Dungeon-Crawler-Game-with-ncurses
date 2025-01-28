#ifndef Mover_h
#define Mover_h
#include <cstring>

class Mover
{
protected:
    int Posx;//coordinate x
    int Posy;//coordinate y
    char Id;
public:
    void MoveTo(int newy , int newx);//moves ovject
    void SetId(char A);//set symbol for ovject
    int GetPosx(){return Posx;};
    int GetPosy(){return Posy;};
    void SetPosy(int newy){Posy=newy;};
    void SetPosx(int newx){Posx=newx;};
};

#endif
