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
 * MakeScreen()
 *---------------------------------------------------------------------
 */
void MakeScreen(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[SCREEN][0],&Object[num].where,0);
if(Robot[SCREEN][0].visible)DrawPrism(&Robot[SCREEN][0],0);
Object[num].visible=FALSE;
}
