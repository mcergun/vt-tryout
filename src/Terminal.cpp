#include <cstdio>
#include <cstring>
#include "Terminal.h"

Terminal::Terminal()
{
	int ret = SetAttributes(&term, &termOrig);
	initialized = !ret;
}

Terminal::Terminal(int inBuf)
	: inputBuffer(inBuf)
{
	int ret = SetAttributes(&term, &termOrig);
	initialized = !ret;
}

int Terminal::SetAttributes(termios *term, termios *termOrig)
{
	tcgetattr(0, term);
	// save original state
	*termOrig = *term;

	// tcflag_t c_iflag;      /* input modes */
	// tcflag_t c_oflag;      /* output modes */
	// tcflag_t c_cflag;      /* control modes */ 
	// tcflag_t c_lflag;      /* local modes */
	// cc_t     c_cc[NCCS];   /* special characters */

	term->c_lflag &= ~ICANON;
	term->c_lflag &= ~ECHO;
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	// cfmakeraw(term);

	return tcsetattr(0, TCSANOW, term);
}

int Terminal::ReadBuf()
{
	memset(buf, 0, sizeof(buf));
	int ret = read(0, buf, 1);
	Key k = conv.ToKey(buf);
	char lineBuf[MAX_LINELEN];
	if (k.InCode != Input_Escape || k.InCode != Input_Unknown)
	{
		if(!line.HandleKey(k))
		{
			char outBuf[16] = {0};
			switch(k.OutCode)
			{
			case Output_NoAction:
				break;
			case Output_Visual:
				// Print these
				fputc(k.Visual, stdout);
				fflush(stdout);
				break;
			case Output_Clear:
			case Output_Refresh:
				conv.ToAnsiiCode(outBuf, Output_Refresh);
				fputs(outBuf, stdout);
				line.GetLine(lineBuf);
				fputs(lineBuf, stdout);
				conv.ToAnsiiCode(outBuf, Output_CursorStart);
				fputs(outBuf, stdout);
				for (int i = 0; i < line.GetCurPos(); ++i)
				{
					conv.ToAnsiiCode(outBuf, Output_CursorForward);
					fputs(outBuf, stdout);
				}
				fflush(stdout);
				break;
			case Output_NLRefresh:
			case Output_CursorUp:
			case Output_CursorDown:
			case Output_CursorForward:
			case Output_CursorBackward:
			case Output_Delete:
			case Output_Backspace:
			case Output_CursorStart:
			case Output_CursorEnd:
			case Output_SaveCursorPos:
			case Output_RestoreCursorPos:
			case Output_EraseDisplay:
			case Output_EraseLine:
			case Output_DeleteCharacter:
			case Output_EraseCharacter:
				conv.ToAnsiiCode(outBuf, k.OutCode);
				fputs(outBuf, stdout);
				fflush(stdout);
				break;
			default:
				break;
			}
		}
	}
	if (k.OutCode != Output_NoAction)
	{
		// Handle output related sh*t here
	}
	return ret;
}

void Terminal::GetLine(char *dst)
{
	line.GetLine(dst);
}