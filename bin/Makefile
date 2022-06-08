CFLAGS = 

#-g -DMAP -ansi -pedantic -std=c++11

analog: main.o Lecture.o StatLog.o
	g++ $(CFLAGS) -o analog *.o

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp
    
Lecture.o: Lecture.cpp
	g++ $(CFLAGS) -c Lecture.cpp

StatLog.o: StatLog.cpp
	g++ $(CFLAGS) -c StatLog.cpp