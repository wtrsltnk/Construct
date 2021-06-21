#include "Data.h"

Data::Data()
{
	this->header = 0;
	this->models = 0;
	this->visibility = 0;
	this->lighting = 0;
	this->textures = 0;
	this->entities = 0;
	this->leafs = 0;
	this->planes = 0;
	this->nodes = 0;
	this->vertices = 0;
	this->edges = 0;
	this->faces = 0;
	this->texinfo = 0;
	this->clipnodes = 0;
	this->marksurfaces = 0;
	this->surfedges = 0;
	this->wads = 0;
	this->texs = 0;
}

Data::~Data()
{
	if (this->header != 0) delete this->header;
	if (this->models != 0) delete this->models;
	if (this->visibility != 0) delete this->visibility;
	if (this->lighting != 0) delete this->lighting;
	if (this->textures != 0) delete this->textures;
	if (this->entities != 0) delete this->entities;
	if (this->leafs != 0) delete this->leafs;
	if (this->planes != 0) delete this->planes;
	if (this->nodes != 0) delete this->nodes;
	if (this->vertices != 0) delete this->vertices;
	if (this->edges != 0) delete this->edges;
	if (this->faces != 0) delete this->faces;
	if (this->texinfo != 0) delete this->texinfo;
	if (this->clipnodes != 0) delete this->clipnodes;
	if (this->marksurfaces != 0) delete this->marksurfaces;
	if (this->surfedges != 0) delete this->surfedges;
	if (this->wads != 0) delete this->wads;
	if (this->texs != 0) delete this->texs;
	this->ents.Cleanup();
}
