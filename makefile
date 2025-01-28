main: main.o engine.o player.o mover.o monster.o highscore.o
	g++ engine.o main.o mover.o player.o monster.o highscore.o -o main -lncurses

engine.o: engine.cpp engine.h
	g++ -c engine.cpp   

main.o: main.cpp
	g++ -c main.cpp

player.o: player.cpp player.h
	g++ -c player.cpp

mover.o: mover.cpp mover.h
	g++ -c mover.cpp

monster.o: monster.cpp monster.h
	g++ -c monster.cpp

highscore.o: highscore.cpp highscore.h
	g++ -c highscore.cpp

clean:
	rm *.o main

run:
	./main labirinth.txt scores.bin
