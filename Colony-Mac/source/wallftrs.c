/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
/*-----------------------------------------------------------------------* 
 * wall_features.c
 *-----------------------------------------------------------------------* 
 * drawwind(ldata,rdata)
 *		int ldata[2],rdata[2];
 * drawClosedDoor(ldata,rdata)
 *		int ldata[2],rdata[2];
 * drawOpenDoor(ldata,rdata,ldata2,rdata2)
 *		int ldata[2],rdata[2],ldata2[2],rdata2[2];
 * drawTunnel(ldata,rdata,ldata2,rdata2)
 *		int ldata[2],rdata[2],ldata2[2],rdata2[2];
 * drawglyphs(ldata,rdata)
 *		int ldata[2],rdata[2];
 * drawbooks(ldata,rdata,ldata2,rdata2)
 *		int ldata[2],rdata[2];
 *		int ldata2[2],rdata2[2];
 * draw_up_stairs(ldata,rdata,ldata2,rdata2)
 *		int ldata[2],rdata[2];
 *		int ldata2[2],rdata2[2];
 * draw_dn_stairs(ldata,rdata,ldata2,rdata2)
 *		int ldata[2],rdata[2];
 *		int ldata2[2],rdata2[2];
 * drawALOpen(ldata,rdata)
 *		int ldata[2],rdata[2];
 * drawALClosed(ldata,rdata)
 *		int ldata[2],rdata[2];
 * drawOpenSSDoor(ldata,rdata)
 *		int ldata[2],rdata[2];
 * drawClosedSSDoor(ldata,rdata)
 *		int ldata[2],rdata[2];
 * drawelevator(ldata,rdata)
 *		int ldata[2],rdata[2];
 * drawColor(map,ldata,rdata)
 *		char map[4];
 *		int ldata[2],rdata[2];
 * int split7x7(ldata,rdata,lr,ud)
 *		int ldata[2],rdata[2];
 *		int lr[7];
 *		int ud[7][7];
 *-----------------------------------------------------------------------*/
#define EXT extern
#include "cgamedefs.h"
#include "colordef.h"
/*-----------------------------------------------------------------------*/
drawwind(ldata,rdata)
int ldata[2],rdata[2];
{
int x1,x2,xc;
int xx1,xx2;
int y1,y2,y3,y4;
int yl,yr;
int yy1,yy2,yy3,yy4;
int yy[4],xx[4];

ColorWall(ldata,rdata);
x1=ldata[0];
x2=rdata[0];

y1=ldata[1];
y2=rdata[1];
y3=Height-rdata[1];
y4=Height-ldata[1];

xc=(x1+x2)>>1;

xx1=(xc+x1)>>1;
xx2=(xc+x2)>>1;
if(xx2<0||xx1>Width)return;
yl=(y1+y4)>>1;
yr=(y2+y3)>>1;
yy1=(yl+y1)>>1;
yy2=(yr+y2)>>1;
yy3=(yl+y3)>>1;
yy4=(yr+y4)>>1;

yy[0]=Height-((((yy1+yy2)>>1)+yy1)>>1);
yy[1]=Height-((((yy1+yy2)>>1)+yy2)>>1);
yy[2]=Height-((((yy3+yy4)>>1)+yy3)>>1);
yy[3]=Height-((((yy3+yy4)>>1)+yy4)>>1);
xx[0]=xx1;
xx[1]=xx2;
xx[2]=xx2;
xx[3]=xx1;
SuperPoly(c_window,4,xx,yy);
MoveTo(xc,(yy[0]+yy[1])>>1);
LineTo(xc,(yy[2]+yy[3])>>1);
MoveTo(xx1,yl);
LineTo(xx2,yr);
}
/*-----------------------------------------------------------------------*/
drawClosedDoor(ldata,rdata)
int ldata[2],rdata[2];
{
int x1,x2,xc;
int xx1,xx2;
int y1,y2,y3,y4,yc;
int ybl,ybr;
int ytl,ytr;
int x[4],y[4];

ColorWall(ldata,rdata);
x1=ldata[0];
x2=rdata[0];
y1=ldata[1];
y2=rdata[1];
y3=Height-rdata[1];
y4=Height-ldata[1];

xc=(x1+x2)>>1;
xx1=(xc+x1)>>1;
xx2=(xc+x2)>>1;
if(xx2<0||xx1>Width)return;

yc=(y1+y2)>>1;
ytl=(yc+y1)>>1;
ytr=(yc+y2)>>1;

yc=(y4+y3)>>1;
ybl=(yc+y4)>>1;
ybr=(yc+y3)>>1;

ytl=(((((ybl+ytl)>>1)+ytl)>>1)+ytl)>>1;
ytr=(((((ybr+ytr)>>1)+ytr)>>1)+ytr)>>1;
x[0]=xx1; y[0]= ybl;
x[1]=xx1; y[1]=ytl;
x[2]=xx2; y[2]=ytr;
x[3]=xx2; y[3]=ybr;
SuperPoly(c_door,4,x,y);
ybl=(ybl+ytl)>>1;
ybr=(ybr+ytr)>>1;
yc=(ybl+ybr)>>1;
ybl=(((yc+ybl)>>1)+ybl)>>1;
ybr=(((yc+ybr)>>1)+ybr)>>1;
xx1=(((xx1+xc)>>1)+xx1)>>1;
xx2=(((xx2+xc)>>1)+xx2)>>1;

MoveTo(xx1,ybl);
LineTo(xx2,ybr);

}
/*-----------------------------------------------------------------------*/
drawOpenDoor(ldata,rdata,ldata2,rdata2)
int ldata[2],rdata[2],ldata2[2],rdata2[2];
{
int x1,x2,xc;
int y1,y2,y3,y4,yc;
int xl,xr,xd;
int xfl,xfr;
int ybl,ybr;
int ytl,ytr;
int yfl,yfr;
int ydb,ydt;
int x[4],y[4];

ColorWall(ldata,rdata);
x1=ldata[0];
x2=rdata[0];
y1=ldata[1];
y2=rdata[1];
y3=Height-rdata[1];
y4=Height-ldata[1];

xc=(x1+x2)>>1;
xl=(xc+x1)>>1;
xr=(xc+x2)>>1;

yc=(y1+y2)>>1;
ytl=(yc+y1)>>1;
ytr=(yc+y2)>>1;

yc=(y4+y3)>>1;
ybl=(yc+y4)>>1;
ybr=(yc+y3)>>1;

ytl=(((((ybl+ytl)>>1)+ytl)>>1)+ytl)>>1;
ytr=(((((ybr+ytr)>>1)+ytr)>>1)+ytr)>>1;

if(xr<0||xl>Width)return;
x[0]=xl; y[0]=ybl;
x[1]=xl; y[1]=ytl;
x[2]=xr; y[2]=ytr;
x[3]=xr; y[3]=ybr;
SuperPoly(BLACK,4,x,y);

x1=ldata2[0];
x2=rdata2[0];
y1=Height-ldata2[1];
y2=Height-rdata2[1];

xc=(x1+x2)>>1;
xfl=(xc+x1)>>1;
xfr=(xc+x2)>>1;

yc=(y1+y2)>>1;
yfl=(yc+y1)>>1;
yfr=(yc+y2)>>1;

x1=min(xl,xfl);
x1=min(x1,xfr);
x1=min(x1,xr);
x2=max(xl,xfl);
x2=max(x2,xfr);
x2=max(x2,xr);
y1=min(ybl,yfl);
y1=min(y1,yfr);
y1=min(y1,ybr);
y2=max(ybl,yfl);
y2=max(y2,yfr);
y2=max(y2,ybr);

x[0]=xl; y[0]=ybl;
x[1]=xfl; y[1]=yfl;
x[2]=xfr; y[2]=yfr;
x[3]=xr; y[3]=ybr;
x1=Clip.left;
x2=Clip.right;
if(Clip.left<xl)Clip.left=xl;
if(Clip.right>xr)Clip.right=xr;
ClipRect(&Clip);
if(corepower[coreindex])SuperPoly(c_lwall,4,x,y);
else SuperPoly(c_dwall,4,x,y);
Clip.left=x1;
Clip.right=x2;
}
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/
drawTunnel(ldata,rdata,ldata2,rdata2)
int ldata[2],rdata[2],ldata2[2],rdata2[2];
{
int i;
int x1,x2,xc;
int y1,y2,y3,y4,yc;
int xl,xr;
int xfl,xfr;
int ybl,ybr;
int ytl,ytr;
int yfl,yfr;
int ydb,ydt;
int base_x[7],base_y[7],tunnel_y[7][7];
long h,hl,hr;
Rect r;
int x[6],y[6];

ColorWall(ldata,rdata);
xl=ldata[0];
xr=rdata[0];
ytl=ldata[1];
ytr=rdata[1];
ybr=Height-rdata[1];
ybl=Height-ldata[1];
hl=ybl-ytl;
hr=ybr-ytr;
h=max(hl,hr);
split7(base_x,xl,xr);
if(base_x[0]>Width||base_x[6]<0)return;
split7(base_y,ybl,ybr);
for(i=0;i<7;i++)split7(tunnel_y[i],base_y[i],Height-base_y[i]);

x[0]=base_x[0]; y[0]=base_y[0];
x[1]=base_x[0]; y[1]=tunnel_y[0][5];
x[2]=base_x[1]; y[2]=tunnel_y[1][6];
x[3]=base_x[5]; y[3]=tunnel_y[5][6];
x[4]=base_x[6]; y[4]=tunnel_y[6][5];
x[5]=base_x[6]; y[5]=base_y[6];
SuperPoly(c_tunnel,6,x,y);
}
/*-----------------------------------------------------------------------*/
drawglyphs(ldata,rdata)
int ldata[2],rdata[2];
{
PenState pnstate;
int xl,xr,xc;
int y1,y2,y3,y4;
int ytc,ybc;
int ytl,ytr,ybl,ybr;
int yl1,yl2,yl3,yl4,yl5;
int yr1,yr2,yr3,yr4,yr5;
int x[4],y[4];

ColorWall(ldata,rdata);
GetPenState(&pnstate);
PenPat(&gray);

xl=ldata[0];
xr=rdata[0];

y1=ldata[1];
y2=rdata[1];
y3=Height-rdata[1];
y4=Height-ldata[1];
x[0]=xl; y[0]=y1;
x[1]=xr; y[1]=y2;
x[2]=xr; y[2]=y3;
x[3]=xl; y[3]=y4;
SuperPoly(c_glyph,4,x,y);
xc=(xl+xr)>>1;
xl=(((xc+xl)>>1)+xl)>>1;
xr=(((xc+xr)>>1)+xr)>>1;

ytc=(y1+y2)>>1;
ybc=(y3+y4)>>1;

ytl=(((y1+ytc)>>1)+y1)>>1;
ytr=(((y2+ytc)>>1)+y2)>>1;
ybl=(((y4+ybc)>>1)+y4)>>1;
ybr=(((y3+ybc)>>1)+y3)>>1;

yl1=(ytl+ybl)>>1;
yr1=(ytr+ybr)>>1;
yl2=(yl1+ytl)>>1;
yr2=(yr1+ytr)>>1;
yl3=(yl2+yl1)>>1;
yr3=(yr2+yr1)>>1;
yl4=(yl1+ybl)>>1;
yr4=(yr1+ybr)>>1;
yr5=(yr4+yr1)>>1;
yl5=(yl4+yl1)>>1;

MoveTo(xl,yl1);
LineTo(xr,yr1);
MoveTo(xl,yl2);
LineTo(xr,yr2);
MoveTo(xl,yl3);
LineTo(xr,yr3);
MoveTo(xl,yl4);
LineTo(xr,yr4);
MoveTo(xl,yl5);
LineTo(xr,yr5);
MoveTo(xl,(yl2+yl3)>>1);
LineTo(xr,(yr2+yr3)>>1);
MoveTo(xl,(yl3+yl1)>>1);
LineTo(xr,(yr3+yr1)>>1);
MoveTo(xl,(yl1+yl5)>>1);
LineTo(xr,(yr1+yr5)>>1);
MoveTo(xl,(yl4+yl5)>>1);
LineTo(xr,(yr4+yr5)>>1);
SetPenState(&pnstate);
}
/*-----------------------------------------------------------------------*/
drawbooks(ldata,rdata,ldata2,rdata2)
int ldata[2],rdata[2];
int ldata2[2],rdata2[2];
{
int i;
int lf[7],rf[7];
int lb[7],rb[7];
int x[4],y[4];

x[0]=ldata[0]; y[0]=ldata[1];
x[1]=rdata[0]; y[1]=rdata[1];
x[2]=rdata[0]; y[2]=Height-rdata[1];
x[3]=ldata[0]; y[3]=Height-ldata[1];
SuperPoly(c_shelves,4,x,y);

for(i=0;i<2;i++)
	{
	ldata2[0]=(ldata2[0]+ldata[0])>>1;
	ldata2[1]=(ldata2[1]+ldata[1])>>1;
	rdata2[0]=(rdata2[0]+rdata[0])>>1;
	rdata2[1]=(rdata2[1]+rdata[1])>>1;
	}	
MoveTo(ldata2[0],ldata2[1]);
LineTo(ldata2[0],Height-ldata2[1]);
LineTo(rdata2[0],Height-rdata2[1]);
LineTo(rdata2[0],rdata2[1]);
LineTo(ldata2[0],ldata2[1]);
MoveTo(ldata[0],ldata[1]);
LineTo(ldata2[0],ldata2[1]);
MoveTo(ldata[0],Height-ldata[1]);
LineTo(ldata2[0],Height-ldata2[1]);
MoveTo(rdata[0],rdata[1]);
LineTo(rdata2[0],rdata2[1]);
MoveTo(rdata[0],Height-rdata[1]);
LineTo(rdata2[0],Height-rdata2[1]);

split7(lf,ldata[1],Height-ldata[1]);
split7(rf,rdata[1],Height-rdata[1]);
split7(lb,ldata2[1],Height-ldata2[1]);
split7(rb,rdata2[1],Height-rdata2[1]);

for(i=0;i<7;i++)
	{
	MoveTo(ldata[0],	lf[i]);
	LineTo(rdata[0],	rf[i]);
	LineTo(rdata2[0],	rb[i]);
	LineTo(ldata2[0],	lb[i]);
	LineTo(ldata[0],	lf[i]);
	}
}
/*-----------------------------------------------------------------------*/
draw_up_stairs(ldata,rdata,ldata2,rdata2)
int ldata[2],rdata[2];
int ldata2[2],rdata2[2];
{
int i;
int yl[7][7],yr[7][7];
int xl[7],xr[7];
int bl[7],br[7];
int endl[7],endr[7];
int x[4],y[4];
int mx;

ColorWall(ldata,rdata);
split7(endl,Height-ldata2[1],ldata2[1]);
split7(endr,Height-rdata2[1],rdata2[1]);
split7(bl,ldata[1],ldata2[1]);
split7(br,rdata[1],rdata2[1]);
split7(xl,ldata[0],ldata2[0]);
split7(xr,rdata[0],rdata2[0]);
for(i=0;i<7;i++)
	{
	split7(yl[i],Height-bl[i],bl[i]);
	split7(yr[i],Height-br[i],br[i]);
	}

mx=max(ldata[1],rdata[1]);

MoveTo(ldata2[0],endl[6]);
LineTo(ldata2[0],mx);
MoveTo(rdata2[0],mx);
LineTo(rdata2[0],endr[6]);

x[0]=xl[6]; y[0]=yl[6][6];
x[1]=ldata2[0]; y[1]=endl[6];
x[2]=rdata2[0]; y[2]=endr[6];
x[3]=xr[6]; y[3]=yr[6][6];
SuperPoly(c_upstairs2,4,x,y);
/*first step*/
x[0]=ldata[0]; y[0]=Height-ldata[1];
x[1]=xl[0]; y[1]=Height-bl[0];
x[2]=xr[0]; y[2]=Height-br[0];
x[3]=rdata[0]; y[3]=Height-rdata[1];
SuperPoly(c_upstairs1,4,x,y);

x[0]=xl[0]; y[0]=yl[0][0];
x[1]=xl[0]; y[1]=Height-bl[0];
x[2]=xr[0]; y[2]=Height-br[0];
x[3]=xr[0]; y[3]=yr[0][0];
SuperPoly(c_upstairs2,4,x,y);
/*top of steps*/
for(i=3;i>=0;i--)
	{
	x[0]=xl[i];   y[0]=yl[i][i];
	x[1]=xl[i+1]; y[1]=yl[i+1][i];
	x[2]=xr[i+1]; y[2]=yr[i+1][i];
	x[3]=xr[i];   y[3]=yr[i][i];
	SuperPoly(c_upstairs1,4,x,y);
	}
/*front of steps*/
for(i=5;i>=0;i--)
	{
	x[0]=xl[i+1]; y[0]=yl[i+1][i+1];
	x[1]=xl[i+1]; y[1]=yl[i+1][i];
	x[2]=xr[i+1]; y[2]=yr[i+1][i];
	x[3]=xr[i+1]; y[3]=yr[i+1][i+1];
	SuperPoly(c_upstairs2,4,x,y);
	}

PenSize(2,2);
MoveTo(ldata[0],centerY);
LineTo(xl[3],mx);
MoveTo(rdata[0],centerY);
LineTo(xr[3],mx);
PenSize(1,1);
}
/*-----------------------------------------------------------------------*/
draw_dn_stairs(ldata,rdata,ldata2,rdata2)
int ldata[2],rdata[2];
int ldata2[2],rdata2[2];
{
int i;
int yl[7],yr[7];
int xl[7],xr[7];
int x;

int xx[4],yy[4];

xx[0]=ldata[0]; yy[0]=ldata[1];
xx[1]=rdata[0]; yy[1]=rdata[1];
xx[2]=rdata[0]; yy[2]=Height-rdata[1];
xx[3]=ldata[0]; yy[3]=Height-ldata[1];
SuperPoly(c_dnstairs,4,xx,yy);

split7(yl,ldata[1],ldata2[1]);
split7(yr,rdata[1],rdata2[1]);
split7(xl,ldata[0],ldata2[0]);
split7(xr,rdata[0],rdata2[0]);
x=max(yl[0],yr[0]);
/*----------ceiling*/
MoveTo(ldata[0],ldata[1]);
LineTo(xl[3],yl[3]);
LineTo(xr[3],yr[3]);
LineTo(rdata[0],rdata[1]);
/*----------slant*/
MoveTo(xl[3],yl[3]);
LineTo(ldata2[0],centerY);
LineTo(rdata2[0],centerY);
LineTo(xr[3],yr[3]);
/*----------left line down*/
MoveTo(ldata2[0],centerY);
LineTo(ldata2[0],Height-x);
/*----------right line down*/
MoveTo(rdata2[0],centerY);
LineTo(rdata2[0],Height-x);
/*----------first step*/
MoveTo(ldata[0],Height-ldata[1]);
LineTo(xl[0],Height-yl[0]);
LineTo(xr[0],Height-yr[0]);
LineTo(rdata[0],Height-rdata[1]);
PenSize(2,2);
/*----------left rail*/
MoveTo(ldata[0],centerY);
LineTo(xl[3],Height-yl[3]);
/*----------right rail*/
MoveTo(rdata[0],centerY);
LineTo(xr[3],Height-yr[3]);
PenSize(1,1);
}
/*-----------------------------------------------------------------------*/
drawALOpen(ldata,rdata)
int ldata[2],rdata[2];
{
int lr[7];
int ud[7][7];
int x[8],y[8];

ColorWall(ldata,rdata);
split7x7(ldata,rdata,lr,ud);

x[0]=lr[0]; y[0]=ud[3][0];
x[1]=lr[1]; y[1]=ud[5][1];
x[2]=lr[3]; y[2]=ud[6][3];
x[3]=lr[5]; y[3]=ud[5][5];
x[4]=lr[6]; y[4]=ud[3][6];
x[5]=lr[5]; y[5]=ud[1][5];
x[6]=lr[3]; y[6]=ud[0][3];
x[7]=lr[1]; y[7]=ud[1][1];
SuperPoly(BLACK,8,x,y);
}
/*-----------------------------------------------------------------------*/
drawALClosed(ldata,rdata)
int ldata[2],rdata[2];
{
int lr[7];
int ud[7][7];
int x[8],y[8];

ColorWall(ldata,rdata);
split7x7(ldata,rdata,lr,ud);
x[0]=lr[0]; y[0]=ud[3][0];
x[1]=lr[1]; y[1]=ud[5][1];
x[2]=lr[3]; y[2]=ud[6][3];
x[3]=lr[5]; y[3]=ud[5][5];
x[4]=lr[6]; y[4]=ud[3][6];
x[5]=lr[5]; y[5]=ud[1][5];
x[6]=lr[3]; y[6]=ud[0][3];
x[7]=lr[1]; y[7]=ud[1][1];
SuperPoly(c_airlock,8,x,y);

MoveTo(lr[0],ud[3][0]);
LineTo(lr[2],ud[4][2]);
LineTo(lr[3],ud[3][3]);
MoveTo(lr[1],ud[5][1]);
LineTo(lr[3],ud[4][3]);
LineTo(lr[3],ud[3][3]);
MoveTo(lr[3],ud[6][3]);
LineTo(lr[4],ud[4][4]);
LineTo(lr[3],ud[3][3]);
MoveTo(lr[5],ud[5][5]);
LineTo(lr[4],ud[3][4]);
LineTo(lr[3],ud[3][3]);
MoveTo(lr[6],ud[3][6]);
LineTo(lr[4],ud[2][4]);
LineTo(lr[3],ud[3][3]);
MoveTo(lr[5],ud[1][5]);
LineTo(lr[3],ud[2][3]);
LineTo(lr[3],ud[3][3]);
MoveTo(lr[3],ud[0][3]);
LineTo(lr[2],ud[2][2]);
LineTo(lr[3],ud[3][3]);
MoveTo(lr[1],ud[1][1]);
LineTo(lr[2],ud[3][2]);
LineTo(lr[3],ud[3][3]);
}
/*-----------------------------------------------------------------------*/
drawOpenSSDoor(ldata,rdata)
int ldata[2],rdata[2];
{
int lr[7];
int ud[7][7];
int x[8],y[8];

ColorWall(ldata,rdata);
split7x7(ldata,rdata,lr,ud);

x[0]=lr[2]; y[0]=ud[0][2];
x[1]=lr[1]; y[1]=ud[1][1];
x[2]=lr[1]; y[2]=ud[5][1];
x[3]=lr[2]; y[3]=ud[6][2];
x[4]=lr[4]; y[4]=ud[6][4];
x[5]=lr[5]; y[5]=ud[5][5];
x[6]=lr[5]; y[6]=ud[1][5];
x[7]=lr[4]; y[7]=ud[0][4];
SuperPoly(BLACK,8,x,y);
}
/*-----------------------------------------------------------------------*/
drawClosedSSDoor(ldata,rdata)
int ldata[2],rdata[2];
{
int lr[7];
int ud[7][7];
int x[8],y[8];

ColorWall(ldata,rdata);
split7x7(ldata,rdata,lr,ud);

x[0]=lr[2]; y[0]=ud[0][2];
x[1]=lr[1]; y[1]=ud[1][1];
x[2]=lr[1]; y[2]=ud[5][1];
x[3]=lr[2]; y[3]=ud[6][2];
x[4]=lr[4]; y[4]=ud[6][4];
x[5]=lr[5]; y[5]=ud[5][5];
x[6]=lr[5]; y[6]=ud[1][5];
x[7]=lr[4]; y[7]=ud[0][4];
SuperPoly(c_bulkhead,8,x,y);
MoveTo(lr[2],ud[1][2]);
LineTo(lr[2],ud[5][2]);
LineTo(lr[4],ud[5][4]);
LineTo(lr[4],ud[1][4]);
LineTo(lr[2],ud[1][2]);
}
/*-----------------------------------------------------------------------*/
drawelevator(ldata,rdata)
int ldata[2],rdata[2];
{
int x1,x2,xc;
int xx1,xx2;
int y1,y2,y3,y4,ybc,ytc;
int ybl,ybr;
int ytl,ytr;
int x[4],y[4];

ColorWall(ldata,rdata);
x1=ldata[0];
x2=rdata[0];
y1=ldata[1];
y2=rdata[1];
y3=Height-rdata[1];
y4=Height-ldata[1];

xc=(x1+x2)>>1;
xx1=(xc+x1)>>1;
xx1=(x1+xx1)>>1;
xx2=(xc+x2)>>1;
xx2=(x2+xx2)>>1;
if(xx2<0||xx1>Width)return;

ytc=(y1+y2)>>1;
ytl=(ytc+y1)>>1;
ytl=(ytl+y1)>>1;
ytr=(ytc+y2)>>1;
ytr=(ytr+y2)>>1;
ybc=(y4+y3)>>1;
ybl=(ybc+y4)>>1;
ybl=(ybl+y4)>>1;
ybr=(ybc+y3)>>1;
ybr=(ybr+y3)>>1;

ytl=(((((ybl+ytl)>>1)+ytl)>>1)+ytl)>>1;
ytr=(((((ybr+ytr)>>1)+ytr)>>1)+ytr)>>1;

x[0]=xx1; y[0]=ybl;
x[1]=xx1; y[1]=ytl;
x[2]=xx2; y[2]=ytr;
x[3]=xx2; y[3]=ybr;
SuperPoly(c_elevator,4,x,y);
ytc=(ytl+ytr)>>1;
MoveTo(xc,ybc);
LineTo(xc,ytc);
}
/*-----------------------------------------------------------------------*/
drawColor(map,ldata,rdata)
char map[4];
int ldata[2],rdata[2];
{
int xl,xr;
int yl[5],yr[5];
int i;
int color;
int x[4],y[4];

xl=ldata[0];
xr=rdata[0];

yl[0]=ldata[1];
yr[0]=rdata[1];
yl[4]=Height-yl[0];
yr[4]=Height-yr[0];
yl[2]=(yl[0]+yl[4])>>1;
yr[2]=(yr[0]+yr[4])>>1;
yl[1]=(yl[0]+yl[2])>>1;
yl[3]=(yl[2]+yl[4])>>1;
yr[1]=(yr[0]+yr[2])>>1;
yr[3]=(yr[2]+yr[4])>>1;

for(i=0;i<4;i++)
	{
	x[0]=xl; y[0]=yl[i];
	x[1]=xl; y[1]=yl[i+1];
	x[2]=xr; y[2]=yr[i+1];
	x[3]=xr; y[3]=yr[i];
	switch(map[i+1])
			{
			case WHITE:
				SuperPoly(c_color0,4,x,y);
				break;
			case LTGRAY:
				SuperPoly(c_color1,4,x,y);
				break;
			case GRAY:
				SuperPoly(c_color2,4,x,y);
				break;
			case DKGRAY:
				SuperPoly(c_color3,4,x,y);
				break;
			case BLACK:
				SuperPoly(BLACK,4,x,y);
				break;
			default:
				color=map[i+1]+count;
				color%=5;
				switch(color)
					{
					case WHITE:
						SuperPoly(c_color0,4,x,y);
						break;
					case LTGRAY:
						SuperPoly(c_color1,4,x,y);
						break;
					case GRAY:
						SuperPoly(c_color2,4,x,y);
						break;
					case DKGRAY:
						SuperPoly(c_color3,4,x,y);
						break;
					case BLACK:
						SuperPoly(BLACK,4,x,y);
						break;
					}
				break;
			}
		}
}
/*-----------------------------------------------------------------------*/
int split7x7(ldata,rdata,lr,ud)
int ldata[2],rdata[2];
int lr[7];
int ud[7][7];
{
int left_x,left_y,right_x,right_y;
int l_ud[7],r_ud[7];
int i;
long t;
int aleft_y,aright_y;

if(rdata[0]<ldata[0])
	{
	right_x=ldata[0];
	left_x=rdata[0];
	right_y=ldata[1];
	left_y=rdata[1];
	}
else
	{
	left_x=ldata[0];
	right_x=rdata[0];
	left_y=ldata[1];
	right_y=rdata[1];
	}
split7(lr,left_x,right_x);
if(flip)
	{
	split7(l_ud,left_y,Height-left_y);
	split7(r_ud,right_y,Height-right_y);
	}
else
	{
	split7(l_ud,Height-left_y,left_y);
	split7(r_ud,Height-right_y,right_y);
	}
for(i=0;i<7;i++)split7(ud[i],l_ud[i],r_ud[i]);
}

/*-----------------------------------------------------------------------*/
ColorWall(ldata,rdata)
int ldata[2],rdata[2];
{
int xx[4],yy[4];
int cc;

if(corepower[coreindex] && polyfill)
	{
	cc=c_char0+level-1;
	cColor[cc].pattern=BLACK;
	xx[0]=ldata[0]; yy[0]=ldata[1];
	xx[1]=rdata[0]; yy[1]=rdata[1];
	xx[2]=rdata[0]; yy[2]=Height-rdata[1];
	xx[3]=ldata[0]; yy[3]=Height-ldata[1];
	SuperPoly(cc,4,xx,yy);
	}
}
