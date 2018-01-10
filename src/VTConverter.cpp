#include <cstring>
#include "VTConverter.h"

//  CUU             Cursor up               esc [ A         1B 5B 41
//  CUD             Cursor down             esc [ B         1B 5B 42
//  CUF             Cursor forward          esc [ C         1B 5B 43
//  CUB             Cursor backward         esc [ D         1B 5B 44
//  SC              Save cursor             esc [ s         1B 5B 73
//  RC              Restore cursor          esc [ u         1B 5B 75
//  ED              Erase display           esc [ 2 J       1B 5B 32 4A
//  EL              Erase line              esc [ K         1B 5B 4B
int VTConverter::ToAnsiiCode(char *str, EscapeCodes code)
{
	int ret = 0;
	switch(code)
	{
	case Escape_CursorUp:
		strcpy(str, "\x1B\x5B\x41");
		break;
	case Escape_CursorDown:
		strcpy(str, "\x1B\x5B\x42");
		break;
	case Escape_CursorForward:
		strcpy(str, "\x1B\x5B\x43");
		break;
	case Escape_CursorBackward:
		strcpy(str, "\x1B\x5B\x44");
		break;
	case Escape_SaveCursorPos:
		strcpy(str, "\x1B\x5B\x73");
		break;
	case Escape_RestoreCursorPos:
		strcpy(str, "\x1B\x5B\x75");
		break;
	case Escape_EraseDisplay:
		strcpy(str, "\x1B\x5B\x32\x4A");
		break;
	case Escape_EraseLine:
		strcpy(str, "\x1B\x5B\x4B");
		break;
	default:
		ret = -1;
		break;
	}

	return ret;
}