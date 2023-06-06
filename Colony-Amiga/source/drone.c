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
 * MakeDrone()
 *---------------------------------------------------------------------
 */
extern int faraway;
void MakeDrone(num)
int num;
{
int tp,i;
int body;

tp=Object[num].type;
MakePrism(&Robot[tp][0],&Object[num].where,0);
body=1;
if(Robot[tp][0].vsurface[0]&&Robot[tp][0].vsurface[1])body=1;
if(Robot[tp][0].vsurface[2]&&Robot[tp][0].vsurface[3])body=1;
if(Robot[tp][0].vsurface[0]&&Robot[tp][0].vsurface[3])body=0;
if(Robot[tp][0].vsurface[1]&&Robot[tp][0].vsurface[2])body=2;
if(body==0 && Robot[tp][0].visible)
	DrawPrism(&Robot[tp][0],0);
seteyes(num);
if(faraway>=0)draweyes(num,c_edrone);
if(body==1 && Robot[tp][0].visible)
	{
	for(i=0;i<8;i++)Robot[tp][0].surface[i][0]=c_drone;
	DrawPrism(&Robot[tp][0],0);
	}
if(faraway>=0)draweyes(num,c_edrone);
if(body==2 && Robot[tp][0].visible)
	DrawPrism(&Robot[tp][0],0);
Object[num].visible=FALSE;
}
/*---------------------------------------------------------------------
 * MakeSoldier()
 *---------------------------------------------------------------------
 */
void MakeSoldier(num)
int num;
{
int i;
int tp;
int body;
int look;

tp=Object[num].type;
MakePrism(&Robot[tp][0],&Object[num].where,0);
body=1;
if(Robot[tp][0].vsurface[0]&&Robot[tp][0].vsurface[1])body=1;
if(Robot[tp][0].vsurface[2]&&Robot[tp][0].vsurface[3])body=1;
if(Robot[tp][0].vsurface[0]&&Robot[tp][0].vsurface[3])body=0;
if(Robot[tp][0].vsurface[1]&&Robot[tp][0].vsurface[2])body=2;
for(i=0;i<4;i++)
	{
	look=nabs(Object[num].where.lookx)-32;
	if(look<0)look+=256;
	if(look>=256)look-=256;
	Rotate(look,Robot[tp][3].pnt[i],Robot[tp][1].pnt[i]);
	Robot[tp][1].pnt[i][2]=Robot[tp][3].pnt[i][2];
	Robot[tp][1].pnt[i][0]+=120;
	look=abs(Object[num].where.lookx)-32;
	if(look<0)look+=256;
	if(look>=256)look-=256;
	Rotate(look,Robot[tp][4].pnt[i],Robot[tp][2].pnt[i]);
	Robot[tp][2].pnt[i][2]=Robot[tp][4].pnt[i][2];
	Robot[tp][2].pnt[i][0]+=120;
	}
MakePrism(&Robot[tp][1],&Object[num].where,0);
MakePrism(&Robot[tp][2],&Object[num].where,0);
seteyes(num);
for(i=0;i<8;i++)Robot[tp][0].surface[i][0]=c_soldier;
switch(body)
	{
	case 0:
		if(Robot[tp][0].visible)DrawPrism(&Robot[tp][0],0);
		if(faraway>=0){draweyes(num,c_esoldier);draweyes(num,c_esoldier);}
		if(Robot[tp][1].copy[1][1]<Robot[tp][2].copy[1][1])
			{
			if(Robot[tp][2].visible)DrawPrism(&Robot[tp][2],0);
			if(Robot[tp][1].visible)DrawPrism(&Robot[tp][1],0);
			}
		else
			{
			if(Robot[tp][1].visible)DrawPrism(&Robot[tp][1],0);
			if(Robot[tp][2].visible)DrawPrism(&Robot[tp][2],0);
			}
		break;
	case 1:
		if(faraway>=0)draweyes(num,c_esoldier);
		if(Robot[tp][0].visible)DrawPrism(&Robot[tp][0],0);
		if(Robot[tp][1].copy[1][1]<Robot[tp][2].copy[1][1])
			{
			if(Robot[tp][2].visible)DrawPrism(&Robot[tp][2],0);
			if(Robot[tp][1].visible)DrawPrism(&Robot[tp][1],0);
			}
		else
			{
			if(Robot[tp][1].visible)DrawPrism(&Robot[tp][1],0);
			if(Robot[tp][2].visible)DrawPrism(&Robot[tp][2],0);
			}
		if(faraway>=0)draweyes(num,c_esoldier);
		break;
	case 2:
		if(faraway>=0){draweyes(num,c_esoldier);draweyes(num,c_esoldier);}
		if(Robot[tp][1].copy[1][1]<Robot[tp][2].copy[1][1])
			{
			if(Robot[tp][2].visible)DrawPrism(&Robot[tp][2],0);
			if(Robot[tp][1].visible)DrawPrism(&Robot[tp][1],0);
			}
		else
			{
			if(Robot[tp][1].visible)DrawPrism(&Robot[tp][1],0);
			if(Robot[tp][2].visible)DrawPrism(&Robot[tp][2],0);
			}
		if(Robot[tp][0].visible)DrawPrism(&Robot[tp][0],0);
		break;
	}
Object[num].visible=FALSE;
}

