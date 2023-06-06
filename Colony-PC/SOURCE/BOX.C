/*  #define IBM_MakeBox1    */
/*  #define IBM_MakeBox2    */
/*  #define IBM_MakeBench   */
/*  #define IBM_MakeCBench  */
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
 * MakeBox1()
 *---------------------------------------------------------------------
 */
void MakeBox1(num)
{
#if !defined(IBM_MakeBox1)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[BOX1][0],&Object[num].where,0);
if(Robot[BOX1][0].visible)
	DrawPrism(&Robot[BOX1][0],0);
Object[num].visible=FALSE;
#endif
}
/*---------------------------------------------------------------------
 * MakeBox2()
 *---------------------------------------------------------------------
 */
void MakeBox2(num)
{
#if !defined(IBM_MakeBox2)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[BOX2][0],&Object[num].where,0);
MakePrism(&Robot[BOX2][1],&Object[num].where,0);
if(Robot[BOX2][1].visible)
	{
	DrawPrism(&Robot[BOX2][1],0);
	DrawPrism(&Robot[BOX2][0],0);
	}
Object[num].visible=FALSE;
#endif
}
/*---------------------------------------------------------------------
 * MakeBench()
 *---------------------------------------------------------------------
 */
void MakeBench(num)
{
#if !defined(IBM_MakeBench)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
Robot[BENCH][0].surface[4][0]=BLACK;
MakePrism(&Robot[BENCH][0],&Object[num].where,0);
if(Robot[BENCH][0].visible)
	DrawPrism(&Robot[BENCH][0],0);
Robot[BENCH][0].surface[4][0]=LTGRAY;
Object[num].visible=FALSE;
#endif
}

/*---------------------------------------------------------------------
 * MakeCBench()
 *---------------------------------------------------------------------
 */
void MakeCBench(num)
{
#if !defined(IBM_MakeCBench)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
Robot[CBENCH][0].surface[4][0]=BLACK;
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
Robot[CBENCH][0].surface[4][0]=LTGRAY;
Object[num].visible=FALSE;
#endif
}
