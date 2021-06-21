#include "WorldRenderer.h"

WorldRenderer::WorldRenderer()
{
}

WorldRenderer::~WorldRenderer()
{
}

void WorldRenderer::SetupRenderer(array_t<3> *vertlist)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (GLfloat*)*vertlist);
}

void WorldRenderer::Render(tFace* firstface)
{
	while (firstface != 0)
	{
		glDrawArrays(firstface->type, firstface->first, firstface->count);
		firstface = firstface->next;
	}
}
