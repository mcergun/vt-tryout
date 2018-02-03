#include <cstring>
#include <Terminal.h>
#include <ConsoleComm.h>

Terminal::Terminal()
{
	channel = new ConsoleComm();
	initialized = !channel->Initialize();
}

Terminal::~Terminal()
{
	delete channel;
	channel = nullptr;
}

int Terminal::ReadBuf()
{
	memset(buf, 0, sizeof(buf));
	int ret = channel->Read(buf);
	Key k = conv.ToKey(buf);
	char lineBuf[MAX_LINELEN];
	int outLen = 0;
	if (k.InCode != Input_Escape || k.InCode != Input_Unknown)
	{
		if(!line.HandleKey(k))
		{
			char outBuf[16] = {0};
			switch(k.OutCode)
			{
			case Output_Visual:
				// Print these
				channel->Write(&(k.Visual), 1);
				channel->FlushBuffers();
				break;
			case Output_Clear:
			case Output_Refresh:
				outLen = conv.ToAnsiiCode(outBuf, Output_Refresh);
				channel->Write(outBuf, outLen);
				line.GetLine(lineBuf);
				channel->Write(lineBuf, line.GetLineLen());
				outLen = conv.ToAnsiiCode(outBuf, Output_CursorStart);
				channel->Write(outBuf, outLen);
				for (int i = 0; i < line.GetCurPos(); ++i)
				{
					outLen = conv.ToAnsiiCode(outBuf, 
						Output_CursorForward);
					channel->Write(outBuf, outLen);
				}
				channel->FlushBuffers();
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
				outLen = conv.ToAnsiiCode(outBuf, k.OutCode);
				channel->Write(outBuf, outLen);
				channel->FlushBuffers();
				break;
			case Output_NoAction:
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