#ifndef PACKAGELIST_H_
#define PACKAGELIST_H_

#include "Package.h"

class PackageList
{
private:
	class Item
	{
	public:
		Item(Item* next, Package* pack) : next(next), pack(pack) { }
		virtual ~Item() { }
		
		Item* next;
		Package* pack;
	};
	
protected:
	int nSize;
	Item* pFirst;
	Item* pLast;
	
public:
	PackageList();
	virtual ~PackageList();
	
	int AddPackage(Package* package);
	
	int Size();
	Package* GetPackage(int index);
};

#endif /*PACKAGELIST_H_*/
