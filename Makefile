all : proj

proj : proj1.o
	gcc proj1.o -o run

proj1.o : proj1.c
	gcc -c proj1.c -std=c99 
	
clean :
	rm *.o