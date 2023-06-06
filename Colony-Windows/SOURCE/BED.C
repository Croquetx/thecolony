/*  #define IBM_MakeBed  */
/*  #define IBM_MakeBBed  */
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
 * MakeBed()
 *---------------------------------------------------------------------
 */
void MakeBed(num)
{
#if !defined(IBM_MakeBed)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[BED][0],&Object[num].where,0);
MakePrism(&Robot[BED][1],&Object[num].where,0);
MakePrism(&Robot[BED][2],&Object[num].where,0);
if(Robot[BED][1].visible)
	{
	if(Robot[BED][0].vsurface[0])
		{
		DrawPrism(&Robot[BED][0],1);
		DrawPrism(&Robot[BED][2],0);
		DrawPrism(&Robot[BED][1],0);
		}
	else
		{
		DrawPrism(&Robot[BED][1],0);
		DrawPrism(&Robot[BED][2],0);
		DrawPrism(&Robot[BED][0],1);
		}
	}
Object[num].visible=FALSE;
#endif
}

/*---------------------------------------------------------------------
 * MakeBBed()
 *---------------------------------------------------------------------
 */
void MakeBBed(num)
{
#if !defined(IBM_MakeBBed)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[BBED][0],&Object[num].where,0);
MakePrism(&Robot[BBED][1],&Object[num].where,0);
MakePrism(&Robot[BBED][2],&Object[num].where,0);
if(Robot[BBED][1].visible)
	{
	if(Robot[BBED][0].vsurface[0])
		{
		DrawPrism(&Robot[BBED][0],1);
		DrawPrism(&Robot[BBED][2],0);
		DrawPrism(&Robot[BBED][1],0);
		}
	else
		{
		DrawPrism(&Robot[BBED][1],0);
		DrawPrism(&Robot[BBED][2],0);
		DrawPrism(&Robot[BBED][0],1);
		}
	}
Object[num].visible=FALSE;
#endif
}
