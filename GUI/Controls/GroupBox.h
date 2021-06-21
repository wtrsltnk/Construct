#ifndef GROUPBOX_H_
#define GROUPBOX_H_

#include "Control.h"

class GroupBox : public Control
{
protected:
	virtual LRESULT ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
public:
	GroupBox();
	virtual ~GroupBox();
};

#endif /*GROUPBOX_H_*/
