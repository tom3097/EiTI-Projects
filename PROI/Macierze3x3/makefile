# PLIK MAKEFILE DO PROJEKTU PIERWSZEGO: MACIERZE_3X3
# PRZYGOTOWAL: TOMASZ BOCHENSKI

CC = g++
LFLAGS = -Wall
CFLAGS = -Wall -c 
ARCHIVABLE = main.cpp Macierze_3x3.cpp Macierze_3x3.h main.o Macierze_3x3.o start makefile

start: main.o Macierze_3x3.o
	$(info LACZENIE)
	$(CC) $(LFLAGS) main.o Macierze_3x3.o -o start

main.o: main.cpp
	$(info KOMPILACJA MAIN.CPP)
	$(CC) $(CFLAGS) main.cpp

Macierze_3x3.o: Macierze_3x3.cpp Macierze_3x3.h
	$(info KOMPILACJA Macierze_3x3.CPP)
	$(CC) $(CFLAGS) Macierze_3x3.cpp

clean:
	$(info CZYSZCZENIE)
	rm -f *.o start Macierze_3x3.tar

tar:
	rm -f Macierze_3x3.tar
	tar cfv Macierze_3x3.tar $(ARCHIVABLE)
