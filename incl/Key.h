#ifndef _KEY_H_
#define _KEY_H_

#include <LineBuffer.h>
#include <OutputChannel.h>

class KeyCommand
{
	virtual ~KeyCommand() {};
	virtual int Execute(LineBuffer &lb, OutputChannel &oc) = 0;
};

class Key : public KeyCommand
{
public:
	virtual ~Key() {};
	Key(char c) : outCode(c) {};
protected:
	char outCode;
};

#endif