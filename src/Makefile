# compiler

CC = g++

# flags

FLAGS = -O2 -std=c++11 -pedantic -Wall -Werror

# >>>>>>>> Rules default to create program <<<<<< #

all: main

main: main.o logger.o
	$(CC) -g3 $(FLAGS) main.o logger.o -o main
	./main

main.o:	logger.o
	$(CC) $(FLAGS) -c main.cpp

logger.o:
	$(CC) $(FLAGS) -c logger.cpp 

.PHONY: clean

clean:
	rm main *.o

# >>>>>>>>>>>>>>>>>>> END FILE <<<<<<<<<<<<<<<<<<< #