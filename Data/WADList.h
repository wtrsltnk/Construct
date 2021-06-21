#ifndef WADLIST_H_
#define WADLIST_H_

#include "../World/WADFile.h"

class WADList
{
private:
	class Item
	{
	public:
		Item(Item* next, WADFile* wad) : next(next), wad(wad) { }
		virtual ~Item() { }
		
		Item* next;
		WADFile* wad;
	};

protected:
	int nSize;
	Item* pFirst;
	Item* pLast;
	
public:
	WADList();
	virtual ~WADList();
	
	int AddWAD(WADFile* wad);
	
	int Size();
	WADFile* GetWAD(int index);
};

#endif /*WADLIST_H_*/
