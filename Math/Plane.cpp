#include "Plane.h"

Plane::Plane()
	 : x(0.0f), y(0.0f), z(0.0f), d(0.0f)
{
}

Plane::Plane(float x, float y, float z, float d)
	 : x(x), y(y), z(z), d(d)
{
}

Plane::~Plane()
{
}

void Plane::Create(Vector v1, Vector v2, Vector v3)
{
	Vector a1, a2, n;
	
	a1 = v2 - v1;
	a2 = v3 - v1;
	
	n = a1.CrossProduct(a2);
	n.Normalize();
	
	this->x = n.x;
	this->y = n.y;
	this->z = n.z;
}

float Plane::GetDistance(Vector v)
{
	return this->x * v.x + this->y * v.y + this->z * v.z + this->d;
}

int Plane::ClassifyPoint(Vector v, float& distance)
{
	float dist = GetDistance(v);
	
	if (dist != 0)
		distance = dist;
	
	if (dist > 0)
		return 1;
	
	if (dist < 0)
		return -1;
	
	return 0;
}
