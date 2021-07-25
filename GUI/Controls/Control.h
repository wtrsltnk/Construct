#ifndef CONTROL_H_
#define CONTROL_H_

#include <windows.h>

class Control
{
private:
    static LRESULT WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
    LPCTSTR strWindowClassName = NULL;
    LPCTSTR strWindowTitle = NULL;
    HWND hParent = NULL;
    HWND hWnd = NULL;
    DWORD dwExStyle = 0;
    DWORD dwStyle = 0;
    DWORD dwX = 0;
    DWORD dwY = 0;
    DWORD dwWidth = 0;
    DWORD dwHeight = 0;
    DWORD dwId = 0;
    HICON hIcon = NULL;
    HICON hCursor = NULL;
    HBRUSH hBackgroundColor = NULL;

    bool RegisterClass();
    virtual LRESULT ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;

public:
    Control();
    virtual ~Control();

    bool Show(HWND hParent = HWND_DESKTOP, DWORD dwId = 0);
    void Close();

    void AddControl(Control *control, DWORD id);

    void GetSize(int &w, int &h);
    void SetSize(int w, int h);

    void GetPosition(int &x, int &y);
    void SetPosition(int x, int y);

    void GetWindowStyle(DWORD &style, DWORD &exstyle);
    void SetWindowStyle(DWORD style, DWORD exstyle);

    void SetText(const char *text);
    void AddText(const char *text);
    const char *GetText();
};

#endif /*CONTROL_H_*/
