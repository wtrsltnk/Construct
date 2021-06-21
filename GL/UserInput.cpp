#include "UserInput.h"

UserInput::UserInput(tKeyMap* key_map)
{
	this->key_map = key_map;
	
	for (int i = 0; i < MAX_KEYS; i++)
	{
		this->key_state[i] = eUnpressed;
	}
}

UserInput::~UserInput()
{
}

void UserInput::ChangeKeyState(eKeys key, eKeyState state)
{
	this->key_state[key] = state;
	
	Hook* tmph = this->pFirstHook;
	while (tmph)
	{
		tmph->fpUserInputHook(key, state, this);
		tmph = tmph->next;
	}
}

void UserInput::ChangeKeyState(unsigned int mapped_key, bool pressed)
{
	if (mapped_key < this->key_map->mapsize)
	{
		ChangeKeyState(this->key_map->map[mapped_key], this->key_state[this->key_map->map[mapped_key]] = pressed ? ePressed : eUnpressed);
	}
}

eKeyState UserInput::GetKeyState(eKeys key)
{
	return this->key_state[key];
}

void UserInput::AddHook(FP_USERINPUTHOOK hook)
{
	Hook* h = new Hook();
	h->fpUserInputHook = *hook;
	h->next = this->pFirstHook;
	this->pFirstHook = h;
}
