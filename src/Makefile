# Created By: Marcos alves
# Created Date: May 3th, 2016	  
# Last Modified: May 7th, 2016	

# compiler

CC = g++

# flags

FLAGS = -O2 -std=c++11 -pedantic -Wall -Werror

# >>>>>>>> Rules default to create program <<<<<< #

all: main

main: main.o logger.o socket.o emulator.o
	$(CC) -pthread -g3 $(FLAGS) main.o socket.o logger.o emulator.o -o main
	./main

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

logger.o: logger.cpp
	$(CC) $(FLAGS) -c logger.cpp 

socket.o: socket.cpp
	$(CC) $(FLAGS) -c socket.cpp

emulator.o: emulator.cpp
	$(CC) $(FLAGS) -c emulator.cpp	

.PHONY: clean

clean:
	rm main *.o

# >>>>>>>>>>>>>>>>>>> END FILE <<<<<<<<<<<<<<<<<<< #