all:    main asm link

main:   main.c
	gcc -g -c -m64 main.c -o main.o

asm:    UnconditionalDrawPoint.s
	nasm -f elf64 UnconditionalDrawPoint.s -o UnconditionalDrawPoint.o

link:   main.o UnconditionalDrawPoint.o
	gcc -g -m64 -o output main.o UnconditionalDrawPoint.o -lglut -lGL -lGLEW -lGLU
