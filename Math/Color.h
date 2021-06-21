// Color.h: interface for the Color class.
//
//////////////////////////////////////////////////////////////////////

#ifndef COLOR_H
#define COLOR_H

class Color  
{
protected:
	float R;
	float G;
	float B;
	float A;
public:
	Color();
	virtual ~Color();
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);

	void Set(float r, float g, float b);
	void Set(float r, float g, float b, float a);
	void Set(float color[]);
	float GetR();
	float GetG();
	float GetB();
	float GetA();
	void Get(float color[]);
	float* GetP();

};

#endif
