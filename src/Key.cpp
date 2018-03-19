#include <cstring>
#include <Key.h>

Key::Key(char c) :
	visual(c)
{
}

KeyConverter::KeyConverter()
{
	// TODO: Find a better way to handle number of keys
	// fill the list to be returned to converter requests
	keyList[0] = new KeyIgnore();
	keyList[1] = new KeyEscape();
	keyList[2] = new KeyReturn();
	keyList[3] = new KeyUpArrow();
	keyList[4] = new KeyDownArrow();
	keyList[5] = new KeyRightArrow();
	keyList[6] = new KeyLeftArrow();
	keyList[7] = new KeyVisual('\0');
	keyList[8] = new KeyBackspace();
	keyList[9] = new KeyDelete();
	keyList[10] = new KeyHome();
	keyList[11] = new KeyEnd();
}

KeyConverter::~KeyConverter()
{
	// TODO: Find a better way to handle number of keys
	for (int i = 0; i < 12; ++i)
	{
		delete keyList[i];
		keyList[i] = nullptr;
	}
}

Key & KeyConverter::ToKey(const char *str)
{
	int curLen = strlen(str);
	int retIdx = 0;
	for (int i = 0; i < curLen; ++i)
	{
		char curChar = str[i];
		if (!isEscapeSequence)
		{
			if (curChar == CODE_ESC_START)
			{
				isEscapeSequence = true;
				seqLen++;
				retIdx = 1;
			}
			else
			{
				// should be a visual character
				switch (curChar)
				{
				case 0x0a:
					retIdx = 2;
					break;
				case 0x09:
					// TODO: add support for TAB key, too.
					retIdx = 0;
					break;
				case 0x7f:
					retIdx = 8;
					break;
				case 0x20:
				case 0x2d:
				case 0x2b:
				case 0x2a:
				case 0x2f:
				case 0x2e:
				case 0x2c:
				case 0x27:
				case 0x22:
				case 0x3b:
				case 0x3a:
				case 0x3c:
				case 0x3e:
				case 0x3f:
				case 0x7e:
				case 0x21:
				case 0x40:
				case 0x23:
				case 0x24:
				case 0x25:
				case 0x5e:
				case 0x26:
				case 0x28:
				case 0x29:
				case 0x5f:
				case 0x7b:
				case 0x7d:
				case 0x5c:
				case 0x7c:
					retIdx = 7;
					keyList[retIdx]->visual = curChar;
					break;
				default:
					if ((curChar >= 'a' && curChar <= 'z') ||
					    (curChar >= 'A' && curChar <= 'Z'))
					{
						retIdx = 7;
						keyList[retIdx]->visual = curChar;
					}
					else if (curChar >= '0' && curChar <= '9')
					{
						retIdx = 7;
						keyList[retIdx]->visual = curChar;
					}
					// else, keep code as unknown
					break;
				}
			}
		}
		else
		{
			// continue checking characters for incoming parts
			if (seqLen == 1 && curChar == 0x5B)
			{
				seqLen++;
				retIdx = 1;
			}
			else if (seqLen == 2)
			{
				switch (curChar)
				{
				case 0x46:
					retIdx = 11;
					break;
				case 0x48:
					retIdx = 10;
					break;
				case 0x41:
					retIdx = 3;
					break;
				case 0x42:
					retIdx = 4;
					break;
				case 0x43:
					retIdx = 5;
					break;
				case 0x44:
					retIdx = 6;
					break;
				case 0x33:
					seqLen++;
					retIdx = 1;
					break;
				default:
					break;
				}
			}
			else if (seqLen == 3)
			{
				if (curChar == 0x7E)
				{
					retIdx = 9;
				}
			}
			// else, keep code as unknown
		}

	}
	if (retIdx != 1)
	{
		// refresh status variables if return code has been altered
		seqLen = 0;
		isEscapeSequence = false;
	}
	return *keyList[retIdx];
}

int KeyReturn::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	lb.AddToHistory(lb.GetCurrentLine());
	lb.GetCurrentLine().Clear();
	oc.NewLine();

	return ret;
}

int KeyUpArrow::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.GetNextFromHistory(lb.GetCurrentLine());
	if (!ret)
		ret = oc.ClearLine();
	if (!ret)
	{
		const char *curLineStr = lb.GetCurrentLine().GetStringContent();
		ret = oc.Write(curLineStr, strlen(curLineStr));
	}
	return ret;
}

int KeyDownArrow::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	Line &curLine = lb.GetCurrentLine();
	ret = lb.GetPrevFromHistory(curLine);
	if (ret)
	{
		// means end of history, clear the buffer
		curLine.Clear();
	}
	oc.ClearLine();
	if (!ret)
	{
		const char *curLineStr = lb.GetCurrentLine().GetStringContent();
		ret = oc.Write(curLineStr, strlen(curLineStr));
	}
	return ret;
}

int KeyLeftArrow::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.GetCurrentLine().MoveCursorLeft();
	if (!ret)
		ret = oc.MoveCursorLeft();
	return ret;
}

int KeyRightArrow::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.GetCurrentLine().MoveCursorRight();
	if (!ret)
		ret = oc.MoveCursorRight();
	return ret;
}

int KeyVisual::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	Line &curLine = lb.GetCurrentLine();
	ret = curLine.Insert(this->visual);
	if (!ret)
	{
		oc.ClearLine();
		oc.Write(curLine.GetStringContent(), curLine.GetLength());
		oc.MoveCursorToStart();
		for (int i = 0; i < curLine.GetPosition(); ++i)
		{
			oc.MoveCursorRight();
		}
	}
	return ret;
}

int KeyBackspace::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.GetCurrentLine().MoveCursorLeft();
	if (!ret)
		ret = lb.GetCurrentLine().Erase();
	if (!ret)
	{
		ret = oc.MoveCursorLeft();
		ret = oc.Erase();
	}
	return ret;
}

int KeyDelete::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.GetCurrentLine().Erase();
	if (!ret)
		ret = oc.Erase();
	return ret;
}

int KeyHome::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.GetCurrentLine().MoveCursorToStart();
	ret = oc.MoveCursorToStart();
	return ret;
}

int KeyEnd::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	int len = lb.GetCurrentLine().GetLength();
	ret = lb.GetCurrentLine().MoveCursorToEnd();
	ret = oc.MoveCursorToStart();
	ret = oc.MoveCursorRight(len);
	return ret;
}