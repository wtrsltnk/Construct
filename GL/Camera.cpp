#include <glad/glad.h>
#include <windows.h>

#include "Camera.h"

Camera::Camera()
{
    this->mViewMatrix.FillIndenity();
    this->vPosition.Fill(0.0f, 0.0f, 0.0f);

    this->fPitch = 0.0f;
    this->fRoll = 0.0f;
    this->fYaw = 0.0f;
}

Camera::~Camera()
{
}

void Camera::Run()
{
    Matrix p, r, y, pos;

    p.MatrixRotateXDeg(this->fPitch);
    r.MatrixRotateYDeg(this->fRoll);
    y.MatrixRotateZDeg(this->fYaw);

    /* Gebruik MatrixTranslateInv samen met MatrixTranspose om een player type
	 * camera te krijgen
	 * Gebruik alleen MatrixTranslate om de camera om het 0 punt te roteren
	 */
    pos.MatrixTranslateInv(this->vPosition);
    //pos.MatrixTranslate(this->vPosition);

    this->mViewMatrix = p * r * y * pos;

    this->mViewMatrix.MatrixTranspose();

    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();

    ::glLoadMatrixf((GLfloat *)this->mViewMatrix.Get());
}

void Camera::Move(float front, float right, float up)
{
#ifndef WORLDCAMERA
    if (right != 0)
    {
        this->vPosition.x += this->mViewMatrix.At(0, 0) * right;
        this->vPosition.y += this->mViewMatrix.At(1, 0) * right;
        this->vPosition.z += this->mViewMatrix.At(2, 0) * right;
    }
    if (up != 0)
    {
        this->vPosition.x += this->mViewMatrix.At(0, 1) * up;
        this->vPosition.y += this->mViewMatrix.At(1, 1) * up;
        this->vPosition.z += this->mViewMatrix.At(2, 1) * up;
    }
    if (front != 0)
    {
        this->vPosition.x += this->mViewMatrix.At(0, 2) * front;
        this->vPosition.y += this->mViewMatrix.At(1, 2) * front;
        this->vPosition.z += this->mViewMatrix.At(2, 2) * front;
    }
#else
    this->vPosition.x += right;
    this->vPosition.y += up;
    this->vPosition.z += front;
#endif
}

void Camera::Rotate(float pitch, float roll, float yaw)
{
    if (pitch != 0)
    {
        this->fPitch += pitch;
        if (this->fPitch > 360)
            this->fPitch = this->fPitch - 360;
        else if (this->fPitch < 0)
            this->fPitch = this->fPitch + 360;
    }
    if (roll != 0)
    {
        this->fRoll += roll;
    }
    if (yaw != 0)
    {
        this->fYaw += yaw;
    }
}

Vector Camera::GetPosition()
{
    return this->vPosition;
}
