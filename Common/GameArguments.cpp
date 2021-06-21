#include "GameArguments.h"
#include <string.h>
#include <stdio.h>

GameArguments::GameArguments(int argc, char* argv[])
{
	this->SetBinPath("");
	this->SetGame("");
	this->SetConsole(false);
	this->SetChangeDispSettings(false);
	this->SetArguments(argc, argv);
}

GameArguments::~GameArguments()
{
	if (this->binpath != 0)
	{
		delete [] this->binpath;
		this->binpath = 0;
	}
	if (this->game != 0)
	{
		delete [] this->game;
		this->game = 0;
	}
}

void GameArguments::SetArguments(int argc, char* argv[])
{
	if (argc >= 1)
	{
		this->SetBinPath(argv[0]);
		
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-game") == 0)
			{
				if (argc >= (i+1))
				{
					this->SetGame(argv[i+1]);
				}
			}
			else if (strcmp(argv[i], "-console") == 0)
			{
				this->SetConsole(true);
			}
			else if (strcmp(argv[i], "-changedispsettings") == 0)
			{
				this->SetChangeDispSettings(true);
			}
		}
	}
}

void GameArguments::SetBinPath(char* val)
{
	if (val == 0) val = "";
	if (this->binpath != 0) delete [] this->binpath;
	
	this->binpath = new char[strlen(val) + 1];
	strcpy(this->binpath, val);
}

void GameArguments::SetGame(char* val)
{
	if (val == 0) val = "";
	if (this->game != 0) delete [] this->game;
	
	this->game = new char[strlen(val) + 1];
	strcpy(this->game, val);
}

void GameArguments::SetConsole(bool val)
{
	this->console = val;
}

void GameArguments::SetChangeDispSettings(bool val)
{
	this->changedispsettings = val;
}

const char* GameArguments::BinPath()
{
	return this->binpath;
}

const char* GameArguments::Game()
{
	return this->game;
}

bool GameArguments::Console()
{
	return this->console;
}

bool GameArguments::ChangeDispSettings()
{
	return this->changedispsettings;
}
