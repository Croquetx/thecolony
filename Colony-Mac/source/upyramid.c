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
 * MakeUPyramid()
 *---------------------------------------------------------------------
 */
void MakeUPyramid(num)
int num;
{
int tp;
int i,c;

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
	{
	if(tp==M_UPYRAMID)c=c_mupyramid;
	else c=c_upyramid;
	for(i=0;i<4;i++)Robot[tp][0].surface[i][0]=c;
	DrawPrism(&Robot[tp][0],0);
	}
Object[num].visible=FALSE;
}
