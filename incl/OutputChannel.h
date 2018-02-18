#ifndef _OUTPUT_CHANNEL_H_
#define _OUTPUT_CHANNEL_H_

#include <termios.h>

class OutputChannel
{
public:
	OutputChannel();
	~OutputChannel();
	int Initialize();
	int Read(void *buf);
	int Write(void *buf, int len);
	void FlushBuffers();
	
private:
	termios term, termOrig;
};

#endif