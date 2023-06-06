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
 * MakeTele()
 *---------------------------------------------------------------------
 */
void MakeTele(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[TELEPORT][0],&Object[num].where,0);
if(Robot[TELEPORT][0].visible)
	DrawPrism(&Robot[TELEPORT][0],0);
Object[num].visible=FALSE;
}
