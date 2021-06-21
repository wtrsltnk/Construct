#include "BSPFile.h"

bool isWindowsApp = true;

int ArrayUsage( char *szItem, int items, int maxitems, int itemsize )
{
   float percentage = maxitems ? items * (float)100.0 / maxitems : (float)0.0;

   printf("%-12s  %7i/%-7i  %7i/%-7i  (%4.1f%%)", 
          szItem, items, maxitems, items * itemsize, maxitems * itemsize, percentage );
   if ( percentage > 80.0 )
      printf( "VERY FULL!\n" );
   else if ( percentage > 95.0 )
      printf( "SIZE DANGER!\n" );
   else if ( percentage > 99.9 )
      printf( "SIZE OVERFLOW!!!\n" );
   else
      printf( "\n" );
   return items * itemsize;
}

int GlobUsage( char *szItem, int itemstorage, int maxstorage )
{
   float percentage = maxstorage ? itemstorage * (float)100.0 / maxstorage : (float)0.0;
   printf("%-12s     [variable]    %7i/%-7i  (%4.1f%%)", 
          szItem, itemstorage, maxstorage, percentage );
   if ( percentage > 80.0 )
      printf( "VERY FULL!\n" );
   else if ( percentage > 95.0 )
      printf( "SIZE DANGER!\n" );
   else if ( percentage > 99.9 )
      printf( "SIZE OVERFLOW!!!\n" );
   else
      printf( "\n" );
   return itemstorage;
}

bool BSPFile::LoadBSP(char *bspname)
{
	   int   i;

	//
	// load the file header
	//
	   LoadFile (bspname, (void **)&header);

	// swap the header
	   for (i=0 ; i< (int)sizeof(dheader_t)/4 ; i++)
	      ((int *)header)[i] = LittleLong ( ((int *)header)[i]);

	   if (header->version != BSPVERSION)
	      Error ("%s is version %i, not %i", bspname, header->version, BSPVERSION);

	   nummodels = CopyLump (LUMP_MODELS, (void **)&dmodels, sizeof(dmodel_t));
	   numvertexes = CopyLump (LUMP_VERTEXES, (void **)&dvertexes, sizeof(dvertex_t));
	   numplanes = CopyLump (LUMP_PLANES, (void **)&dplanes, sizeof(dplane_t));
	   numleafs = CopyLump (LUMP_LEAFS, (void **)&dleafs, sizeof(dleaf_t));
	   numnodes = CopyLump (LUMP_NODES, (void **)&dnodes, sizeof(dnode_t));
	   numtexinfo = CopyLump (LUMP_TEXINFO, (void **)&texinfo, sizeof(texinfo_t));
	   numclipnodes = CopyLump (LUMP_CLIPNODES, (void **)&dclipnodes, sizeof(dclipnode_t));
	   numfaces = CopyLump (LUMP_FACES, (void **)&dfaces, sizeof(dface_t));
	   nummarksurfaces = CopyLump (LUMP_MARKSURFACES, (void **)&dmarksurfaces, sizeof(dmarksurfaces[0]));
	   numsurfedges = CopyLump (LUMP_SURFEDGES, (void **)&dsurfedges, sizeof(dsurfedges[0]));
	   numedges = CopyLump (LUMP_EDGES, (void **)&dedges, sizeof(dedge_t));

	   texdatasize = CopyLump (LUMP_TEXTURES, (void **)&dtexdata, 1);
	   visdatasize = CopyLump (LUMP_VISIBILITY, (void **)&dvisdata, 1);
	   lightdatasize = CopyLump (LUMP_LIGHTING, (void **)&dlightdata, 1);
	   entdatasize = CopyLump (LUMP_ENTITIES, (void **)&dentdata, 1);
	        
	//
	// swap everything
	//
	   SwapBSPFile (false);
	   return true;
}

void BSPFile::WriteBSPFile (char *bspname)
{
   dheader_t *header = &outheader;
   
   memset (header, 0, sizeof(dheader_t));

   SwapBSPFile (true);

   header->version = LittleLong (BSPVERSION);

   FILE* bspfile = SafeOpenWrite (bspname);
   SafeWrite (bspfile, header, sizeof(dheader_t)); // overwritten later

   AddLump (LUMP_PLANES, dplanes, numplanes*sizeof(dplane_t), bspfile);
   AddLump (LUMP_LEAFS, dleafs, numleafs*sizeof(dleaf_t), bspfile);
   AddLump (LUMP_VERTEXES, dvertexes, numvertexes*sizeof(dvertex_t), bspfile);
   AddLump (LUMP_NODES, dnodes, numnodes*sizeof(dnode_t), bspfile);
   AddLump (LUMP_TEXINFO, texinfo, numtexinfo*sizeof(texinfo_t), bspfile);
   AddLump (LUMP_FACES, dfaces, numfaces*sizeof(dface_t), bspfile);
   AddLump (LUMP_CLIPNODES, dclipnodes, numclipnodes*sizeof(dclipnode_t), bspfile);
   AddLump (LUMP_MARKSURFACES, dmarksurfaces, nummarksurfaces*sizeof(dmarksurfaces[0]), bspfile);
   AddLump (LUMP_SURFEDGES, dsurfedges, numsurfedges*sizeof(dsurfedges[0]), bspfile);
   AddLump (LUMP_EDGES, dedges, numedges*sizeof(dedge_t), bspfile);
   AddLump (LUMP_MODELS, dmodels, nummodels*sizeof(dmodel_t), bspfile);

   AddLump (LUMP_LIGHTING, dlightdata, lightdatasize, bspfile);
   AddLump (LUMP_VISIBILITY, dvisdata, visdatasize, bspfile);
   AddLump (LUMP_ENTITIES, dentdata, entdatasize, bspfile);
   AddLump (LUMP_TEXTURES, dtexdata, texdatasize, bspfile);

   fseek (bspfile, 0, SEEK_SET);
   SafeWrite (bspfile, header, sizeof(dheader_t));
   fclose (bspfile);
}

void BSPFile::PrintBSPFileSizes (void)
{
   //int numtextures = texdatasize ? ((dmiptexlump_t*)dtexdata)->nummiptex : 0;
   int totalmemory = 0;

   printf("\n");
   printf("Object names  Objects/Maxobjs  Memory / Maxmem  Fullness\n" );
   printf("------------  ---------------  ---------------  --------\n" );

   totalmemory += ArrayUsage( "models", nummodels, MAX_MAP_MODELS, sizeof(dmodel_t) );
   totalmemory += ArrayUsage( "planes", numplanes, MAX_MAP_PLANES, sizeof(dplane_t) );
   totalmemory += ArrayUsage( "vertexes", numvertexes, MAX_MAP_VERTS, sizeof(dvertex_t) );
   totalmemory += ArrayUsage( "nodes", numnodes, MAX_MAP_NODES, sizeof(dnode_t) );
   totalmemory += ArrayUsage( "texinfos", numtexinfo, MAX_MAP_TEXINFO, sizeof(texinfo_t) );
   totalmemory += ArrayUsage( "faces", numfaces, MAX_MAP_FACES, sizeof(dface_t) );
   totalmemory += ArrayUsage( "clipnodes", numclipnodes, MAX_MAP_CLIPNODES, sizeof(dclipnode_t) );
   totalmemory += ArrayUsage( "leaves", numleafs, MAX_MAP_LEAFS, sizeof(dleaf_t) );
   totalmemory += ArrayUsage( "marksurfaces", nummarksurfaces, MAX_MAP_MARKSURFACES, sizeof(unsigned short) );
   totalmemory += ArrayUsage( "surfedges", numsurfedges, MAX_MAP_SURFEDGES, sizeof(int) );
   totalmemory += ArrayUsage( "edges", numedges, MAX_MAP_EDGES, sizeof(dedge_t) );

   totalmemory += GlobUsage( "texdata", texdatasize, MAX_MAP_MIPTEX );
   totalmemory += GlobUsage( "lightdata", lightdatasize, MAX_MAP_LIGHTING );
   totalmemory += GlobUsage( "visdata", visdatasize, MAX_MAP_VISIBILITY );
   totalmemory += GlobUsage( "entdata", entdatasize, MAX_MAP_ENTSTRING );

   printf( "=== Total BSP file data space used: %d bytes ===\n", totalmemory );
}

int BSPFile::CopyLump(int lump, void **dest, int size)
{
   int   length, ofs;
   int   num;

   length = header->lumps[lump].filelen;
   ofs = header->lumps[lump].fileofs;

   if (length % size)
      Error ("LoadBSPFile: odd lump size");

   num = length / size;

   if (*dest == NULL)
   {
      // allocate memory for this lump...
      *dest = malloc(num * size);

      if (*dest == NULL)
         Error("Error allocating memory for BSP file lump!\n");
   }

   memcpy (*dest, (byte *)header + ofs, length);

   return num;
}

void BSPFile::AddLump (int lumpnum, void *data, int len, FILE* bspfile)
{
   lump_t *lump;

   lump = &header->lumps[lumpnum];

   lump->fileofs = LittleLong( ftell(bspfile) );
   lump->filelen = LittleLong(len);
   SafeWrite (bspfile, data, (len+3)&~3);
}


void BSPFile::SwapBSPFile (qboolean todisk)
{
   int   i, j, c;
   dmodel_t *d;
   dmiptexlump_t  *mtl;


// models
   for (i=0 ; i<nummodels ; i++)
   {
      d = &dmodels[i];

      for (j=0 ; j<MAX_MAP_HULLS ; j++)
         d->headnode[j] = LittleLong (d->headnode[j]);

      d->visleafs = LittleLong (d->visleafs);
      d->firstface = LittleLong (d->firstface);
      d->numfaces = LittleLong (d->numfaces);
        
      for (j=0 ; j<3 ; j++)
      {
         d->mins[j] = LittleFloat(d->mins[j]);
         d->maxs[j] = LittleFloat(d->maxs[j]);
         d->origin[j] = LittleFloat(d->origin[j]);
      }
   }

//
// vertexes
//
   for (i=0 ; i<numvertexes ; i++)
   {
      for (j=0 ; j<3 ; j++)
         dvertexes[i].point[j] = LittleFloat (dvertexes[i].point[j]);
   }
        
//
// planes
//
   for (i=0 ; i<numplanes ; i++)
   {
      for (j=0 ; j<3 ; j++)
         dplanes[i].normal[j] = LittleFloat (dplanes[i].normal[j]);
      dplanes[i].dist = LittleFloat (dplanes[i].dist);
      dplanes[i].type = LittleLong (dplanes[i].type);
   }

//
// texinfos
//
   for (i=0 ; i<numtexinfo ; i++)
   {
      for (j=0 ; j<8 ; j++)
         texinfo[i].vecs[0][j] = LittleFloat (texinfo[i].vecs[0][j]);
      texinfo[i].miptex = LittleLong (texinfo[i].miptex);
      texinfo[i].flags = LittleLong (texinfo[i].flags);
   }

//
// faces
//
   for (i=0 ; i<numfaces ; i++)
   {
      dfaces[i].texinfo = LittleShort (dfaces[i].texinfo);
      dfaces[i].planenum = LittleShort (dfaces[i].planenum);
      dfaces[i].side = LittleShort (dfaces[i].side);
      dfaces[i].lightofs = LittleLong (dfaces[i].lightofs);
      dfaces[i].firstedge = LittleLong (dfaces[i].firstedge);
      dfaces[i].numedges = LittleShort (dfaces[i].numedges);
   }

//
// nodes
//
   for (i=0 ; i<numnodes ; i++)
   {
      dnodes[i].planenum = LittleLong (dnodes[i].planenum);
      for (j=0 ; j<3 ; j++)
      {
         dnodes[i].mins[j] = LittleShort (dnodes[i].mins[j]);
         dnodes[i].maxs[j] = LittleShort (dnodes[i].maxs[j]);
      }
      dnodes[i].children[0] = LittleShort (dnodes[i].children[0]);
      dnodes[i].children[1] = LittleShort (dnodes[i].children[1]);
      dnodes[i].firstface = LittleShort (dnodes[i].firstface);
      dnodes[i].numfaces = LittleShort (dnodes[i].numfaces);
   }

//
// leafs
//
   for (i=0 ; i<numleafs ; i++)
   {
      dleafs[i].contents = LittleLong (dleafs[i].contents);
      for (j=0 ; j<3 ; j++)
      {
         dleafs[i].mins[j] = LittleShort (dleafs[i].mins[j]);
         dleafs[i].maxs[j] = LittleShort (dleafs[i].maxs[j]);
      }

      dleafs[i].firstmarksurface = LittleShort (dleafs[i].firstmarksurface);
      dleafs[i].nummarksurfaces = LittleShort (dleafs[i].nummarksurfaces);
      dleafs[i].visofs = LittleLong (dleafs[i].visofs);
   }

//
// clipnodes
//
   for (i=0 ; i<numclipnodes ; i++)
   {
      dclipnodes[i].planenum = LittleLong (dclipnodes[i].planenum);
      dclipnodes[i].children[0] = LittleShort (dclipnodes[i].children[0]);
      dclipnodes[i].children[1] = LittleShort (dclipnodes[i].children[1]);
   }

//
// miptex
//
   if (texdatasize)
   {
      mtl = (dmiptexlump_t *)dtexdata;
      if (todisk)
         c = mtl->nummiptex;
      else
         c = LittleLong(mtl->nummiptex);
      mtl->nummiptex = LittleLong (mtl->nummiptex);
      for (i=0 ; i<c ; i++)
         mtl->dataofs[i] = LittleLong(mtl->dataofs[i]);
   }

//
// marksurfaces
//
   for (i=0 ; i<nummarksurfaces ; i++)
      dmarksurfaces[i] = LittleShort (dmarksurfaces[i]);

//
// surfedges
//
   for (i=0 ; i<numsurfedges ; i++)
      dsurfedges[i] = LittleLong (dsurfedges[i]);

//
// edges
//
   for (i=0 ; i<numedges ; i++)
   {
      dedges[i].v[0] = LittleShort (dedges[i].v[0]);
      dedges[i].v[1] = LittleShort (dedges[i].v[1]);
   }
}

BSPFile::BSPFile()
{
	this->nummodels = 0;
	this->dmodels = 0;

	this->visdatasize = 0;
	this->dvisdata = 0;

	this->lightdatasize = 0;
	this->dlightdata = 0;

	this->texdatasize = 0;
	this->dtexdata = 0;

	this->entdatasize = 0;
	this->dentdata = 0;

	this->numleafs = 0;
	this->dleafs = 0;

	this->numplanes = 0;
	this->dplanes = 0;

	this->numvertexes = 0;
	this->dvertexes = 0;

	this->numnodes = 0;
	this->dnodes = 0;

	this->numtexinfo = 0;
	this->texinfo = 0;

	this->numfaces = 0;
	this->dfaces = 0;

	this->numclipnodes = 0;
	this->dclipnodes = 0;

	this->numedges = 0;
	this->dedges = 0;

	this->nummarksurfaces = 0;
	this->dmarksurfaces = 0;

	this->numsurfedges = 0;
	this->dsurfedges = 0;
}

BSPFile::~BSPFile()
{
	this->Cleanup();
}

void BSPFile::Cleanup()
{
	if (this->dmodels != 0)
	{
		free(this->dmodels);
		this->nummodels = 0;
		this->dmodels = 0;
	}

	if (this->dvisdata != 0)
	{
		free(this->dvisdata);
		this->visdatasize = 0;
		this->dvisdata = 0;
	}

	if (this->dlightdata != 0)
	{
		free(this->dlightdata);
		this->lightdatasize = 0;
		this->dlightdata = 0;
	}

	if (this->dtexdata != 0)
	{
		free(this->dtexdata);
		this->texdatasize = 0;
		this->dtexdata = 0;
	}

	if (this->dentdata != 0)
	{
		free(this->dentdata);
		this->entdatasize = 0;
		this->dentdata = 0;
	}

	if (this->dleafs != 0)
	{
		free(this->dleafs);
		this->numleafs = 0;
		this->dleafs = 0;
	}

	if (this->dplanes != 0)
	{
		free(this->dplanes);
		this->numplanes = 0;
		this->dplanes = 0;
	}

	if (this->dvertexes != 0)
	{
		free(this->dvertexes);
		this->numvertexes = 0;
		this->dvertexes = 0;
	}

	if (this->dnodes != 0)
	{
		free(this->dnodes);
		this->numnodes = 0;
		this->dnodes = 0;
	}

	if (this->texinfo != 0)
	{
		free(this->texinfo);
		this->numtexinfo = 0;
		this->texinfo = 0;
	}

	if (this->dfaces != 0)
	{
		free(this->dfaces);
		this->numfaces = 0;
		this->dfaces = 0;
	}

	if (this->dclipnodes != 0)
	{
		free(this->dclipnodes);
		this->numclipnodes = 0;
		this->dclipnodes = 0;
	}

	if (this->dedges != 0)
	{
		free(this->dedges);
		this->numedges = 0;
		this->dedges = 0;
	}

	if (this->dmarksurfaces != 0)
	{
		free(this->dmarksurfaces);
		this->nummarksurfaces = 0;
		this->dmarksurfaces = 0;
	}

	if (this->dsurfedges != 0)
	{
		free(this->dsurfedges);
		this->numsurfedges = 0;
		this->dsurfedges = 0;
	}
}
