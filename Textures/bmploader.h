#ifndef BMPLOADER_H_
#define BMPLOADER_H_

#include <glad/glad.h>
#include <windows.h>

#include "../World/wad.h"

/* Image type - contains height, width, and data */
struct Image
{
    unsigned long sizeX;
    unsigned long sizeY;
    int bpp;
    char *data;
};
typedef struct Image Image;

int ImageLoad(char *filename, Image *image);
int LoadRedImage(Image *image);
int LoadWadImage(Image *image, char *data);
int LoadGLTextures(Image *image);

#endif /*BMPLOADER_H_*/
