# compiler

CC = g++

# flags

FLAGS = -O2 -std=c++11 -pedantic -Wall -Werror

# >>>>>>>> Rules default to create program <<<<<< #

all: main

main: main.o logger.o socket.o
	$(CC) -g3 $(FLAGS) main.o socket.o logger.o -o main
	./main

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

logger.o: logger.cpp
	$(CC) $(FLAGS) -c logger.cpp 

socket.o: socket.cpp
	$(CC) $(FLAGS) -c socket.cpp
	
.PHONY: clean

clean:
	rm main *.o

# >>>>>>>>>>>>>>>>>>> END FILE <<<<<<<<<<<<<<<<<<< #