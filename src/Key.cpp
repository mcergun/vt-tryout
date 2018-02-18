#include <cstring>
#include <Key.h>

Key::Key(const char *str)
{
	strcpy(outCode, str);
}