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
extern int pcycle[];
/*---------------------------------------------------------------------
 * MakePowerSuit()
 *---------------------------------------------------------------------
 */
void MakePowerSuit(num)
{
int pcyclenum = count % 6;

ClipRect(&Object[num].clip);
MakePrism(&Robot[POWERSUIT][0],&Object[num].where,0);
MakePrism(&Robot[POWERSUIT][1],&Object[num].where,0);
MakePrism(&Robot[POWERSUIT][2],&Object[num].where,0);
MakePrism(&Robot[POWERSUIT][3],&Object[num].where,0);
MakePrism(&Robot[POWERSUIT][4],&Object[num].where,0);
Robot[POWERSUIT][4].surface[0][0]=pcycle[pcyclenum];
if(Robot[POWERSUIT][1].visible)
	{
	DrawPrism(&Robot[POWERSUIT][0],0);
	DrawPrism(&Robot[POWERSUIT][1],0);
	DrawPrism(&Robot[POWERSUIT][2],0);
	DrawPrism(&Robot[POWERSUIT][3],0);
	DrawPrism(&Robot[POWERSUIT][4],0);
	}
Object[num].visible=FALSE;
}
