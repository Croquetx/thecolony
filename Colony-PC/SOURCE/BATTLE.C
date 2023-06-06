/*  #define IBM_asqrt		 */
/*  #define IBM_BattleSet	 */
/*  #define IBM_BThink		 */
/*  #define IBM_Battlebackdrop	 */
/*  #define IBM_BattlePyramid	 */
/*  #define IBM_BattleQuadrant	 */
/*  #define IBM_BattleTank	 */
/*  #define IBM_BattleMake	 */
/*  #define IBM_BattleCommand	 */
/*  #define IBM_BattleShoot      */
/*  #define IBM_ProjCommand      */
/*  #define IBM_DrawBPrism	 */
/*  #define IBM_BClockwise	 */
/*  #define IBM_BRotate 	 */
/*                       	 */
/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/

/*
#include <Quickdraw.h>
#include <WindowMgr.h>
#include <MenuMgr.h>
#include <EventMgr.h>
#include <DialogMgr.h>
#include <DeskMgr.h>
#include <math.h>
*/

#define EXT extern 
#include "gamedefs.h"
#define BSIZE 150
#define BW 1
#define LROTATE 1
#define RROTATE	2
#define FORWARD	3
#define SHOOT	4
Locate *pwh[100];
int maxp;
int round=0;
int battledx;
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
long asqrt(d,seed)
long d,seed;
{
#if !defined(IBM_asqrt)
long try=seed>>1,try2,i=0;
long hitry=seed,lotry=0;
long error=d>>8;
long distance;
try2=try*try;
distance=d-try2;
while(abs(distance)>error && i<20)
	{
	i++;
	if(distance>0)
		{
		lotry=try;
		try=(try+hitry)>>1;
		}
	else if(distance<0)
		{
		hitry=try;
		try=(try+lotry)>>1;
		}
	else if(distance==0)return(try);
	distance=d-(try2=try*try);
	}
return(try);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
BattleSet()
{
#if !defined(IBM_BattleSet)
int i,j,k;
int fx,fy;

for(i=0;i<4;i++)
for(j=0;j<4;j++)
	{
	k=i+j*4;
	bfight[k].xloc=(0x2000*i+BSIZE)-0x3000;
	bfight[k].yloc=(0x2000*j+BSIZE)-0x3000;
	bfight[k].look=bfight[k].ang=0xFF&Random();
	bfight[k].lookx=0;
	bfight[k].delta=4;
	bfight[k].type=CUBE;
	bfight[k].power[1]=15+0x00F&Random();
	for(k=0;k<MAXQUAD;k++)
		{
		do	{
			fx=0x2000*i+BSIZE+(0x1FFF&Random());
			while(fx>0x2000*(i+1)-BSIZE)
				fx=0x2000*i+BSIZE+(0x1FFF&Random());
			fy=0x2000*j+BSIZE+(0x1FFF&Random());
			while(fy>0x2000*(j+1)-BSIZE)
				fy=0x2000*j+BSIZE+(0x1FFF&Random());
			}while((fx>Enter.xloc-8*BSIZE && 
				fx<Enter.xloc+2*BSIZE &&
				fy>Enter.yloc-2*BSIZE &&
				fy<Enter.yloc+2*BSIZE)||
				(fx>Ship.xloc-2*BSIZE && 
				fx<Ship.xloc+2*BSIZE &&
				fy>Ship.yloc-2*BSIZE &&
				fy<Ship.yloc+2*BSIZE));
		(*pwhere)[i][j][k].xloc=fx;
		(*pwhere)[i][j][k].yloc=fy;
		(*pwhere)[i][j][k].ang=0xFF&Random();
		(*pwhere)[i][j][k].type=PYRAMID;
		}
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int Bcounter=0;
BThink()
{
#if !defined(IBM_BThink)
int i,j;
unsigned char *pang;
int fx,fy;
long ax,ay,dx,dy,adx,ady;
long dir,d;
int len;
int toofar;
int d_shoot=4000;
int yes_shoot=0;
int who_shoot;
int xcheck,ycheck;
if(projon)
	{
	fx=Proj.xloc+(cost[Proj.ang]<<2);
	fy=Proj.yloc+(sint[Proj.ang]<<2);
	if(0==(pcount--))projon=FALSE;
	ProjCommand(fx,fy);
	}
xcheck=bfight[round].xloc;
ycheck=bfight[round].yloc;
for(i=0;i<16;i++)
	{
	if(xcheck>bfight[i].xloc-BSIZE && 
	   xcheck<bfight[i].xloc+BSIZE &&
	   ycheck>bfight[i].yloc-BSIZE &&
	   ycheck<bfight[i].yloc+BSIZE &&i!=round)
		{
		while(bfight[i].xloc-Me.xloc<2000&&
				bfight[i].yloc-Me.yloc<2000)
				{
				bfight[i].xloc=Random();
				bfight[i].yloc=Random();
				}
		}
	pang=&bfight[i].ang;
	ax=cost[*pang]; 
	ay=sint[*pang];
	dx=bfight[i].xloc-Me.xloc;
	dy=bfight[i].yloc-Me.yloc;
	adx=abs(dx);
	ady=abs(dy);
	toofar=FALSE;
	if(adx>4000 || ady>4000)
		{
		dx>>=8;
		dy>>=8;
		toofar=TRUE;
		}
	dir=dx*ay-dy*ax;
	if(!toofar)
		{
		d=asqrt(dx*dx+dy*dy,max(adx,ady));
		if(d>0)
			{
			dir=dir/d;
			if(abs(dir)<10)
				{
				if(dir<0)(*pang)-=1;
				if(dir>0)(*pang)+=1;
				}
			else
				{
				if(dir<0)(*pang)-=4;
				if(dir>0)(*pang)+=4;
				}
			if(abs(dir)==0)
				{
				if((!projon) && d<d_shoot)
					{
					d_shoot=d;
					who_shoot=i;
					yes_shoot=TRUE;
					}
				}
			}
		}
	else
		{
		if(dir<0)(*pang)-=4;
		if(dir>0)(*pang)+=4;
		}
	if((*pang)<0)(*pang)+=256;
	if((*pang)>255)(*pang)-=256;
	fx=bfight[i].xloc+(cost[*pang]>>2);
	fy=bfight[i].yloc+(sint[*pang]>>2);
	if(d>250||toofar)
		{
		if( fx>Ship.xloc-2*BSIZE && 
			fx<Ship.xloc+2*BSIZE &&
			fy>Ship.yloc-4*BSIZE &&
			fy<Ship.yloc+4*BSIZE)
			{
			(*pang)+=8;
/*			if((*pang)>255)(*pang)-=256;*/
			}
		else if(fx>Enter.xloc-2*BSIZE && 
			fx<Enter.xloc+2*BSIZE &&
			fy>Enter.yloc-2*BSIZE &&
			fy<Enter.yloc+2*BSIZE)
			{
			(*pang)+=8;
/*			if((*pang)>255)(*pang)-=256;*/
			}
		else
			{
			bfight[i].xloc=fx;
			bfight[i].yloc=fy;
			}
		}
	else DoBonkSound();
	bfight[i].look=(*pang);
	}
round++;
if(round==16)round=0;
if(yes_shoot)
	{
	DoShootSound();
	Proj.ang=bfight[who_shoot].ang;
	Proj.look=bfight[who_shoot].look;
	Proj.xloc=bfight[who_shoot].xloc+(cost[Proj.ang]<<1);
	Proj.yloc=bfight[who_shoot].yloc+(sint[Proj.ang]<<1);
	pcount=10;
	projon=TRUE;
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
 
Battlebackdrop()
{
#if !defined(IBM_Battlebackdrop)
int xloc,i,sunx,sunon=0;
int ang;
Rect sun;
Rect Sky, Ground;

battledx=1+((screenR.right-screenR.left)/59);
if(MonoCrome)    PenColor(realcolor[vBLACK]);
else    PenColor(realcolor[vBLUE]);
Sky.left=screenR.left;
Sky.right=screenR.right;
Sky.top=screenR.top;
Sky.bottom=centerY;
FillRect(&Sky,1);

PenColor(realcolor[vBLACK]);

Ground.left=screenR.left;
Ground.right=screenR.right;
Ground.top=centerY;
Ground.bottom=screenR.bottom;
FillRect(&Ground,1);

/* PenPat(white); return;/**/
/*   PenPat(ltGray);   randy  */
ang=Me.look;
xloc= -battledx;
if(ang&0x01)
	{
	xloc+=battledx;
	ang--;
	}
if(ang<0)ang+=256;
if(!MonoCrome)PenColor(realcolor[vBROWN]);
else PenColor(1);
xloc+=screenR.left;
MoveTo(xloc,mountains[ang]+centerY);
for(i=0;i<64;i+=2)
	{
	xloc+=2*battledx;
	ang-=2;
	if(ang<0)
		{
		ang+=256;
		sunx=xloc-battledx;
		sunon=TRUE;
		}
	LineTo(xloc,mountains[ang]+centerY);
	}

if(MonoCrome)
	{
	PenColor(1);
	MoveTo(screenR.left,centerY);
	LineTo(screenR.right,centerY);
	}
if(sunon)
	{
	if ( !MonoCrome )PenColor(realcolor[vYELLOW]);
	BackColor(realcolor[vBLACK]);
	sun.top=pix_per_Qinch_y;
	sun.left=sunx-pix_per_Qinch_x*2;
	sun.right=sunx+pix_per_Qinch_x*2;
	sun.bottom=pix_per_Qinch_y*5;
	FillOval(&sun,1);

	sun.top=pix_per_Qinch_y*2;
	sun.left=sunx-pix_per_Qinch_x;
	sun.right=sunx;
	sun.bottom=pix_per_Qinch_y*3;
	FillOval(&sun,2);

	sun.top=pix_per_Qinch_y*3.5;
	sun.left=sunx-pix_per_Qinch_x*1.5;
	sun.right=sunx-pix_per_Qinch_x*1;
	sun.bottom=pix_per_Qinch_y*4.0;
	FillOval(&sun,2);

	sun.top=pix_per_Qinch_y*3.0;
	sun.left=sunx+pix_per_Qinch_x*0.5;
	sun.right=sunx+pix_per_Qinch_x*1.0;
	sun.bottom=pix_per_Qinch_y*4.0;
	FillOval(&sun,2);
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
BattlePyramid()
{
#if !defined(IBM_BattlePyramid)
int i;
int qx,qy;
int quad;
int xloc,yloc;

if(!MonoCrome)PenColor(realcolor[vBROWN]);
else PenColor(1);
maxp=0;
if(0>(xloc=Me.xloc))xloc+=0x7FFF;
if(0>(yloc=Me.yloc))yloc+=0x7FFF;
qx=xloc>>13;
qy=yloc>>13;
quad=Me.look>>6;	/*divide by 64*/
tsin=cost[Me.look];
tcos=sint[Me.look];
switch(quad)
	{
	case 0:/*north*/
		BattleQuadrant(qx,qy,xloc,yloc);
		BattleQuadrant(qx-1,qy,xloc,yloc);
		BattleQuadrant(qx+1,qy,xloc,yloc);
		qy++;
		BattleQuadrant(qx,qy,xloc,yloc);
		BattleQuadrant(qx-1,qy,xloc,yloc);
		BattleQuadrant(qx+1,qy,xloc,yloc);
		break;
	case 1:/*west*/
		BattleQuadrant(qx,qy,xloc,yloc);
		BattleQuadrant(qx,qy-1,xloc,yloc);
		BattleQuadrant(qx,qy+1,xloc,yloc);
		qx--;
		BattleQuadrant(qx,qy,xloc,yloc);
		BattleQuadrant(qx,qy-1,xloc,yloc);
		BattleQuadrant(qx,qy+1,xloc,yloc);
		break;
	case 2:/*south*/
		BattleQuadrant(qx,qy,xloc,yloc);
		BattleQuadrant(qx-1,qy,xloc,yloc);
		BattleQuadrant(qx+1,qy,xloc,yloc);
		qy--;
		BattleQuadrant(qx,qy,xloc,yloc);
		BattleQuadrant(qx-1,qy,xloc,yloc);
		BattleQuadrant(qx+1,qy,xloc,yloc);
		break;
	case 3:/*east*/
		BattleQuadrant(qx,qy,xloc,yloc);
		BattleQuadrant(qx,qy-1,xloc,yloc);
		BattleQuadrant(qx,qy+1,xloc,yloc);
		qx++;
		BattleQuadrant(qx,qy,xloc,yloc);
		BattleQuadrant(qx,qy-1,xloc,yloc);
		BattleQuadrant(qx,qy+1,xloc,yloc);
		break;
	}
BattleTank();
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
extern Prism Rock;
BattleQuadrant(qx,qy,xMe,yMe)
int qx,qy,xMe,yMe;
{
#if !defined(IBM_BattleQuadrant)
long xloc,yloc;
int xx,yy;
int i,j;
Locate *pw;
int dx=0,dy=0;
int look;

if(qx<0){qx=3; dx=0x7FFF;}
if(qx>3){qx=0; dx=0x7FFF;}
if(qy<0){qy=3; dy=0x7FFF;}
if(qy>3){qy=0; dy=0x7FFF;}
pw=(*pwhere)[qx][qy];
for(i=0;i<MAXQUAD;i++)
	{
	xloc=pw[i].xloc-(xMe+dx);
	yloc=pw[i].yloc-(yMe+dy);
	if((abs(xloc))+(abs(yloc))<8000)
		{
		/*rotation*/
		yy = (xloc * tsin + yloc * tcos) >> 7;
		if(yy>0)
			{
			xx = (xloc * tcos - yloc * tsin) >> 7;
			if(yy>abs(xx))
				{
				pw[i].xmn=Width;
				pw[i].xmx=0;
				pw[i].zmn=Height;
				pw[i].zmx=0;
				BattleMake(&Rock,&pw[i],xx,yy);
				DrawBPrism(&Rock,0);
				pwh[maxp]=&pw[i];
				maxp++;
				pw[i].dist=yy;
				}
			}
		}
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
#define TANKMAX 24
extern Prism Tank[7];
extern Prism Project;
extern Prism Entrance[2];
extern Prism Shuttle[7];
BattleTank()
{
#if !defined(IBM_BattleTank)
int i,j,look,xx,yy;
long xloc,yloc;
if(!MonoCrome)PenColor(realcolor[vMAGENTA]);
else PenColor(1);
for(i=0;i<16;i++)
	{
	xloc=bfight[i].xloc-Me.xloc;
	yloc=bfight[i].yloc-Me.yloc;
	if((abs(xloc))+(abs(yloc))<8000)
		{
		/*rotation*/
		yy = (xloc * tsin + yloc * tcos) >> 7;
		if(yy>0)
			{
			xx = (xloc * tcos - yloc * tsin) >> 7;
			if(yy>abs(xx))
				{
				bfight[i].xmn=Width;
				bfight[i].xmx=0;
				bfight[i].zmn=Height;
				bfight[i].zmx=0;
				BattleMake(&Tank[0],&bfight[i],xx,yy);
				bfight[i].lookx+=bfight[i].delta;
				if(bfight[i].lookx<-TANKMAX||
				   bfight[i].lookx>TANKMAX)
					bfight[i].delta=-bfight[i].delta;
				for(j=0;j<4;j++)
					{
					look=nabs(bfight[i].lookx)-32;
					if(look<0)look+=256;
					if(look>=256)look-=256;
					BRotate(look,Tank[3].pnt[j],Tank[1].pnt[j]);
					Tank[1].pnt[j][2]=Tank[3].pnt[j][2];
					Tank[1].pnt[j][0]+=120;
					look=abs(bfight[i].lookx)-32;
					if(look<0)look+=256;
					if(look>=256)look-=256;
					BRotate(look,Tank[4].pnt[j],Tank[2].pnt[j]);
					Tank[2].pnt[j][2]=Tank[4].pnt[j][2];
					Tank[2].pnt[j][0]+=120;
					}
				BattleMake(&Tank[1],&bfight[i],xx,yy);
				BattleMake(&Tank[2],&bfight[i],xx,yy);
				BattleMake(&Tank[5],&bfight[i],xx,yy);
				BattleMake(&Tank[6],&bfight[i],xx,yy);
				if(!MonoCrome)PenColor(realcolor[vGREEN]);
				else PenColor(1);
				DrawBPrism(&Tank[5],0);
				DrawBPrism(&Tank[6],0);
				PenColor(realcolor[vWHITE]);
				DrawBPrism(&Tank[0],0);
				DrawBPrism(&Tank[1],0);
				DrawBPrism(&Tank[2],0);
				bfight[i].dist=yy;
				pwh[maxp]=&bfight[i];
				maxp++;
				bfight[i].dist=yy;
				insight = insight||(bfight[i].xmn<centerX &&
					bfight[i].xmx>centerX);
				}
			}
		}
	}

if(!MonoCrome)PenColor(realcolor[vYELLOW]);
else PenColor(1);

if(projon)
	{
	xloc=Proj.xloc-Me.xloc;
	yloc=Proj.yloc-Me.yloc;
	if((abs(xloc))+(abs(yloc))<20000)
		{
		/*rotation*/
		yy = (xloc * tsin + yloc * tcos) >> 7;
		if(yy>0)
			{
			xx = (xloc * tcos - yloc * tsin) >> 7;
			if(yy>abs(xx))
				{
				Proj.xmn=Width;
				Proj.xmx=0;
				Proj.zmn=Height;
				Proj.zmx=0;
				BattleMake(&Project,&Proj,xx,yy);
				DrawBPrism(&Project,0);
				pwh[maxp]=&Proj;
				maxp++;
				Proj.dist=yy;
				}
			}
		}
	}


if(!MonoCrome)PenColor(realcolor[vRED]);
else PenColor(1);

xloc=Enter.xloc-Me.xloc;
yloc=Enter.yloc-Me.yloc;
if((abs(xloc))+(abs(yloc))<20000)
	{
	/*rotation*/
	yy = (xloc * tsin + yloc * tcos) >> 7;
	if(yy>0)
		{
		xx = (xloc * tcos - yloc * tsin) >> 7;
		if(yy>abs(xx))
			{
			Enter.xmn=Width;
			Enter.xmx=0;
			Enter.zmn=Height;
			Enter.zmx=0;
			BattleMake(&Entrance[0],&Enter,xx,yy);
			DrawBPrism(&Entrance[0],0);
			BattleMake(&Entrance[1],&Enter,xx,yy);
			DrawBPrism(&Entrance[1],0);
			pwh[maxp]=&Enter;
			maxp++;
			Enter.dist=yy;
			}
		}
	}
xloc=Ship.xloc-Me.xloc;
yloc=Ship.yloc-Me.yloc;
if((abs(xloc))+(abs(yloc))<20000)
	{
	/*rotation*/
	yy = (xloc * tsin + yloc * tcos) >> 7;
	if(yy>0)
		{
		xx = (xloc * tcos - yloc * tsin) >> 7;
		if(yy>abs(xx))
			{
			BattleMake(&Shuttle[0],&Ship,xx,yy);
			DrawBPrism(&Shuttle[0],0);
			BattleMake(&Shuttle[1],&Ship,xx,yy);
			DrawBPrism(&Shuttle[1],0);
			BattleMake(&Shuttle[2],&Ship,xx,yy);
			DrawBPrism(&Shuttle[2],0);
			BattleMake(&Shuttle[3],&Ship,xx,yy);
			DrawBPrism(&Shuttle[3],1);
			BattleMake(&Shuttle[4],&Ship,xx,yy);
			DrawBPrism(&Shuttle[4],1);
			BattleMake(&Shuttle[5],&Ship,xx,yy);
			DrawBPrism(&Shuttle[5],1);
			BattleMake(&Shuttle[6],&Ship,xx,yy);
			DrawBPrism(&Shuttle[6],0);
			pwh[maxp]=&Ship;
			maxp++;
			Ship.dist=yy;
			}
		}
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
BattleMake(this,where,x,y)
Prism *this;
Locate *where;
int x,y;
{
#if !defined(IBM_BattleMake)
int i;
int xx,yy,zz;
unsigned char ang;
int mnmx;

ang=32+where->ang-Me.look;
/*if(ang<0)ang+=256;
if(ang>255)ang-=256;*/
for(i=0; i < this->points ;i++)
	{ 
	BRotate(ang,this->pnt[i],this->copy[i]);
	xx=this->copy[i][0]+=x;
	yy=this->copy[i][1]+=y;
	zz=this->copy[i][2] = this->pnt[i][2];
	/*projection*/
	if(yy <= 0)yy=1;
	this->copy[i][0] = centerX + ((long)xx << 8) / yy;/*compute x projection	*/
	this->copy[i][1] = yy;
	this->copy[i][2] = centerY - ((long)zz << 8) / yy;/*compute z projection	*/
	mnmx=this->copy[i][0];
	if(where->xmn>mnmx)where->xmn=mnmx;
	if(where->xmx<mnmx)where->xmx=mnmx;
	mnmx=this->copy[i][2];
	if(where->zmn>mnmx)where->zmn=mnmx;
	if(where->zmx<mnmx)where->zmx=mnmx;
	}
for(i=0;i < this->surfaces ;i++)
	this->vsurface[i]=BClockwise(this,i);/*which side are we on?*/
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
BattleCommand(xnew,ynew)
int xnew,ynew;
{
#if !defined(IBM_BattleCommand)
int xcheck,ycheck,i,j,qx,qy,oldx,oldy;
Locate *pw;

xcheck=xnew;
ycheck=ynew;
for(i=0;i<16;i++)
	if(xcheck>bfight[i].xloc-BSIZE && 
	   xcheck<bfight[i].xloc+BSIZE &&
	   ycheck>bfight[i].yloc-BSIZE &&
	   ycheck<bfight[i].yloc+BSIZE)
		{
		oldx=Me.xloc;
		oldy=Me.yloc;
		Me.xloc=xnew;
		Me.yloc=ynew;
		/*  Display();	*/
		DoBonkSound();
		Me.xloc=oldx;
		Me.yloc=oldy;
		return;
		}
if( xcheck>Ship.xloc-2*BSIZE && 
	xcheck<Ship.xloc &&
	ycheck>Ship.yloc-BSIZE/2 &&
	ycheck<Ship.yloc+BSIZE/2)
	{
	game=COLONY;
	Me.xloc=900;
	Me.yloc=3000;
	Me.xindex=Me.xloc>>8;
	Me.yindex=Me.yloc>>8;
	for(i=0;i<32;i++)
	for(j=0;j<32;j++)
		robotarray[i][j]=0;
	robotarray[Me.xindex][Me.yindex]=MENUM;
	TunnelAirlock();
	load_mapnum(1,TRUE);	/*	load spaceship		*/
	return;
	}
if( xcheck>Enter.xloc-2*BSIZE && 
	xcheck<Enter.xloc &&
	ycheck>Enter.yloc-BSIZE/2 &&
	ycheck<Enter.yloc+BSIZE/2)
	{
	game=COLONY;
	Me.xloc=384;
	Me.yloc=640;
	Me.xindex=1;
	Me.yindex=1;
	for(i=0;i<32;i++)
	for(j=0;j<32;j++)
		robotarray[i][j]=0;
	robotarray[Me.xindex][Me.yindex]=MENUM;
	TunnelAirlock();
	load_mapnum(2,TRUE);	/*	load first map		*/
	return;
	}
if( xcheck>Ship.xloc-2*BSIZE && 
	xcheck<Ship.xloc+2*BSIZE &&
	ycheck>Ship.yloc-4*BSIZE &&
	ycheck<Ship.yloc+4*BSIZE)
	{
	oldx=Me.xloc;
	oldy=Me.yloc;
	Me.xloc=xnew;
	Me.yloc=ynew;
	/*  Display();	 */
	DoBonkSound();
	Me.xloc=oldx;
	Me.yloc=oldy;
	return;
	}
if(xcheck>Enter.xloc-2*BSIZE && 
	xcheck<Enter.xloc+2*BSIZE &&
	ycheck>Enter.yloc-2*BSIZE &&
	ycheck<Enter.yloc+2*BSIZE)
	{
	oldx=Me.xloc;
	oldy=Me.yloc;
	Me.xloc=xnew;
	Me.yloc=ynew;
	/*  Display();	*/
	DoBonkSound();
	Me.xloc=oldx;
	Me.yloc=oldy;
	return;
	}
if(xcheck<0)xcheck+=0x7FFF;
if(ycheck<0)ycheck+=0x7FFF;
qx=xcheck>>13;
qy=ycheck>>13;
pw=(*pwhere)[qx][qy];
for(i=0;i<MAXQUAD;i++)
	if(xcheck>pw[i].xloc-BSIZE && xcheck<pw[i].xloc+BSIZE &&
	   ycheck>pw[i].yloc-BSIZE && ycheck<pw[i].yloc+BSIZE)
		{
		oldx=Me.xloc;
		oldy=Me.yloc;
		Me.xloc=xnew;
		Me.yloc=ynew;
		/*   Display();   */
		DoBonkSound();
		Me.xloc=oldx;
		Me.yloc=oldy;
		return;
		}
Me.xloc=xnew;
Me.yloc=ynew;
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int send=0;
BattleShoot()
{
#if !defined(IBM_BattleShoot)
int s0,s1;
register long i;	
GrafPtr	savePort;
int psize=10;
int dy=11584,num=-1,r0;
Rect r;

if(cshoot)
	{
	cx=myPt.h;
	cy=myPt.v;
	}
else
	{
	cx=centerX;
	cy=centerY;
	}
if(Me.power[0] && weapons && !fl)   /* any weapons? */
	{
	DoBangSound();

	doShootCircles(cx, cy);

	SetPower(-2,0,0);
	num=maxp;
	for(i=0;i<maxp;i++)
		if( pwh[i]->xmn<cx &&
			pwh[i]->xmx>cx &&
			pwh[i]->zmn<cy &&
			pwh[i]->zmx>cy &&
			pwh[i]->dist<dy)
			{
			dy=pwh[i]->dist;
			num=i;
			}
	if(num<maxp&&dy<4000)
		{
		r0=rtable[dy];
		if(r0>100)r0=100;
		r.top=cy-r0;
		r.bottom=cy+r0;
		r.left=cx-r0;
		r.right=cx+r0;

		doBurnHole(&r);

		if(pwh[num]->type==CUBE)
			{
			pwh[num]->power[1]-=epower[0];
			if(pwh[num]->power[1]<0)
				{
				pwh[num]->power[1]=15+0x00F&Random();
				if(send)
					{
					pwh[num]->xloc=Me.xloc+16000;
					pwh[num]->yloc=Me.yloc+Random();
					}
				else
					{
					pwh[num]->xloc=Me.xloc+Random();
					pwh[num]->yloc=Me.yloc+16000;
					}
				send=!send;
				DoExplodeSound();
				/*while(!SoundDone());   /* randy InvertRect(&Clip);  */
				}
			}
		}
	/*  SetPort(savePort);	*/
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
ProjCommand(xcheck,ycheck)
int xcheck,ycheck;
{
#if !defined(IBM_ProjCommand)
int i,j,qx,qy;
Locate *pw;
GrafPtr	savePort;

Proj.xloc=xcheck;
Proj.yloc=ycheck;
if(xcheck>Me.xloc-200 && 
	xcheck<Me.xloc+200 &&
	ycheck>Me.yloc-200 &&
	ycheck<Me.yloc+200)
	{
	/*  Display();	*/
	SetPower(-4,-4,-4);
	DoExplodeSound();
	/*  GetPort( &savePort );    */
	/*  SetPort( theWindow );   */
	/*   InvertRect(&Clip);    */
	/*  SetPort( savePort );  */
	projon=FALSE;
	return;
	}
for(i=0;i<16;i++)
	if(xcheck>bfight[i].xloc-BSIZE && 
	   xcheck<bfight[i].xloc+BSIZE &&
	   ycheck>bfight[i].yloc-BSIZE &&
	   ycheck<bfight[i].yloc+BSIZE)
		{
		while(bfight[i].xloc-Me.xloc<2000&&
				bfight[i].yloc-Me.yloc<2000)
				{
				bfight[i].xloc=Random();
				bfight[i].yloc=Random();
				}
		DoBonkSound();
		projon=FALSE;
		return;
		}
if( xcheck>Ship.xloc-2*BSIZE && 
	xcheck<Ship.xloc+2*BSIZE &&
	ycheck>Ship.yloc-4*BSIZE &&
	ycheck<Ship.yloc+4*BSIZE)
	{
	DoBonkSound();
	projon=FALSE;
	return;
	}
if(xcheck>Enter.xloc-2*BSIZE && 
	xcheck<Enter.xloc+2*BSIZE &&
	ycheck>Enter.yloc-2*BSIZE &&
	ycheck<Enter.yloc+2*BSIZE)
	{
	DoBonkSound();
	projon=FALSE;
	return;
	}
if(xcheck<0)xcheck+=0x7FFF;
if(ycheck<0)ycheck+=0x7FFF;
qx=xcheck>>13;
qy=ycheck>>13;
pw=(*pwhere)[qx][qy];
for(i=0;i<MAXQUAD;i++)
	if(xcheck>pw[i].xloc-BSIZE && xcheck<pw[i].xloc+BSIZE &&
	   ycheck>pw[i].yloc-BSIZE && ycheck<pw[i].yloc+BSIZE)
		{
		DoBonkSound();
		projon=FALSE;
		return;
		}
#endif
}
/*---------------------------------------------------------------------
 * DrawBPrism()
 *---------------------------------------------------------------------
 */
DrawBPrism(obj,force)
register Prism *obj;
int force;
{
#if !defined(IBM_DrawBPrism)
register long i,j;
register int x[64],y[64];

for(i=0;i < obj->surfaces ;i++)
	{
	if(obj->vsurface[i]||force)
		{
		MoveTo(obj->copy[obj->surface[i][2]][0],
			obj->copy[obj->surface[i][2]][2]);
		for(j=0;j<obj->surface[i][1];j++)
			LineTo(obj->copy[obj->surface[i][j+2]][0],
				obj->copy[obj->surface[i][j+2]][2]);
		LineTo(obj->copy[obj->surface[i][2]][0],
			obj->copy[obj->surface[i][2]][2]);
		}
	}
#endif
}
/*---------------------------------------------------------------------
 * BClockwise(pt)
 *---------------------------------------------------------------------
 */
int BClockwise(obj,surf)
Prism *obj;
int surf;
{
#if !defined(IBM_BClockwise)
register long dx,dy,dxp,dyp;
long i;
long b;

for(i=2 ; i<obj->surface[surf][1] ; i++)
	{
	dx= obj->copy[obj->surface[surf][i]][0] -
		obj->copy[obj->surface[surf][i+1]][0]; 
	dy= obj->copy[obj->surface[surf][i]][2] -
		obj->copy[obj->surface[surf][i+1]][2];
	dxp=obj->copy[obj->surface[surf][i+2]][0] -
		obj->copy[obj->surface[surf][i+1]][0]; 
	dyp=obj->copy[obj->surface[surf][i+2]][2] -
		obj->copy[obj->surface[surf][i+1]][2];
	if(dx<0)
		{
		if(dy==0)
			{
			if( dyp>0 ) return(FALSE);
			if( dyp<0 ) return(TRUE);
			}
		else
			{
			b = dy*dxp-dx*dyp;
			if( b>0 ) return(FALSE);
			if( b<0 ) return(TRUE);
			}
		}
	else if( dx>0 )
		{
		if( dy==0 )
			{
			if(dyp<0)return(FALSE);
			if(dyp>0)return(TRUE);
			}
		else
			{
			b=dx*dyp-dy*dxp;
			if(b<0)return(FALSE);
			if(b>0)return(TRUE);
			}
		}
	else /*dx==0*/
		{
		if(dy<0)
			{
			if(dxp>0)return(TRUE);
			if(dxp<0)return(FALSE);
			}
		if(dy>0)
			{
			if(dxp<0)return(TRUE);
			if(dxp>0)return(FALSE);
			}
		}
	}
return(FALSE);
#endif
}
/*---------------------------------------------------------------------
 * BRotate(ang,x,y,px,py)
 * unsigned char ang;
 * int x,y;
 * int *px,*py;
 * Generalized rotation function rotates x and y around z through
 * angle ang and places result in *px and *py.
 *---------------------------------------------------------------------
 */
BRotate(ang,from,to)
register int from[2],to[2];
unsigned char ang;
{	
#if !defined(IBM_BRotate)
register long tcos,tsin;

tcos=cost[ang];
tsin=sint[ang];
to[0] = (from[0] * tcos - from[1] * tsin) >> 7;
to[1] = (from[0] * tsin + from[1] * tcos) >> 7;
#endif
}
