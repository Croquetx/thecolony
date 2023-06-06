/*  #define IBM_MakePyramid  /*  */
/*  #define IBM_draweye      /*  */
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
 * MakePyramid()
 *---------------------------------------------------------------------
 */
void MakePyramid(num)
int num;
{
#if !defined(IBM_MakePyramid)
int tp;

tp=Object[num].type;
MakePrism(&Robot[tp][0],&Object[num].where,1);
if(tp==PYRAMID)
	{
	MakePrism(&Robot[tp][1],&Object[num].where,1);
	if(Robot[tp][1].visible)
		DrawPrism(&Robot[tp][1],0);
	}
if(Robot[tp][0].visible)
	DrawPrism(&Robot[tp][0],0);
if(tp==PYRAMID)draweye(num);
Object[num].visible=FALSE;
#endif
}

/*---------------------------------------------------------------------
 * draweye()
 *---------------------------------------------------------------------
 */
draweye(num)
int num;
{
#if !defined(IBM_draweye)
int faraway=TRUE,diameter,xd,yd;
Rect r;

PenColor(realcolor[vBLACK]);

xd=Object[num].where.xloc-Me.xloc;
yd=Object[num].where.yloc-Me.yloc;
if(xd<=64 && xd>=-64 && yd<=64 && yd >= -64)faraway=FALSE;
Robot[PYRAMID][2].copy[0][0] = 
	Object[num].where.xloc+Robot[PYRAMID][2].pnt[0][0];
Robot[PYRAMID][2].copy[0][1] = 
	Object[num].where.yloc+Robot[PYRAMID][2].pnt[0][1];
Robot[PYRAMID][2].copy[0][2] = Robot[PYRAMID][2].pnt[0][2];
TransRotProj(&Robot[PYRAMID][2].copy[0]);
Robot[PYRAMID][2].copy[1][0] = 
	Object[num].where.xloc+Robot[PYRAMID][2].pnt[0][0];
Robot[PYRAMID][2].copy[1][1] = 
	Object[num].where.yloc+Robot[PYRAMID][2].pnt[1][1];
Robot[PYRAMID][2].copy[1][2] = Robot[PYRAMID][2].pnt[1][2];
TransRotProj(&Robot[PYRAMID][2].copy[1]);

diameter=Robot[PYRAMID][2].copy[0][2]-Robot[PYRAMID][2].copy[1][2];
r.bottom=Robot[PYRAMID][2].copy[0][2];
if(diameter>1000)return;
r.top=Robot[PYRAMID][2].copy[1][2]-diameter;
r.left=Robot[PYRAMID][2].copy[1][0]-diameter;
r.right=Robot[PYRAMID][2].copy[1][0]+diameter;
if(r.left<Object[num].where.xmn)Object[num].where.xmn=r.left;
if(r.right>Object[num].where.xmx)Object[num].where.xmx=r.right;

PenColor(realcolor[vINTWHITE]);
if(faraway)FillOval(&r,1);
PenColor(realcolor[vBLACK]);
FrameOval(&r);


MakePrism(&Robot[PYRAMID][3],&Object[num].where,0);
MakePrism(&Robot[PYRAMID][4],&Object[num].where,0);
if(Robot[PYRAMID][3].vsurface[0])
	{
	r.bottom=Robot[PYRAMID][3].copy[0][2];
	r.top=Robot[PYRAMID][3].copy[2][2];
	r.left=Robot[PYRAMID][3].copy[3][0];
	r.right=Robot[PYRAMID][3].copy[1][0];

	PenColor(realcolor[vBLUE]);
	BackColor(realcolor[vINTWHITE]);
	if(faraway)FillOval(&r,3);
	FrameOval(&r);
	BackColor(realcolor[vWHITE]);

	r.bottom=Robot[PYRAMID][4].copy[0][2];
	r.top=Robot[PYRAMID][4].copy[2][2];
	r.left=Robot[PYRAMID][4].copy[3][0];
	r.right=Robot[PYRAMID][4].copy[1][0];

	PenColor(realcolor[vBLACK]);
	if(faraway)FillOval(&r,1);
	else FrameOval(&r);
	}/* Round Eye */
#endif
}
