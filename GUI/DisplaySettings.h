#ifndef DISPLAYSETTINGS_H_
#define DISPLAYSETTINGS_H_

#include "Controls/Window.h"
#include "Controls/Label.h"
#include "Controls/Button.h"
#include "Controls/GroupBox.h"
#include "Controls/ComboBox.h"

#define ID_HEADER 65467
#define ID_BTNCLOSE 65468
#define ID_GRPGL 65469
#define ID_CMBAPI 65470

class DisplaySettings : public Window
{
protected:
	Label lblHeader;
	Button btnClose;
	GroupBox grpOpenGL;
	ComboBox cmbApi;

	virtual void PreShow() { }
	virtual void OnInitialize() { }
	virtual void OnIdle() { }
	virtual void OnDestroy() { }

	virtual LRESULT ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
public:
	DisplaySettings();
	virtual ~DisplaySettings();
};

#endif /*DISPLAYSETTINGS_H_*/
