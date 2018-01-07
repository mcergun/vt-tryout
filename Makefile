CC = g++

all: exec LineBuffer
	$(CC) -o bin/main obj/exec.o obj/LineBuffer.o

exec:
	$(CC) -o obj/exec.o -c src/main.cpp -Iincl

LineBuffer:
	$(CC) -o obj/LineBuffer.o -c src/LineBuffer.cpp -Iincl

clean:
	rm -rf obj/*
	rm -rf bin/*