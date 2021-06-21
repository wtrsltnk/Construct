#include "DisplaySettings.h"

DisplaySettings::DisplaySettings()
{
	this->strWindowClassName = "DisplaySettings";
	this->strWindowTitle = "Display Settings";
	this->dwExStyle = WS_EX_WINDOWEDGE;
	this->dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	this->dwHeight = 400;
	this->dwWidth = 300;
}

DisplaySettings::~DisplaySettings()
{
}

LRESULT DisplaySettings::ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			this->lblHeader.Show(hWnd, ID_HEADER);
			this->lblHeader.SetPosition(10, 10);
			this->lblHeader.SetSize(280, 40);
			this->lblHeader.SetText("Choose your render API");
			
			this->cmbApi.Show(hWnd, ID_CMBAPI);
			this->cmbApi.SetPosition(10, 40);
			this->cmbApi.SetSize(150, 80);
			this->cmbApi.AddItem("OpenGL", true);
			this->cmbApi.AddItem("DirectX");
			
			this->grpOpenGL.Show(hWnd, ID_GRPGL);
			this->grpOpenGL.SetPosition(10, 70);
			this->grpOpenGL.SetSize(275, 240);
			this->grpOpenGL.SetText("OpenGL");
			
			this->btnClose.Show(hWnd, ID_BTNCLOSE);
			this->btnClose.SetPosition(200, 330);
			this->btnClose.SetSize(80, 25);
			this->btnClose.SetText("Close");
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case ID_BTNCLOSE:
				{
					::MessageBox(hWnd, "CLOSE", "", MB_OK);
					break;
				}
			}
			break;
		}
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
