#ifndef _LINE_BUFFER_H_
#define _LINE_BUFFER_H_

class Line
{
public:
	static const int MAX_LINE_LEN = 1024;
	Line();
	Line& operator=(Line &ln);
	bool operator==(Line &ln);
	bool operator!=(Line &ln);
	int MoveCursorLeft(int count = 1);
	int MoveCursorRight(int count = 1);
	int MoveCursorToHome();
	int MoveCursorToEnd();
	int Insert(char c);
	int Insert(const char *c, int len);
	int InsertAt(char c, int idx);
	int InsertAt(const char *c, int len, int idx);
	int Erase(int len = 1);
	int Replace(const char *str);
	int Clear();
private:
	char lineBuf[MAX_LINE_LEN];
	char lineIntmdBuf[MAX_LINE_LEN];
	int curPos = 0;
	int lineLen = 0;
};

class LineBuffer
{
public:
	static const int MAX_HISTORY_CNT = 64;
	LineBuffer();
	int AddToHistory(Line &ln);
	int GetNextFromHistory(Line &ln);
	int GetPrevFromHistory(Line &ln);
private:
	Line history[MAX_HISTORY_CNT];
	int historyCnt = 0;
	int curHistory = 0;
};

#endif