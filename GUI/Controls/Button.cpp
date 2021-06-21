#include "Button.h"

Button::Button()
{
	this->strWindowClassName = "BUTTON";
	this->strWindowTitle = "Button";
}

Button::~Button()
{
}

LRESULT Button::ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
