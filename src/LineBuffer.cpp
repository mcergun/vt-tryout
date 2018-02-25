#include "LineBuffer.h"

LineBuffer::LineBuffer()
{

}

Line & LineBuffer::GetCurrentLine()
{
	return currentLine;
}

int LineBuffer::AddToHistory()
{
	int ret = 0;
	if (historyCnt < MAX_HISTORY_CNT)
	{
		if (history[historyCnt] != currentLine)
			history[historyCnt++] = currentLine;
	}
	else
	{
		ret = -1;
	}

	return ret;
}

int LineBuffer::AddToHistory(Line &ln)
{
	int ret = 0;
	// if (historyCnt < MAX_HISTORY_CNT)
	// {
	// 	if (historyCnt == 0)
	// 	{
	// 		history[historyCnt++] = ln;
	// 		curHistory = historyCnt;
	// 	}
	// 	else
	// 	{
	// 		if (history[historyCnt - 1] != ln && ln.GetLength() > 0)
	// 		{
	// 			history[historyCnt++] = ln;
	// 			curHistory = historyCnt;
	// 		}
	// 		else
	// 		{
	// 			ret = -1;
	// 		}
	// 	}
	// }
	// else
	// {
	// 	ret = -1;
	// }

	if (historyCnt == 0)
	{
		history[historyCnt++] = ln;
		curHistory = historyCnt;
	}
	else if (historyCnt < MAX_HISTORY_CNT)
	{
		if (history[historyCnt - 1] != ln && ln.GetLength() > 0)
		{
			history[historyCnt++] = ln;
			curHistory = historyCnt;
		}
		else
		{
			ret = -1;
		}
	}
	else
	{
		ret = -1;
	}

	return ret;
}

int LineBuffer::GetNextFromHistory(Line &ln)
{
	int ret = 0;
	if (curHistory < 1)
	{
		curHistory = 0;
		ret = -1;
	}
	else
	{
		ln = history[--curHistory];
	}
	return ret;
}

int LineBuffer::GetPrevFromHistory(Line &ln)
{
	int ret = 0;
	if (curHistory < historyCnt - 1)
	{
		ln = history[++curHistory];
	}
	else
	{
		curHistory = historyCnt;
		ret = -1;
	}
	return ret;
}

// LineBuffer::LineBuffer()
// {
// }
//
// int LineBuffer::HandleKey(Key k)
// {
// 	int ret = 0;
// 	switch(k.InCode)
// 	{
// 	case Input_Escape:
// 		// ret = HandleEscapeKey();
// 		break;
// 	case Input_Unknown:
// 		// ret = HandleUnknownKey();
// 		break;
// 	case Input_Delete:
// 		ret = HandleDelKey();
// 		break;
// 	case Input_End:
// 		ret = HandleEndKey();
// 		break;
// 	case Input_Home:
// 		ret = HandleHomeKey();
// 		break;
// 	case Input_CursorUp:
// 		ret = HandleUpArrowKey();
// 		break;
// 	case Input_CursorDown:
// 		ret = HandleDownArrowKey();
// 		break;
// 	case Input_CursorForward:
// 		ret = HandleRightArrowKey();
// 		break;
// 	case Input_CursorBackward:
// 		ret = HandleLeftArrowKey();
// 		break;
// 	case Input_Enter:
// 		ret = HandleEnterKey();
// 		break;
// 	case Input_Tab:
// 		// ret = HandleTabKey();
// 		break;
// 	case Input_Backspace:
// 		ret = HandleBackspaceKey();
// 		break;
// 	case Input_Numerical:
// 	case Input_Letters:
// 	case Input_SpecialSymbols:
// 		ret = HandleVisualKey(k.Visual);
// 		break;
// 	}

// 	return ret;
// }

// void LineBuffer::GetLine(void *dst)
// {
// 	char *dstBuf = reinterpret_cast<char *>(dst);
// 	strcpy(dstBuf, line);
// 	dstBuf[lineLen] = '\0';
// }


// int LineBuffer::GetLineLen() const
// {
// 	return lineLen;
// }
// int LineBuffer::GetCurPos() const
// {
// 	return curPos;
// }

// void LineBuffer::CopyToLine(void *ptr, int len)
// {
// 	strcpy(line, reinterpret_cast<char *>(ptr));
// 	int newLen = strlen(line);
// 	curPos = newLen;
// 	lineLen = newLen; 
// }

// int LineBuffer::HandleDelKey()
// {
// 	// 0123456789
// 	// ...I......
// 	// 012456789
// 	int ret = 0;
// 	if (curPos < lineLen)
// 	{
// 		strcpy(line + curPos, line + curPos + 1);
// 		lineLen--;
// 	}
// 	else
// 	{
// 		ret = -1;
// 	}

// 	return ret;
// }

// int LineBuffer::HandleBackspaceKey()
// {
// 	// 0123456789
// 	// ...I......
// 	// 013456789
// 	int ret = 0;
// 	if (curPos > 0 && curPos <= lineLen)
// 	{
// 		curPos--;
// 		lineLen--;
// 		strcpy(line + curPos, line + curPos + 1);
// 	}
// 	else
// 	{
// 		ret = -1;
// 	}

// 	return ret;
// }

// int LineBuffer::HandleEnterKey()
// {
// 	int ret = 0;
// 	if (lineLen > 0)
// 	{
// 		if (historyCount > 0)
// 		{
// 			// This may be a duplicate entry
// 			if (strcmp(line, lineHistory[historyCount - 1]) != 0)
// 			{
// 				// Original entry, log it
// 				CopyLineToHistory();
// 				ClearLine();
// 			}
// 			else
// 			{
// 				// Duplicate entry, ignore it
// 				ClearLine();
// 			}
// 		}
// 		else
// 		{
// 			CopyLineToHistory();
// 			ClearLine();
// 		}
// 	}

// 	return ret;
// }

// int LineBuffer::HandleUpArrowKey()
// {
// 	int ret = 0;
// 	// Copy last next history entry to line buffer
// 	if (curHistory < 1)
// 	{
// 		ret = -1;
// 		curHistory = 0;
// 	}
// 	else
// 	{
// 		CopyHistoryToLine(--curHistory);
// 	}
// 	return ret;
// }

// int LineBuffer::HandleDownArrowKey()
// {
// 	int ret = 0;
// 	// Copy last history entry to line buffer
// 	if (curHistory < historyCount - 1)
// 	{
// 		CopyHistoryToLine(++curHistory);
// 	}
// 	else
// 	{
// 		curHistory = historyCount;
// 		ClearLine();
// 	}
// 	return ret;
// }

// int LineBuffer::HandleRightArrowKey()
// {
// 	int ret = 0;
// 	if (curPos < lineLen)
// 	{
// 		curPos++;
// 	}
// 	else
// 	{
// 		ret = -1;
// 		curPos = lineLen;
// 	}
// 	return ret;
// }

// int LineBuffer::HandleLeftArrowKey()
// {
// 	int ret = 0;
// 	if (curPos > 0)
// 	{
// 		curPos--;
// 	}
// 	else
// 	{
// 		ret = -1;
// 		curPos = 0;
// 	}
	
// 	return ret;
// }

// int LineBuffer::HandleVisualKey(char vis)
// {
// 	// 0123456789
// 	// ...I......
// 	// 012a3456789
// 	// ....I.....
// 	int ret = 0;
// 	if (curPos < lineLen)
// 	{
// 		memset(lineIntmd, 0, sizeof(lineIntmd));
// 		strcpy(lineIntmd, line + curPos);
// 		strcpy(line + curPos + 1, lineIntmd);
// 	}
// 	line[curPos] = vis;
// 	curPos++;
// 	lineLen++;

// 	return ret;
// }

// void LineBuffer::ClearLine()
// {
// 	memset(line, 0, MAX_LINELEN);
// 	curPos = 0;
// 	lineLen = 0;
// }

// void LineBuffer::CopyHistoryToLine(int idx)
// {
// 	char *lastHistory = lineHistory[idx];
// 	strcpy(line, lastHistory);
// 	lineLen = strlen(lastHistory);
// 	curPos = lineLen;
// }

// void LineBuffer::CopyLineToHistory()
// {
// 	strcpy(lineHistory[historyCount], line);
// 	if (historyCount == curHistory)
// 	{
// 		curHistory++;
// 	}
// 	historyCount++;
// }