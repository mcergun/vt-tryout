#ifndef _LINE_BUFFER_H_
#define _LINE_BUFFER_H_

#include <Line.h>

class LineBuffer
{
public:
	static const int MAX_HISTORY_CNT = 64;
	LineBuffer();
	Line &GetCurrentLine();
	int AddToHistory();
	int AddToHistory(Line &ln);
	int GetNextFromHistory(Line &ln);
	int GetPrevFromHistory(Line &ln);
private:
	Line history[MAX_HISTORY_CNT];
	Line currentLine;
	int historyCnt = 0;
	int curHistory = 0;
};

#endif