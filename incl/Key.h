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
	static const int MAX_SEQ_LEN = 16;
	virtual ~Key() {};
	Key(const char *c);
protected:
	char outCode[MAX_SEQ_LEN];
};

class KeyReturn : public Key
{
public:
	KeyReturn() : Key(VTConverter::ToAnsiiCode(Output_NLRefresh)) {};
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyUpArrow : public Key
{
public:
	KeyUpArrow();
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyDownArrow : public Key
{
public:
	KeyDownArrow();
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyLeftArrow : public Key
{
public:
	KeyLeftArrow();
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

class KeyRightrrow : public Key
{
public:
	KeyRightrrow();
	int Execute(LineBuffer &lb, OutputChannel &oc);
};

#endif