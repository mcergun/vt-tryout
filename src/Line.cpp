#include <cstring>
#include <Line.h>

Line::Line()
{

}

Line::Line(const Line &ln)
{
	Replace(ln);
}

Line& Line::operator=(Line &ln)
{
	Replace(ln);
	return *this;
}

bool Line::operator==(Line &ln)
{
	return !strcmp(this->lineBuf, ln.lineBuf);
}

bool Line::operator!=(Line &ln)
{
	return !operator==(ln);
}

const unsigned int Line::GetLength() const
{
	return lineLen;
}

const unsigned int Line::GetPosition() const
{
	return curPos;
}

const char * Line::GetStringContent() const
{
	return const_cast<const char *>(lineBuf);
}

int Line::MoveCursorLeft(unsigned int count)
{
	int ret = 0;
	if (count > curPos)
	{
		curPos = 0;
		ret = -1;
	}
	else
	{
		curPos -= count;
	}
	return ret;
}

int Line::MoveCursorRight(unsigned int count)
{
	int ret = 0;
	if (curPos + count > lineLen)
	{
		ret = -1;
		curPos = lineLen;
	}
	else
	{
		curPos += count;
	}
	return ret;
}

int Line::MoveCursorToStart()
{
	curPos = 0;
	return 0;
}

int Line::MoveCursorToEnd()
{
	curPos = lineLen;
	return 0;
}

int Line::Insert(const char c)
{
	return Insert(&c, 1);
}

int Line::Insert(const char *str, unsigned int len)
{
	int ret = 0;
	if (curPos < lineLen)
	{
		memset(lineIntmdBuf, 0, sizeof(lineIntmdBuf));
		strcpy(lineIntmdBuf, lineBuf + curPos);
		strcpy(lineBuf + curPos + len, lineIntmdBuf);
	}
	else
	{
		curPos = lineLen;
	}
	memcpy(lineBuf + curPos, str, len);
	curPos += len;
	lineLen += len;

	return ret;
}

int Line::InsertAt(const char c, unsigned int idx)
{
	curPos = idx;
	return Insert(&c, 1);
}

int Line::InsertAt(const char *str, unsigned int len, int idx)
{
	curPos = idx;
	return Insert(str, len);
}

int Line::Erase(unsigned int len)
{
	int ret = 0;
	if (curPos < lineLen)
	{
		strcpy(lineBuf + curPos, lineBuf + curPos + 1);
		lineLen--;
	}
	else
	{
		ret = -1;
	}
	return ret;
}

int Line::Replace(const char *str)
{
	strcpy(lineBuf, str);
	return 0;
}

int Line::Replace(const Line &ln)
{
	memcpy(this->lineBuf, ln.lineBuf, MAX_LINE_LEN);
	memcpy(this->lineIntmdBuf, ln.lineIntmdBuf, MAX_LINE_LEN);
	this->lineLen = ln.lineLen;
	this->curPos = ln.lineLen;
	return 0;
}

int Line::Clear()
{
	memset(lineBuf, 0, MAX_LINE_LEN);
	memset(lineIntmdBuf, 0, MAX_LINE_LEN);
	lineLen = 0;
	curPos = 0;

	return 0;
}

int Line::AutoCompleteCurPos()
{
	if (completer != nullptr)
	{
		if (curPos == lineLen)
		{
			unsigned int wordStartIdx = GetStartIdxOfWord();
			if (curPos > wordStartIdx)
			{
				AutoCompleteWord word;
				char candidateBuf[AutoComplete::MAX_CANDIDATE_LEN] = { 0 };
				word.ptr = candidateBuf;
				word.len = curPos - wordStartIdx;
				strncpy(candidateBuf, &lineBuf[wordStartIdx], word.len);
				word = completer->GetCandidate(word);
				if (word.len > 0)
				{
					int curLen = curPos - wordStartIdx;
					int addLen = word.len - curLen;
					strncpy(&lineBuf[curPos], &word.ptr[curLen], addLen);
					lineLen += addLen;
					curPos = lineLen;
				}
			}
		}
		// const char *ans = completer->GetCandidate(curWord);
		// if (strcmp(curWord, ans) != 0)
		// {
		// 	curPos += (strlen(ans) - strlen(curWord));
		// 	lineLen += (strlen(ans) - strlen(curWord));
		// 	strcpy(curWord, ans);
		// }
	}
	else
	{
		completer = new AutoComplete();
	}

	return 0;
}

unsigned int Line::GetStartIdxOfWord()
{
	unsigned int ret = 0;
	if (curPos > 0)
	{
		ret = curPos - 1;
		bool isSpace = false;
		while (ret > 0 && !isSpace)
		{
			isSpace = lineBuf[ret] == ' ';
			if (!isSpace)
				ret--;
		}
		if (isSpace)
			ret++;
	}
	return ret;
}

void Line::SetAutoCompleter(AutoComplete *completer)
{
	this->completer = completer;
}