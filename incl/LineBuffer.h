#ifndef _LINE_BUFFER_
#define _LINE_BUFFER_

static const int MAX_HISTORY = 10;
static const int MAX_LINELEN = 1024;

enum Keys
{
	KeyDelete,
	KeyBackspace,
	KeyEnter,
	KeyRArrow,
	KeyLArrow,
	KeyUArrow,
	KeyDArrow,
};

class LineBuffer
{
public:
	LineBuffer();
	int HandleKey(Keys key);
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
	int HandleArrowKeys(Keys key);
};

#endif