#include <stdio.h>

//*
#include "Construct.h"
#include "DisplaySettings.h"
#include "../Common/GameRoot.h"
#include "../Common/Utility.h"

int main(int argc, char* argv[])
{
	GameArguments arguments(argc, argv);
	
	GameRoot::Initialize(Utility::GetFilePath(arguments.BinPath()));
	
	if (arguments.ChangeDispSettings())
	{
		DisplaySettings app;
		
		return app.RunApplication();
	}
	else
	{
		Construct app;
		
		app.SetArguments(&arguments);
		
		return app.RunGame();
	}
	
	return 0;
}

/*/

#include "../Common/Utility.h"

int main(int argc, char* argv[])
{
	Utility::Drive* drive = Utility::Drive::Open('c');
	printf(drive->GetDrive());
	
	Utility::Directory* dir = drive->GetSubDir("Windows");
	printf(dir->GetPath());
	
	return 0;
}

//*/
