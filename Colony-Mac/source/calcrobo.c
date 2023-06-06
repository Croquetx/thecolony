/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
/*---------------------------------------------------------------------
 * CalcRobot.c
 *---------------------------------------------------------------------
 * MakePrism(this,where,look)
 *		Prism *this;
 *		Locate *where;
 *		int look;
 * DrawPrism(obj,force)
 *		Prism *obj;
 *		int force;
 * int Clockwise(obj,surf)
 *		Prism *obj;
 *		int surf;
 * Rotate(ang,x,y,px,py)
 * 		unsigned char ang;
 * 		int x,y;
 * 		int *px,*py;
 * 		Generalized rotation function rotates x and y around z through
 * 		angle ang and places result in *px and *py.
 * TransRotProj(xyz)
 * 		register int xyz[3];
 * 		This function does the complete calculation for the manipulation of
 * 		a given point. First translation, then rotation, and finally the
 * 		perspective projection.
 * int XYClip(yline,x1,y1,x2,y2)
 *		int yline,x1,y1,x2,y2;
 * SuperPoly(pnum,length,x,y)
 *		int pnum;
 *		int length,x[],y[];
 *---------------------------------------------------------------------
 */
#define EXT extern 
#include "cgamedefs.h"
#include "colordef.h"
extern RGBColor lineColor;
extern RGBColor wallColor;
/*---------------------------------------------------------------------
 * MakePrism(this,look)
 *---------------------------------------------------------------------
 */
MakePrism(this,where,look)
register Prism *this;
register Locate *where;
int look;
{
register int i,mnmx;
unsigned char ang;
if(look)ang=where->look;
else ang=where->ang;
for(i=0; i < this->points ;i++)
	{ 
	Rotate(ang,this->pnt[i],this->copy[i]);
	this->copy[i][0]+=where->xloc;
	this->copy[i][1]+=where->yloc;
	this->copy[i][2] = this->pnt[i][2];
	TransRotProj(this->copy[i]);
	mnmx=this->copy[i][0];
	if(mnmx<where->xmn)where->xmn=mnmx;
	if(mnmx>where->xmx)where->xmx=mnmx;
	mnmx=this->copy[i][2];
	if(mnmx<where->zmn)where->zmn=mnmx;
	if(mnmx>where->zmx)where->zmx=mnmx;
	if(this->copy[i][1]<where->dist)where->dist=this->copy[i][1];
	}
for(i=0;i < this->surfaces ;i++)this->vsurface[i]=Clockwise(this,i);/*which side are we on?*/
if(where->xmx<0 || where->xmn>Width||where->zmn>Height)this->visible=FALSE;
else {this->visible=TRUE;this->fill=TRUE;}
}
/*---------------------------------------------------------------------
 * DrawPrism()
 *---------------------------------------------------------------------
 */
DrawPrism(obj,force)
register Prism *obj;
int force;
{
register long i,j;
register int x[64],y[64];

for(i=0;i < obj->surfaces ;i++)
	{
	if(obj->vsurface[i] || force)
		{
		for(j=0;j<obj->surface[i][1];j++)
			{
			x[j]=obj->copy[obj->surface[i][j+2]][0]; 
			y[j]=obj->copy[obj->surface[i][j+2]][2];
			}
		SuperPoly((int)obj->surface[i][0],(int)obj->surface[i][1],x,y);
		}
	}
}
/*---------------------------------------------------------------------
 * Clockwise(pt)
 *---------------------------------------------------------------------
 */
int Clockwise(obj,surf)
Prism *obj;
int surf;
{
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
}
/*---------------------------------------------------------------------
 * Rotate(ang,x,y,px,py)
 * unsigned char ang;
 * int x,y;
 * int *px,*py;
 * Generalized rotation function rotates x and y around z through
 * angle ang and places result in *px and *py.
 *---------------------------------------------------------------------
 */
Rotate(ang,from,to)
register int from[2],to[2];
unsigned char ang;
{	
register long tcos,tsin;

tcos=cost[ang];
tsin=sint[ang];
to[0] = (from[0] * tcos - from[1] * tsin) >> 7;
to[1] = (from[0] * tsin + from[1] * tcos) >> 7;
}
/*---------------------------------------------------------------------
 * TransRotProj(xyz)
 * register int xyz[3];
 * This function does the complete calculation for the manipulation of
 * a given point. First translation, then rotation, and finally the
 * perspective projection.
 *---------------------------------------------------------------------
 */
TransRotProj(xyz)
register int xyz[3];
{
register long tcos,tsin;
register long x,y,xx,yy,zz;

/*translation*/
x = xyz[0] - Me.xloc;
y = xyz[1] - Me.yloc;
zz= xyz[2];
/*xyz[2] += Me.zloc;*/

/*rotation*/
tsin=cost[Me.look];
tcos=sint[Me.look];
xx = (x * tcos - y * tsin) >> 7;
yy = (x * tsin + y * tcos) >> 7;

/*projection*/
if(yy <= 16)yy=16;
xyz[0] = centerX + ((long)xx << 8) / yy;/*compute x projection	*/
xyz[1] = yy;
xyz[2] = centerY - ((long)zz << 8) / yy;/*compute z projection	*/
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int XYClip(yline,x1,y1,x2,y2)
int yline,x1,y1,x2,y2;
{
register long dyl,dx,dy;

dyl=yline-y1;
dx=x2-x1;
dy=y2-y1;
return((int)(x1+(dyl*dx)/dy));
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
SuperPoly(pnum,length,x,y)
int pnum;
int length,x[],y[];
{
register long i;
register int mx[64],my[64],nx[64],ny[64];
register int nindex,mindex;
long l=length-1;
PolyHandle poly;
extern RGBColor wallColor;
extern RGBColor black_Color;
extern RGBColor white_Color;

if(Clip.left>Clip.right)return;
/*---TOP---*/
nindex=0;
for(i=0;i<l;i++)
	{
	if(y[i]>=Clip.top)
		{
		ny[nindex]=y[i];
		nx[nindex]=x[i];
		nindex++;
		if(y[i+1]<Clip.top)
			{
			ny[nindex]=Clip.top;
			nx[nindex]=XYClip(Clip.top,x[i],y[i],x[i+1],y[i+1]);
			nindex++;
			}
		}
	else if(y[i+1]>=Clip.top)
		{
		ny[nindex]=Clip.top;
		nx[nindex]=XYClip(Clip.top,x[i],y[i],x[i+1],y[i+1]);
		nindex++;
		}
	}
if(y[l]>=Clip.top)
	{
	ny[nindex]=y[l];
	nx[nindex]=x[l];
	nindex++;
	if(y[0]<Clip.top)
		{
		ny[nindex]=Clip.top;
		nx[nindex]=XYClip(Clip.top,x[l],y[l],x[0],y[0]);
		nindex++;
		}
	}
else if(y[0]>=Clip.top)
	{
	ny[nindex]=Clip.top;
	nx[nindex]=XYClip(Clip.top,x[l],y[l],x[0],y[0]);
	nindex++;
	}
if(nindex==0)return;
/*---BOTTOM---*/
mindex=0;
l=nindex-1;
for(i=0;i<l;i++)
	{
	if(ny[i]<=Clip.bottom)
		{
		my[mindex]=ny[i];
		mx[mindex]=nx[i];
		mindex++;
		if(ny[i+1]>Clip.bottom)
			{
			my[mindex]=Clip.bottom;
			mx[mindex]=XYClip(Clip.bottom,nx[i],ny[i],nx[i+1],ny[i+1]);
			mindex++;
			}
		}
	else if(ny[i+1]<=Clip.bottom)
		{
		my[mindex]=Clip.bottom;
		mx[mindex]=XYClip(Clip.bottom,nx[i],ny[i],nx[i+1],ny[i+1]);
		mindex++;
		}
	}
if(ny[l]<=Clip.bottom)
	{
	my[mindex]=ny[l];
	mx[mindex]=nx[l];
	mindex++;
	if(ny[0]>Clip.bottom)
		{
		my[mindex]=Clip.bottom;
		mx[mindex]=XYClip(Clip.bottom,nx[l],ny[l],nx[0],ny[0]);
		mindex++;
		}
	}
else if(ny[0]<=Clip.bottom)
	{
	my[mindex]=Clip.bottom;
	mx[mindex]=XYClip(Clip.bottom,nx[l],ny[l],nx[0],ny[0]);
	mindex++;
	}
if(mindex==0)return;

/*---LEFT---*/
nindex=0;
l=mindex-1;
for(i=0;i<l;i++)
	{
	if(mx[i]>=Clip.left)
		{
		ny[nindex]=my[i];
		nx[nindex]=mx[i];
		nindex++;
		if(mx[i+1]<Clip.left)
			{
			nx[nindex]=Clip.left;
			ny[nindex]=XYClip(Clip.left,my[i],mx[i],my[i+1],mx[i+1]);
			nindex++;
			}
		}
	else if(mx[i+1]>=Clip.left)
		{
		nx[nindex]=Clip.left;
		ny[nindex]=XYClip(Clip.left,my[i],mx[i],my[i+1],mx[i+1]);
		nindex++;
		}
	}
if(mx[l]>=Clip.left)
	{
	ny[nindex]=my[l];
	nx[nindex]=mx[l];
	nindex++;
	if(mx[0]<Clip.left)
		{
		nx[nindex]=Clip.left;
		ny[nindex]=XYClip(Clip.left,my[l],mx[l],my[0],mx[0]);
		nindex++;
		}
	}
else if(mx[0]>=Clip.left)
	{
	nx[nindex]=Clip.left;
	ny[nindex]=XYClip(Clip.left,my[l],mx[l],my[0],mx[0]);
	nindex++;
	}
if(nindex==0)return;

/*---RIGHT---*/
mindex=0;
l=nindex-1;
for(i=0;i<l;i++)
	{
	if(nx[i]<=Clip.right)
		{
		my[mindex]=ny[i];
		mx[mindex]=nx[i];
		mindex++;
		if(nx[i+1]>Clip.right)
			{
			mx[mindex]=Clip.right;
			my[mindex]=XYClip(Clip.right,ny[i],nx[i],ny[i+1],nx[i+1]);
			mindex++;
			}
		}
	else if(nx[i+1]<=Clip.right)
		{
		mx[mindex]=Clip.right;
		my[mindex]=XYClip(Clip.right,ny[i],nx[i],ny[i+1],nx[i+1]);
		mindex++;
		}
	}
if(nx[l]<=Clip.right)
	{
	my[mindex]=ny[l];
	mx[mindex]=nx[l];
	mindex++;
	if(nx[0]>Clip.right)
		{
		mx[mindex]=Clip.right;
		my[mindex]=XYClip(Clip.right,ny[l],nx[l],ny[0],nx[0]);
		mindex++;
		}
	}
else if(nx[0]<=Clip.right)
	{
	mx[mindex]=Clip.right;
	my[mindex]=XYClip(Clip.right,ny[l],nx[l],ny[0],nx[0]);
	mindex++;
	}
if(mindex==0)return;

poly=OpenPoly();
MoveTo(mx[0],my[0]);
for(i=1;i<mindex;i++)LineTo(mx[i],my[i]);
LineTo(mx[0],my[0]);
ClosePoly();
if(corepower[coreindex])
	{
	if(pnum==c_lwall)
		{
		RGBForeColor(&lineColor);
		RGBBackColor(&wallColor);
		pnum=WHITE;
		}
	else
		{
		RGBForeColor(&cColor[pnum].f);
		RGBBackColor(&cColor[pnum].b);
		}
	}
else 
	{
	if(pnum==c_dwall)
		{
		RGBForeColor(&wallColor);
		RGBBackColor(&wallColor);
		}
	else
		{
		RGBForeColor(&black_Color);
		RGBBackColor(&white_Color);
		}
	}
switch(cColor[pnum].pattern)
	{
	case WHITE:
		if(corepower[coreindex])
			{
			FillPoly(poly,white);
			FramePoly(poly);
			}
		else FillPoly(poly,black);
		break;
	case LTGRAY:
		if(corepower[coreindex])
			{
			FillPoly(poly,ltGray);
			FramePoly(poly);
			}
		else FillPoly(poly,black);
		break;
	case GRAY:
		if(corepower[coreindex])
			{
			FillPoly(poly,gray);
			FramePoly(poly);
			}
		else FillPoly(poly,black);
		break;
	case DKGRAY:
		if(corepower[coreindex])
			{
			FillPoly(poly,dkGray);
			FramePoly(poly);
			}
		else FillPoly(poly,black);
		break;
	case BLACK:
		FillPoly(poly,black);
		break;
	case CLEAR:
		FramePoly(poly);
		break;
	default:
		break;
	}
if(pnum==c_dwall)
	{
	RGBForeColor(&lineColor);
	FramePoly(poly);
	}
KillPoly(poly);
}