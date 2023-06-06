/*  #define IBM_MakeUPyramid  */
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
 * MakeUPyramid()
 *---------------------------------------------------------------------
 */
void MakeUPyramid(num)
int num;
{
#if !defined(IBM_MakeUPyramid)
int tp;

tp=Object[num].type;
if(tp==UPYRAMID)draweye(num);
if(tp==UPYRAMID)
	{
	MakePrism(&Robot[UPYRAMID][1],&Object[num].where,1);
	if(Robot[UPYRAMID][1].visible)
		DrawPrism(&Robot[UPYRAMID][1],0);
	}
MakePrism(&Robot[tp][0],&Object[num].where,1);
if(Robot[tp][0].visible)
	DrawPrism(&Robot[tp][0],0);
Object[num].visible=FALSE;
#endif
}
