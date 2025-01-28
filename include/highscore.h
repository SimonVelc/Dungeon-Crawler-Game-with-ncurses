#ifndef HiScore_h
#define HiScore_h
#include <fstream>

using namespace std;

struct Entries{
	char name[11];//max name-length 10
	int score;//players' score
};

class HiScore
{
protected:
    Entries entries[5];//table of top 5
    string fname;//filename of score file
    char Name[11];
public:
    HiScore(string argv);//reads score file
    HiScore &operator<<(char *);//to save player name
    void operator<<(int a);//to add new score
};

#endif
