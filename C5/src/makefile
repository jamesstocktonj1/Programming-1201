#
#         File: makefile
#       Author: Steve Gunn
#      License: MIT License
#         Date: 27th October 2018
#  Description: Makefile to build circuit simulator.
#

CC = gcc
FLAGS = -pedantic -Wall

analyse: analyse.c circuit.o matrix.o vector.o 
	$(CC) analyse.c circuit.o matrix.o vector.o -o analyse $(FLAGS)

circuit.o: circuit.c circuit.h
	$(CC) -c circuit.c $(FLAGS)

matrix.o: matrix.c matrix.h
	$(CC) -c matrix.c $(FLAGS)

vector.o: vector.c vector.h
	$(CC) -c vector.c $(FLAGS)

clean:
	del /F *.o analyse.exe
	