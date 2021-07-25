#ifndef WIN32FONT_H_
#define WIN32FONT_H_

#include <glad/glad.h>
#include <windows.h>

#include "Font.h"

class Win32Font : public Font
{
private:
    int font_index;

public:
    Win32Font();
    virtual ~Win32Font();

    bool Initialize(HDC hDC, const char *family, int size);
    virtual void Destroy();
    virtual void PrintText(int x, int y, const char *str, ...);
};

#endif /*WIN32FONT_H_*/
