//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// vis.cpp
//
// Copyright (C) 2001 - Jeffrey "botman" Broome
//
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
//
// See the GNU General Public License for more details at:
// http://www.gnu.org/copyleft/gpl.html
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "Visibility.h"

Visibility::Visibility()
{
   leaf_visibility = NULL;
}

Visibility::~Visibility()
{
	this->CleanupLeafs();
}

void Visibility::CleanupLeafs()
{
	if (leaf_visibility)
	{
		for (int i = 0; i < this->numleafs; i++)
		{
			if (leaf_visibility[i].leafs)
				free(leaf_visibility[i].leafs);
		}
		free(leaf_visibility);
		this->leaf_visibility = NULL;
	}
}

void Visibility::Decompress_VIS(int numleafs, dleaf_t *dleafs, dmodel_t *dmodels, byte *dvisdata)
{
    int count;
    int i, c, index;
    unsigned char bit;
    
    this->numleafs = numleafs;

    this->CleanupLeafs();
    this->leaf_visibility = (vis_leaf_t *)malloc(numleafs * sizeof(vis_leaf_t));

    if (this->leaf_visibility == NULL)
        Error("Error allocating memory for leaf visibility!\n");

    for (i = 0; i < numleafs; i++)
    {
        int v = dleafs[i].visofs;

        count = 0;

        // first count the number of visible leafs...
        for (c = 1; c < dmodels[0].visleafs; v++)
        {
            if (dvisdata[v] == 0)
            {
                v++;
                c += (dvisdata[v]<<3);
            }
            else
            {
                for (bit = 1; bit; bit<<=1,c++)
                {
                    if (dvisdata[v] & bit)
                       count++;
                }
            }
        }

        if (count > 0)
        {
            // allocate space to store the uncompressed VIS bit set...
        	this->leaf_visibility[i].leafs = (int *)malloc(count * sizeof(int));

            if (this->leaf_visibility[i].leafs == NULL)
                Error("Error allocating memory for leaf visibility!\n");
        }
        else
        	this->leaf_visibility[i].leafs = NULL;  // no leafs are visible

        this->leaf_visibility[i].num_leafs = count;
    }

    // now go through the VIS bit set again and store the VIS leafs...

    for (i=0; i < numleafs; i++)
    {
        int v = dleafs[i].visofs;

        index = 0;

        for (c = 1; c < dmodels[0].visleafs; v++)
        {
            if (dvisdata[v] == 0)
            {
                v++;
                c += (dvisdata[v]<<3);
            }
            else
            {
                for (bit = 1; bit; bit<<=1,c++)
                {
                    if (dvisdata[v] & bit)
                    {
                        if (this->leaf_visibility[i].leafs != NULL)
                        	this->leaf_visibility[i].leafs[index] = c;
                        index++;
                    }
                }
            }
        }
    }
}

int Visibility::GetNumVisLeafs()
{
	return this->numleafs;
}

vis_leaf_t& Visibility::VisLeaf(int index)
{
   return leaf_visibility[index];
}

