#include "Quaternion.h"
#include <math.h>

Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f)
{ }

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z)
{ }

Quaternion::Quaternion(const Quaternion& q) : w(q.w), x(q.x), y(q.y), z(q.z)
{ }

Quaternion::Quaternion(float angle, Vector axis)
{
	this->w = cosf(angle/2);
	this->x = axis.x * sinf(angle/2);
	this->y = axis.y * sinf(angle/2);
	this->z = axis.z * sinf(angle/2);
}

Quaternion::~Quaternion()
{
}

void Quaternion::Normalize()
{
}

float Quaternion::Magnitude()
{
	return sqrt(w*w + x*x + y*y + z*z);
}

void Quaternion::operator=(Quaternion q)
{
	this->w = q.w;
	this->x = q.x;
	this->y = q.y;
	this->z = q.z;
}

Quaternion Quaternion::operator*(Quaternion q)
{
	return Quaternion(
			(this->w*q.w) - (this->x*q.x) - (this->y*q.y) - (this->z*q.z),
			(this->w*q.x) + (this->x*q.w) + (this->y*q.z) - (this->z*q.y),
			(this->w*q.y) - (this->x*q.z) + (this->y*q.w) + (this->z*q.x),
			(this->w*q.z) + (this->x*q.y) - (this->y*q.x) + (this->z*q.w));
}
