#ifndef BSPENTITIES_H_
#define BSPENTITIES_H_

#include "ent.h"
#include "../Common/Tokenizer.h"
#include "../Common/cmdlib.h"

class BSPEntities
{
protected:
	int numentities;
	entity_t entities[MAX_ENTITIES];
	
	bool ParseEntity(Tokenizer* tok);
	epair_t* ParseEpair(Tokenizer* tok);
	
public:
	BSPEntities();
	virtual ~BSPEntities();
	
	int ParseEntities(char* data, int datasize);
	
	entity_t* Entities();
	int EntityCount();
	
	entity_t* FindEntityByClassName(const char* classname);
	static const char* FindEntityValue(entity_t* ent, const char* key);
	
	void Cleanup();
};

#endif /*BSPENTITIES_H_*/
