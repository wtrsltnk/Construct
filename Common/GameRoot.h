#ifndef GAMEROOT_H_
#define GAMEROOT_H_

#define DEFAULT_GAMENAME "wtr"

class GameRoot
{
private:
	static GameRoot* instance;
	
public:
	static bool Initialize(const char* gameroot, const char* gamename = 0);
	static GameRoot* GetInstance();
	
protected:
	char* gameroot;
	char* gamename;
	
	GameRoot(const char* gameroot, const char* gamename);
	
public:
	virtual ~GameRoot();

	const char* GetGameRoot();
	const char* GetGameName();
	char* FindEngineFile(char* filename);
	char* FindGameFile(char* filename);
};

#endif /*GAMEROOT_H_*/
