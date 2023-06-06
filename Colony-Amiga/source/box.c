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
/*---------------------------------------------------------------------
 * MakeBox1()
 *---------------------------------------------------------------------
 */
void MakeBox1(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[BOX1][0],&Object[num].where,0);
if(Robot[BOX1][0].visible)
	DrawPrism(&Robot[BOX1][0],0);
Object[num].visible=FALSE;
}
/*---------------------------------------------------------------------
 * MakeBox2()
 *---------------------------------------------------------------------
 */
void MakeBox2(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[BOX2][0],&Object[num].where,0);
MakePrism(&Robot[BOX2][1],&Object[num].where,0);
if(Robot[BOX2][1].visible)
	{
	DrawPrism(&Robot[BOX2][1],0);
	DrawPrism(&Robot[BOX2][0],0);
	}
Object[num].visible=FALSE;
}
/*---------------------------------------------------------------------
 * MakeBench()
 *---------------------------------------------------------------------
 */
void MakeBench(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[BENCH][0],&Object[num].where,0);
if(Robot[BENCH][0].visible)
	DrawPrism(&Robot[BENCH][0],0);
Object[num].visible=FALSE;
}

/*---------------------------------------------------------------------
 * MakeCBench()
 *---------------------------------------------------------------------
 */
void MakeCBench(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[CBENCH][0],&Object[num].where,0);
MakePrism(&Robot[CBENCH][1],&Object[num].where,0);
if(Robot[CBENCH][0].visible)
	{
	if(Robot[CBENCH][0].vsurface[2])
		{
		DrawPrism(&Robot[CBENCH][0],0);
		DrawPrism(&Robot[CBENCH][1],0);
		}
	else
		{
		DrawPrism(&Robot[CBENCH][1],0);
		DrawPrism(&Robot[CBENCH][0],0);
		}
	}
Object[num].visible=FALSE;
}
