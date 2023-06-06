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
 * MakeTub()
 *---------------------------------------------------------------------
 */
void MakeTub(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[TUB][0],&Object[num].where,0);
MakePrism(&Robot[TUB][1],&Object[num].where,0);
if(Robot[TUB][0].visible)
	{
	DrawPrism(&Robot[TUB][0],0);
	DrawPrism(&Robot[TUB][1],0);
	}
Object[num].visible=FALSE;
}
/*---------------------------------------------------------------------
 * MakeSink()
 *---------------------------------------------------------------------
 */
void MakeSink(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[SINK][0],&Object[num].where,0);
MakePrism(&Robot[SINK][1],&Object[num].where,0);
MakePrism(&Robot[SINK][2],&Object[num].where,0);
if(Robot[SINK][0].visible)
	{
	DrawPrism(&Robot[SINK][0],0);
	DrawPrism(&Robot[SINK][1],0);
	DrawPrism(&Robot[SINK][2],0);
	}
Object[num].visible=FALSE;
}
/*---------------------------------------------------------------------
 * MakeToilet()
 *---------------------------------------------------------------------
 */
void MakeToilet(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[TOILET][0],&Object[num].where,0);
MakePrism(&Robot[TOILET][1],&Object[num].where,0);
MakePrism(&Robot[TOILET][2],&Object[num].where,0);
MakePrism(&Robot[TOILET][3],&Object[num].where,0);
if(Robot[TOILET][0].visible)
	{
	DrawPrism(&Robot[TOILET][0],0);
	DrawPrism(&Robot[TOILET][1],0);
	DrawPrism(&Robot[TOILET][2],0);
	DrawPrism(&Robot[TOILET][3],1);
	}
Object[num].visible=FALSE;
}
/*---------------------------------------------------------------------
 * MakePToilet()
 *---------------------------------------------------------------------
 */
void MakePToilet(num)
{
ClipRect(&Object[num].clip);
MakePrism(&Robot[TOILET][0],&Object[num].where,0);
MakePrism(&Robot[TOILET][1],&Object[num].where,0);
MakePrism(&Robot[TOILET][2],&Object[num].where,0);
MakePrism(&Robot[TOILET][3],&Object[num].where,0);
MakePrism(&Robot[TOILET][4],&Object[num].where,0);
if(Robot[TOILET][0].visible)
	{
	if(Robot[TOILET][4].vsurface[0])DrawPrism(&Robot[TOILET][4],1);
	DrawPrism(&Robot[TOILET][0],0);
	DrawPrism(&Robot[TOILET][1],0);
	DrawPrism(&Robot[TOILET][2],0);
	DrawPrism(&Robot[TOILET][3],1);
	if(!Robot[TOILET][4].vsurface[0])DrawPrism(&Robot[TOILET][4],1);
	}
Object[num].visible=FALSE;
}
/*---------------------------------------------------------------------
 * MakeReactor()
 *---------------------------------------------------------------------
 */
void MakeReactor(num)
{
int color=1+count%5;
int i;
int height;

switch(corestate[coreindex])
	{
	case 0: /*reactor is closed or closing*/
			if(coreheight[coreindex]<256)coreheight[coreindex]+=16;
			break;
	case 1: /*reactor is opened or opening*/
			if(coreheight[coreindex])coreheight[coreindex]-=16;
			break;
	case 2: /*reactor is open, core is gone*/
			coreheight[coreindex]=0;
			break;
	}
height=coreheight[coreindex];
for(i=0;i<4;i++)
	{
	Robot[REACTOR][1].surface[i][0]=color;
	Robot[REACTOR][2].surface[i][0]=color;
	}
if(corepower[coreindex]>1)color=1+color%3;
else color = vWHITE;
for(i=0;i<6;i++)
	Robot[REACTOR][0].surface[i][0]=color;
/*Set height of core*/
if(corestate[coreindex]<2)
	for(i=6;i<12;i++)
		Robot[REACTOR][0].pnt[i][2]=height+32-Floor;
		
for(i=0;i<4;i++)
	Robot[REACTOR][1].pnt[i][2]=height-Floor;
for(i=4;i<8;i++)
	Robot[REACTOR][1].pnt[i][2]=height+32-Floor;
ClipRect(&Object[num].clip);
MakePrism(&Robot[REACTOR][0],&Object[num].where,0);
MakePrism(&Robot[REACTOR][1],&Object[num].where,0);
MakePrism(&Robot[REACTOR][2],&Object[num].where,0);
if(Robot[REACTOR][0].visible)
	{
	DrawPrism(&Robot[REACTOR][2],0);
	if(Robot[REACTOR][1].vsurface[4])
		{
		DrawPrism(&Robot[REACTOR][1],0);
		if(corestate[coreindex]<2)DrawPrism(&Robot[REACTOR][0],0);
		}
	else
		{
		if(corestate[coreindex]<2)DrawPrism(&Robot[REACTOR][0],0);
		DrawPrism(&Robot[REACTOR][1],0);
		}
	}
Object[num].visible=FALSE;
}
