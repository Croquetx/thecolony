/*  #define IBM_MakeCryo  */
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
 * MakeCryo()
 *---------------------------------------------------------------------
 */
void MakeCryo(num)
{
#if !defined(IBM_MakeCryo)
nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[CRYO][0],&Object[num].where,0);
MakePrism(&Robot[CRYO][1],&Object[num].where,0);
if(Robot[CRYO][1].visible)
	{
	DrawPrism(&Robot[CRYO][1],0);
	DrawPrism(&Robot[CRYO][0],0);
	}
Object[num].visible=FALSE;
#endif
}
