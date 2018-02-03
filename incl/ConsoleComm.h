#ifndef _CONSOLECOMM_H_
#define _CONSOLECOMM_H_

#include <termios.h>
#include <ICommChannel.h>

class ConsoleComm : public ICommChannel
{
public:
	int Initialize();
	int Read(void *buf);
	int Write(void *buf, int len);
	void FlushBuffers();

private:
	termios term, termOrig;
};

#endif