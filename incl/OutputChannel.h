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
	int Write(const void *buf, int len);
	void FlushBuffers();
	int NewLine();
	int ClearLine();
	int InsertChar(const char c);
	int InsertCharAt(const char c, int idx);
	int Erase(unsigned int count = 1);
	int MoveCursorToStart();
	int MoveCursorToEnd();
	int MoveCursorUp(unsigned int count = 1);
	int MoveCursorDown(unsigned int count = 1);
	int MoveCursorRight(unsigned int count = 1);
	int MoveCursorLeft(unsigned int count = 1);
	
private:
	static constexpr int MAX_CMD_LEN = 32;
	termios term, termOrig;
	char cmdBuf[MAX_CMD_LEN] = {0};

	inline void FillThreeSeqWithNumber(const char keyCode, unsigned int count);
};

#endif