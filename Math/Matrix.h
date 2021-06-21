// Matrix.h: interface for the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

class Matrix  
{
private:
	float m[4][4];

public:
	Matrix();
	Matrix(float n[4][4]);
	virtual ~Matrix();
	const float At(int i, int j);

	void FillIndenity();
	void FillZero();
	void Fill(float n[][4]);
	void Get(float n[][4]);
	float* Get();
	void MatrixTranslate(Vector v);
	void MatrixTranslateInv(Vector v);
	void MatrixRotateDeg(Vector v);
	void MatrixRotateRad(Vector v);
	void MatrixScale(Vector v);
	void MatrixRotateXDeg(float x);
	void MatrixRotateYDeg(float y);
	void MatrixRotateZDeg(float z);
	void MatrixRotateXRad(float x);
	void MatrixRotateYRad(float y);
	void MatrixRotateZRad(float z);
	void MatrixTranspose();
	void inverseRotateVect(Vector& pVect);
	void inverseTranslateVect(Vector& pVect);

	Matrix operator*(Matrix m2);
	Matrix operator/(Matrix m2);
	Matrix operator+(Matrix m2);
	Matrix operator-(Matrix m2);
	Matrix operator=(Matrix m2);

	bool Equals(Matrix m2);

};

#endif
