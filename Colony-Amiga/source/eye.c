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
 * MakeEye()
 *---------------------------------------------------------------------
 */
void MakeEye(num)
int num;
{
int i;
Rect r;
int diameter;
int tp;
int xd,yd;
int faraway=TRUE;

tp=Object[num].type;
if(tp==EYE)/*if big eye don't draw if too close*/
	{
	xd=Object[num].where.xloc-Me.xloc;
	yd=Object[num].where.yloc-Me.yloc;
	if(xd<=256 && xd>=-256 && yd<=256 && yd >= -256)
		{
		/*if much too close quit now!*/
		if(xd<=64 && xd>=-64 && yd<=64 && yd >= -64)return;
		faraway=FALSE;
		}
	}
Robot[tp][0].copy[0][0] = Object[num].where.xloc+Robot[tp][0].pnt[0][0];
Robot[tp][0].copy[0][1] = Object[num].where.yloc+Robot[tp][0].pnt[0][1];
Robot[tp][0].copy[0][2] = Robot[tp][0].pnt[0][2];
TransRotProj(&Robot[tp][0].copy[0]);
Robot[tp][0].copy[1][0] = Object[num].where.xloc+Robot[tp][0].pnt[0][0];
Robot[tp][0].copy[1][1] = Object[num].where.yloc+Robot[tp][0].pnt[1][1];
Robot[tp][0].copy[1][2] = Robot[tp][0].pnt[1][2];
TransRotProj(&Robot[tp][0].copy[1]);

diameter=Robot[tp][0].copy[0][2]-Robot[tp][0].copy[1][2];
r.bottom=Robot[tp][0].copy[0][2];
if(diameter>1000)return;
r.top=Robot[tp][0].copy[1][2]-diameter;
r.left=Robot[tp][0].copy[1][0]-diameter;
r.right=Robot[tp][0].copy[1][0]+diameter;
if(r.left<Object[num].where.xmn)Object[num].where.xmn=r.left;
if(r.right>Object[num].where.xmx)Object[num].where.xmx=r.right;

if(level==1||level==7)ColorOval(&r,c_pupil);
else ColorOval(&r,c_eyeball);
MakePrism(&Robot[tp][1],&Object[num].where,0);
MakePrism(&Robot[tp][2],&Object[num].where,0);
if(Robot[tp][1].vsurface[0])
	{
	r.bottom=Robot[tp][1].copy[0][2];
	r.top=Robot[tp][1].copy[2][2];
	r.left=Robot[tp][1].copy[3][0];
	r.right=Robot[tp][1].copy[1][0];
	if(tp==M_EYE)ColorOval(&r,c_meye);
	else ColorOval(&r,c_eye);
	r.bottom=Robot[tp][2].copy[0][2];
	r.top=Robot[tp][2].copy[2][2];
	r.left=Robot[tp][2].copy[3][0];
	r.right=Robot[tp][2].copy[1][0];
	if(level==1||level==7)ColorOval(&r,c_eyeball);
	else ColorOval(&r,c_pupil);
	}/* Round Eye */
Object[num].visible=FALSE;
}
