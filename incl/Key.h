#ifndef _KEY_H_
#define _KEY_H_

#include <LineBuffer.h>
#include <OutputChannel.h>

enum KeyCodes
{
	KeyCode_Escape = 0x1B,
	KeyCode_Escape2 = 0x5B,
	KeyCode_Escape3 = 0x33,
	KeyCode_End = 0x46,
	KeyCode_Home = 0x48,
	KeyCode_Delete = 0x7E,
	KeyCode_Return = 0x0A,
	KeyCode_Tab = 0x09,
	KeyCode_Backspace = 0x7F,
	KeyCode_UpArrow = 0x41,
	KeyCode_DownArrow = 0x42,
	KeyCode_RightArrow = 0x43,
	KeyCode_LeftArrow = 0x44,

	KeyCode_VisSpace = 0x20,
	KeyCode_VisExclMark = 0x21,
	KeyCode_VisDoubleQuotes = 0x22,
	KeyCode_VisSharp = 0x23,
	KeyCode_VisDollar = 0x24,
	KeyCode_VisPercent = 0x25,
	KeyCode_VisAmpercend = 0x26,
	KeyCode_VisSingleQuote = 0x27,
	KeyCode_VisLeftParanth = 0x28,
	KeyCode_VisRightParanth = 0x29,
	KeyCode_VisAsterisk = 0x2A,
	KeyCode_VisPlusSign = 0x2B,
	KeyCode_VisComma = 0x2C,
	KeyCode_VisMinusSign = 0x2D,
	KeyCode_VisDot = 0x2E,
	KeyCode_VisSlash = 0x2F,
	KeyCode_VisColon = 0x3A,
	KeyCode_VisSemiColon = 0x3B,
	KeyCode_VisLessThan = 0x3C,
	KeyCode_VisEqual = 0x3D,
	KeyCode_VisGrtThan = 0x3E,
	KeyCode_VisQuestion = 0x3F,
	KeyCode_VisAtSign = 0x40,
	KeyCode_VisLeftBracket = 0x5B,
	KeyCode_VisBackSlash = 0x5C,
	KeyCode_VisRightBracket = 0x5D,
	KeyCode_VisCaret = 0x5E,
	KeyCode_VisUnderscore = 0x5F,
	KeyCode_VisLeftBraces = 0x7B,
	KeyCode_VisPerpendicular = 0x7C,
	KeyCode_VisRightBraces = 0x7D,
	KeyCode_VisTilde = 0x7E,
};

class KeyCommand
{
public:
	virtual ~KeyCommand() {};
	virtual int Execute(LineBuffer &lb, OutputChannel &oc) = 0;
};

class Key : public KeyCommand
{
public:
	virtual ~Key() {};
	Key(char c);
	char visual;
};

class KeyConverter
{
public:
	KeyConverter();
	~KeyConverter();
	Key & ToKey(const char *str);
private:
	static constexpr int UNIQ_KEY_COUNT = 12;
	Key *keyList[UNIQ_KEY_COUNT];
	bool isEscapeSequence = false;
	int seqLen = 0;
};

class KeyIgnore : public Key
{
public:
	KeyIgnore() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc) { return 0;}
};

class KeyEscape : public Key
{
public:
	KeyEscape() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc) { return 0;}
};

class KeyReturn : public Key
{
public:
	KeyReturn() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyUpArrow : public Key
{
public:
	KeyUpArrow() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyDownArrow : public Key
{
public:
	KeyDownArrow() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyLeftArrow : public Key
{
public:
	KeyLeftArrow() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyRightArrow : public Key
{
public:
	KeyRightArrow() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyVisual : public Key
{
public:
	KeyVisual(char vis) : Key(vis) {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
private:
	KeyVisual();
};

class KeyBackspace : public Key
{
public:
	KeyBackspace() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyDelete : public Key
{
public:
	KeyDelete() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyHome : public Key
{
public:
	KeyHome() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyEnd : public Key
{
public:
	KeyEnd() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

#endif