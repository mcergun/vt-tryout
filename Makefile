CC = g++
CFLAGS = -Iincl -Wall -g

# all: exec Terminal LineBuffer VTConverter ConsoleComm
# 	$(CC) -o bin/main obj/exec.o obj/LineBuffer.o obj/VTConverter.o obj/Terminal.o obj/ConsoleComm.o

# exec:
# 	$(CC) -o obj/exec.o -c src/main.cpp $(CFLAGS)

# Terminal:
# 	$(CC) -o obj/Terminal.o -c src/Terminal.cpp $(CFLAGS)

# ConsoleComm:
# 	$(CC) -o obj/ConsoleComm.o -c src/ConsoleComm.cpp $(CFLAGS)

# LineBuffer:
# 	$(CC) -o obj/LineBuffer.o -c src/LineBuffer.cpp $(CFLAGS)

# VTConverter:
# 	$(CC) -o obj/VTConverter.o -c src/VTConverter.cpp $(CFLAGS)

all: Main Key LineBuffer Line OutputChannel
	$(CC) -o bin/term-impl obj/OutputChannel.o obj/LineBuffer.o obj/Line.o obj/Key.o obj/Main.o

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

clean:
	rm -rf obj/*
	rm -rf bin/*