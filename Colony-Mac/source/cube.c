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
 * MakeCube()
 *---------------------------------------------------------------------
 */
void MakeCube(num)
int num;
{
int tp;
int xsize,zsize;
int i,c;

tp=Object[num].type;
MakePrism(&Robot[tp][0],&Object[num].where,1);
if(Robot[tp][0].visible)
	{
	if(tp==M_CUBE)c=c_mdiamond;
	else c=c_diamond;
	for(i=0;i<8;i++)Robot[tp][0].surface[i][0]=c;
	DrawPrism(&Robot[tp][0],0);
	if(tp==CUBE)draweye(num);
	}
Object[num].visible=FALSE;
}
