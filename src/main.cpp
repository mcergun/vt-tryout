#include <Key.h>
#include <OutputChannel.h>
#include <cstdio>

int main()
{
	OutputChannel oc;
	char buf[256] = {0};
	
	oc.Read(buf);
	printf("%s\n", buf);
	return 0;
}