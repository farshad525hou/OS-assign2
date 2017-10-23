CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
all: P1 P2

P1 : ./Part1/semassign2_p1.o
	$(CC) ./Part1/semassign2_p1.o -pthread -o P1

semassign2.o : ./Part1/semassign2_p1.c buffer.h
	$(CC) -c ./Part1/semassign2_p1.c

P2 : ./Part2/semassign2_p2.o
		$(CC) ./Part2/semassign2_p2.o -pthread -o P2

semassign2_p2.o : ./Part2/semassign2_p2.c buffer.h
		$(CC) -c ./Part2/semassign2_p2.c







clean:
	rm *P1
	rm ./Part1/*.o
	rm *P2
	rm ./Part2/*.o
