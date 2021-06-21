// Color.cpp: implementation of the Color class.
//
//////////////////////////////////////////////////////////////////////

#include "Color.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Color::Color()
{
	this->R = 0.0f;
	this->G = 0.0f;
	this->B = 0.0f;
	this->A = 1.0f;
}
Color::~Color()
{

}

Color::Color(float r, float g, float b)
{
	this->R = r;
	this->G = g;
	this->B = b;
	this->A = 1.0f;
}

Color::Color(float r, float g, float b, float a)
{
	this->R = r;
	this->G = g;
	this->B = b;
	this->A = a;
}

void Color::Set(float r, float g, float b)
{
	this->R = r;
	this->G = g;
	this->B = b;
	this->A = 1.0f;
}

void Color::Set(float r, float g, float b, float a)
{
	this->R = r;
	this->G = g;
	this->B = b;
	this->A = a;
}

void Color::Set(float color[])
{
	this->R = color[0];
	this->G = color[1];
	this->B = color[2];
	this->A = 1.0f;
}

float Color::GetR()
{
	return this->R;
}

float Color::GetG()
{
	return this->G;
}

float Color::GetB()
{
	return this->B;
}

float Color::GetA()
{
	return this->A;
}

void Color::Get(float color[])
{
	color[0] = this->R;
	color[1] = this->G;
	color[2] = this->B;
	color[3] = this->A;
}

float* Color::GetP()
{
	float* color = new float[4];
	color[0] = this->R;
	color[1] = this->G;
	color[2] = this->B;
	color[3] = this->A;

	return color;
}
