#include <cstring>
#include "VTConverter.h"

// Some of the following sequences can be used for N times
// Those are marked with {n}, simply replace {n} with "string" number
// Move cursor forward 5 times -> "\x1B\x5B" "5\x43"

// Erase character and delete character seem to be doing the same thing?

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
	case Escape_DeleteCharacter:
		strcpy(str, "\x1B\x5B\x50");
		break;
	case Escape_EraseCharacter:
		strcpy(str, "\x1B\x5B\x58");
		break;
	case Escape_Delete:
		strcpy(str, "\x7F");
		break;
	case Escape_Backspace:
		strcpy(str, "\x08");
		break;
	case Escape_Keypad0:
		strcpy(str, "\x1B\x4F\x70");
		break;
	case Escape_Keypad1:
		strcpy(str, "\x1B\x4F\x71");
		break;
	case Escape_Keypad2:
		strcpy(str, "\x1B\x4F\x72");
		break;
	case Escape_Keypad3:
		strcpy(str, "\x1B\x4F\x73");
		break;
	case Escape_Keypad4:
		strcpy(str, "\x1B\x4F\x74");
		break;
	case Escape_Keypad5:
		strcpy(str, "\x1B\x4F\x75");
		break;
	case Escape_Keypad6:
		strcpy(str, "\x1B\x4F\x76");
		break;
	case Escape_Keypad7:
		strcpy(str, "\x1B\x4F\x77");
		break;
	case Escape_Keypad8:
		strcpy(str, "\x1B\x4F\x78");
		break;
	case Escape_Keypad9:
		strcpy(str, "\x1B\x4F\x79");
		break;
	case Escape_Keypadminus:
		strcpy(str, "\x1B\x4F\x6D");
		break;
	case Escape_Keypadcomma:
		strcpy(str, "\x1B\x4F\x6C");
		break;
	case Escape_Keypadperiod:
		strcpy(str, "\x1B\x4F\x6E");
		break;
	case Escape_KeypadEnter:
		strcpy(str, "\x1B\x4F\x4D");
		break;
	case Escape_KeypadPF1:
		strcpy(str, "\x1B\x4F\x50");
		break;
	case Escape_KeypadPF2:
		strcpy(str, "\x1B\x4F\x51");
		break;
	case Escape_KeypadPF3:
		strcpy(str, "\x1B\x4F\x52");
		break;
	case Escape_KeypadPF4:
		strcpy(str, "\x1B\x4F\x53");
		break;
	default:
		ret = -1;
		break;
	}

	return ret;
}