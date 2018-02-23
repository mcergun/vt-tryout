#include <cstring>
#include <Key.h>

Key::Key(char c) :
	visual(c)
{
}

int KeyReturn::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.AddToHistory(lb.GetCurrentLine());
	ret = lb.GetCurrentLine().Clear();
	ret = oc.NewLine();

	return ret;
}

int KeyUpArrow::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.GetPrevFromHistory(lb.GetCurrentLine());
	ret = oc.ClearLine();
	const char *curLineStr = lb.GetCurrentLine().GetStringContent();
	ret = oc.Write(curLineStr, strlen(curLineStr));
	return ret;
}

int KeyDownArrow::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.GetNextFromHistory(lb.GetCurrentLine());
	ret = oc.ClearLine();
	const char *curLineStr = lb.GetCurrentLine().GetStringContent();
	ret = oc.Write(curLineStr, strlen(curLineStr));
	return ret;
}

int KeyLeftArrow::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.GetCurrentLine().MoveCursorLeft();
	ret = oc.MoveCursorLeft();
	return ret;
}

int KeyRightrrow::Execute(LineBuffer &lb, OutputChannel &oc)
{
	int ret = 0;
	ret = lb.GetCurrentLine().MoveCursorRight();
	ret = oc.MoveCursorRight();
	return ret;
}