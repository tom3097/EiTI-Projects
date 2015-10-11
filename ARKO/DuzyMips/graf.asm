#	Przygotowal: Tomasz Bochenski
#	Temat projektu: grafika wektorowa
#	Ostatnie modyfikacje: 14.11.2014

#	Uzywane rejestry:
#	$t0 - deskryptor pliku, rejestr pomocniczy
#	$t1 - zaalokowany bufor
#	$t2 - szerokosc bitmapy
#	$t3 - wysokosc bitmapy
#	$t4 - szerokosc mapy z uwzglednieniem paddingu
#	$t5 - aktualny kolor
#	$t6 - rejestr pomocniczy
#	$t7 - rozmiar tablicy pikseli
#	$s0 - rejestr pomocniczy, piksel poczatkowy prostokata, srodek kol
#	$s1 - wspolrzedna x (srodka kola / lewego dolnego rogu prostokata)
#	$s2 - wspolrzedna y (srodka kola / lewego dolnego roku prostokata)
#	$s3 - szerokosc prostokata, rejestr pomocniczy
#	$s4 - wysokosc prostokata, rejestr pomocniczy
#	$s5 - dlugosc promienia kola
#	$s6 - pomocniczy rejestr
#	$s7 - pomocniczy rejestr
#	$t8 - rejestr pomocniczy
#	$t9 - rejestr pomocniczy


			.data
	in:		.asciiz		"in.bmp"
	header:		.space		54
	error_info:	.asciiz		"Blad podczas wczytywania pliku\n"
	success_end:	.asciiz		"Program zakonczony z sukcesem\n"
	rectangle_x:	.asciiz		"Podaj wspolrzedna x lewego dolnego rogu (0 - 1024):\n"
	rectangle_y:	.asciiz		"Podaj wspolrzedna y lewego dolnego rogu (0 - 1024):\n"
	rectangle_length:	.asciiz	"Podaj dlugosc prostokata (0 - 1024):\n"
	rectangle_height:	.asciiz	"Podaj wysokosc prostokata (0 - 1024):\n"
	circle_x:	.asciiz		"Podaj x srodka kola (0 - 1024):\n"
	circle_y:	.asciiz		"Podaj y srodka kola (0 - 1024):\n"
	circle_r:	.asciiz		"Podaj promien (0 - 1024):\n"
	color:		.asciiz		"Wybierz kolor: 1- czerwony; 2- niebieski; 3- zielony, 4- czarny:\n"
	decision:	.asciiz		"Wybierz operacje ktora chcesz przeprowadzic:\n1- rysuj prostokat; 2- rysuj kolo; 3- zakoncz program:\n"
	
			.text
			
			.globl main
	
	main:
			# wczytywanie pliku
			li	$v0,	13	# 13: otwieranie pliku
			la	$a0, 	in	# sciezka do pliku
			li	$a1,	0	# flaga: read only
			li	$a2, 	0	# mode
			syscall
			
			move	$t0,	$v0	# $t0 przechowuje deskryptor pliku
			
			beq	$t0,	0xffffffff,	error_found
				
			# wczytywanie naglowka
			li	$v0,	14	# 14: czytanie z pliku
			la	$a0,	($t0)	# deskryptor
			la	$a1,	header	# bufor docelowy
			li	$a2,	54	# maksymalny rozmiar
			syscall
			
			# zamykanie pliku
			li	$v0,	16	# 16: zamykanie pliku
			move	$a0,	$t0	# do $a0 trafia deskryptor pliku
			syscall
			
			# odczytywanie rozmiaru tablicy pikseli z naglowka i alokowanie odpowiedniej ilosci pamieci
			la	$t6,	header
			
			li	$v0,	9	# 9: alokowanie pamieci
			ulw	$a0,	34($t6)	# ilosc bajtow do alokacji znajduje sie pod 34 bajtem naglowka
			
			move	$t7,	$a0	# kopiujemy do $t7 rozmiar tablicy pikseli
			syscall
			
			move	$t1,	$v0	#adres do nowo zaalokowanej pamieci skopiowany do $t1		
			
			# odczytywanie dlugosci i szerokosci i zapis w odpowiednich rejestrach
			la	$t6,	header
			ulw	$t2,	18($t6)	# szerokosc bitmapy to 18-ty bajt
			ulw	$t3,	22($t6)	# wysokosc bitmapy to 22-gi bajt
			
			# ustawiam kolor oraz adres ostatniego piksela
			li	$t5,	0xff	# kolor: bialy
			addu	$t6,	$t1,	$t7	# $t6 - adres ostatniego piksela
			
			# czyszczenie mapy - wypelnianie jej bialym kolorem
			move	$s0,	$t1	# kopiuje adres zaalokowanego bufora do $s0
			
	continue_cleaning:
			usw	$t5,	($s0)	# koloruje na bialo podany piksel
			addi 	$s0,	$s0,	1	# przechodze do nastepnego pikselu
			blt	$s0,	$t6,	continue_cleaning	# wraca do pocaatku petli czyszczacej
			
			# przeprowadzanie paddingu
			mulu	$t4,	$t2,	3	# poniewaz na kazdy piksel przypadaja 3 bajty, mnoze szerokosc przez 3
			andi	$t6,	$t4,	3	# operacja rownowazna modulo 4
			
			beqz	$t6,	finish_padding	# gdy podana szerokosc jest podzielna przez 4 nie wymaga wyrownania
			
			li	$s0,	4	# laduje 4 do rejestru pomocniczego
			subu	$t6,	$s0,	$t6	# otrzymuje liczbe ktora nalezy dodac aby otrzymac wyrownanie
			addu	$t4,	$t4,	$t6	# wyrownanie
				
	finish_padding:
	main_loop:
			
			# wybieranie figury do narysowania
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	decision
			syscall
			
			# wczytywanie decyzji
			li	$v0,	5	# 5: wczytywanie int
			syscall
			
			move	$t6,	$v0	# ladowanie wczytanej liczby do rejestru $t6
			
			beq	$t6,	1,	draw_rectangle
			beq	$t6,	2	draw_circle
			beq	$t6,	3,	finish_program
			
	draw_circle:		
			# rysujemy kolo
			
			# komunikat wczytywania koloru
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	color
			syscall
			
			# wczytywanie koloru
			li	$v0,	5	# 5: wczytywanie int
			syscall
			
			move	$t5,	$v0
			
			# komunikat wczytywania wspolrzednej x
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	circle_x
			syscall
			
			# wczytywanie wspolrzednej x
			li	$v0,	5	# 5: wczytywanie int
			syscall
			
			move	$s1,	$v0	# kopiowanie wczytanej wspolrzednej to rejestru $s1
			
			# komunikat wczytywania wspolrzednej y
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	circle_y
			syscall
			
			# wczytywanie wspolrzednej y
			li	$v0,	5	# 5: wczytywanie int
			syscall
			
			move 	$s2,	$v0	# kopiowanie wczytanej wspolrzednej do rejestru $s2
			
			# komunikat wczytywania promienia kola
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	circle_r
			syscall
			
			# wczytywanie dlugosci promienia kola
			li	$v0,	5	# 5: wczytywanie int
			syscall
			
			move	$s5,	$v0
			
			# ustawiam odpowiednia wspolrzedna x biorac pod uwage realna szerokosc bitmapy
			mulu	$s1,	$s1,	$t2	# do rejestru $s1 trafia szerokosc bitmapy pomnozona przez wpisany x
			srl	$s1,	$s1,	10	# bo przecinek znajduje sie 10 pozycji na lewo
			
			# ustawiam odpowiednia wspolrzedna y biorac pod uwage realna wysokosc bitmapy
			mulu	$s2,	$s2,	$t3	# do rejestru $s2 trafia wysokosc bitmapy pomnozona przez wpisany y
			srl	$s2,	$s2,	10	# bo przecinek znajduje sie 10 pozycji na lewo
			
			# ustawiam odpowiedni promien kola biorac pod uwage realna szerokosc bitmapy
			mulu	$s5,	$s5,	$t2	# do rejestru $s5 trafia szerokosc bitmapy pomnozona przez wpisany r
			srl	$s5,	$s5,	10	# bo przecinek znajduje sie 10 pozycji na lewo
			
			# odnajduje wspolrzedne srodka kola w tablicy pikseli
			move	$s0,	$t1	# kopiuje adres zaalokowanego bufora do $s0
			
			# odszukiwanie wspolrzednej x piksela
			mulu	$t6,	$s1,	3	# mnoze obliczona x przez 3 bo na kazdy piksel przypadaja 3 bajty
			addu	$s0,	$s0,	$t6	# dodaje do bufora wynik poprzedniej operacji, mamy wspolrzeda x piksela
			
			# odszukiwanie wspolrzednej y piksela
			mulu	$t6,	$s2,	$t4	# mnoze y przez szerokosc bitmapy z paddingiem
			addu	$s0,	$s0,	$t6	# dodaje do bufora wynik poprzedniej operacji, mam wsp y piksela
			
			#################### Algorytm Bresenhama rysowania kola #################
			
			# Rejestry uzyte w algorytmie:
			# $s7 - przechowuje aktualny x
			# $s6 - przechowuje aktualny y
			# $s4 - przechowuje aktualny wspolczynnik e
			# $s3 - pierwszy adres ostatniego pixela do malowania
			# $t8 - drugi adres ostatniego piksela do malowania
			# $t6 - przechowuje wspolczynnik e2
			# $t0 - rejestr pomocniczy, przechowuje: ilosc pozostalych do zamalowania pikseli, e1
			# $t9 - rejestr pomocniczy, przechowuje 0xff
			
			li	$s7,	0	# inicjalizuje wartosc x na 0
			move	$s6,	$s5	# inicjalizuje wartosc y na r
			li	$s4,	0	# inicjalizuje wartosc e na 0
			
	circle_begin:
			
			bgt	$s7,	$s6,	finish_painting		# gdy x > y konczymy rysowanie
			
			# wyliczam ilosc pixeli do pomalowania w jednej linii
			move	$t0,	$s6	# laduje y do $t0
			mulu	$t0,	$t0,	2	# mnoze wartosc przez 2
			addu	$t0,	$t0,	1	# dodaje 1
			
			# ustawiam poczatki miejsc do kolorowania
			move	$s3,	$s0	# kopiuje lokalizacje srodka kola
			
			mulu	$t9,	$s6,	3	# mnoze przez 3 wspolrzedna x, bo 3 bajty na piksel
			addu	$s3,	$s3,	$t9	# wspolrzedna x zostaje ustawiona
			move	$t8,	$s3		# kopiuje $s3 do $t8 zeby dwa razy nie ustawiac
			mulu	$t9,	$s7,	$t4	# mnoze y przez szerokosc mapy z uwzglednieniem paddingu
			addu	$s3,	$s3,	$t9	# $s3 ustawione w odpowiednim miejscu (adres1)
			subu	$t8,	$t8,	$t9	# $t8 ustawione w odpowiednim miejscu (adres2)	
			
			li	$t9, 0xff		# bezposrednio przed malowaniem ustawiamy $t9 na 0xff
			
	still_drawing:
			beqz	$t0,	go_to_next_level	# gdy ilosc pikseli do zamalowania wynosi 0 wychodzimy z petli
			
			beq	$t5,	1,	first_red_coloring_circle		# skacze do miejsca gdzie kolorowane jest na czerwono
			beq	$t5,	2,	first_blue_coloring_circle		# skacze do miejsca gdzie kolorowane jest na niebiesko
			beq	$t5,	3,	first_green_coloring_circle		# skacze do miejsca gdzie kolorowane jest na zielono
			beq	$t5,	4,	first_black_coloring_circle		# skacze do miejsca gdzie kolorowane jest na czarno
			
			# kolorowanie na czerwono kola	
	first_red_coloring_circle:
			sb	$zero,	($t8)
			sb	$zero,	1($t8)
			sb	$t9,	2($t8)
			
			sb	$zero,	($s3)
			sb	$zero,	1($s3)
			sb	$t9,	2($s3)
			
			j	ret_from_first_coloring_circle
			# kolorowanie na niebiesko kola
	first_blue_coloring_circle:
			sb	$t9,	($t8)
			sb	$zero,	1($t8)
			sb	$zero,	2($t8)
			
			sb	$t9,	($s3)
			sb	$zero,	1($s3)
			sb	$zero,	2($s3)
			
			j	ret_from_first_coloring_circle
			# kolorowanie na zielono kola
	first_green_coloring_circle:
			sb	$zero,	($t8)
			sb	$t9,	1($t8)
			sb	$zero,	2($t8)
			
			sb	$zero,	($s3)
			sb	$t9,	1($s3)
			sb	$zero,	2($s3)
			
			j	ret_from_first_coloring_circle
			# kolorowanie na czarno kola
	first_black_coloring_circle:
			sb	$zero,	($t8)
			sb	$zero,	1($t8)
			sb	$zero,	2($t8)
			
			sb	$zero,	($s3)
			sb	$zero,	1($s3)
			sb	$zero,	2($s3)
			
			j	ret_from_first_coloring_circle
	
	ret_from_first_coloring_circle:	
			subu	$t8,	$t8,	3	# cofam sie o 1 piksel (3 bajty)
			subu	$s3,	$s3,	3	# cofam sie o 1 piksel (3 bajty)
			subu	$t0,	$t0,	1	# zmniejszamy liczby pikseli do pokolorowania o 1
			j	still_drawing
			
	go_to_next_level:
			
			# liczymy e1
			mulu	$t0,	$s7,	2	# zapisuje wynik 2*x
			addu	$t0,	$t0,	1	# dodaje 1
			addu	$t0,	$t0,	$s4	# dodaje e
			
			# licze e2
			addu	$t6,	$t0,	1	# zapisuje wynik e1+1
			subu	$t6,	$t6,	$s6	# odejmuje y
			subu	$t6,	$t6,	$s6	# odejmuje y
				
			#licze -e2 ( pomocniczo)
			mulu	$t6,	$t6,	-1	# zmieniam znak (-e2)
			
			blt	$t0,	$t6,  skip_draw_part	# gdy e1 + e2 < 0 to skacze
			
			mulu	$t6,	$t6,	-1	# zmieniam znak (e2)
			move	$s4,	$t6		# e = e2	
			
			# wyliczam ilosc pixeli do pomalowania w jednej linii
			move	$t0,	$s7	# laduje x do $t0
			mulu	$t0,	$t0,	2	# mnoze wartosc przez 2
			addu	$t0,	$t0,	1	# dodaje 1
			
			move	$s3,	$s0	# kopiuje lokalizacje srodka kola
			mulu	$t9,	$s7,	3	# mnoze przez 3 wspolrzedna x, bo 3 bajty na piksel
			addu	$s3,	$s3,	$t9	# wspolrzedna x zostaje ustawiona
			move	$t8,	$s3		# kopiuje $s3 do $t8 zeby dwa razy nie ustawiac
			mulu	$t9,	$s6,	$t4	# mnoze y przez szerokosc mapy z uwzglednieniem paddingu
			addu	$s3,	$s3,	$t9	# $s3 ustawione w odpowiednim miejscu (adres1)
			subu	$t8,	$t8,	$t9	# $t8 ustawione w odpowiednim miejscu (adres2)	
			
			li	$t9, 0xff		# bezposrednio przed malowaniem ustawiamy $t9 na 0xff
			
	sec_still_drawing:	

			beqz	$t0,	sec_go_to_next_level
			
			beq	$t5,	1,	sec_red_coloring_circle		# skacze do miejsca gdzie kolorowane jest na czerwono
			beq	$t5,	2,	sec_blue_coloring_circle		# skacze do miejsca gdzie kolorowane jest na niebiesko
			beq	$t5,	3,	sec_green_coloring_circle		# skacze do miejsca gdzie kolorowane jest na zielono
			beq	$t5,	4,	sec_black_coloring_circle		# skacze do miejsca gdzie kolorowane jest na czarno
			
			# kolorowanie na czerwono kola	
	sec_red_coloring_circle:
			sb	$zero,	($t8)
			sb	$zero,	1($t8)
			sb	$t9,	2($t8)
			
			sb	$zero,	($s3)
			sb	$zero,	1($s3)
			sb	$t9,	2($s3)
			
			j	ret_from_sec_coloring_circle
			# kolorowanie na niebiesko kola
	sec_blue_coloring_circle:
			sb	$t9,	($t8)
			sb	$zero,	1($t8)
			sb	$zero,	2($t8)
			
			sb	$t9,	($s3)
			sb	$zero,	1($s3)
			sb	$zero,	2($s3)
			
			j	ret_from_sec_coloring_circle
			# kolorowanie na zielono kola
	sec_green_coloring_circle:
			sb	$zero,	($t8)
			sb	$t9,	1($t8)
			sb	$zero,	2($t8)
			
			sb	$zero,	($s3)
			sb	$t9,	1($s3)
			sb	$zero,	2($s3)
			
			j	ret_from_sec_coloring_circle
			# kolorowanie na czarno kola
	sec_black_coloring_circle:
			sb	$zero,	($t8)
			sb	$zero,	1($t8)
			sb	$zero,	2($t8)
			
			sb	$zero,	($s3)
			sb	$zero,	1($s3)
			sb	$zero,	2($s3)
			
			j	ret_from_sec_coloring_circle
			
	ret_from_sec_coloring_circle:
			subu	$t8,	$t8,	3	# cofam sie o 1 pixel (3 bajty)
			subu	$s3,	$s3,	3	# cofam sie o 1 pixel (3 bajty)
			
			subu	$t0,	$t0,	1	# zmniejszamy liczbe pozostalych do pokolorowania pikseli o 1
			
			j sec_still_drawing
	
	sec_go_to_next_level:	
			subu	$s6,	$s6,	1	# zmniejszamy y o 1
			addu	$s7,	$s7,	1	# zwiekszamy x o 1
			j	circle_begin		
	
	skip_draw_part:
			
			move	$s4,	$t0	# e = e1
			addu	$s7,	$s7,	1	# x = x+1
			j 	circle_begin
						
	draw_rectangle:
			# rysujemy prostokat
			
			# komunikat wczytywania koloru
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	color
			syscall
			
			# wczytywanie koloru
			li	$v0,	5	# 5: wczytywanie int
			syscall
			
			move	$t5,	$v0
			
			# komunikat wczytywania wspolrzednej x
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	rectangle_x
			syscall
			
			# wczytywanie wspolrzednej x
			li	$v0,	5	# 5: wczytywanie int
			syscall
			
			move	$s1,	$v0	# kopiowanie wczytanej wspolrzednej to rejestru $s1
			
			# komunikat wczytywania wspolrzednej y
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	rectangle_y
			syscall
			
			# wczytywanie wspolrzednej y
			li	$v0,	5	# 5: wczytywanie int
			syscall
			
			move 	$s2,	$v0	# kopiowanie wczytanej wspolrzednej do rejestru $s2
			
			# komunikat wczytywania szerokosci prostokata
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	rectangle_length
			syscall
			
			# wczytywanie szerokosci prostokata
			li	$v0,	5	# 5: wczytywanie int
			syscall
			
			move	$s3,	$v0	# kopiowanie wczytanej szerokosci do rejestru $s3
			
			# komunikat wczytywania wysokosci prostokata
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	rectangle_height
			syscall
			
			# wczytywanie wysokosci prostokata
			li	$v0,	5	# 5: wczytywanie int
			syscall
			
			move	$s4,	$v0	# kopiowanie wczytanej szerokosci do rejestru $s4	
			
			# ustawiam odpowiednia wspolrzedna x biorac pod uwage realna szerokosc bitmapy
			mulu	$s1,	$s1,	$t2	# do rejestru $s1 trafia szerokosc bitmapy pomnozona przez wpisany x
			srl	$s1,	$s1,	10	# bo przecinek znajduje sie 10 pozycji na lewo
			
			# ustawiam odpowiednia wspolrzedna y biorac pod uwage realna wysokosc bitmapy
			mulu	$s2,	$s2,	$t3	# do rejestru $s2 trafia wysokosc bitmapy pomnozona przez wpisany y
			srl	$s2,	$s2,	10	# bo przecinek znajduje sie 10 pozycji na lewo
			
			# ustawiam odpowiednia szerokosc prostokata biarac pod uwage realna szerokosc bitmapy
			mulu	$s3,	$s3,	$t2	# do rejestru $s3 trafia szerokosc bitmapy pomnozona przez dlugosc prostokata
			srl	$s3,	$s3,	10	# bo przecinek znajduje sie 10 pozycji na lewo
			
			# ustawiam odpowiedniea wysokosc prostokata biorac pod uwage realna wysokosc bitmapy
			mulu	$s4,	$s4,	$t3	# do rejestru $s4 trafia wysokosc bitmapy pomnozona przez wysokosc prostokata
			srl	$s4,	$s4,	10	# bo przecinek znajduje sie 10 pozycji na lewo
			
			move	$s0,	$t1	# kopiuje adres zaalokowanego bufora do $s0
			
			# odszukiwanie wspolrzednej x piksela
			mulu	$t6,	$s1,	3	# mnoze obliczona x przez 3 bo na kazdy piksel przypadaja 3 bajty
			addu	$s0,	$s0,	$t6	# dodaje do bufora wynik poprzedniej operacji, mam wsp x piksela
			
			# odszukiwanie wspolrzednej y piksela
			mulu	$t6,	$s2,	$t4	# mnoze y przez szerokosc bitmapy z paddingiem
			addu	$s0,	$s0,	$t6	# dodaje do bufora wynik poprzedniej operacji, mam wsp y piksela
			
			li	$t0,	0xff		# laduje skladowa koloru
	
	new_level:
			beqz	$s4,	finish_painting
			move	$t6,	$s0		# do rejestru pomocniczego trafia lokalizacja pierwszego do pomalowania pixela
			move	$s7,	$s3		# do $s7 trafia szerokosc prostokata
	line_coloring:
			beqz	$s7,	next_level	# szerokosc powstalej lini rowna szerokosci prostokata, skaczemy na nastepny level
			
			beq	$t5,	1,	red_coloring_rectangle		# skacze do miejsca gdzie kolorowane jest na czerwono
			beq	$t5,	2,	blue_coloring_rectangle		# skacze do miejsca gdzie kolorowane jest na niebiesko
			beq	$t5,	3,	green_coloring_rectangle	# skacze do miejsca gdzie kolorowane jest na zielono
			beq	$t5,	4,	black_coloring_rectangle	# skacze do miejsca gdzie kolorowane jest na czarno
				
			# kolorowanie na czerwono prostokat
	red_coloring_rectangle:
			sb	$zero,	($t6)
			sb	$zero,	1($t6)
			sb	$t0,	2($t6)
			
			j	ret_from_coloring	
			# kolorowanie na niebiesko prostokata
	blue_coloring_rectangle:	
			sb	$t0,	($t6)
			sb	$zero,	1($t6)
			sb	$zero,	2($t6)
			
			j	ret_from_coloring
			# kolorowanie na zielono prostokata
	green_coloring_rectangle:	
			sb	$zero,	($t6)
			sb	$t0,	1($t6)
			sb	$zero,	2($t6)
			
			j	ret_from_coloring
			# kolorowanie na czarno prostokata
	black_coloring_rectangle:	
			sb	$zero,	($t6)
			sb	$zero,	1($t6)
			sb	$zero,	2($t6)
			
			j	ret_from_coloring	
			
	ret_from_coloring:
			
			addu	$t6,	$t6,	3	# zwiekszam, przechodze na kolejny piksel
			subu	$s7,	$s7,	1	# zmniejszam pozostala do pomalowania ilosc pikseli
			
			j	line_coloring
	
	next_level:
			addu	$s0,	$s0,	$t4	# zwiekszam o szerokosc paddingu, przechodze na nastepny poziom
			subu	$s4,	$s4,	1	# zmniejszam ilosc poziomow pozostalych do pomalowania
			
			j	new_level	
	
	finish_painting:	
			j	main_loop
			
	finish_program:
			# otwieranie pliku do zapisu
			li	$v0,	13	# 13: otwieranie pliku
			la	$a0,	in	# sciezka do pliku
			li	$a1,	1	# flaga: otwieranie w calu zapisu
			li	$a2,	0	# mode
			syscall
			
			move	$t0,	$v0	# t0 przechowuje deskryptor pliku
			
			# zapisywanie naglowka do pliku
			li	$v0,	15	# 15: zapis do pliku
			move	$a0,	$t0	# kopiuje deskryptor pliku
			la	$a1,	header	# parametr ktory ma zostac zapisany
			li	$a2,	54	# rozmiar naglowka
			syscall
			
			# zapisywanie tablicy pikseli do pliku
			li	$v0,	15	# 15: zapis do pliku
			move	$a0,	$t0	# kopiuje deskryptor pliku
			la	$a1,	($t1)	# parametr ktory ma zostac zapisany
			move	$a2,	$t7	# rozmiar tablicy pikseli
			syscall
			
			# zamykanie pliku
			li	$v0,	16	# 16: zamykanie pliku
			move	$a0,	$t0	# deskryptor pliku do zamkniecia
			syscall
			
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	success_end
			syscall
			
			j	exit
			
	error_found:	
			li	$v0,	4	# 4: wyswietlanie komunikatu
			la	$a0,	error_info
			syscall
			
	exit:
			# konczenie programu
			li	$v0,	10
			syscall		
