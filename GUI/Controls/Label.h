#ifndef LABEL_H_
#define LABEL_H_

#include "Control.h"

class Label : public Control
{
protected:
	virtual LRESULT ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
public:
	Label();
	virtual ~Label();
};

#endif /*LABEL_H_*/
