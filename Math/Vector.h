// Vector.h: interface for the Vector class.
//
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR_H
#define VECTOR_H

class Vector  
{
	public:
		float x;
		float y;
		float z;
	
	public:
		Vector();
		Vector(float x, float y, float z);
		virtual ~Vector();
	
		void Fill(float x, float y, float z);
		Vector Vectorize(Vector v);
		void Normalize();
		float Magnitude();
		Vector CrossProduct(Vector v);
		float DotProduct(Vector v);
	
		void operator*=(Vector v);
		Vector operator*(Vector v);
		Vector operator*(float f);
		void operator/=(Vector v);
		Vector operator/(Vector v);
		Vector operator/(float f);
		void operator+=(Vector v);
		Vector operator+(Vector v);
		Vector operator+(float f);
		void operator-=(Vector v);
		Vector operator-(Vector v);
		Vector operator-(float f);
		void operator=(Vector v);
	
		bool Equals(Vector v);
		
};

#endif
