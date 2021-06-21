#include "Texture.h"
#include <stdio.h>

int Texture::UploadTexture()
{
    ::glGenTextures(1, &this->glid);
    ::glBindTexture(GL_TEXTURE_2D, this->glid);

    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //	::gluBuild2DMipmaps(GL_TEXTURE_2D, this->img.bpp, this->img.sizeX, this->img.sizeY, this->img.bpp==3?GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, this->img.data);

    free(this->img.data);
    this->img.data = 0;

    return this->glid;
}

void Texture::CleanupTexture()
{
    ::glDeleteTextures(1, &this->glid);
}

void Texture::PrintTextureInfo()
{
    printf("------------------------\n");
    printf("Texture:	%s\n", this->name);
    printf("width:		%i\n", (int)this->img.sizeX);
    printf("height:		%i\n", (int)this->img.sizeY);
    printf("bpp:		%d\n", this->img.bpp);
    printf("glid:		%d\n", this->glid);
}

Texture::Texture()
{
    this->img.sizeX = 0;
    this->img.sizeY = 0;
    this->img.bpp = 0;
    this->img.data = 0;
    this->glid = 0;
}

Texture::Texture(int w, int h, int bpp, char *data)
{
    this->img.sizeX = w;
    this->img.sizeY = h;
    this->img.bpp = bpp;
    this->img.data = data;
    this->glid = 0;
}

Texture::~Texture()
{
    if (this->img.data != 0)
    {
        free(this->img.data);
    }
    this->img.sizeX = 0;
    this->img.sizeY = 0;
    this->img.bpp = 0;
    this->img.data = 0;
    this->glid = 0;
}
