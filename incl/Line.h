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
	const unsigned int GetLength() const;
	const unsigned int GetPosition() const;
	const char * GetStringContent() const;
	int MoveCursorLeft(unsigned int count = 1);
	int MoveCursorRight(unsigned int count = 1);
	int MoveCursorToStart();
	int MoveCursorToEnd();
	int Insert(const char c);
	int Insert(const char *c, unsigned int len);
	int InsertAt(const char c, unsigned int idx);
	int InsertAt(const char *c, unsigned int len, int idx);
	int Erase(unsigned int len = 1);
	int Replace(const char *str);
	int Replace(const Line &ln);
	int Clear();
private:
	char lineBuf[MAX_LINE_LEN] = {0};
	char lineIntmdBuf[MAX_LINE_LEN] = {0};
	unsigned int curPos = 0;
	unsigned int lineLen = 0;
};

#endif