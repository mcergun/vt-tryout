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

all: Key Line OutputChannel

Key:
	$(CC) -o obj/Key.o -c src/Key.cpp $(CFLAGS)

Line:
	$(CC) -o obj/Line.o -c src/LineBuffer.cpp $(CFLAGS)

OutputChannel:
	$(CC) -o obj/OutputChannel.o -c src/OutputChannel.cpp $(CFLAGS)

clean:
	rm -rf obj/*
	rm -rf bin/*