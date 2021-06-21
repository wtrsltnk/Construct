#ifndef BUTTON_H_
#define BUTTON_H_

#include "Control.h"

class Button : public Control
{
protected:
	virtual LRESULT ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
public:
	Button();
	virtual ~Button();
};

#endif /*BUTTON_H_*/
