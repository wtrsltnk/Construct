#ifndef CONSTRUCT_H_
#define CONSTRUCT_H_

#include "Controls/Window.h"
#include "TimeTicker.h"
#include "../GL/Win32Context.h"
#include "../GL/View.h"
#include "../GL/Camera.h"
#include "../GL/UserInput.h"
#include "../GL/WorldRenderer.h"
#include "../GL/Console.h"
#include "../World/World.h"
#include "../Common/GameArguments.h"

#include <memory>

typedef struct tVidProps
{
	int resx, resy;
	int bpp;
	bool fullscreen;
	
} tVidProps;

class Construct : public Window
{
protected:
	Win32Context context;
	TimeTicker ticker;
	View view;
	Camera cam;
    Font* font = nullptr;
    std::unique_ptr<UserInput> userinput = nullptr;
    Console* console = nullptr;
	World world;
	WorldRenderer renderer;

	virtual void PreShow();
	virtual void OnInitialize();
	virtual void OnIdle();
	virtual void OnDestroy();
	
    virtual LRESULT ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	static tKeyMap* GetWindowsKeyMap();
public:
	Construct();
	virtual ~Construct();
	
	void SetArguments(GameArguments* args);
	void SetVideoProps(tVidProps props);
};

#endif /*CONSTRUCT_H_*/
