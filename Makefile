CC = g++
CFLAGS = -Iincl -Wall

all: exec LineBuffer
	$(CC) -o bin/main obj/exec.o obj/LineBuffer.o

exec:
	$(CC) -o obj/exec.o -c src/main.cpp $(CFLAGS)

LineBuffer:
	$(CC) -o obj/LineBuffer.o -c src/LineBuffer.cpp $(CFLAGS)

clean:
	rm -rf obj/*
	rm -rf bin/*