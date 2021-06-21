// Matrix.cpp: implementation of the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#include "Matrix.h"
#include "Math.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Matrix::Matrix()
{
	FillZero();
}

Matrix::Matrix(float N[][4])
{
	for ( int i = 0; i < 4; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			this->m[i][j] = N[i][j];
		}
	}
}

Matrix::~Matrix()
{
}

void Matrix::FillIndenity()
{
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i == j )
				this->m[i][j] = 1;
			else
				this->m[i][j] = 0;
		}
	}
}

void Matrix::FillZero()
{
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			this->m[i][j] = 0;
		}
	}
}

void Matrix::Fill(float n[][4])
{
	for ( int i = 0; i < 4; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			this->m[i][j] = n[i][j];
		}
	}
}

void Matrix::Get(float n[][4])
{
	for ( int i = 0; i < 4; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			n[i][j] = this->m[i][j];
		}
	}
}

float* Matrix::Get()
{
	return &this->m[0][0];
}

const float Matrix::At(int i, int j)
{
	return this->m[i][j];
}

Matrix Matrix::operator*(Matrix m2)
{
	float n[4][4];

	n[0][0] =	(this->m[0][0] * m2.m[0][0]) + (this->m[0][1] * m2.m[1][0]) +
					(this->m[0][2] * m2.m[2][0]) + (this->m[0][3] * m2.m[3][0]);

	n[0][1] =	(this->m[0][0] * m2.m[0][1]) + (this->m[0][1] * m2.m[1][1]) +
					(this->m[0][2] * m2.m[2][1]) + (this->m[0][3] * m2.m[3][1]);

	n[0][2] =	(this->m[0][0] * m2.m[0][2]) + (this->m[0][1] * m2.m[1][2]) +
					(this->m[0][2] * m2.m[2][2]) + (this->m[0][3] * m2.m[3][2]);

	n[0][3] =	(this->m[0][0] * m2.m[0][3]) + (this->m[0][1] * m2.m[1][3]) +
					(this->m[0][2] * m2.m[2][3]) + (this->m[0][3] * m2.m[3][3]);


	n[1][0] =	(this->m[1][0] * m2.m[0][0]) + (this->m[1][1] * m2.m[1][0]) +
					(this->m[1][2] * m2.m[2][0]) + (this->m[1][3] * m2.m[3][0]);

	n[1][1] =	(this->m[1][0] * m2.m[0][1]) + (this->m[1][1] * m2.m[1][1]) +
					(this->m[1][2] * m2.m[2][1]) + (this->m[1][3] * m2.m[3][1]);

	n[1][2] =	(this->m[1][0] * m2.m[0][2]) + (this->m[1][1] * m2.m[1][2]) +
					(this->m[1][2] * m2.m[2][2]) + (this->m[1][3] * m2.m[3][2]);

	n[1][3] =	(this->m[1][0] * m2.m[0][3]) + (this->m[1][1] * m2.m[1][3]) +
					(this->m[1][2] * m2.m[2][3]) + (this->m[1][3] * m2.m[3][3]);


	n[2][0] =	(this->m[2][0] * m2.m[0][0]) + (this->m[2][1] * m2.m[1][0]) +
					(this->m[2][2] * m2.m[2][0]) + (this->m[2][3] * m2.m[3][0]);

	n[2][1] =	(this->m[2][0] * m2.m[0][1]) + (this->m[2][1] * m2.m[1][1]) +
					(this->m[2][2] * m2.m[2][1]) + (this->m[2][3] * m2.m[3][1]);

	n[2][2] =	(this->m[2][0] * m2.m[0][2]) + (this->m[2][1] * m2.m[1][2]) +
					(this->m[2][2] * m2.m[2][2]) + (this->m[2][3] * m2.m[3][2]);

	n[2][3] =	(this->m[2][0] * m2.m[0][3]) + (this->m[2][1] * m2.m[1][3]) +
					(this->m[2][2] * m2.m[2][3]) + (this->m[2][3] * m2.m[3][3]);


	n[3][0] =	(this->m[3][0] * m2.m[0][0]) + (this->m[3][1] * m2.m[1][0]) +
					(this->m[3][2] * m2.m[2][0]) + (this->m[3][3] * m2.m[3][0]);

	n[3][1] =	(this->m[3][0] * m2.m[0][1]) + (this->m[3][1] * m2.m[1][1]) +
					(this->m[3][2] * m2.m[2][1]) + (this->m[3][3] * m2.m[3][1]);

	n[3][2] =	(this->m[3][0] * m2.m[0][2]) + (this->m[3][1] * m2.m[1][2]) +
					(this->m[3][2] * m2.m[2][2]) + (this->m[3][3] * m2.m[3][2]);

	n[3][3] =	(this->m[3][0] * m2.m[0][3]) + (this->m[3][1] * m2.m[1][3]) +
					(this->m[3][2] * m2.m[2][3]) + (this->m[3][3] * m2.m[3][3]);

	return Matrix(n);
}

Matrix Matrix::operator/(Matrix m2)
{
	return Matrix();
}

Matrix Matrix::operator+(Matrix m2)
{
	return Matrix();
}

Matrix Matrix::operator-(Matrix m2)
{
	return Matrix();
}

Matrix Matrix::operator=(Matrix m2)
{
	for (int i =0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m[i][j] = m2.m[i][j];
	return this->m;
}

bool Matrix::Equals(Matrix m2)
{
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( this->m[i][j] != m2.At(i,j) )
				return false;
		}
	}
	return true;
}

void Matrix::MatrixTranslateInv(Vector v)
{
	FillIndenity();
	this->m[0][3] = v.x;
	this->m[1][3] = v.y;
	this->m[2][3] = v.z;
}

void Matrix::MatrixTranslate(Vector v)
{
	FillIndenity();
	this->m[3][0] = v.x;
	this->m[3][1] = v.y;
	this->m[3][2] = v.z;
}

void Matrix::MatrixRotateDeg(Vector v)
{
	MatrixRotateXDeg(v.x);
	MatrixRotateYDeg(v.y);
	MatrixRotateZDeg(v.z);
}

void Matrix::MatrixRotateRad(Vector v)
{
	MatrixRotateXRad(v.x);
	MatrixRotateYRad(v.y);
	MatrixRotateZRad(v.z);
}

void Matrix::MatrixScale(Vector v)
{
	FillIndenity();
	this->m[0][0] = v.x;
	this->m[1][1] = v.y;
	this->m[2][2] = v.z;
}

void Matrix::MatrixRotateXDeg(float x)
{
	FillIndenity();
	this->m[1][1] = cosf(Math::DEG2RAD(x));
	this->m[1][2] = sinf(Math::DEG2RAD(x));
	this->m[2][1] = -sinf(Math::DEG2RAD(x));
	this->m[2][2] = cosf(Math::DEG2RAD(x));
/*
	[ 1,         0,          0, 0]
	[ 0, cos(xrot),  sin(xrot), 0]
	[ 0,-sin(xrot),  cos(xrot), 0]
	[ 0,         0,          0, 1]
*/
}

void Matrix::MatrixRotateYDeg(float y)
{
	FillIndenity();
	this->m[0][0] = cosf(Math::DEG2RAD(y));
	this->m[0][2] = -sinf(Math::DEG2RAD(y));
	this->m[2][0] = sinf(Math::DEG2RAD(y));
	this->m[2][2] = cosf(Math::DEG2RAD(y));
/*
	[ cos(yrot), 0,-sin(yrot), 0]
	[         0, 1,         0, 0]
	[ sin(yrot), 0, cos(yrot), 0]
	[         0, 0,         0, 1]
*/
}

void Matrix::MatrixRotateZDeg(float z)
{
	FillIndenity();
	this->m[0][0] = cosf(Math::DEG2RAD(z));
	this->m[0][1] = sinf(Math::DEG2RAD(z));
	this->m[1][0] = -sinf(Math::DEG2RAD(z));
	this->m[1][1] = cosf(Math::DEG2RAD(z));
/*
	[ cos(zrot),  sin(zrot), 0, 0]
	[-sin(zrot),  cos(zrot), 0, 0]
	[         0,          0, 1, 0]
	[         0,          0, 0, 1]
*/
}

void Matrix::MatrixRotateXRad(float x)
{
	FillIndenity();
	this->m[1][1] = cosf(x);
	this->m[1][2] = sinf(x);
	this->m[2][1] = -sinf(x);
	this->m[2][2] = cosf(x);
}

void Matrix::MatrixRotateYRad(float y)
{
	FillIndenity();
	m[0][0] = cosf(y);
	m[0][2] = -sinf(y);
	m[2][0] = sinf(y);
	m[2][2] = cosf(y);
}

void Matrix::MatrixRotateZRad(float z)
{
	FillIndenity();
	this->m[0][0] = cosf(z);
	this->m[0][1] = sinf(z);
	this->m[1][0] = -sinf(z);
	this->m[1][1] = cosf(z);
}

void Matrix::MatrixTranspose()
{
	float fTemp;

	fTemp = this->m[0][1];
	this->m[0][1] = this->m[1][0];
	this->m[1][0] = fTemp;

	fTemp = this->m[0][2];
	this->m[0][2] = this->m[2][0];
	this->m[2][0] = fTemp;

	fTemp = this->m[0][3];
	this->m[0][3] = this->m[3][0];
	this->m[3][0] = fTemp;

	fTemp = this->m[1][2];
	this->m[1][2] = this->m[2][1];
	this->m[2][1] = fTemp;

	fTemp = this->m[1][3];
	this->m[1][3] = this->m[3][1];
	this->m[3][1] = fTemp;

	fTemp = this->m[2][3];
	this->m[2][3] = this->m[3][2];
	this->m[3][2] = fTemp;
}

void Matrix::inverseRotateVect(Vector& pVect)
{
	float vec[3];

	vec[0] = pVect.x * this->m[0][0] + pVect.x * this->m[0][1] + pVect.x * this->m[0][2];
	vec[1] = pVect.y * this->m[1][0] + pVect.y * this->m[1][1] + pVect.y * this->m[1][2];
	vec[2] = pVect.z * this->m[2][0] + pVect.z * this->m[2][1] + pVect.z * this->m[2][2];

	pVect.x = vec[0];
	pVect.y = vec[1];
	pVect.z = vec[2];
}

void Matrix::inverseTranslateVect(Vector& pVect)
{
	pVect.x = pVect.x - this->m[3][0];
	pVect.y = pVect.y - this->m[3][1];
	pVect.z = pVect.z - this->m[3][2];
}
