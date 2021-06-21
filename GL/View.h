#ifndef VIEW_H_
#define VIEW_H_

#include <glad/glad.h>

class View
{
protected:
    int width, height;

    float clipping_angle;
    float clipping_near;
    float clipping_far;

public:
    View();
    View(int w, int h);
    virtual ~View();

    void Resize(int w, int h);
    void Setup3D();
    void Setup2D();

    void SetClipping(float deg, float n, float f);
    void GetClipping(float &deg, float &n, float &f);

    int GetWidth() { return this->width; }
    int GetHeight() { return this->height; }
};

#endif /*VIEW_H_*/
