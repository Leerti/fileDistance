CC = gcc
objects = main.o distance.o levenshteindistance.o stackCommand.o iofile.o timer.o

all : main

all : $(objects)
	$(CC) -o fileDistance $(objects)

main.o : main.c distance.o 
	gcc -c main.c


distance.o : distance.c timer.o levenshteindistance.o iofile.o stackCommand.o distance.h
	gcc -c  distance.c

levenshteindistance.o : levenshteindistance.c levenshteindistance.h stackCommand.o  iofile.o
	gcc -c levenshteindistance.c

iofile.o : iofile.c iofile.h stackCommand.o
	gcc -c iofile.c

stackCommand.o : stackCommand.c stackCommand.h
	gcc -c stackCommand.c
	

timer.o : timer.c timer.h
	gcc -c timer.c


clean : 
	rm *.o distance