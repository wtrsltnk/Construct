#include "GameRoot.h"
#include "../Common/Utility.h"
#include <string.h>
#include <stdio.h>

GameRoot* GameRoot::instance = 0;

bool GameRoot::Initialize(const char* gameroot, const char* gamename)
{
	if (GameRoot::instance != 0)
		return false;
	
	GameRoot::instance = new GameRoot(gameroot, gamename);
	
	return true;
}

GameRoot* GameRoot::GetInstance()
{
	return GameRoot::instance;
}

const char* GameRoot::GetGameRoot()
{
	return this->gameroot;
}

const char* GameRoot::GetGameName()
{
	return this->gamename;
}

char* GameRoot::FindEngineFile(char* filename)
{
	static char result[256] = { 0 };
	
	sprintf(result, "%s\\%s", this->gameroot, filename);
	if (Utility::File::Exists(result))
	{
		return result;
	}
	return 0;
}

char* GameRoot::FindGameFile(char* filename)
{
	static char result[256] = { 0 };
	
	sprintf(result, "%s\\%s\\%s", this->gameroot, this->gamename, filename);
	if (Utility::File::Exists(result))
	{
		return result;
	}
	
	sprintf(result, "%s\\%s\\%s", this->gameroot, DEFAULT_GAMENAME, filename);
	if (Utility::File::Exists(result))
	{
		return result;
	}
	return 0;
}

GameRoot::GameRoot(const char* gameroot, const char* gamename)
{
	if (gamename == 0) gamename = DEFAULT_GAMENAME;
	
	this->gameroot = new char[strlen(gameroot)+1];
	strcpy(this->gameroot, gameroot);
	
	this->gamename = new char[strlen(gamename)+1];
	strcpy(this->gamename, gamename);
}

GameRoot::~GameRoot()
{
	delete [] this->gameroot;
	delete [] this->gamename;
}
