#include "GameArguments.h"
#include <stdio.h>
#include <string.h>

GameArguments::GameArguments(int argc, char *argv[])
{
    this->SetBinPath("");
    this->SetGame("");
    this->SetConsole(false);
    this->SetChangeDispSettings(false);
    this->SetArguments(argc, argv);
}

GameArguments::~GameArguments()
{}

void GameArguments::SetArguments(int argc, char *argv[])
{
    if (argc >= 1)
    {
        this->SetBinPath(argv[0]);

        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-game") == 0)
            {
                if (argc >= (i + 1))
                {
                    this->SetGame(argv[i + 1]);
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

void GameArguments::SetBinPath(const char *val)
{
    if (val == nullptr) val = "";

    this->binpath = val;
}

void GameArguments::SetGame(const char *val)
{
    if (val == nullptr) val = "";

    this->game = val;
}

void GameArguments::SetConsole(bool val)
{
    this->console = val;
}

void GameArguments::SetChangeDispSettings(bool val)
{
    this->changedispsettings = val;
}

const char *GameArguments::BinPath()
{
    return this->binpath.c_str();
}

const char *GameArguments::Game()
{
    return this->game.c_str();
}

bool GameArguments::Console()
{
    return this->console;
}

bool GameArguments::ChangeDispSettings()
{
    return this->changedispsettings;
}
