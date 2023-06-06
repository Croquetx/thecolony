/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
/*----------------------------------------------------------------------* 
 * compass.c
 *----------------------------------------------------------------------* 
 * DrawCompass()
 * DoCompass(cerase)
 *		int cerase;
 *----------------------------------------------------------------------*/
#define EXT extern
#include "cgamedefs.h"
/*----------------------------------------------------------------------*/
#define CSIZE 64
#define CCENTER 35
int oldang;
int oldxloc,oldyloc;
int oldxindex,oldyindex;
int oldegg[5],oldrobot[5];
int xcorner[8],ycorner[8];
Rect compRect,floorRect;
DrawCompass()
{
Rect r;
int xloc,yloc;
int tsin,tcos;
int dx,dy;
int cx,cy;
int i;
PicHandle comp;
int xSize,ySize;

for(i=0;i<5;i++){oldegg[i]=0; oldrobot[i]=0;}
oldang=Me.ang;
oldxloc=Me.xloc;
oldyloc=Me.yloc;
oldxindex=Me.xindex;
oldyindex=Me.yindex;
SetPort(moveWindow);
SetOrigin(0,0);
	comp=GetPicture(-32757);
	SizeRect(&xSize,&ySize,&(**comp).picFrame);
	SetRect(&compRect,-2,-2,xSize-2,ySize-2);
	ClipRect(&compRect);
	DrawPicture(comp,&compRect);
compRect.top=0; compRect.left=0; compRect.bottom=3*CCENTER; compRect.right=2*CCENTER; 
PenMode(patCopy);
ClipRect(&compRect);
/*
FillRect(&compRect,white);
*/
PenMode(patXor);
r.top=2*CCENTER-4;
r.bottom=2*CCENTER+28;
r.left=CCENTER-16;
r.right=CCENTER+16;
FillOval(&r,black);
r.top-=2; r.left-=2;
r.bottom+=2;r.right+=2;
/*
FrameOval(&r);
*/
MoveTo(CCENTER,2*CCENTER+12);
LineTo(CCENTER+(cost[oldang]>>3),(2*CCENTER+12)-(sint[oldang]>>3));
PenMode(patCopy);
floorRect.top=7;floorRect.left=7;
floorRect.bottom=2*CCENTER-7; floorRect.right=2*CCENTER-7;
/*
FrameRect(&floorRect);
*/
floorRect.top++; floorRect.left++;
floorRect.bottom--; floorRect.right--;
ClipRect(&floorRect);
oldxloc=xloc=((Me.xindex<<8)-Me.xloc)>>2;
oldyloc=yloc=((Me.yindex<<8)-Me.yloc)>>2;
oldxindex=Me.xindex; oldyindex=Me.yindex;
oldang=Me.ang;
r.top=CCENTER-5;   r.bottom=CCENTER+5;
r.left=CCENTER-10; r.right=CCENTER+10;
FrameOval(&r);
r.left=CCENTER-5; r.right=CCENTER+5;
FillOval(&r,black);
if(game!=COLONY)
	{
	ClipRect(&compRect);
	PenMode(patCopy);
	return;
	}
PenMode(patXor);
tsin=sint[Me.ang];
tcos=cost[Me.ang];
xcorner[0]=CCENTER+(((long)xloc * tsin - (long)yloc * tcos) >> 8);
ycorner[0]=CCENTER-(((long)yloc * tsin + (long)xloc * tcos) >> 8);		
xcorner[1]=CCENTER+(((long)(xloc+64) * tsin - (long)yloc * tcos) >> 8);
ycorner[1]=CCENTER-(((long)yloc * tsin + (long)((xloc+64) * tcos)) >> 8);		
xcorner[2]=CCENTER+(((long)(xloc+64) * tsin - (long)(yloc+64) * tcos) >> 8);
ycorner[2]=CCENTER-(((long)(yloc+64) * tsin + (long)(xloc+64) * tcos) >> 8);		
xcorner[3]=CCENTER+(((long)(xloc * tsin - (long)(yloc+64) * tcos)) >> 8);
ycorner[3]=CCENTER-(((long)(yloc+64) * tsin + (long)xloc * tcos) >> 8);
xcorner[4]=CCENTER+(((long)(xloc+32) * tsin - (long)(yloc+32) * tcos) >> 8);
ycorner[4]=CCENTER-(((long)(yloc+32) * tsin + (long)(xloc+32) * tcos) >> 8);		
xcorner[5]=CCENTER+(((long)(xloc+32) * tsin - (long)(yloc) * tcos) >> 8);
ycorner[5]=CCENTER-(((long)(yloc) * tsin + (long)(xloc+32) * tcos) >> 8);		
dx=xcorner[1]-xcorner[0]; dy=ycorner[0]-ycorner[1];
MoveTo(xcorner[0]-dx,ycorner[0]+dy);
LineTo(xcorner[1]+dx,ycorner[1]-dy);
MoveTo(xcorner[1]+dy,ycorner[1]+dx);
LineTo(xcorner[2]-dy,ycorner[2]-dx);
MoveTo(xcorner[2]+dx,ycorner[2]-dy);
LineTo(xcorner[3]-dx,ycorner[3]+dy);
MoveTo(xcorner[3]-dy,ycorner[3]-dx);
LineTo(xcorner[0]+dy,ycorner[0]+dx);
if(foodarray[Me.xindex][Me.yindex])
	{
	r.left=xcorner[4]-3;
	r.right=xcorner[4]+3;
	r.top=ycorner[4]-3;
	r.bottom=ycorner[4]+3;
	FrameOval(&r);
	oldegg[0]=TRUE;
	}
if(!(Wall[Me.xindex][Me.yindex]&0x01))
	{
	if(foodarray[Me.xindex][Me.yindex-1])
		{
		r.left=(xcorner[4]+dy)-3;
		r.right=(xcorner[4]+dy)+3;
		r.top=(ycorner[4]+dx)-3;
		r.bottom=(ycorner[4]+dx)+3;
		FrameOval(&r);
		oldegg[1]=TRUE;
		}
	if(robotarray[Me.xindex][Me.yindex-1])
		{
		r.left=(xcorner[4]+dy)-5;
		r.right=(xcorner[4]+dy)+5;
		r.top=(ycorner[4]+dx)-5;
		r.bottom=(ycorner[4]+dx)+5;
		FrameOval(&r);
		oldrobot[1]=TRUE;
		}
	}
if(!(Wall[Me.xindex][Me.yindex]&0x02))
	{
	if(foodarray[Me.xindex-1][Me.yindex])
		{
		r.left=(xcorner[4]-dx)-3;
		r.right=(xcorner[4]-dx)+3;
		r.top=(ycorner[4]+dy)-3;
		r.bottom=(ycorner[4]+dy)+3;
		FrameOval(&r);
		oldegg[2]=TRUE;
		}
	if(robotarray[Me.xindex-1][Me.yindex])
		{
		r.left=(xcorner[4]-dx)-5;
		r.right=(xcorner[4]-dx)+5;
		r.top=(ycorner[4]+dy)-5;
		r.bottom=(ycorner[4]+dy)+5;
		FrameOval(&r);
		oldrobot[2]=TRUE;
		}
	}
if(!(Wall[Me.xindex][Me.yindex+1]&0x01))
	{
	if(foodarray[Me.xindex][Me.yindex+1])
		{
		r.left=(xcorner[4]-dy)-3;
		r.right=(xcorner[4]-dy)+3;
		r.top=(ycorner[4]-dx)-3;
		r.bottom=(ycorner[4]-dx)+3;
		FrameOval(&r);
		oldegg[3]=TRUE;
		}
	if(robotarray[Me.xindex][Me.yindex+1])
		{
		r.left=(xcorner[4]-dy)-5;
		r.right=(xcorner[4]-dy)+5;
		r.top=(ycorner[4]-dx)-5;
		r.bottom=(ycorner[4]-dx)+5;
		FrameOval(&r);
		oldrobot[3]=TRUE;
		}
	}
if(!(Wall[Me.xindex+1][Me.yindex]&0x02))
	{
	if(foodarray[Me.xindex+1][Me.yindex])
		{
		r.left=(xcorner[4]+dx)-3;
		r.right=(xcorner[4]+dx)+3;
		r.top=(ycorner[4]-dy)-3;
		r.bottom=(ycorner[4]-dy)+3;
		FrameOval(&r);
		oldegg[4]=TRUE;
		}
	if(robotarray[Me.xindex+1][Me.yindex])
		{
		r.left=(xcorner[4]+dx)-5;
		r.right=(xcorner[4]+dx)+5;
		r.top=(ycorner[4]-dy)-5;
		r.bottom=(ycorner[4]-dy)+5;
		FrameOval(&r);
		oldrobot[4]=TRUE;
		}
	}
ClipRect(&compRect);
PenMode(patCopy);
}
/*---------------------------------------------------------------------- 
 */
DoCompass(cerase)
int cerase;
{
Rect r;
int xloc,yloc;
int tsin,tcos;
int dx,dy;
int cx,cy;

xloc=((Me.xindex<<8)-Me.xloc)>>2;
yloc=((Me.yindex<<8)-Me.yloc)>>2;
SetPort(moveWindow);
PenMode(patXor);
if(oldang!=Me.ang)
	{
	MoveTo(CCENTER,2*CCENTER+12);
	LineTo(CCENTER+(cost[oldang]>>3),(2*CCENTER+12)-(sint[oldang]>>3));
	MoveTo(CCENTER,2*CCENTER+12);
	LineTo(CCENTER+(cost[Me.ang]>>3),(2*CCENTER+12)-(sint[Me.ang]>>3));
	}
if(game==COLONY||cerase)
/*if(oldxloc!=xloc||oldyloc!=yloc||oldang!=Me.ang)*/
	{
	ClipRect(&floorRect);
	dx=xcorner[1]-xcorner[0]; dy=ycorner[0]-ycorner[1];
	MoveTo(xcorner[0]-dx,ycorner[0]+dy);
	LineTo(xcorner[1]+dx,ycorner[1]-dy);
	MoveTo(xcorner[1]+dy,ycorner[1]+dx);
	LineTo(xcorner[2]-dy,ycorner[2]-dx);
	MoveTo(xcorner[2]+dx,ycorner[2]-dy);
	LineTo(xcorner[3]-dx,ycorner[3]+dy);
	MoveTo(xcorner[3]-dy,ycorner[3]-dx);
	LineTo(xcorner[0]+dy,ycorner[0]+dx);
	if(oldegg[0])
		{
		r.left=xcorner[4]-3;
		r.right=xcorner[4]+3;
		r.top=ycorner[4]-3;
		r.bottom=ycorner[4]+3;
		FrameOval(&r);
		oldegg[0]=FALSE;
		}
	/*if(!(Wall[oldxindex][oldyindex]&0x01))*/
		{
		if(oldegg[1])
			{
			r.left=(xcorner[4]+dy)-3;
			r.right=(xcorner[4]+dy)+3;
			r.top=(ycorner[4]+dx)-3;
			r.bottom=(ycorner[4]+dx)+3;
			FrameOval(&r);
			oldegg[1]=FALSE;
			}
		if(oldrobot[1])
			{
			r.left=(xcorner[4]+dy)-5;
			r.right=(xcorner[4]+dy)+5;
			r.top=(ycorner[4]+dx)-5;
			r.bottom=(ycorner[4]+dx)+5;
			FrameOval(&r);
			oldrobot[1]=FALSE;
			}
		}
	/*if(!(Wall[oldxindex][oldyindex]&0x02))*/
		{
		if(oldegg[2])
			{
			r.left=(xcorner[4]-dx)-3;
			r.right=(xcorner[4]-dx)+3;
			r.top=(ycorner[4]+dy)-3;
			r.bottom=(ycorner[4]+dy)+3;
			FrameOval(&r);
			oldegg[2]=FALSE;
			}
		if(oldrobot[2])
			{
			r.left=(xcorner[4]-dx)-5;
			r.right=(xcorner[4]-dx)+5;
			r.top=(ycorner[4]+dy)-5;
			r.bottom=(ycorner[4]+dy)+5;
			FrameOval(&r);
			oldrobot[2]=FALSE;
			}
		}
	/*if(!(Wall[oldxindex][oldyindex+1]&0x01))*/
		{
		if(oldegg[3])
			{
			r.left=(xcorner[4]-dy)-3;
			r.right=(xcorner[4]-dy)+3;
			r.top=(ycorner[4]-dx)-3;
			r.bottom=(ycorner[4]-dx)+3;
			FrameOval(&r);
			oldegg[3]=FALSE;
			}
		if(oldrobot[3])
			{
			r.left=(xcorner[4]-dy)-5;
			r.right=(xcorner[4]-dy)+5;
			r.top=(ycorner[4]-dx)-5;
			r.bottom=(ycorner[4]-dx)+5;
			FrameOval(&r);
			oldrobot[3]=FALSE;
			}
		}
	/*if(!(Wall[oldxindex+1][oldyindex]&0x02))*/
		{
		if(oldegg[4])
			{
			r.left=(xcorner[4]+dx)-3;
			r.right=(xcorner[4]+dx)+3;
			r.top=(ycorner[4]-dy)-3;
			r.bottom=(ycorner[4]-dy)+3;
			FrameOval(&r);
			oldegg[4]=FALSE;
			}
		if(oldrobot[4])
			{
			r.left=(xcorner[4]+dx)-5;
			r.right=(xcorner[4]+dx)+5;
			r.top=(ycorner[4]-dy)-5;
			r.bottom=(ycorner[4]-dy)+5;
			FrameOval(&r);
			oldrobot[4]=FALSE;
			}
		}
	tsin=sint[Me.ang];
	tcos=cost[Me.ang];
	xcorner[0]=CCENTER+(((long)xloc * tsin - (long)yloc * tcos) >> 8);
	ycorner[0]=CCENTER-(((long)yloc * tsin + (long)xloc * tcos) >> 8);		
	xcorner[1]=CCENTER+(((long)(xloc+64) * tsin - (long)yloc * tcos) >> 8);
	ycorner[1]=CCENTER-(((long)yloc * tsin + (long)((xloc+64) * tcos)) >> 8);		
	xcorner[2]=CCENTER+(((long)(xloc+64) * tsin - (long)(yloc+64) * tcos) >> 8);
	ycorner[2]=CCENTER-(((long)(yloc+64) * tsin + (long)(xloc+64) * tcos) >> 8);		
	xcorner[3]=CCENTER+(((long)(xloc * tsin - (long)(yloc+64) * tcos)) >> 8);
	ycorner[3]=CCENTER-(((long)(yloc+64) * tsin + (long)xloc * tcos) >> 8);
	xcorner[4]=CCENTER+(((long)(xloc+32) * tsin - (long)(yloc+32) * tcos) >> 8);
	ycorner[4]=CCENTER-(((long)(yloc+32) * tsin + (long)(xloc+32) * tcos) >> 8);		
	xcorner[5]=CCENTER+(((long)(xloc+32) * tsin - (long)(yloc) * tcos) >> 8);
	ycorner[5]=CCENTER-(((long)(yloc) * tsin + (long)(xloc+32) * tcos) >> 8);		
	dx=xcorner[1]-xcorner[0]; dy=ycorner[0]-ycorner[1];
	MoveTo(xcorner[0]-dx,ycorner[0]+dy);
	LineTo(xcorner[1]+dx,ycorner[1]-dy);
	MoveTo(xcorner[1]+dy,ycorner[1]+dx);
	LineTo(xcorner[2]-dy,ycorner[2]-dx);
	MoveTo(xcorner[2]+dx,ycorner[2]-dy);
	LineTo(xcorner[3]-dx,ycorner[3]+dy);
	MoveTo(xcorner[3]-dy,ycorner[3]-dx);
	LineTo(xcorner[0]+dy,ycorner[0]+dx);
	if(foodarray[Me.xindex][Me.yindex])
		{
		r.left=xcorner[4]-3;
		r.right=xcorner[4]+3;
		r.top=ycorner[4]-3;
		r.bottom=ycorner[4]+3;
		FrameOval(&r);
		oldegg[0]=TRUE;
		}
if(!(Wall[Me.xindex][Me.yindex]&0x01))
	{
	if(foodarray[Me.xindex][Me.yindex-1])
		{
		r.left=(xcorner[4]+dy)-3;
		r.right=(xcorner[4]+dy)+3;
		r.top=(ycorner[4]+dx)-3;
		r.bottom=(ycorner[4]+dx)+3;
		FrameOval(&r);
		oldegg[1]=TRUE;
		}
	if(robotarray[Me.xindex][Me.yindex-1])
		{
		r.left=(xcorner[4]+dy)-5;
		r.right=(xcorner[4]+dy)+5;
		r.top=(ycorner[4]+dx)-5;
		r.bottom=(ycorner[4]+dx)+5;
		FrameOval(&r);
		oldrobot[1]=TRUE;
		}
	}
if(!(Wall[Me.xindex][Me.yindex]&0x02))
	{
	if(foodarray[Me.xindex-1][Me.yindex])
		{
		r.left=(xcorner[4]-dx)-3;
		r.right=(xcorner[4]-dx)+3;
		r.top=(ycorner[4]+dy)-3;
		r.bottom=(ycorner[4]+dy)+3;
		FrameOval(&r);
		oldegg[2]=TRUE;
		}
	if(robotarray[Me.xindex-1][Me.yindex])
		{
		r.left=(xcorner[4]-dx)-5;
		r.right=(xcorner[4]-dx)+5;
		r.top=(ycorner[4]+dy)-5;
		r.bottom=(ycorner[4]+dy)+5;
		FrameOval(&r);
		oldrobot[2]=TRUE;
		}
	}
if(!(Wall[Me.xindex][Me.yindex+1]&0x01))
	{
	if(foodarray[Me.xindex][Me.yindex+1])
		{
		r.left=(xcorner[4]-dy)-3;
		r.right=(xcorner[4]-dy)+3;
		r.top=(ycorner[4]-dx)-3;
		r.bottom=(ycorner[4]-dx)+3;
		FrameOval(&r);
		oldegg[3]=TRUE;
		}
	if(robotarray[Me.xindex][Me.yindex+1])
		{
		r.left=(xcorner[4]-dy)-5;
		r.right=(xcorner[4]-dy)+5;
		r.top=(ycorner[4]-dx)-5;
		r.bottom=(ycorner[4]-dx)+5;
		FrameOval(&r);
		oldrobot[3]=TRUE;
		}
	}
if(!(Wall[Me.xindex+1][Me.yindex]&0x02))
	{
	if(foodarray[Me.xindex+1][Me.yindex])
		{
		r.left=(xcorner[4]+dx)-3;
		r.right=(xcorner[4]+dx)+3;
		r.top=(ycorner[4]-dy)-3;
		r.bottom=(ycorner[4]-dy)+3;
		FrameOval(&r);
		oldegg[4]=TRUE;
		}
	if(robotarray[Me.xindex+1][Me.yindex])
		{
		r.left=(xcorner[4]+dx)-5;
		r.right=(xcorner[4]+dx)+5;
		r.top=(ycorner[4]-dy)-5;
		r.bottom=(ycorner[4]-dy)+5;
		FrameOval(&r);
		oldrobot[4]=TRUE;
		}
	}
	}
PenMode(patCopy);
oldxloc=xloc;
oldyloc=yloc;
oldxindex=Me.xindex;
oldyindex=Me.yindex;
oldang=Me.ang;
ClipRect(&compRect);
cerase=0;
}
