/*  #define IBM_MakePlant   */
/*  #define IBM_DrawLeaf    */
/*                       */
/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
#define EXT extern 
#include "gamedefs.h"
/*---------------------------------------------------------------------
 * MakePlant()
 *---------------------------------------------------------------------
 */
void MakePlant(num)
{
#if !defined(IBM_MakePlant)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
if(xmas)
	{
	MakePrism(&Robot[PLANT][0],&Object[num].where,0);
	MakePrism(&Robot[PLANT][1],&Object[num].where,0);
	if(Robot[PLANT][0].visible)
		{
		DrawPrism(&Robot[PLANT][0],0);
		DrawPrism(&Robot[PLANT][1],0);
		}
	}
else 
	{
	MakePrism(&Robot[PLANT][0],&Object[num].where,0);
	MakePrism(&Robot[PLANT][1],&Object[num].where,0);
	MakePrism(&Robot[PLANT][2],&Object[num].where,0);
	MakePrism(&Robot[PLANT][3],&Object[num].where,0);
	MakePrism(&Robot[PLANT][4],&Object[num].where,0);
	MakePrism(&Robot[PLANT][5],&Object[num].where,0);
	MakePrism(&Robot[PLANT][6],&Object[num].where,0);
	MakePrism(&Robot[PLANT][7],&Object[num].where,0);
	if(Robot[PLANT][0].visible)
		{
		DrawPrism(&Robot[PLANT][1],0);
		PenColor(realcolor[vGREEN]);
		DrawLeaf(&Robot[PLANT][2],0);
		DrawLeaf(&Robot[PLANT][3],0);
		DrawLeaf(&Robot[PLANT][4],0);
		DrawLeaf(&Robot[PLANT][5],0);
		DrawLeaf(&Robot[PLANT][6],0);
		DrawLeaf(&Robot[PLANT][7],0);
		DrawPrism(&Robot[PLANT][0],0);
		}
	Object[num].visible=FALSE;
	}
#endif
}

DrawLeaf(obj,how,doit)
Prism *obj;
int how;
int doit;
{
#if !defined(IBM_DrawLeaf)
register int i,j;

for(i=0;i < obj->surfaces ;i++)
	{
	if(obj->vsurface[i] || doit)
		{
		MoveTo( obj->copy[obj->surface[i][2]][0],
				obj->copy[obj->surface[i][2]][2]);			 
		for(j=3;j<=obj->surface[i][1]+1;j++)
			LineTo(obj->copy[obj->surface[i][j]][0], 
					obj->copy[obj->surface[i][j]][2]);
		}
	}
#endif
}
