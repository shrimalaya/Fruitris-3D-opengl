CC = g++
CFLAGS = -g -Wall
LIBS = -lGL -lGLU -lglut
SRC = main.cpp
OUTPUT = FruitTetris3D

all:$(SRC)
	$(CC) -o $(OUTPUT) $(SRC) $(CFLAGS) $(LIBS)

