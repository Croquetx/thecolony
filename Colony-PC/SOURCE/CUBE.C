/*  #define IBM_MakeCube  */
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
 * MakeCube()
 *---------------------------------------------------------------------
 */
void MakeCube(num)
int num;
{
#if !defined(IBM_MakeCube)
int tp;
int xsize,zsize;

PenColor(realcolor[vRED]);

tp=Object[num].type;
MakePrism(&Robot[tp][0],&Object[num].where,1);
if(Robot[tp][0].visible)
	DrawPrism(&Robot[tp][0],0);
if(tp==CUBE)draweye(num);
Object[num].visible=FALSE;
#endif
}
