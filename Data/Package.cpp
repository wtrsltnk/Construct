#include "Package.h"

Package::Package()
{
	this->pDataFile = 0;
	this->nItemCount = 0;
	this->pFirst = 0;
}

Package::~Package()
{
	if (this->pDataFile != 0)
	{
		this->pDataFile->CloseFile();
		delete this->pDataFile;
		this->pDataFile = 0;
	}
	
	this->nItemCount = 0;
	
	while (this->pFirst != 0)
	{
		Item* tmp = this->pFirst->next;
		delete this->pFirst;
		this->pFirst = tmp;
	}
}

void Package::Setup(DataFile* file)
{
	this->pDataFile = file;
}

bool Package::AddPackageItem(int size, int offset, char* name)
{
	if ((offset + size) >= this->pDataFile->Size())
	{
		if (this->pFirst == 0)
		{
			this->pFirst = new Item(0, size, offset, name);
			this->pLast = this->pFirst;
		}
		else
		{
			this->pLast->next = new Item(0, size, offset, name);
			this->pLast = this->pLast->next;
		}
		this->nItemCount++;
		
		return false;
	}
	return false;
}

DataBlock* Package::GetItem(int index)
{
	Item* item = this->pFirst;
	
	for (int i = 0; i < this->nItemCount; i++)
	{
		if (item == 0) break;
		item = item->next;
	}
	
	if (item != 0)
	{
		return this->pDataFile->ReadDataBlock(item->size, item->offset);
	}
	return 0;
}

DataBlock* Package::GetItem(char* name)
{
	Item* item = this->pFirst;
	
	while (item != 0)
	{
		if (strncmp(item->name, name, 16) == 0)
		{
			return this->pDataFile->ReadDataBlock(item->size, item->offset);
		}
	}
	return 0;
}

int Package::GetItemCount()
{
	return this->nItemCount;
}
