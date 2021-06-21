#include "Window.h"

Window::Window()
{
	this->strWindowTitle = (LPTSTR)"DefaultWindow";
	this->dwExStyle = WS_EX_CLIENTEDGE;
	this->dwStyle = WS_OVERLAPPEDWINDOW;
	this->dwX = CW_USEDEFAULT;
	this->dwY = CW_USEDEFAULT;
	this->dwWidth = CW_USEDEFAULT;
	this->dwHeight = CW_USEDEFAULT;
	this->hIcon = ::LoadIcon((HINSTANCE) NULL, IDI_APPLICATION);
	this->hCursor = ::LoadCursor((HINSTANCE) NULL, IDC_ARROW);
	this->hBackgroundColor = (HBRUSH)(COLOR_WINDOW);
	this->bActive = FALSE;
}

Window::~Window()
{
}

int Window::RunApplication()
{
	MSG msg;
	BOOL bRet;
	
	if (this->Show())
	{
		while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
		{
			if (bRet == -1)
	        {
	            DWORD error = ::GetLastError();
				// Check error codes op:
				// http://msdn2.microsoft.com/en-us/library/ms681381.aspx
	            
	            return error;
	        }
	        else
	        {
	            ::TranslateMessage(&msg); 
	            ::DispatchMessage(&msg); 
	        }
	    }
	    
		return msg.wParam;
	}
	return 0;
}

int Window::RunGame()
{
	MSG msg;
	
	this->PreShow();
	
	if (this->Show())
	{
		this->OnInitialize();
		
		while(msg.message != WM_QUIT)
	    {
	        if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	        {
	            ::TranslateMessage(&msg);
	            ::DispatchMessage(&msg);
	        }
	        else
	        	this->OnIdle();
	    }
	    this->OnDestroy();
	    
		return msg.wParam;
	}
	return 0;
}
