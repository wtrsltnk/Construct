#include "TextureList.h"

TextureList::TextureList()
{
	this->pFirst = 0;
	this->pLast = 0;
	this->nSize = 0;
}

TextureList::~TextureList()
{
	this->nSize = 0;
	while (this->pFirst != 0)
	{
		Item* tmp = this->pFirst->next;
		delete this->pFirst;
		this->pFirst = tmp;
	}
}

int TextureList::AddTexture(Texture* tex)
{
	if (tex != 0)
	{
		if (this->pFirst == 0)
		{
			this->pFirst = new Item(0, tex);
			this->pLast = this->pFirst;
		}
		else
		{
			this->pLast->next = new Item(0, tex);
			this->pLast = this->pLast->next;
		}
		
		return this->nSize++;
	}
	
	return -1;
}

int TextureList::Size()
{
	return this->nSize;
}

Texture* TextureList::GetTexture(int index)
{
	if (index >= 0 && index < this->nSize)
	{
		Item* item = this->pFirst;
		
		for (int i = 0; i < this->nSize; i++)
		{
			if (item == 0) break;
			item = item->next;
		}
		
		if (item != 0)
		{
			return item->tex;
		}
	}
	return 0;
}
