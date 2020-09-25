CC = gcc
objects = main.o distance.o levenshteindistance.o stackCommand.o priorityQueueFile.o iofile.o timer.o

all : fileDistance

fileDistance : $(objects)
	$(CC) -o fileDistance $(objects)

main.o : main.c distance.h

distance.o : distance.c timer.h levenshteindistance.h iofile.h stackCommand.h

levenshteindistance.o : levenshteindistance.c stackCommand.h priorityQueueFile.h iofile.h

iofile.o : iofile.c stackCommand.h

stackCommand.o : stackCommand.c

priorityQueueFile.o : priorityQueueFile.h

timer.o : timer.c

clean : 
	rm *.o fileDistance