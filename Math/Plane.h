#ifndef PLANE_H_
#define PLANE_H_

#include "Vector.h"

class Plane
{
	protected:
		float x, y, z;	// normal
		float d;		// distance from (0, 0, 0)
		
	public:
		Plane();
		Plane(float x, float y, float z, float d);
		virtual ~Plane();
		
		void Create(Vector v1, Vector v2, Vector v3);
		float GetDistance(Vector v);
		int ClassifyPoint(Vector v, float& distance);
};

#endif /*PLANE_H_*/
