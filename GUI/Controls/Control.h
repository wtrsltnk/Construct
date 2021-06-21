#ifndef CONTROL_H_
#define CONTROL_H_

#include<windows.h>

class Control
{
private:
	static LRESULT WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
protected:
	LPTSTR strWindowClassName;
	LPTSTR strWindowTitle;
	HWND hParent;
	HWND hWnd;
	DWORD dwExStyle;
	DWORD dwStyle;
	DWORD dwX;
	DWORD dwY;
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwId;
	HICON hIcon;
	HICON hCursor;
	HBRUSH hBackgroundColor;

	bool RegisterClass();
	virtual LRESULT ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

public:
	Control();
	virtual ~Control();
	
	bool Show(HWND hParent = HWND_DESKTOP, DWORD dwId = 0);
	void Close();
	
	void AddControl(Control* control, DWORD id);
	
	void GetSize(int &w, int &h);
	void SetSize(int w, int h);
	
	void GetPosition(int &x, int &y);
	void SetPosition(int x, int y);

	void GetWindowStyle(DWORD &style, DWORD &exstyle);
	void SetWindowStyle(DWORD style, DWORD exstyle);
	
	void SetText(const char* text);
	void AddText(const char* text);
	const char* GetText();
};

#endif /*CONTROL_H_*/
