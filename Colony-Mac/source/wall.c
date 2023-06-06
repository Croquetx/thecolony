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
 * MakeFWall()
 *---------------------------------------------------------------------
 */
void MakeFWall(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[FWALL][0],&Object[num].where,0);
if(Robot[FWALL][0].visible)
	{
	if(corepower[coreindex])Robot[FWALL][0].surface[0][0]=c_lwall;
	else Robot[FWALL][0].surface[0][0]=c_dwall;
	DrawPrism(&Robot[FWALL][0],1);
	}
Object[num].visible=FALSE;
}

/*---------------------------------------------------------------------
 * MakeCWall()
 *---------------------------------------------------------------------
 */
void MakeCWall(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[CWALL][0],&Object[num].where,0);
if(Robot[CWALL][0].visible)
	{
	if(corepower[coreindex])
		{
		Robot[CWALL][0].surface[0][0]=c_lwall;
		Robot[CWALL][0].surface[1][0]=c_lwall;
		Robot[CWALL][0].surface[2][0]=c_lwall;
		}
	else
		{
		Robot[CWALL][0].surface[0][0]=c_dwall;
		Robot[CWALL][0].surface[1][0]=c_dwall;
		Robot[CWALL][0].surface[2][0]=c_dwall;
		}
	DrawPrism(&Robot[CWALL][0],1);
	}
Object[num].visible=FALSE;
}

