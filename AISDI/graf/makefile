CC = g++
LFLAGS = -Wall
CFLAGS = -Wall -c 
ARCHIVABLE = main.cpp graf.cpp graf.h main.o graf.o start makefile

start: main.o graf.o
	$(info LACZENIE)
	$(CC) $(LFLAGS) main.o graf.o -o start

main.o: main.cpp
	$(info KOMPILACJA MAIN.CPP)
	$(CC) $(CFLAGS) main.cpp

graf.o: graf.cpp graf.h
	$(info KOMPILACJA graf.CPP)
	$(CC) $(CFLAGS) graf.cpp

clean:
	$(info CZYSZCZENIE)
	rm -f *.o start graf.tar

tar:
	rm -f graf.tar
	tar cfv graf.tar $(ARCHIVABLE)
