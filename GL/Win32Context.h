#ifndef WIN32CONTEXT_H_
#define WIN32CONTEXT_H_

#include <glad/glad.h>
#include <windows.h>

#include "Font.h"

class Win32Context
{
protected:
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    float bgcolor[4];

public:
    Win32Context();
    virtual ~Win32Context();

    bool Initialize(HWND hWnd);
    void OpenFrame();
    void CloseFrame();
    void DestroyGL();

    Font *CreateFont(char *family, int size);
    void SetBGColor(float color[4]);

    void DrawOrigin();
};

#endif /*WIN32CONTEXT_H_*/
