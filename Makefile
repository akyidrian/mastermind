mm4pc: main.o frame.o 
	gcc -o mm4pc main.o frame.o 

main.o: main.c
	gcc -Wall -g -c main.c

frame.o: frame.c
	gcc -Wall -g -c frame.c




