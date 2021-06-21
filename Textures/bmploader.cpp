#include "bmploader.h"
#include <stdio.h>

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	printf("File Not Found : %s\n",filename);
	return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
	printf("Error reading width from %s.\n", filename);
	return 0;
    }
    printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height 
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("Error reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("Error reading bpp from %s.\n", filename);
	return 0;
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    image->data = (char *) malloc(size);
	image->bpp = 3;
    if (image->data == NULL) {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
	return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	temp = image->data[i];
	image->data[i] = image->data[i+2];
	image->data[i+2] = temp;
    }
    
    // we're done.
    return 1;
}

int LoadRedImage(Image* image)
{
	if (image != 0)
	{
		image->sizeX = 64;
		image->sizeY = 64;
		image->bpp = 3;
		int size = 64 * 64 * image->bpp;
		image->data = (char*)malloc(size);
		
		for (int i = 0; i < (64 * 64); i++)
		{
			image->data[i*image->bpp] = (i%32) ? 155 : 255;
			image->data[i*image->bpp+1] = 0;
			image->data[i*image->bpp+2] = 0;
		}
	}
	return 1;
}

int LoadWadImage(Image* image, char* data)
{
	miptex_t* miptex = (miptex_t*)data;
	
	//printf("Miptex: %s, w=%i, h=%i\n", miptex->name, miptex->width, miptex->height);
	int size = miptex->width * miptex->height;
	
	byte* indices = (byte*)miptex + miptex->offsets[0];
	byte* palette = (byte*)miptex + miptex->offsets[3] + (size / 64) + 2;

	image->sizeX = miptex->width;
	image->sizeY = miptex->height;
    image->bpp = 4;
	image->data = (char*) malloc(size * image->bpp);
	
	int pos = 0;
	for (int i = 0; i < size; i++)
	{
		image->data[pos++] = palette[indices[i]*3];
		image->data[pos++] = palette[indices[i]*3 + 1];
		image->data[pos++] = palette[indices[i]*3 + 2];
		image->data[pos++] = 255;
	}
	return 1;
}
    
// Load Bitmaps And Convert To Textures
int LoadGLTextures(Image *image1)
{	
	GLuint id = 0;
    
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, image1->bpp, image1->sizeX, image1->sizeY, 0, image1->bpp==3?GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, image1->data);
	
    return id;
};
