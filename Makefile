CC = g++
CFLAGS = -Iincl -Wall -g

all: exec LineBuffer VTConverter
	$(CC) -o bin/main obj/exec.o obj/LineBuffer.o obj/VTConverter.o

exec:
	$(CC) -o obj/exec.o -c src/main.cpp $(CFLAGS)

LineBuffer:
	$(CC) -o obj/LineBuffer.o -c src/LineBuffer.cpp $(CFLAGS)

VTConverter:
	$(CC) -o obj/VTConverter.o -c src/VTConverter.cpp $(CFLAGS)

clean:
	rm -rf obj/*
	rm -rf bin/*