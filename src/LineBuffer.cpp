#include <cstring>
#include "LineBuffer.h"

LineBuffer::LineBuffer()
{
	// test code, remove it later
	char *line = "Ahmet Mehmet";
	CopyToLine(line, strlen(line));
	HandleEnterKey();
	line = "Ayse Fatma";
	CopyToLine(line, strlen(line));
	curPos = 3;
}

void LineBuffer::CopyToLine(void *ptr, int len)
{
	strcpy(line, reinterpret_cast<char *>(ptr));
	int newLen = strlen(line);
	curPos = newLen;
	lineLen = newLen; 
}

int LineBuffer::HandleKey(Keys key)
{
	int ret = 0;
	switch (key)
	{
	case KeyDelete:
		ret = HandleDelKey();
		break;
	case KeyBackspace:
		ret = HandleBackspaceKey();
		break;
	case KeyEnter:
		ret = HandleEnterKey();
		break;
	}
}

int LineBuffer::HandleDelKey()
{
	// 0123456789
	// ...I......
	// 012456789
	int ret = 0;
	if (curPos < lineLen)
	{
		strcpy(line + curPos, line + curPos + 1);
	}
	else
	{
		ret = -1;
	}

	return ret;

}

int LineBuffer::HandleBackspaceKey()
{
	// 0123456789
	// ...I......
	// 013456789
	int ret = 0;
	if (curPos > 0 && curPos < lineLen)
	{
		curPos--;
		strcpy(line + curPos, line + curPos + 1);
	}
	else
	{
		ret = -1;
	}

	return ret;
}

int LineBuffer::HandleEnterKey()
{
	int ret = 0;
	if (lineLen > 0)
	{
		strcpy(lineHistory[historyCount++], line);
		memset(line, 0, MAX_LINELEN);
	}
	return ret;
}

int LineBuffer::HandleArrowKeys()
{

}