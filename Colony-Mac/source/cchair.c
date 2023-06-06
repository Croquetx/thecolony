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
 * MakeCChair()
 *---------------------------------------------------------------------
 */
void MakeCChair(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[CCHAIR][0],&Object[num].where,0);
MakePrism(&Robot[CCHAIR][1],&Object[num].where,0);
MakePrism(&Robot[CCHAIR][2],&Object[num].where,0);
MakePrism(&Robot[CCHAIR][3],&Object[num].where,0);
MakePrism(&Robot[CCHAIR][4],&Object[num].where,0);
if(Robot[CCHAIR][4].visible)
	DrawPrism(&Robot[CCHAIR][4],0);
if(Robot[CCHAIR][0].visible)
	{
	DrawPrism(&Robot[CCHAIR][0],0);
	if(Robot[CCHAIR][3].vsurface[0])
		{
		DrawPrism(&Robot[CCHAIR][3],1);
		if(Robot[CCHAIR][1].vsurface[0])
			{
			DrawPrism(&Robot[CCHAIR][1],1);
			DrawPrism(&Robot[CCHAIR][2],1);	
			}
		else
			{
			DrawPrism(&Robot[CCHAIR][2],1);	
			DrawPrism(&Robot[CCHAIR][1],1);
			}
		}
	else
		{
		if(Robot[CCHAIR][1].vsurface[0])
			{
			DrawPrism(&Robot[CCHAIR][1],1);
			DrawPrism(&Robot[CCHAIR][2],1);	
			}
		else
			{
			DrawPrism(&Robot[CCHAIR][2],1);	
			DrawPrism(&Robot[CCHAIR][1],1);
			}
		DrawPrism(&Robot[CCHAIR][3],1);	
		}
	}
Object[num].visible=FALSE;
}
