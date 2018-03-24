CC = g++
CFLAGS = -Iincl -Wall -g

all: CreateFolders Main Key LineBuffer Line OutputChannel AutoComplete
	$(CC) -o bin/term-impl obj/OutputChannel.o obj/AutoComplete.o obj/LineBuffer.o obj/Line.o obj/Key.o obj/Main.o

CreateFolders:
	mkdir -p obj
	mkdir -p bin

Main:
	$(CC) -o obj/Main.o -c src/main.cpp $(CFLAGS)

Key:
	$(CC) -o obj/Key.o -c src/Key.cpp $(CFLAGS)

LineBuffer:
	$(CC) -o obj/LineBuffer.o -c src/LineBuffer.cpp $(CFLAGS)

Line:
	$(CC) -o obj/Line.o -c src/Line.cpp $(CFLAGS)

OutputChannel:
	$(CC) -o obj/OutputChannel.o -c src/OutputChannel.cpp $(CFLAGS)
	
AutoComplete:
	$(CC) -o obj/AutoComplete.o -c src/AutoComplete.cpp $(CFLAGS)

clean:
	rm -rf obj/*
	rm -rf bin/*