#include <cstring>
#include "LineBuffer.h"

LineBuffer::LineBuffer()
{
}

int LineBuffer::HandleKey(Key k)
{
	int ret = 0;
	switch(k.InCode)
	{
	case Input_Escape:
		// ret = HandleEscapeKey();
		break;
	case Input_Unknown:
		// ret = HandleUnknownKey();
		break;
	case Input_Delete:
		ret = HandleDelKey();
		break;
	case Input_End:
		// ret = HandleEndKey();
		break;
	case Input_Home:
		// ret = HandleHomeKey();
		break;
	case Input_CursorUp:
		ret = HandleUpArrowKey();
		break;
	case Input_CursorDown:
		ret = HandleDownArrowKey();
		break;
	case Input_CursorForward:
		ret = HandleRightArrowKey();
		break;
	case Input_CursorBackward:
		ret = HandleLeftArrowKey();
		break;
	case Input_Enter:
		ret = HandleEnterKey();
		break;
	case Input_Tab:
		// ret = HandleTabKey();
		break;
	case Input_Backspace:
		ret = HandleBackspaceKey();
		break;
	case Input_Numerical:
	case Input_Letters:
	case Input_SpecialSymbols:
		ret = HandleVisualKey(k.Visual);
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
	if (lineLen > 0 && strcmp(line, lineHistory[historyCount - 1]) != 0)
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

int LineBuffer::HandleVisualKey(char vis)
{
	// 0123456789
	// ...I......
	// 012a3456789
	// ....I.....
	int ret = 0;
	if (curPos < lineLen)
	{
		// Use current history buffer as intermediate
		strcpy(lineHistory[historyCount], line + curPos);
		strcpy(line + curPos + 1, lineHistory[historyCount]);
	}
	line[curPos] = vis;
	curPos++;
	lineLen++;

	return ret;
}
