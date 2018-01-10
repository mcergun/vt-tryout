#include <cstdio>
#include <unistd.h>
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

int main()
{
	LineBuffer line;
	char lineBuf[MAX_LINELEN];
	printLineBuffer(line, lineBuf);
	sleep(1);

	printWFlush(DEL_LINE);
	line.HandleKey(KeyBackspace);
	printLineBuffer(line, lineBuf);
	sleep(1);

	char str[16] = {0};
	VTConverter::ToAnsiiCode(str, Escape_EraseDisplay);
	printWFlush(str);
	sleep(1);

	printWFlush(DEL_LINE);
	line.HandleKey(KeyDelete);
	printLineBuffer(line, lineBuf);
	fputs("\n", stdout);

	return 0;
}