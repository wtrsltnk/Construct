#include "Win32Font.h"
#include <windows.h>
#include <stdio.h>

Win32Font::Win32Font()
{
	this->font_index = 0;
}

Win32Font::~Win32Font()
{
}

bool Win32Font::Initialize(HDC hDC, char* family, int size)
{
	HFONT font;
	HFONT oldfont;
	
	this->line_height = size + 2;
	this->font_index = ::glGenLists(96);
	
	font = ::CreateFont(size,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						family);						// Font Name
	
	oldfont = (HFONT)::SelectObject(hDC, font);
	::wglUseFontBitmaps(hDC, 32, 96, this->font_index);
	::SelectObject(hDC, oldfont);
	::DeleteObject(font);
	
	return true;
}

void Win32Font::Destroy()
{
	::glDeleteLists(this->font_index, 96);
}

void Win32Font::PrintText(int x, int y, char* str, ...)
{
	char text[256];
	va_list ap;

	if (str == NULL)
		return;

	::va_start(ap, str);
	    ::vsprintf(text, str, ap);
	::va_end(ap);

	::glRasterPos2i(x, y);
	::glPushAttrib(GL_LIST_BIT);
	::glListBase(this->font_index - 32);
	::glCallLists(::strlen(text), GL_BYTE, text);
	::glPopAttrib();
}
