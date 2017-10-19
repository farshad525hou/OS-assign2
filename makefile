CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Part1 : semassign2.o
	$(CC) semassign2.o -pthread -o Part1

semassign2.o : semassign2.c buffer.h
	$(CC) -c semassign2.c


 



	
clean:	
	rm *.o *Part1
