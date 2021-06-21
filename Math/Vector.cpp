// Vector.cpp: implementation of the Vector class.
//
//////////////////////////////////////////////////////////////////////

#include "Vector.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Vector::Vector()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector::Vector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::~Vector()
{
}

void Vector::Fill(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector Vector::Vectorize(Vector v)
{
	return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}

void Vector::Normalize()
{
	float magnitude = Magnitude();
	
	if (magnitude <= 0.00001) magnitude = 1;
	magnitude = 1 / magnitude;
	
	this->x *= magnitude;
	this->y *= magnitude;
	this->z *= magnitude;
}

float Vector::Magnitude()
{
	return (float)sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

Vector Vector::CrossProduct(Vector v)
{
	return Vector((this->y * v.z) - (this->z * v.y), (this->z * v.x) - (this->x * v.z), (this->x * v.y) - (this->y * v.x));
}

float Vector::DotProduct(Vector v)
{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

void Vector::operator*=(Vector v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}

Vector Vector::operator*(Vector v)
{
	return Vector(this->x * v.x, this->y * v.y, this->z * v.z);
}

Vector Vector::operator*(float f)
{
	return Vector(this->x * f, this->y * f, this->z * f);
}

void Vector::operator/=(Vector v)
{
	if(v.x == 0 || v.y == 0 || v.z == 0)
		return;
		
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
}

Vector Vector::operator/(Vector v)
{
	if(v.x == 0 || v.y == 0 || v.z == 0)
		return Vector(0.0f, 0.0f, 0.0f);
		
	return Vector(this->x / v.x, this->y / v.y, this->z / v.z);
}

Vector Vector::operator/(float f)
{
	if (f == 0)
		return Vector(this->x, this->y, this->z);
		
	return Vector(this->x / f, this->y / f, this->z / f);
}

void Vector::operator+=(Vector v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

Vector Vector::operator+(Vector v)
{
	return Vector(this->x + v.x, this->y + v.y, this->z + v.y);
}

Vector Vector::operator+(float f)
{
	return Vector(this->x + f, this->y + f, this->z + f);
}

void Vector::operator-=(Vector v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

Vector Vector::operator-(Vector v)
{
	return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector Vector::operator-(float f)
{
	return Vector(this->x - f, this->y - f, this->z - f);
}

void Vector::operator=(Vector v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

bool Vector::Equals(Vector v)
{
	if (v.x == this->x && v.y == this->y && v.z == this->z)
		return true;
	return false;
}
