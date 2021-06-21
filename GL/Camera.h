#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Math/Matrix.h"
#include "../Math/Vector.h"

class Camera
{
protected:
    Matrix mViewMatrix;
    Vector vPosition;

    float fPitch;
    float fRoll;
    float fYaw;

    void UpdateCameraMatrix();

public:
    Camera();
    virtual ~Camera();

    virtual void Run();

    void Move(float front, float right, float up);
    void Rotate(float pitch, float roll, float yaw);

    Vector GetPosition();
};

#endif /*CAMERA_H_*/
