#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <unistd.h>
#include <termios.h>
#include <LineBuffer.h>
#include <VTConverter.h>
#include <ICommChannel.h>

static const int BUF_SIZE = 64;

class Terminal
{
public:
	Terminal();
	~Terminal();
	int ReadBuf();
	void GetLine(char *dst);
private:
	LineBuffer line;
	VTConverter conv;
	ICommChannel *channel = nullptr;
	char buf[BUF_SIZE] = {0};
	bool initialized = false;
};

#endif