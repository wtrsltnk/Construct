#include "View.h"

View::View()
{
	this->width = 300;
	this->height = 300;
	this->clipping_angle = 45.0f;
	this->clipping_near = 1.0f;
	this->clipping_far = 100.0f;
}

View::View(int w, int h)
{
	this->width = w;
	this->height = h;
	this->clipping_angle = 45.0f;
	this->clipping_near = 1.0f;
	this->clipping_far = 100.0f;
}

View::~View()
{
}

void View::Resize(int w, int h)
{
	this->width = w;
	this->height = h;
	
	if (this->height == 0)
	{
		this->height = 1;
	}
	
	::glViewport(0, 0, this->width, this->height);
}

void View::Setup3D()
{
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	
	::gluPerspective(this->clipping_angle, (GLfloat)this->width/this->height, this->clipping_near, this->clipping_far);
	
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}

void View::Setup2D()
{
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	::glOrtho(0.0f, this->width, this->height, 0.0f, -1.0f, 1.0f);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}

void View::SetClipping(float deg, float n, float f)
{
	this->clipping_angle = deg;
	this->clipping_near = n;
	this->clipping_far = f;
}

void View::GetClipping(float& deg, float& n, float& f)
{
	deg = this->clipping_angle;
	n = this->clipping_near;
	f = this->clipping_far;
}
