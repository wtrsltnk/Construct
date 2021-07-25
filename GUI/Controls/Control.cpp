#include "Control.h"

Control::Control()
{
    this->strWindowClassName = NULL;
    this->strWindowTitle = (LPCTSTR) "DefaultControl";
    this->dwStyle = WS_CHILD;
    this->dwExStyle = WS_EX_WINDOWEDGE;
    this->dwX = CW_USEDEFAULT;
    this->dwY = CW_USEDEFAULT;
    this->dwWidth = CW_USEDEFAULT;
    this->dwHeight = CW_USEDEFAULT;
    this->hIcon = ::LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
    this->hCursor = ::LoadCursor((HINSTANCE)NULL, IDC_ARROW);
    this->hBackgroundColor = (HBRUSH)(COLOR_WINDOW);
}

Control::~Control()
{
}

bool Control::Show(HWND hParent, DWORD dwId)
{
    this->hParent = hParent;
    this->dwId = dwId;

    if (!this->RegisterClass())
    {
        return false;
    }

    this->hWnd = ::CreateWindowEx(this->dwExStyle,
                                  this->strWindowClassName,
                                  this->strWindowTitle,
                                  this->dwStyle,
                                  this->dwX,
                                  this->dwY,
                                  this->dwWidth,
                                  this->dwHeight,
                                  (HWND)this->hParent,
                                  (HMENU)this->dwId,
                                  ::GetModuleHandle(NULL),
                                  (VOID *)this);

    if (this->hWnd == NULL)
    {
        return false;
    }

    ::ShowWindow(this->hWnd, SW_SHOW);
    //::UpdateWindow(this->hWnd);

    return true;
}

void Control::Close()
{
    ::DestroyWindow(this->hWnd);
}

void Control::AddControl(Control *control, DWORD id)
{
    if (control != 0)
    {
        control->Show(this->hWnd, id);
    }
}

bool Control::RegisterClass()
{
    WNDCLASS wc;

    if (::GetClassInfo(::GetModuleHandle(NULL), this->strWindowClassName, &wc) == 0)
    {
        wc.style = 0;
        wc.lpfnWndProc = (WNDPROC)Control::WinProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = ::GetModuleHandle(NULL);
        wc.hIcon = this->hIcon;
        wc.hCursor = this->hCursor;
        wc.hbrBackground = this->hBackgroundColor;
        wc.lpszMenuName = "ControlMenu";
        wc.lpszClassName = this->strWindowClassName;

        if (!::RegisterClass(&wc))
            return false;
    }
    return true;
}

LRESULT Control::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Control *window = nullptr;

    if (msg == WM_NCCREATE)
    {
        window = reinterpret_cast<Control *>(((LPCREATESTRUCT)lParam)->lpCreateParams);

        if (window != nullptr)
        {
            window->hWnd = hWnd;

            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<long long>(window));

            return window->ObjectProc(hWnd, msg, wParam, lParam);
        }
    }
    else if (msg == WM_NCDESTROY)
    {
        ::PostQuitMessage(0);
    }
    else
    {
        window = reinterpret_cast<Control *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        if (window != nullptr)
        {
            return window->ObjectProc(hWnd, msg, wParam, lParam);
        }
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

void Control::GetSize(int &w, int &h)
{
    RECT rc;
    ::GetWindowRect(this->hWnd, &rc);

    w = rc.right - rc.left;
    h = rc.bottom - rc.top;
}

void Control::SetSize(int w, int h)
{
    ::SetWindowPos(this->hWnd, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void Control::GetPosition(int &x, int &y)
{
    RECT rc;
    ::GetWindowRect(this->hWnd, &rc);

    x = rc.right;
    y = rc.bottom;
}

void Control::SetPosition(int x, int y)
{
    ::SetWindowPos(this->hWnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void Control::GetWindowStyle(DWORD &style, DWORD &exstyle)
{
    style = this->dwStyle;
    exstyle = this->dwExStyle;
}

void Control::SetWindowStyle(DWORD style, DWORD exstyle)
{
    this->dwStyle = style;
    this->dwExStyle = exstyle;

    ::SetWindowLong(this->hWnd, GWL_STYLE, style);
    ::SetWindowLong(this->hWnd, GWL_EXSTYLE, exstyle);

    ::SetWindowPos(this->hWnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    ::ShowWindow(this->hWnd, SW_SHOW);
}

void Control::SetText(const char *text)
{
    ::SetWindowText(this->hWnd, text);
}

void Control::AddText(const char *text)
{
    int current_len = ::GetWindowTextLength(this->hWnd);
    size_t input_len = strlen(text);
    size_t new_len = current_len + input_len + 1;
    char *newtext = new char[new_len];

    ::GetWindowText(this->hWnd, newtext, current_len);
    strcat_s(newtext, new_len, text);

    this->SetText(newtext);
    delete[] newtext;
}

const char *Control::GetText()
{
    static char *text = 0;

    if (text != 0)
    {
        delete[] text;
    }

    int current_len = ::GetWindowTextLength(this->hWnd);
    text = new char[current_len + 1];

    ::GetWindowText(this->hWnd, text, current_len);

    return text;
}
