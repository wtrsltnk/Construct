#include "Win32Context.h"
#include "Win32Font.h"
#include <stdio.h>

Win32Context::Win32Context()
{
	this->hWnd = 0;
	this->hDC = 0;
	this->hRC = 0;
	this->bgcolor[0] = 0.3f;	// RED
	this->bgcolor[1] = 0.4f;	// GREEN
	this->bgcolor[2] = 0.7f;	// BLUE
	this->bgcolor[3] = 1.0f;	// ALPHA
}

Win32Context::~Win32Context()
{
}

bool Win32Context::Initialize(HWND hWnd)
{
	this->hWnd = hWnd;
	GLuint uiPixelFormat = 0;
	
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),							// Size Of This Pixel Format Descriptor
		1,														// Version Number
		PFD_DRAW_TO_WINDOW |									// Format Must Support Window
		PFD_SUPPORT_OPENGL |									// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,										// Must Support Double Buffering
		PFD_TYPE_RGBA,											// Request An RGBA Format
		24,														// Select Our Color Depth
		0, 0, 0, 0, 0, 0,										// Color Bits Ignored
		0,														// No Alpha Buffer
		0,														// Shift Bit Ignored
		0,														// No Accumulation Buffer
		0, 0, 0, 0,												// Accumulation Bits Ignored
		16,														// 16Bit Z-Buffer (Depth Buffer)  
		0,														// No Stencil Buffer
		0,														// No Auxiliary Buffer
		PFD_MAIN_PLANE,											// Main Drawing Layer
		0,														// Reserved
		0, 0, 0													// Layer Masks Ignored
	};
	
	if (this->hWnd != NULL)
	{
		if (!(this->hDC = ::GetDC(this->hWnd)))
		{
			//ErrorHandler::Instance()->ReportError("Error creating Device Context");
			this->DestroyGL();
			return false;
		}
	
		if (!(uiPixelFormat = ::ChoosePixelFormat(this->hDC, &pfd)))
		{
			//ErrorHandler::Instance()->ReportError("Error choosing Pixel Format");
			this->DestroyGL();
			return false;
		}
		
		if (!::SetPixelFormat(this->hDC, uiPixelFormat, &pfd))
		{
			//ErrorHandler::Instance()->ReportError("Error setting Pixel Format");
			this->DestroyGL();
			return false;
		}
		
		if (!(this->hRC = ::wglCreateContext(this->hDC)))
		{
			//ErrorHandler::Instance()->ReportError("Error creating Render Context");
			this->DestroyGL();
			return false;
		}
		
		if (!::wglMakeCurrent(this->hDC, this->hRC))
		{
			//ErrorHandler::Instance()->ReportError("Error making current Context");
			this->DestroyGL();
			return false;
		}
		
		::glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		::glShadeModel(GL_SMOOTH);
		::glClearColor(this->bgcolor[0], this->bgcolor[1], this->bgcolor[2], this->bgcolor[3]);
		::glClearDepth(1.0f);
		::glEnable(GL_DEPTH_TEST);
		::glDepthFunc(GL_LEQUAL);
		::glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}
	return true;
}

void Win32Context::OpenFrame()
{
	::wglMakeCurrent(this->hDC, this->hRC);
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	::glClearColor(this->bgcolor[0], this->bgcolor[1], this->bgcolor[2], this->bgcolor[3]);
}

void Win32Context::CloseFrame()
{
	::SwapBuffers(this->hDC);
}

void Win32Context::DestroyGL()
{
	if (this->hRC != NULL)
	{
		if (!::wglMakeCurrent(NULL, NULL))
		{
			//ErrorHandler::Instance()->ReportError("Error finalizing current Context");
		}
		
		if (!::wglDeleteContext(this->hRC))
		{
			//ErrorHandler::Instance()->ReportError("Error deleting Render Context");
		}
		this->hRC = NULL;
	}
	
	if (this->hDC != NULL)
	{
		if (::ReleaseDC(this->hWnd, this->hDC) == 0)
		{
			//ErrorHandler::Instance()->ReportError("Error releasing Device Context");
		}
		this->hDC = NULL;
	}
}

Font* Win32Context::CreateFont(char* family, int size)
{
	::wglMakeCurrent(this->hDC, this->hRC);
	
	Win32Font* result = new Win32Font();
	
	if (result->Initialize(this->hDC, family, size))
		return result;
	
	return 0;
}

void Win32Context::SetBGColor(float color[4])
{
	for (int i = 0; i < 4; i++)
		this->bgcolor[i] = color[i];
}

void Win32Context::DrawOrigin()
{
	float size = 4.0f;
	::glDisable(GL_TEXTURE_2D);
	::glBegin(GL_LINES);
	
	// Draw X-axis (red)
	::glColor3f(1.0f, 0.0f, 0.0f);
	::glVertex3f( size, 0.0f, 0.0f);
	::glVertex3f(-size, 0.0f, 0.0f);
	
	// Draw Y-axis (green)
	::glColor3f(0.0f, 1.0f, 0.0f);
	::glVertex3f(0.0f,  size, 0.0f);
	::glVertex3f(0.0f, -size, 0.0f);
	
	// Draw Z-axis (blue)
	::glColor3f(0.0f, 0.0f, 1.0f);
	::glVertex3f(0.0f, 0.0f,  size);
	::glVertex3f(0.0f, 0.0f, -size);
	
	::glEnd();
}
