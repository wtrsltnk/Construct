#ifndef GAMEARGUMENTS_H_
#define GAMEARGUMENTS_H_

#include <string>

class GameArguments
{
protected:
    std::string binpath;
    std::string game;
    bool console;
    bool changedispsettings;

    void SetArguments(int argc, char *argv[]);

    void SetBinPath(const char *val);
    void SetGame(const char *val);
    void SetConsole(bool val);
    void SetChangeDispSettings(bool val);

public:
    GameArguments(int argc, char *argv[]);
    virtual ~GameArguments();

    const char *BinPath();
    const char *Game();
    bool Console();
    bool ChangeDispSettings();
};

#endif /*GAMEARGUMENTS_H_*/
