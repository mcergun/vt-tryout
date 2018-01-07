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
	case KeyUArrow:
		ret = HandleUpArrowKey();
		break;
	case KeyDArrow:
		ret = HandleDownArrowKey();
		break;
	case KeyRArrow:
		ret = HandleRightArrowKey();
		break;
	case KeyLArrow:
		ret = HandleLeftArrowKey();
		break;
	}

	return ret;
}

void LineBuffer::GetLine(void *dst)
{
	strcpy(reinterpret_cast<char *>(dst), line);
}

void LineBuffer::CopyToLine(void *ptr, int len)
{
	strcpy(line, reinterpret_cast<char *>(ptr));
	int newLen = strlen(line);
	curPos = newLen;
	lineLen = newLen; 
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
		curPos = 0;
	}
	return ret;
}

int LineBuffer::HandleUpArrowKey()
{
	int ret = 0;
	// Copy last next history entry to line buffer
	return ret;
}

int LineBuffer::HandleDownArrowKey()
{
	int ret = 0;
	// Copy last previous history entry to line buffer
	return ret;
}

int LineBuffer::HandleRightArrowKey()
{
	int ret = 0;
	if (curPos < lineLen)
	{
		curPos++;
	}
	else
	{
		ret = -1;
		curPos = lineLen;
	}
	return ret;
}

int LineBuffer::HandleLeftArrowKey()
{
	int ret = 0;
	if (curPos > 1)
	{
		curPos--;
	}
	else
	{
		ret = -1;
		curPos = 0;
	}
	return ret;
}
