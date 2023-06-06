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
 * MakePyramid()
 *---------------------------------------------------------------------
 */
void MakePyramid(num)
int num;
{
int tp,i,c;

tp=Object[num].type;
MakePrism(&Robot[tp][0],&Object[num].where,1);
if(tp==PYRAMID)/*draw the shadow*/
	{
	MakePrism(&Robot[tp][1],&Object[num].where,1);
	if(Robot[tp][1].visible)
		DrawPrism(&Robot[tp][1],0);
	}
if(Robot[tp][0].visible)
	{
	if(tp==M_PYRAMID)c=c_mpyramid;
	else c=c_pyramid;
	for(i=0;i<4;i++)Robot[tp][0].surface[i][0]=c;
	DrawPrism(&Robot[tp][0],0);
	if(tp==PYRAMID)draweye(num);
	}
Object[num].visible=FALSE;
}

/*---------------------------------------------------------------------
 * draweye()
 *---------------------------------------------------------------------
 */
draweye(num)
int num;
{
int faraway=TRUE,diameter,xd,yd;
Rect r;

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
if(level==1 || level==7) ColorOval(&r,c_pupil);
else ColorOval(&r,c_eyeball);

MakePrism(&Robot[PYRAMID][3],&Object[num].where,0);
MakePrism(&Robot[PYRAMID][4],&Object[num].where,0);
if(Robot[PYRAMID][3].vsurface[0])
	{
	r.bottom=Robot[PYRAMID][3].copy[0][2];
	r.top=Robot[PYRAMID][3].copy[2][2];
	r.left=Robot[PYRAMID][3].copy[3][0];
	r.right=Robot[PYRAMID][3].copy[1][0];
	ColorOval(&r,c_iris);
	r.bottom=Robot[PYRAMID][4].copy[0][2];
	r.top=Robot[PYRAMID][4].copy[2][2];
	r.left=Robot[PYRAMID][4].copy[3][0];
	r.right=Robot[PYRAMID][4].copy[1][0];
	if(level==1 || level==7)ColorOval(&r,c_eyeball);
	else ColorOval(&r,c_pupil);
	}/* Round Eye */
}

/*---------------------------------------------------------------------*/
ColorOval(pr,cnum)
Rect *pr;
int cnum;
{
RGBForeColor(&cColor[cnum].f);
RGBBackColor(&cColor[cnum].b);
switch(cColor[cnum].pattern)
	{
	case WHITE:
		PenPat(white);
		break;
	case LTGRAY:
		PenPat(ltGray);
		break;
	case GRAY:
		PenPat(gray);
		break;
	case DKGRAY:
		PenPat(dkGray);
		break;
	case BLACK:
		PenPat(black);
		break;
	}
PaintOval(pr);
PenPat(black);
FrameOval(pr);
}