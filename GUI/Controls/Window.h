#ifndef WINDOW_H_
#define WINDOW_H_

#include "../Controls/Control.h"

class Window : public Control
{	
	protected:
		virtual void PreShow() = 0;
		virtual void OnInitialize() = 0;
		virtual void OnIdle() = 0;
		virtual void OnDestroy() = 0;
		BOOL bActive;
		
	public:
		Window();
		virtual ~Window();
		
//		bool Show(HWND hParent = HWND_DESKTOP);
		int RunGame();
		int RunApplication();
};

#endif /*WINDOW_H_*/
