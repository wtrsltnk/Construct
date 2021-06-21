#include "GroupBox.h"

GroupBox::GroupBox()
{
	this->strWindowClassName = "BUTTON";
	this->strWindowTitle = "Button";
	this->dwStyle |= BS_GROUPBOX;
}

GroupBox::~GroupBox()
{
}

LRESULT GroupBox::ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
