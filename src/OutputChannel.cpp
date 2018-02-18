#include <cstdio>
#include <unistd.h>
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

int OutputChannel::Write(void *buf, int len)
{
	int ret = 0;
	char *cbuf = reinterpret_cast<char *>(buf);
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