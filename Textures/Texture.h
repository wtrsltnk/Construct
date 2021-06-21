#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <glad/glad.h>
#include <windows.h>

#include "bmploader.h"

typedef unsigned char byte;

class Texture
{
private:
    GLuint glid;

protected:
    char name[64] = {'\0'};
    Image img;

public:
    Texture();
    Texture(int w, int h, int bpp, char *data);
    virtual ~Texture();

    virtual void Convert() {}

    int UploadTexture();
    void CleanupTexture();

    void PrintTextureInfo();
};

#endif /*TEXTURE_H_*/
