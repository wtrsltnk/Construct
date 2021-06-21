#ifndef GAMEARGUMENTS_H_
#define GAMEARGUMENTS_H_

class GameArguments
{
protected:
	char* binpath;
	char* game;
	bool console; 
	bool changedispsettings;
	
	void SetArguments(int argc, char* argv[]);

	void SetBinPath(char* val);
	void SetGame(char* val);
	void SetConsole(bool val);
	void SetChangeDispSettings(bool val);
	
public:
	GameArguments(int argc, char* argv[]);
	virtual ~GameArguments();
	
	const char* BinPath();
	const char* Game();
	bool Console();
	bool ChangeDispSettings();
};

#endif /*GAMEARGUMENTS_H_*/
