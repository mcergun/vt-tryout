#ifndef _KEY_H_
#define _KEY_H_

#include <LineBuffer.h>
#include <OutputChannel.h>

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
	static constexpr int UNIQ_KEY_COUNT = 13;
	static constexpr unsigned char CODE_ESC_START = 0x1B;
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

class KeyTab : public Key
{
public:
	KeyTab() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

#endif