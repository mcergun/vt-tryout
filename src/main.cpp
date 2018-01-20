#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include "LineBuffer.h"
#include "VTConverter.h"

#define ERS_LINE	"\x1B\x5B\x4B"
#define DEL_LINE	"\x1B\x5B\x4D"
#define CUR_UP		"\x1B\x5B\x41"
#define CUR_DOWN	"\x1B\x5B\x42"
#define CUR_FWD		"\x1B\x5B\x43"
#define CUR_BWD		"\x1B\x5B\x44"
#define CUR_NLINE	"\x1B\x5B\x45"
#define CUR_PLINE	"\x1B\x5B\x46"

void printWFlush(const char *str)
{
	fputs(str, stdout);
	fflush(stdout);
}

void printLineBuffer(LineBuffer &line, char *buf)
{
	line.GetLine(buf);
	printWFlush(buf);
}

int setAttributes(termios *term, termios *termOrig)
{
	tcgetattr(0, term);
	// save original state
	*termOrig = *term;

	// tcflag_t c_iflag;      /* input modes */
	// tcflag_t c_oflag;      /* output modes */
	// tcflag_t c_cflag;      /* control modes */ 
	// tcflag_t c_lflag;      /* local modes */
	// cc_t     c_cc[NCCS];   /* special characters */

	term->c_lflag &= ~ICANON;
	term->c_lflag &= ~ECHO;
	term->c_cc[VMIN] = 0;
	term->c_cc[VTIME] = 0;
	// cfmakeraw(term);

	return tcsetattr(0, TCSANOW, term);
}

int main()
{
	termios term, termOrig;
	char buf[16] = {0};
	VTConverter conv;

	if(setAttributes(&term, &termOrig))
	{
		printWFlush("Failed to set terminal attributes\n");
	}
	else
	{
		while(1)
		{
			if(read(0, buf, 1))
			{
				InputCodes code;
				if(!(conv.ToInputEnum(&code, buf)) && (code != Input_Unknown && code != Input_Escape))
					printf("[%s, %d]", buf, code);
				fflush(0);
			}
		}
	}

	return 0;
}