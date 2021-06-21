#include "Label.h"

Label::Label()
{
	this->strWindowClassName = "STATIC";
}

Label::~Label()
{
}

LRESULT Label::ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
