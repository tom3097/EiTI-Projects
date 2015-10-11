
CC = g++
LFLAGS = -Wall
CFLAGS = -Wall -c -std=c++11

start: main.o zbior.o
	$(CC) $(LFLAGS) main.o zbior.o -o start

main.o: main.cpp zbior.h
	$(CC) $(CFLAGS) main.cpp

zbior.o: zbior.cpp zbior.h macierze_szablon.h
	$(CC) $(CFLAGS) zbior.cpp

clean:
	rm -f main.o zbior.o