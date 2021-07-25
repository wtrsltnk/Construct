#ifndef FONT_H_
#define FONT_H_

class Font
{
	protected:
		int line_height;
		
	public:
		Font();
		virtual ~Font();
		
        virtual void PrintText(int x, int y, const char* str, ...) = 0;
		int GetLineHeight();
		virtual void Destroy() = 0;
};

#endif /*FONT_H_*/
