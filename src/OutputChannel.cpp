#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <HelperFuncs.h>
#include <OutputChannel.h>

OutputChannel::OutputChannel()
{

}

OutputChannel::~OutputChannel()
{

}

int OutputChannel::Initialize()
{
	// Get attributes from stdout
	tcgetattr(0, &term);
	// Save original state
	termOrig = term;

	// tcflag_t c_iflag;      // Input modes
	// tcflag_t c_oflag;      // Output modes
	// tcflag_t c_cflag;      // Control modes 
	// tcflag_t c_lflag;      // Local modes
	// cc_t     c_cc[NCCS];   // Special characters

	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	// cfmakeraw(term);

	// Set attributes for stdout
	return tcsetattr(0, TCSANOW, &term);
}

int OutputChannel::Read(void *buf)
{
	return read(0, buf, 1);
}

int OutputChannel::Write(const void *buf, unsigned int len)
{
	int ret = 0;
	const char *cbuf = reinterpret_cast<const char *>(buf);
	if (len > 0)
	{
		ret = fputs(cbuf, stdout);
	}
	else
	{
		ret = fputc(*cbuf, stdout);
	}
	return ret < 0;
}

void OutputChannel::FlushBuffers()
{
	fflush(stdout);
}
int OutputChannel::NewLine()
{
	int ret = 0;
	strcpy(cmdBuf, "\r\n");
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::ClearLine()
{
	int ret = 0;
	strcpy(cmdBuf, "\x1B\x5B" "999\x44" "\x1B\x5B\x4B");
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::InsertChar(const char c)
{
	int ret = 0;
	ret = Write(&c, 1);
	return ret;
}

int OutputChannel::InsertCharAt(const char c, unsigned int idx)
{
	int ret = 0;
	ret = MoveCursorToStart();
	ret = MoveCursorRight(idx);
	ret = InsertChar(c);
	return ret;
}

int OutputChannel::Erase(unsigned int count)
{
	int ret = 0;
	FillThreeSeqWithNumber(0x50, count);
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::MoveCursorToStart()
{
	int ret = MoveCursorLeft(999);
	return ret;
}

int OutputChannel::MoveCursorToEnd()
{
	int ret = MoveCursorRight(999);
	return ret;
}

int OutputChannel::MoveCursorUp(unsigned int count)
{
	int ret = 0;
	FillThreeSeqWithNumber(0x41, count);
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::MoveCursorDown(unsigned int count)
{
	int ret = 0;
	FillThreeSeqWithNumber(0x42, count);
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::MoveCursorRight(unsigned int count)
{
	int ret = 0;
	FillThreeSeqWithNumber(0x43, count);
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::MoveCursorLeft(unsigned int count)
{
	int ret = 0;
	FillThreeSeqWithNumber(0x44, count);
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

void OutputChannel::FillThreeSeqWithNumber(const char keyCode, unsigned int count)
{
	strcpy(cmdBuf, "\x1B\x5B");
	// Supports up to 999, which is more than enough
	char endbuf[5] = { 0 };
	if (count > 999)
		count = 999;
	itoa(count, endbuf, 10);
	endbuf[strlen(endbuf)] = keyCode;
	endbuf[strlen(endbuf) + 1] = '\0';
	strcpy(&cmdBuf[2], endbuf);
}
