#ifndef _KEY_H_
#define _KEY_H_

#include <LineBuffer.h>
#include <OutputChannel.h>
#include <VTConverter.h>

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
protected:
	char visual;
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

class KeyRightrrow : public Key
{
public:
	KeyRightrrow() : Key('\0') {}
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

#endif