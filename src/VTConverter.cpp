#include <cstring>
#include "VTConverter.h"

// Some of the following sequences can be used for N times
// Those are marked with {n}, simply replace {n} with "string" number
// Move cursor forward 5 times -> "\x1B\x5B" "5\x43"

// Erase character and delete character seem to be doing the same thing?

// Following codes are gathered by me on ubuntu terminal with ~ICANON and ~ECHO
// Delete		1b 5b 33 7e
// End			1b 5b 46
// Home			1b 5b 48
// Cursor Up		1b 5b 41
// Cursor Down		1b 5b 42
// Cursor Forward	1b 5b 43
// Cursor Backward	1b 5b 44
// Enter		0a
// Tab			09
// Backspace		7f
// Minus		2d
// Plus			2b
// Asterisk		2a
// Divide		2f
// Dot			2e
// Comma		2c
// Single Quote		27
// Double Quote		22
// Semicolon		3b
// Colon		3a
// Less than		3c
// Greater than		3e
// Question Mark	3f
// Tilda		7e
// Exclamation Mark	21
// At Symbol		40
// Sharp Symbol		23
// Dollar Sign		24
// Percentage Symbol	25
// Hat Symbol		5e
// Ampercend		26
// Parantheses Start	28
// Parantheses End	29
// Underscore		5f
// Curly Braces Start	7b
// Curly Braces End	7d
// Backslash		5c
// Pipe sign? |		7c

int VTConverter::ToEnumString(char *str, InputCodes code)
{
	int ret = 0;
	switch (code)
	{
		case Input_Escape:
			strcpy(str, "Escape");
			break;
		case Input_Unknown:
			strcpy(str, "Unknown");
			break;
		case Input_Delete:
			strcpy(str, "Delete");
			break;
		case Input_End:
			strcpy(str, "End");
			break;
		case Input_Home:
			strcpy(str, "Home");
			break;
		case Input_CursorUp:
			strcpy(str, "CursorUp");
			break;
		case Input_CursorDown:
			strcpy(str, "CursorDown");
			break;
		case Input_CursorForward:
			strcpy(str, "CursorForward");
			break;
		case Input_CursorBackward:
			strcpy(str, "CursorBackward");
			break;
		case Input_Enter:
			strcpy(str, "Enter");
			break;
		case Input_Tab:
			strcpy(str, "Tab");
			break;
		case Input_Backspace:
			strcpy(str, "Backspace");
			break;
		case Input_Numerical:
			strcpy(str, "Numerical");
			break;
		case Input_Letters:
			strcpy(str, "Letters");
			break;
		case Input_SpecialSymbols:
			strcpy(str, "SpecialSymbols");
			break;
		default:
			strcpy(str, "Input_Unknown");
			ret = -1;
			break;	
	}

	return ret;
}

//  CUU             Cursor up               esc [ A         1B 5B {n} 41
//  CUD             Cursor down             esc [ B         1B 5B {n} 42
//  CUF             Cursor forward          esc [ C         1B 5B {n} 43
//  CUB             Cursor backward         esc [ D         1B 5B {n} 44
//  SC              Save cursor             esc [ s         1B 5B 73
//  RC              Restore cursor          esc [ u         1B 5B 75
//  ED              Erase display           esc [ 2 J       1B 5B 32 4A
//  EL              Erase line              esc [ K         1B 5B 4B
//  DCH             Delete character        esc [ P         1B 5B {n} 50
//  ECH             Erase character         esc [ X         1B 5B {n} 58
//  DEL             Delete                  del             7F
//  BS              Back space              bs              08
//  AK-0            App keypad 0            esc O p         1B 4F 70
//  AK-1            App keypad 1            esc O q         1B 4F 71
//  AK-2            App keypad 2            esc O r         1B 4F 72
//  AK-3            App keypad 3            esc O s         1B 4F 73
//  AK-4            App keypad 4            esc O t         1B 4F 74
//  AK-5            App keypad 5            esc O u         1B 4F 75
//  AK-6            App keypad 6            esc O v         1B 4F 76
//  AK-7            App keypad 7            esc O w         1B 4F 77
//  AK-8            App keypad 8            esc O x         1B 4F 78
//  AK-9            App keypad 9            esc O y         1B 4F 79
//  AK-(-)          App keypad minus        esc O m         1B 4F 6D
//  AK-(,)          App keypad comma        esc O l         1B 4F 6C
//  AK-(.)          App keypad period       esc O n         1B 4F 6E
//  AK-CR           App keypad Enter        esc O M         1B 4F 4D
//  PF1             App keypad PF1          esc O P         1B 4F 50
//  PF2             App keypad PF2          esc O Q         1B 4F 51
//  PF3             App keypad PF3          esc O R         1B 4F 52
//  PF4             App keypad PF4          esc O S         1B 4F 53
int VTConverter::ToAnsiiCode(char *str, OutputCodes code, int n)
{
	int ret = 0;
	switch(code)
	{
	case Output_CursorUp:
		strcpy(str, "\x1B\x5B\x41");
		break;
	case Output_CursorDown:
		strcpy(str, "\x1B\x5B\x42");
		break;
	case Output_CursorForward:
		strcpy(str, "\x1B\x5B\x43");
		break;
	case Output_CursorBackward:
		strcpy(str, "\x1B\x5B\x44");
		break;
	case Output_SaveCursorPos:
		strcpy(str, "\x1B\x5B\x73");
		break;
	case Output_RestoreCursorPos:
		strcpy(str, "\x1B\x5B\x75");
		break;
	case Output_EraseDisplay:
		strcpy(str, "\x1B\x5B\x32\x4A");
		break;
	case Output_EraseLine:
		strcpy(str, "\x1B\x5B\x4B");
		break;
	case Output_DeleteCharacter:
		strcpy(str, "\x1B\x5B\x50");
		break;
	case Output_EraseCharacter:
		strcpy(str, "\x1B\x5B\x58");
	default:
		ret = -1;
		break;
	}

	return ret;
}

Key VTConverter::ToKey(char *str)
{
	Key k{Input_Unknown, Output_Unknown, 0};

	int curLen = strlen(str);
	for (int i = 0; i < curLen; ++i)
	{
		char curChar = str[i];

		if (!isEscapeSequence)
		{
			if (curChar == 0x1B)
			{
				// should be followed by an escape sequence
				isEscapeSequence = true;
				seqLen++;
				k.InCode = Input_Escape;
			}
			else
			{
				// should be a visual character
				switch (curChar)
				{
				case 0x0a:
					k.InCode = Input_Enter;
					break;
				case 0x09:
					k.InCode = Input_Tab;
					break;
				case 0x7f:
					k.InCode = Input_Backspace;
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
					k.InCode = Input_SpecialSymbols;
					k.Visual = curChar;
					break;
				default:
					if ((curChar >= 'a' && curChar <= 'z') ||
					    (curChar >= 'A' && curChar <= 'Z'))
					{
						k.InCode = Input_Letters;
						k.Visual = curChar;
					}
					else if (curChar >= '0' && curChar <= '9')
					{
						k.InCode = Input_Numerical;
						k.Visual = curChar;
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
				k.InCode = Input_Escape;
			}
			else if (seqLen == 2)
			{
				switch (curChar)
				{
				case 0x46:
					k.InCode = Input_End;
					break;
				case 0x48:
					k.InCode = Input_Home;
					break;
				case 0x41:
					k.InCode = Input_CursorUp;
					break;
				case 0x42:
					k.InCode = Input_CursorDown;
					break;
				case 0x43:
					k.InCode = Input_CursorForward;
					break;
				case 0x44:
					k.InCode = Input_CursorBackward;
					break;
				case 0x33:
					seqLen++;
					k.InCode = Input_Escape;
					break;
				default:
					break;
				}
			}
			else if (seqLen == 3)
			{
				if (curChar == 0x7E)
				{
					k.InCode = Input_Delete;
				}
			}
			// else, keep code as unknown
		}
	}
	if ((k.InCode != Input_Unknown && k.InCode != Input_Escape))
	{
		// refresh status variables if return code has been altered
		seqLen = 0;
		isEscapeSequence = false;
	}

	return k;
}

void VTConverter::custItoa(char * dst, int n)
{
	int ndigits = 0;
	int num = n;
	do
	{
		num /= 10;
		ndigits++;
	} while (n > 0);

	dst[ndigits] = '\0';

	do
	{
		dst[ndigits - 1] = n % 10;
		ndigits--;
	} while (ndigits > 0);
}