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
#include "colordef.h"
/*---------------------------------------------------------------------
 * MakeDesk()
 *---------------------------------------------------------------------
 */
void MakeDesk(num)
{
ClipRect(&Object[num].clip);

MakePrism(&Robot[DESK][0],&Object[num].where,0);/*desk top*/
MakePrism(&Robot[DESK][1],&Object[num].where,0);/*left drawers*/
MakePrism(&Robot[DESK][2],&Object[num].where,0);/*right drawers*/
MakePrism(&Robot[DESK][3],&Object[num].where,0);/*seat*/
MakePrism(&Robot[DESK][4],&Object[num].where,0);/*left arm*/
MakePrism(&Robot[DESK][5],&Object[num].where,0);/*right arm*/
MakePrism(&Robot[DESK][6],&Object[num].where,0);/*back*/
MakePrism(&Robot[DESK][7],&Object[num].where,0);/*right arm*/
MakePrism(&Robot[DESK][8],&Object[num].where,0);/*back*/
if(Robot[DESK][0].visible)
	{
	if(Robot[DESK][6].vsurface[1])
		{
		if(Robot[DESK][1].vsurface[3] || Robot[DESK][2].vsurface[3])
			{
			DrawPrism(&Robot[DESK][1],0);
			DrawPrism(&Robot[DESK][2],0);
			}
		else
			{
			DrawPrism(&Robot[DESK][2],0);
			DrawPrism(&Robot[DESK][1],0);
			}
		DrawPrism(&Robot[DESK][0],0);
		DrawPrism(&Robot[DESK][7],0);
		if(Robot[DESK][8].vsurface[0])
			DrawPrism(&Robot[DESK][8],0);
		if(Robot[DESK][4].vsurface[0])
			{
			DrawPrism(&Robot[DESK][4],0);
			DrawPrism(&Robot[DESK][3],0);
			DrawPrism(&Robot[DESK][6],0);
			DrawPrism(&Robot[DESK][5],0);
			}
		else
			{
			DrawPrism(&Robot[DESK][5],0);
			DrawPrism(&Robot[DESK][3],0);
			DrawPrism(&Robot[DESK][6],0);
			DrawPrism(&Robot[DESK][4],0);
			}			
		}
	else
		{
		if(Robot[DESK][4].vsurface[0])
			{
			DrawPrism(&Robot[DESK][4],0);
			DrawPrism(&Robot[DESK][3],0);
			DrawPrism(&Robot[DESK][6],0);
			DrawPrism(&Robot[DESK][5],0);
			}
		else
			{
			DrawPrism(&Robot[DESK][5],0);
			DrawPrism(&Robot[DESK][3],0);
			DrawPrism(&Robot[DESK][6],0);
			DrawPrism(&Robot[DESK][4],0);
			}
		if(Robot[DESK][1].vsurface[3] || Robot[DESK][2].vsurface[3])
			{
			DrawPrism(&Robot[DESK][1],0);
			DrawPrism(&Robot[DESK][2],0);
			}
		else
			{
			DrawPrism(&Robot[DESK][2],0);
			DrawPrism(&Robot[DESK][1],0);
			}
		DrawPrism(&Robot[DESK][0],0);
		DrawPrism(&Robot[DESK][7],0);
		if(Robot[DESK][8].vsurface[0])
			DrawPrism(&Robot[DESK][8],0);
		}
	}
Object[num].visible=FALSE;
}
