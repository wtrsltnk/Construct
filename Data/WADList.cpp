#include "WADList.h"

WADList::WADList()
{
	this->pFirst = 0;
	this->pLast = 0;
	this->nSize = 0;
}

WADList::~WADList()
{
	while (this->pFirst != 0)
	{
		Item* tmp = this->pFirst->next;
		delete this->pFirst->wad;
		delete this->pFirst;
		this->pFirst = tmp;
	}
}

int WADList::AddWAD(WADFile* wad)
{
	if (wad != 0)
	{
		if (this->pFirst == 0)
		{
			this->pFirst = new Item(0, wad);
			this->pLast = this->pFirst;
		}
		else
		{
			this->pLast->next = new Item(0, wad);
			this->pLast = this->pLast->next;
		}
		
		return this->nSize++;
	}
	
	return -1;
}

int WADList::Size()
{
	return this->nSize;
}

WADFile* WADList::GetWAD(int index)
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
			return item->wad;
		}
	}
	return 0;
}
