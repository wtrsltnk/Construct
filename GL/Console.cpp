#include "Console.h"
#include <string.h>

Console* Console::pInstance = 0;
UserInput* Console::pUserInput = 0;

Console* Console::Instance()
{
	if (Console::pInstance == 0)
	{
		Console::pInstance = new Console();
	}
	
	return Console::pInstance;
}

void Console::UserInputKey(eKeys e, eKeyState state, UserInput* pUI)
{
	Console::pUserInput = pUI;
	
	if (Console::pInstance != 0)
	{
		Console::pInstance->OnUserInput(e, state);
	}
}

Console::Console()
{
	this->pFirstEntry = 0;
	this->pInputEntry = new Entry();
	memset(this->pInputEntry->text, 0, 256);
	this->pFont = 0;
	this->focus = false;
	
	this->AddEntry("Console initialized!");
}

Console::~Console()
{
	while (this->pFirstEntry != 0)
	{
		Entry* tmp = this->pFirstEntry->next;
		delete this->pFirstEntry;
		this->pFirstEntry = tmp;
	}
	delete this->pInputEntry;
}

void Console::Render(int width, int height)
{
	if (this->focus)
	{
		if (height == 0) height = 1;
		
		::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		::glDisable(GL_TEXTURE_2D);
		::glColor3f(0.0f, 0.0f, 0.0f);
		
		::glBegin(GL_QUADS);
			::glVertex2i(0, 0);
			::glVertex2i(width, 0);
			::glVertex2i(width, height / 2);
			::glVertex2i(0, height / 2);
		::glEnd();
		
		if (this->pFont != 0)
		{
			::glColor3f(1.0f, 1.0f, 1.0f);
			
			Entry* tmp = this->pFirstEntry;
			int x = 10, y = (height / 2) - 10;
			
			this->pFont->PrintText(x, y, "%s", this->pInputEntry->text);
			y -= this->pFont->GetLineHeight();
			
			while ((tmp != 0) && (y > 0))
			{
				this->pFont->PrintText(x, y, "%s", tmp->text);
				y -= this->pFont->GetLineHeight();
				
				tmp = tmp->next;
			}
		}
	}
}

void Console::AddEntry(const char* entry)
{
	Entry* e = new Entry();
	strcpy(e->text, entry);
	e->next = this->pFirstEntry;
	e->iscommand = false;
	this->pFirstEntry = e;
}

void Console::OnUserInput(eKeys key, eKeyState state)
{
	if (state == ePressed)
	{
		if (key == KEY_RETURN || key == KEY_KP_ENTER)
		{
			this->SubmitInputEntry();
		}
		else if (key == KEY_BACKSPACE)
		{
			this->RemoveCharacter();
		}
		else if (key == KEY_SPACE)
		{
			this->AddCharacter(' ');
		}
		else if (key == KEY_TILDE)
		{
			this->focus = !this->focus;
		}
		else if (key >= KEY_0 && key <= KEY_9)
		{
			this->InputNumber(key);
		}
		else if (key >= KEY_A && key <= KEY_Z)
		{
			this->InputLetter(key);
		}
		else if (key >= KEY_SEMICOLON && key <= KEY_RBRACKET)
		{
			this->InputSpecialLetter(key);
		}
		else if (key >= KEY_KP_0 && key <= KEY_KP_DIVIDE)
		{
			this->InputKeyPad(key);
		}
	}
}

void Console::SubmitInputEntry()
{
	if (this->pInputEntry->cursor > 0)
	{
		this->pInputEntry->next = this->pFirstEntry;
		this->pFirstEntry = this->pInputEntry;
		this->pInputEntry = new Entry();
		memset(this->pInputEntry->text, 0, MAX_ENRTY_TEXT);
	}
}

void Console::InputNumber(eKeys key)
{
	char numbers[] = {
			'0', '1', '2', '3', '4',
			'5', '6', '7', '8', '9',
			')', '!', '@', '#', '$', 
			'%', '^', '&', '*', '('
			};
	int shift = 0;
	
	if (Console::pUserInput != 0)
	{
		if ((Console::pUserInput->GetKeyState(KEY_LSHIFT) == ePressed) || 
				(Console::pUserInput->GetKeyState(KEY_RSHIFT) == ePressed))
		{
			shift = 10;
		}
	}
	
	this->AddCharacter(numbers[key - KEY_0 + shift]);
}

void Console::InputLetter(eKeys key)
{
	char letters[] = { 	
			'a', 'b', 'c', 'd', 'e', 'f',
			'g', 'h', 'i', 'j', 'k', 'l', 
			'm', 'n', 'o', 'p', 'q', 'r',
			's', 't', 'u', 'v', 'w', 'x',
			'y', 'z' 
			};
	
	this->AddCharacter(letters[key - KEY_A]);
}

void Console::InputSpecialLetter(eKeys key)
{
	char specialletters[] = { 	
			';', ',', '.', '\'', '-',
			'\\', '`', '/', '=', '[', ']',
			':', '<', '>', '\"', '_',
			'|', '~', '?', '+', '{', '}'
			};
	int shift = 0;
	
	if (Console::pUserInput != 0)
	{
		if ((Console::pUserInput->GetKeyState(KEY_LSHIFT) == ePressed) || 
				(Console::pUserInput->GetKeyState(KEY_RSHIFT) == ePressed))
		{
			shift = 11;
		}
	}
	
	this->AddCharacter(specialletters[key - KEY_SEMICOLON + shift]);
}

void Console::InputKeyPad(eKeys key)
{
	char numbers[] = {
			'0', '1', '2', '3', '4',
			'5', '6', '7', '8', '9',
			'*', '+', '/', '-', '.',
			'/'
			};
	
	this->AddCharacter(numbers[key - KEY_KP_0]);
}

void Console::AddCharacter(char c)
{
	if (this->pInputEntry != 0 && this->pInputEntry->cursor < MAX_ENRTY_TEXT)
	{
		this->pInputEntry->text[this->pInputEntry->cursor++] = c;
	}
}

void Console::RemoveCharacter()
{
	if (this->pInputEntry != 0 && this->pInputEntry->cursor > 0)
	{
		this->pInputEntry->text[--this->pInputEntry->cursor] = '\0';
	}
}
