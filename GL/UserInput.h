#ifndef USERINPUT_H_
#define USERINPUT_H_

#include "keys.h"

class UserInput;

typedef void (*FP_USERINPUTHOOK)(eKeys key, eKeyState newstate, UserInput* pUI);

class UserInput
{
private:
	class Hook
	{
	public:
		FP_USERINPUTHOOK fpUserInputHook;
		Hook* next;
	};
protected:
	eKeyState key_state[MAX_KEYS];
	tKeyMap* key_map;
	
	Hook* pFirstHook;
	
public:
	UserInput(tKeyMap* key_map);
	virtual ~UserInput();

	void ChangeKeyState(eKeys key, eKeyState state);
	void ChangeKeyState(unsigned int mapped_key, bool pressed);
	eKeyState GetKeyState(eKeys key);
	
	void AddHook(FP_USERINPUTHOOK hook);
};

#endif /*USERINPUT_H_*/
