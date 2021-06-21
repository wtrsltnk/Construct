#ifndef WORLDRENDERER_H_
#define WORLDRENDERER_H_

#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include "../World/World.h"

class WorldRenderer
{
public:
	WorldRenderer();
	virtual ~WorldRenderer();

	void SetupRenderer(array_t<3> *vertlist);
	void Render(tFace* firstface);
};

#endif /*WORLDRENDERER_H_*/
