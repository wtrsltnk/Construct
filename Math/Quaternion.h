#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Vector.h"

class Quaternion
{
	public:
		float w;
		float x;
		float y;
		float z;
		
	public:
		Quaternion();
		Quaternion(const Quaternion& q);
		Quaternion(float w, float x, float y, float z);
		Quaternion(float angle, Vector axis);
		virtual ~Quaternion();
		
		void Normalize();
		float Magnitude();
		
		void operator=(Quaternion q);
		Quaternion operator*(Quaternion q);
};

#endif /*QUATERNION_H_*/
