#ifndef _LINE_BUFFER_
#define _LINE_BUFFER_

#include <VTConverter.h>

static const int MAX_HISTORY = 30;
static const int MAX_LINELEN = 1024;

class LineBuffer
{
public:
	LineBuffer();
	int HandleKey(Key k);
	void GetLine(void *dst);
	int GetLineLen() const;
	int GetCurPos() const;
private:
	char line[MAX_LINELEN] = {0};
	char lineIntmd[MAX_LINELEN] = {0};
	char lineHistory[MAX_HISTORY][MAX_LINELEN];
	int curPos = 0;
	int lineLen = 0;
	int historyCount = 0;
	int curHistory = 0;

	void CopyToLine(void *ptr, int len);

	int HandleDelKey();
	int HandleBackspaceKey();
	int HandleEnterKey();
	int HandleUpArrowKey();
	int HandleDownArrowKey();
	int HandleRightArrowKey();
	int HandleLeftArrowKey();
	int HandleHomeKey();
	int HandleEndKey();
	int HandleVisualKey(char vis);

	void ClearLine();
	void CopyHistoryToLine(int idx);
	void CopyLineToHistory();
};

#endif