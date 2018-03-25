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
		}
		else
		{
			ret = -1;
		}
		curHistory = historyCnt;
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
