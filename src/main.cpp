#include <cstdio>
#include <unistd.h>
#include "LineBuffer.h"

LineBuffer lnB;

#define ERS_LINE	"\x1B\x5B\x4B"
#define DEL_LINE	"\x1B\x5B\x4D"
#define CUR_UP		"\x1B\x5B\x41"
#define CUR_DOWN	"\x1B\x5B\x42"
#define CUR_FWD		"\x1B\x5B\x43"
#define CUR_BWD		"\x1B\x5B\x44"
#define CUR_NLINE	"\x1B\x5B\x45"
#define CUR_PLINE	"\x1B\x5B\x46"

int main()
{
	char lineBuf[MAX_LINELEN];
	lnB.GetLine(lineBuf);
	puts(lineBuf);
	sleep(1);
	lnB.HandleKey(KeyBackspace);
	lnB.GetLine(lineBuf);
	puts(lineBuf);
	sleep(1);
	lnB.HandleKey(KeyDelete);
	lnB.GetLine(lineBuf);
	puts(lineBuf);
	return 0;
}