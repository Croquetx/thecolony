/*  #define IBM_MakeTable      */
/*  #define IBM_MakeProjector  */
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
 * MakeTable()
 *---------------------------------------------------------------------
 */
void MakeTable(num)
{
#if !defined(IBM_MakeTable)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[TABLE][0],&Object[num].where,0);
MakePrism(&Robot[TABLE][1],&Object[num].where,0);
if(Robot[TABLE][1].visible)
	{
	DrawPrism(&Robot[TABLE][1],0);
	DrawPrism(&Robot[TABLE][0],0);
	}
Object[num].visible=FALSE;
#endif
}

/*---------------------------------------------------------------------
 * MakeProjector()
 *---------------------------------------------------------------------
 */
void MakeProjector(num)
{
#if !defined(IBM_MakeProjector)

MakeTable(num);
Object[num].visible=TRUE;
nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[PROJECTOR][0],&Object[num].where,0);
MakePrism(&Robot[PROJECTOR][1],&Object[num].where,0);
MakePrism(&Robot[PROJECTOR][2],&Object[num].where,0);
if(Robot[PROJECTOR][0].visible)
	{
	DrawPrism(&Robot[PROJECTOR][1],1);
	if(Robot[PROJECTOR][2].vsurface[6])
		{
		DrawPrism(&Robot[PROJECTOR][0],0);
		DrawPrism(&Robot[PROJECTOR][2],0);
		}
	else
		{
		DrawPrism(&Robot[PROJECTOR][2],0);
		DrawPrism(&Robot[PROJECTOR][0],0);
		}
	}
Object[num].visible=FALSE;
#endif
}
