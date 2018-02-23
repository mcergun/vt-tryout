#include <cstdio>
#include <unistd.h>
#include <cstring>
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

int OutputChannel::Write(const void *buf, int len)
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

	return ret;
}

void OutputChannel::FlushBuffers()
{
	fflush(stdout);
}
int OutputChannel::NewLine()
{
	int ret = 0;
	strcpy(cmdBuf, "\x1B\x5B\x53\x1B\x5B\x45");
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

int OutputChannel::InsertCharAt(const char c, int idx)
{
	int ret = 0;
	ret = MoveCursorToStart();
	ret = MoveCursorRight(idx);
	ret = InsertChar(c);
	return ret;
}

int OutputChannel::MoveCursorToStart()
{
	int ret = 0;
	strcpy(cmdBuf, "\x1B\x5B""999\x44");
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::MoveCursorToEnd()
{
	int ret = 0;
	strcpy(cmdBuf, "\x1B\x5B""999\x43");
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::MoveCursorUp(int count)
{
	int ret = 0;
	strcpy(cmdBuf, "\x1B\x5B\x41");
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::MoveCursorDown(int count)
{
	int ret = 0;
	strcpy(cmdBuf, "\x1B\x5B\x42");
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::MoveCursorRight(int count)
{
	int ret = 0;
	strcpy(cmdBuf, "\x1B\x5B\x43");
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}

int OutputChannel::MoveCursorLeft(int count)
{
	int ret = 0;
	strcpy(cmdBuf, "\x1B\x5B\x44");
	ret = Write(cmdBuf, strlen(cmdBuf));
	return ret;
}
