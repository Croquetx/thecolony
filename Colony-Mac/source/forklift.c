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
#include "cgamedefs.h"
/*---------------------------------------------------------------------
 * MakeForkLift()
 *---------------------------------------------------------------------
 */
void MakeForkLift(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[FORKLIFT][0],&Object[num].where,0);
MakePrism(&Robot[FORKLIFT][1],&Object[num].where,0);
MakePrism(&Robot[FORKLIFT][2],&Object[num].where,0);
MakePrism(&Robot[FORKLIFT][3],&Object[num].where,0);
MakePrism(&Robot[FORKLIFT][4],&Object[num].where,0);
MakePrism(&Robot[FORKLIFT][5],&Object[num].where,0);
if(Robot[FORKLIFT][0].visible)
	{
	if(Robot[FORKLIFT][2].vsurface[2])
		{
		DrawPrism(&Robot[FORKLIFT][5],0);
		DrawPrism(&Robot[FORKLIFT][4],0);
		DrawPrism(&Robot[FORKLIFT][1],0);
		DrawPrism(&Robot[FORKLIFT][0],0);
		DrawPrism(&Robot[FORKLIFT][2],0);
		DrawPrism(&Robot[FORKLIFT][3],0);
		}
	else if(Robot[FORKLIFT][4].vsurface[1])
		{
		DrawPrism(&Robot[FORKLIFT][3],0);
		DrawPrism(&Robot[FORKLIFT][2],0);
		DrawPrism(&Robot[FORKLIFT][1],0);
		DrawPrism(&Robot[FORKLIFT][0],0);
		DrawPrism(&Robot[FORKLIFT][4],0);
		DrawPrism(&Robot[FORKLIFT][5],0);
		}
	else
		{
		DrawPrism(&Robot[FORKLIFT][3],0);
		DrawPrism(&Robot[FORKLIFT][2],0);
		DrawPrism(&Robot[FORKLIFT][5],0);
		DrawPrism(&Robot[FORKLIFT][4],0);
		DrawPrism(&Robot[FORKLIFT][1],0);
		DrawPrism(&Robot[FORKLIFT][0],0);
		}
	}
Object[num].visible=FALSE;
}
