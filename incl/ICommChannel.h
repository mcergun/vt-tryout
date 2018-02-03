#ifndef _I_COMM_CHANNEL_
#define _I_COMM_CHANNEL_

class ICommChannel
{
public:
	virtual ~ICommChannel() {}
	virtual int Initialize() = 0;
	virtual int Read(void *buf) = 0;
	virtual int Write(void *buf, int len) = 0;
	virtual void FlushBuffers() = 0;
};

#endif