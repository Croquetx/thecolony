/*  #define IBM_MakeSnoop  */
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
 * MakeSnoop()
 *---------------------------------------------------------------------
 */
extern int faraway;
void MakeSnoop(num)
int num;
{
#if !defined(IBM_MakeSnoop)
int tp;

tp=Object[num].type;
MakePrism(&Robot[tp][0],&Object[num].where,0);
MakePrism(&Robot[tp][1],&Object[num].where,0);
if(Robot[tp][0].visible)
	{
	DrawPrism(&Robot[tp][0],0);
	DrawPrism(&Robot[tp][1],0);
	}
Object[num].visible=FALSE;
#endif
}
