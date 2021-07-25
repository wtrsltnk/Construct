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
    return this->gameroot.c_str();
}

const char* GameRoot::GetGameName()
{
    return this->gamename.c_str();
}

char* GameRoot::FindEngineFile(const char* filename)
{
	static char result[256] = { 0 };

    sprintf_s(result, 256, "%s\\%s", this->gameroot.c_str(), filename);
	if (Utility::File::Exists(result))
	{
		return result;
	}

    return 0;
}

char* GameRoot::FindGameFile(const char* filename)
{
	static char result[256] = { 0 };
	
    sprintf_s(result, 256, "%s\\%s\\%s", this->gameroot.c_str(), this->gamename.c_str(), filename);
	if (Utility::File::Exists(result))
	{
		return result;
	}
	
    sprintf_s(result, 256, "%s\\%s\\%s", this->gameroot.c_str(), DEFAULT_GAMENAME, filename);
	if (Utility::File::Exists(result))
	{
		return result;
	}
	return 0;
}

GameRoot::GameRoot(const char* gameroot, const char* gamename)
{
    if (gamename == 0) gamename = DEFAULT_GAMENAME;

    this->gameroot = gameroot;

    this->gamename = gamename;
}

GameRoot::~GameRoot() = default;
