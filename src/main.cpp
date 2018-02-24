#include <Key.h>
#include <OutputChannel.h>
#include <cstdio>
#include <cstring>

int main()
{
	OutputChannel oc;
	KeyConverter kc;
	LineBuffer lb;
	char buf[256] = {0};
	
	oc.Initialize();
	while (1)
	{
		oc.Read(buf);
		Key &k = kc.ToKey(buf);
		k.Execute(lb, oc);
		oc.FlushBuffers();
	}
	return 0;
}