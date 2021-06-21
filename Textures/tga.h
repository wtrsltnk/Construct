#ifndef TGA_H_
#define TGA_H_

#pragma pack(1)

typedef struct tTGAHeader
{
   char  idlength;
   char  colourmaptype;
   char  datatypecode;
   short int colourmaporigin;
   short int colourmaplength;
   char  colourmapdepth;
   short int x_origin;
   short int y_origin;
   short width;
   short height;
   char  bitsperpixel;
   char  imagedescriptor;
   
} tTGAHeader;

#endif /*TGA_H_*/
