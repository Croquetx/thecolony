/*  #define IBM_MakeCouch   */
/*  #define IBM_MakeChair   */
/*  #define IBM_MakeTV	    */
/*  #define IBM_MakeDrawer  */
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
 * MakeCouch()
 *---------------------------------------------------------------------
 */
void MakeCouch(num)
{
#if !defined(IBM_MakeCouch)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[COUCH][0],&Object[num].where,0);
MakePrism(&Robot[COUCH][1],&Object[num].where,0);
MakePrism(&Robot[COUCH][2],&Object[num].where,0);
MakePrism(&Robot[COUCH][3],&Object[num].where,0);
if(Robot[COUCH][0].visible)
	{
	if(Robot[COUCH][2].vsurface[1]&&Robot[COUCH][3].vsurface[2])
		{
		DrawPrism(&Robot[COUCH][2],0);
		DrawPrism(&Robot[COUCH][3],0);
		if(Robot[COUCH][0].vsurface[3])
			{
			DrawPrism(&Robot[COUCH][1],0);
			DrawPrism(&Robot[COUCH][0],0);
			}
		else
			{
			DrawPrism(&Robot[COUCH][0],0);
			DrawPrism(&Robot[COUCH][1],0);
			}
		}
	else if(Robot[COUCH][3].vsurface[1])
		{
		DrawPrism(&Robot[COUCH][2],0);
		if(Robot[COUCH][0].vsurface[3])
			{
			DrawPrism(&Robot[COUCH][1],0);
			DrawPrism(&Robot[COUCH][0],0);
			}
		else
			{
			DrawPrism(&Robot[COUCH][0],0);
			DrawPrism(&Robot[COUCH][1],0);
			}
		DrawPrism(&Robot[COUCH][3],0);
		}
	else
		{
		DrawPrism(&Robot[COUCH][3],0);
		if(Robot[COUCH][0].vsurface[3])
			{
			DrawPrism(&Robot[COUCH][1],0);
			DrawPrism(&Robot[COUCH][0],0);
			}
		else
			{
			DrawPrism(&Robot[COUCH][0],0);
			DrawPrism(&Robot[COUCH][1],0);
			}
		DrawPrism(&Robot[COUCH][2],0);
		}
	}
Object[num].visible=FALSE;
#endif
}

/*---------------------------------------------------------------------
 * MakeChair()
 *---------------------------------------------------------------------
 */
void MakeChair(num)
{
#if !defined(IBM_MakeChair)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[CHAIR][0],&Object[num].where,0);
MakePrism(&Robot[CHAIR][1],&Object[num].where,0);
MakePrism(&Robot[CHAIR][2],&Object[num].where,0);
MakePrism(&Robot[CHAIR][3],&Object[num].where,0);
if(Robot[CHAIR][0].visible)
	{
	if(Robot[CHAIR][2].vsurface[1]&&Robot[CHAIR][3].vsurface[2])
		{
		DrawPrism(&Robot[CHAIR][2],0);
		DrawPrism(&Robot[CHAIR][3],0);
		if(Robot[CHAIR][0].vsurface[3])
			{
			DrawPrism(&Robot[CHAIR][1],0);
			DrawPrism(&Robot[CHAIR][0],0);
			}
		else
			{
			DrawPrism(&Robot[CHAIR][0],0);
			DrawPrism(&Robot[CHAIR][1],0);
			}
		}
	else if(Robot[CHAIR][3].vsurface[1])
		{
		DrawPrism(&Robot[CHAIR][2],0);
		if(Robot[CHAIR][0].vsurface[3])
			{
			DrawPrism(&Robot[CHAIR][1],0);
			DrawPrism(&Robot[CHAIR][0],0);
			}
		else
			{
			DrawPrism(&Robot[CHAIR][0],0);
			DrawPrism(&Robot[CHAIR][1],0);
			}
		DrawPrism(&Robot[CHAIR][3],0);
		}
	else
		{
		DrawPrism(&Robot[CHAIR][3],0);
		if(Robot[CHAIR][0].vsurface[3])
			{
			DrawPrism(&Robot[CHAIR][1],0);
			DrawPrism(&Robot[CHAIR][0],0);
			}
		else
			{
			DrawPrism(&Robot[CHAIR][0],0);
			DrawPrism(&Robot[CHAIR][1],0);
			}
		DrawPrism(&Robot[CHAIR][2],0);
		}
	}
Object[num].visible=FALSE;
#endif
}
/*---------------------------------------------------------------------
 * MakeTV()
 *---------------------------------------------------------------------
 */
void MakeTV(num)
{
#if !defined(IBM_MakeTV)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[TV][0],&Object[num].where,0);
MakePrism(&Robot[TV][1],&Object[num].where,0);
if(Robot[TV][0].visible)
	DrawPrism(&Robot[TV][0],0);
if(Robot[TV][1].vsurface[0])
	DrawPrism(&Robot[TV][1],0);
Object[num].visible=FALSE;
#endif
}
/*---------------------------------------------------------------------
 * MakeDrawer()
 *---------------------------------------------------------------------
 */
void MakeDrawer(num)
{
#if !defined(IBM_MakeDrawer)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[DRAWER][0],&Object[num].where,0);
MakePrism(&Robot[DRAWER][1],&Object[num].where,0);
if(Robot[DRAWER][0].visible)
	{
	DrawPrism(&Robot[DRAWER][0],0);
	DrawPrism(&Robot[DRAWER][1],1);
	}
Object[num].visible=FALSE;
#endif
}
