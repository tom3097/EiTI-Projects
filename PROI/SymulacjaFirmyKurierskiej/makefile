
CC = g++
LFLAGS = -Wall
CFLAGS = -Wall -c -std=c++11

start: main.o Klient.o Przesylka.o Samochod.o Placowka.o Baza.o Oddzial.o 
	$(CC) $(LFLAGS) main.o Klient.o Przesylka.o Samochod.o Placowka.o Baza.o Oddzial.o -o start

main.o: main.cpp Baza.h Oddzial.h
	$(CC) $(CFLAGS) main.cpp

Baza.o: Baza.cpp Baza.h Placowka.h
	$(CC) $(CFLAGS) Baza.cpp

Oddzial.o: Oddzial.cpp Oddzial.h Placowka.h
	$(CC) $(CFLAGS) Oddzial.cpp

Placowka.o: Placowka.cpp Placowka.h Samochod.h
	$(CC) $(CFLAGS) Placowka.cpp

Samochod.o: Samochod.cpp Samochod.h Przesylka.h
	$(CC) $(CFLAGS) Samochod.cpp

Przesylka.o: Przesylka.cpp Przesylka.h Klient.h
	$(CC) $(CFLAGS) Przesylka.cpp

Klient.o: Klient.cpp Klient.h
	$(CC) $(CFLAGS) Klient.cpp

clean:
	rm -f main.o Baza.o Oddzial.o Placowka.o Samochod.o Przesylka.o Klient.o