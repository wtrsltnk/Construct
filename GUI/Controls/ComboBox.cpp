#include "ComboBox.h"

ComboBox::ComboBox()
{
	this->strWindowClassName = "COMBOBOX";
	this->dwStyle |= CBS_DROPDOWNLIST;
}

ComboBox::~ComboBox()
{
}

LRESULT ComboBox::ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

void ComboBox::ClearItems()
{
	::SendMessage(this->hWnd, CB_RESETCONTENT, 0, 0);  
}

int ComboBox::AddItem(const char* item, bool select)
{
	if (item != 0)
	{
		int index =  ::SendMessage(this->hWnd, CB_ADDSTRING, 0, (LPARAM)item);
		
		if (select)
		{
			::SendMessage(this->hWnd, CB_SETCURSEL, (WPARAM)index, 0);
		}
		
		return index;
	}
	return -1;
}

int ComboBox::GetSelectedIndex()
{
	return ::SendMessage(this->hWnd, CB_GETCURSEL, 0, 0);
}
