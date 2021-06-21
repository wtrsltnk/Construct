#include "PackageList.h"

PackageList::PackageList()
{
	this->pFirst = 0;
	this->pLast = 0;
	this->nSize = 0;
}

PackageList::~PackageList()
{
	this->nSize = 0;
	while (this->pFirst != 0)
	{
		Item* tmp = this->pFirst->next;
		delete this->pFirst;
		this->pFirst = tmp;
	}
}

int PackageList::AddPackage(Package* package)
{
	if (package != 0)
	{
		if (this->pFirst == 0)
		{
			this->pFirst = new Item(this->pFirst, package);
			this->pLast = this->pFirst;
		}
		else
		{
			this->pLast->next = new Item(0, package);
			this->pLast = this->pLast->next;
		}
		return this->nSize++;
	}
	
	return -1;
}

int PackageList::Size()
{
	return this->nSize;
}

Package* PackageList::GetPackage(int index)
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
			return item->pack;
		}
	}
	return 0;
}
