#include "Font.h"

Font::Font()
{
	this->line_height = 10;
}

Font::~Font()
{
}

int Font::GetLineHeight()
{
	return this->line_height;
}
