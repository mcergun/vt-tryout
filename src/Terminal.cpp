#include <Terminal.h>

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
	int ret = read(0, buf, 1);
	Key k = conv.ToKey(buf);
	line.HandleKey(k);
	return ret;
}

void Terminal::GetLine(char *dst)
{
	line.GetLine(dst);
}