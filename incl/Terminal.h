#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <unistd.h>
#include <termios.h>
#include <LineBuffer.h>
#include <VTConverter.h>

static const int BUF_SIZE = 64;

class Terminal
{
public:
	Terminal();
	Terminal(int inBuf);
	int SetAttributes(termios *term, termios *termOrig);
	int ReadBuf();
	void GetLine(char *dst);
private:
	termios term, termOrig;
	LineBuffer line;
	VTConverter conv;
	char buf[BUF_SIZE];
	bool initialized = false;
	int inputBuffer = 0;
};

#endif