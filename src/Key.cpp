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
	keyList[12] = new KeyTab();
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
			if (curChar == KeyCode_Escape)
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
				case KeyCode_Return:
					retIdx = 2;
					break;
				case KeyCode_Tab:
					// TODO: add support for TAB key, too.
					retIdx = 12;
					break;
				case KeyCode_Backspace:
					retIdx = 8;
					break;
				case KeyCode_VisSpace:
				case KeyCode_VisExclMark:
				case KeyCode_VisDoubleQuotes:
				case KeyCode_VisSharp:
				case KeyCode_VisDollar:
				case KeyCode_VisPercent:
				case KeyCode_VisAmpercend:
				case KeyCode_VisSingleQuote:
				case KeyCode_VisLeftParanth:
				case KeyCode_VisRightParanth:
				case KeyCode_VisAsterisk:
				case KeyCode_VisPlusSign:
				case KeyCode_VisComma:
				case KeyCode_VisMinusSign:
				case KeyCode_VisDot:
				case KeyCode_VisSlash:
				case KeyCode_VisColon:
				case KeyCode_VisSemiColon:
				case KeyCode_VisLessThan:
				case KeyCode_VisEqual:
				case KeyCode_VisGrtThan:
				case KeyCode_VisQuestion:
				case KeyCode_VisAtSign:
				case KeyCode_VisLeftBracket:
				case KeyCode_VisBackSlash:
				case KeyCode_VisRightBracket:
				case KeyCode_VisCaret:
				case KeyCode_VisUnderscore:
				case KeyCode_VisLeftBraces:
				case KeyCode_VisPerpendicular:
				case KeyCode_VisRightBraces:
				case KeyCode_VisTilde:
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
			if (seqLen == 1 && curChar == KeyCode_Escape2)
			{
				seqLen++;
				retIdx = 1;
			}
			else if (seqLen == 2)
			{
				switch (curChar)
				{
				case KeyCode_End:
					retIdx = 11;
					break;
				case KeyCode_Home:
					retIdx = 10;
					break;
				case KeyCode_UpArrow:
					retIdx = 3;
					break;
				case KeyCode_DownArrow:
					retIdx = 4;
					break;
				case KeyCode_RightArrow:
					retIdx = 5;
					break;
				case KeyCode_LeftArrow:
					retIdx = 6;
					break;
				case KeyCode_Escape3:
					seqLen++;
					retIdx = 1;
					break;
				default:
					break;
				}
			}
			else if (seqLen == 3)
			{
				if (curChar == KeyCode_Delete)
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
	ret = curLine.Insert(visual);
	if (!ret)
	{
		oc.ClearLine();
		oc.Write(curLine.GetStringContent(), curLine.GetLength());
		oc.MoveCursorToStart();
		for (unsigned int i = 0; i < curLine.GetPosition(); ++i)
		{
			oc.MoveCursorRight();
		}
	}
	return ret;
}

int KeyBackspace::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	Line &curLine = lb.GetCurrentLine();
	ret = curLine.MoveCursorLeft();
	if (!ret)
		ret = curLine.Erase();
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

int KeyTab::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	Line &curLine = lb.GetCurrentLine();
	ret = curLine.AutoCompleteCurPos();
	ret = oc.ClearLine();
	ret = oc.Write(curLine.GetStringContent(), curLine.GetLength());
	oc.MoveCursorToStart();
	oc.MoveCursorRight(curLine.GetPosition());
	return ret;
}