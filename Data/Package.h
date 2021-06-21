#ifndef PACKAGE_H_
#define PACKAGE_H_

#include "DataBlock.h"
#include "DataFile.h"
#include <string.h>

class Package
{
private:
	class Item
	{
	public:
		Item(Item* next, int size, int offset, char* name) : next(next), size(size), offset(offset) { strcpy(this->name, name); }
		virtual ~Item() { }
		
		Item* next;
		int size;
		int offset;
		char name[16];
	};
	
protected:
	DataFile* pDataFile;
	int nItemCount;
	Item* pFirst;
	Item* pLast;
	
public:
	Package();
	virtual ~Package();
	
	void Setup(DataFile* file);

	bool AddPackageItem(int size, int offset, char* name);
	
	int GetItemCount();
	DataBlock* GetItem(int index);
	DataBlock* GetItem(char* name);
};

#endif /*PACKAGE_H_*/
