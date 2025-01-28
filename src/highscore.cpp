#include <fstream>
#include <iostream>
#include "highscore.h"
#include <string.h>
#include <cstdlib>

HiScore::HiScore(string argv){
    fname = argv;
    ifstream file(fname , ios::in | ios::binary); 
    file.exceptions (std::ifstream::badbit |std::ifstream::failbit);

    try{
	for(int i=0 ; i <5 ; i++){
		file.read((char*) &entries[i], sizeof(Entries));
	}
        file.close();
    }catch(std::ifstream::failure e){
        std::cerr<<"Exception opening the file\n";
    }
}

HiScore &HiScore::operator<<(char* name){
    int i=strlen(name);
    if(i<11){
	strcpy(Name,name);
    }
    return *this;
}

void HiScore::operator<<(int a){
    ofstream file(fname , ios::out | ios::binary); 
    file.exceptions (std::ofstream::badbit |std::ofstream::failbit);
	int pep=0;
     for(int j=0 ; j < 5 ; j++){
	if(a>entries[j].score){
		pep=1;
	}
	}
    if(pep){
    try{
	
	int temp=entries[0].score;
	int temp1=0;
	char tempc[11];
	for(int i=0 ; i<5 ;i++){
		if(temp>entries[i].score){
			temp=entries[i].score;
			temp1=i;		
		}
	}
	if(temp<a){
		entries[temp1].score=a;
		strcpy(entries[temp1].name,Name);
	}
	for(int i=0 ; i<5 ; i++){
		for(int j=i+1 ; j<5 ; j++){
			if(entries[j].score>entries[i].score){
				temp=entries[i].score;
				strcpy(tempc,entries[i].name);
			entries[i].score=entries[j].score;
		       strcpy(entries[i].name,entries[j].name);
			entries[j].score=temp;
		       strcpy(entries[j].name,tempc);		
			}		
		}
	
	}
	for(int i=0 ; i <5 ; i++){
		file.write((char*) &entries[i], sizeof(Entries));	
	}
	
    }catch(std::exception e){
        std::cerr<<"Exception opening the file\n";
    }}
	file.close(); 
	
}
