#ifndef _LINE_BUFFER_
#define _LINE_BUFFER_

#include <VTConverter.h>

static const int MAX_HISTORY = 10;
static const int MAX_LINELEN = 1024;

class LineBuffer
{
public:
	LineBuffer();
	int HandleKey(InputCodes key);
	void GetLine(void *dst);
private:
	char line[MAX_LINELEN] = {0};
	char lineHistory[MAX_HISTORY][MAX_LINELEN];
	int curPos = 0;
	int lineLen = 0;
	int historyCount = 0;

	void CopyToLine(void *ptr, int len);

	int HandleDelKey();
	int HandleBackspaceKey();
	int HandleEnterKey();
	int HandleUpArrowKey();
	int HandleDownArrowKey();
	int HandleRightArrowKey();
	int HandleLeftArrowKey();
	int HandleVisualKey(char vis);
};

#endif