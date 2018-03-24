#ifndef _LINE_H_
#define _LINE_H_

class Line
{
public:
	static const int MAX_LINE_LEN = 1024;
	Line();
	Line(const Line &ln);
	Line& operator=(Line &ln);
	bool operator==(Line &ln);
	bool operator!=(Line &ln);
	const int GetLength() const;
	const int GetPosition() const;
	const char * GetStringContent() const;
	int MoveCursorLeft(int count = 1);
	int MoveCursorRight(int count = 1);
	int MoveCursorToStart();
	int MoveCursorToEnd();
	int Insert(const char c);
	int Insert(const char *c, int len);
	int InsertAt(const char c, int idx);
	int InsertAt(const char *c, int len, int idx);
	int Erase(int len = 1);
	int Replace(const char *str);
	int Replace(const Line &ln);
	int Clear();
	int AutoCompleteCurPos();
private:
	unsigned int GetStartIdxOfWord();

	char lineBuf[MAX_LINE_LEN] = {0};
	char lineIntmdBuf[MAX_LINE_LEN] = {0};
	int curPos = 0;
	int lineLen = 0;
};

#endif