#ifndef COMBOBOX_H_
#define COMBOBOX_H_

#include "Control.h"

class ComboBox : public Control
{
protected:
	virtual LRESULT ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
public:
	ComboBox();
	virtual ~ComboBox();
	
	void ClearItems();
	int AddItem(const char* item, bool select = false);
	int GetSelectedIndex();
};

#endif /*COMBOBOX_H_*/
