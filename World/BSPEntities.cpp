#include "BSPEntities.h"	

int BSPEntities::ParseEntities(char* data, int datasize)
{
	Tokenizer tok;
	
	tok.Setup(data, datasize);
	this->numentities = 0;
	
	while (this->ParseEntity(&tok))
	{ }
	
	return this->numentities;
}

bool BSPEntities::ParseEntity(Tokenizer* tok)
{
	char *token = (char*)malloc(sizeof(char) * MAX_TOKEN_SIZE);
	
    if ((tok->GetToken(&token) != TOKEN_READY)
        || (strcmp(token, "{") != 0)
        || (this->numentities >= MAX_ENTITIES))
    {
        free(token);
        return false;
    }

    entity_t* ent = &this->entities[this->numentities++];

    do
    {
        if (strcmp(token, "}") == 0)
            break;

        epair_t* e = this->ParseEpair(tok);

        if (e != 0)
        {
            e->next = ent->epairs;
            ent->epairs = e;
        }
    }
    while (tok->GetToken((char**)&token) == TOKEN_READY);

    free(token);

    return true;
}

epair_t* BSPEntities::ParseEpair(Tokenizer* tok)
{
	char *token = (char*)malloc(sizeof(char) * MAX_TOKEN_SIZE);
	epair_t* result = (epair_t*)malloc(sizeof(epair_t));
	memset(result, 0, sizeof(epair_t));

	if (tok->GetToken(&token) == TOKEN_READY)
	{
		result->key = copystring(token);
	}
	if (tok->GetToken(&token) == TOKEN_READY)
	{
		result->value = copystring(token);
	}
	
	free(token);
	return result;
}

entity_t* BSPEntities::Entities()
{
	return this->entities;
}

int BSPEntities::EntityCount()
{
	return this->numentities;
}

entity_t* BSPEntities::FindEntityByClassName(const char* classname)
{
	if (classname != 0)
	{
		for (int i = 0; i < this->numentities; i++)
		{
			epair_t* e = this->entities[i].epairs;
			
			while ((e != 0) && (strcmp(e->key, "classname") != 0))
			{
				e = e->next;
			}
			
			if (e != 0 && strcmp(e->value, classname) == 0)
			{
				return &this->entities[i];
			}
		}
	}
	return 0;
}

const char* BSPEntities::FindEntityValue(entity_t* ent, const char* key)
{
	epair_t* e = ent->epairs;
	
	while ((e != 0) && (strcmp(e->key, key) != 0))
	{
		e = e->next;
	}
	
	if(e != 0)
	{
		return e->value;
	}
	
	return "";
}

BSPEntities::BSPEntities()
{
	this->numentities = 0;
}

BSPEntities::~BSPEntities()
{
	this->Cleanup();
}

void BSPEntities::Cleanup()
{
	for (int i = 0; i < this->numentities; i++)
	{
		epair_t* first = this->entities[i].epairs;
		
		while (first != 0)
		{
			epair_t* tmp = first;
			
			free(first->key);
			free(first->value);
			first = first->next;
			free(tmp);
		}
	}
	
	this->numentities = 0;
}
