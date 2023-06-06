/*  #define IBM_MakePrism    /*    */
/*  #define IBM_DrawPrism    /*    */
/*  #define IBM_Clockwise    /*    */
/*  #define IBM_Rotate	     /*    */
/*  #define IBM_TransRotProj /*    */
/*  #define IBM_SuperPoly	 /*   */
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
/*---------------------------------------------------------------------
 * CalcRobot.c
 *---------------------------------------------------------------------
 * MakePrism(this,where,look)
 *	Prism *this;
 *	Locate *where;
 *	int look;
 * DrawPrism(obj,force)
 *	Prism *obj;
 *	int force;
 * int Clockwise(obj,surf)
 *	Prism *obj;
 *	int surf;
 * Rotate(ang,x,y,px,py)
 * 	unsigned char ang;
 * 	int x,y;
 * 	int *px,*py;
 * 	Generalized rotation function rotates x and y around z through
 * 	angle ang and places result in *px and *py.
 * TransRotProj(xyz)
 * 	register int xyz[3];
 * 	This function does the complete calculation for the manipulation of
 * 	a given point. First translation, then rotation, and finally the
 * 	perspective projection.
 * SuperPoly(pnum,length,x,y)
 *	int pnum;
 *	int length,x[],y[];
 *---------------------------------------------------------------------
 */
#define EXT extern 
#include "gamedefs.h"
/*---------------------------------------------------------------------
 * MakePrism(this,look)
 *---------------------------------------------------------------------
 */
MakePrism(this,where,look)
register Prism *this;
register Locate far *where;
int look;
{
#if !defined(IBM_MakePrism)
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
/*which side are we on?*/
for(i=0;i < this->surfaces ;i++)this->vsurface[i]=Clockwise(this,i);
if(where->xmx<0 || where->xmn>Width||where->zmn>Height)this->visible=FALSE;
else {this->visible=TRUE;this->fill=TRUE;}
#endif
}
/*---------------------------------------------------------------------
 * DrawPrism()
 * There are three different factors to deal with here:
 * color (monchrome or polychrome)
 * polyfill (polygon fill mode on/off)
 * lights on or off
 *---------------------------------------------------------------------
 */
DrawPrism(obj,force)
register Prism *obj;
int force;
{
#if !defined(IBM_DrawPrism)
long i,j;
int polycount=1;
polyHead polyhdr;
point polypoint[64];

if(polyfill)
	{
	polyhdr.polyBgn=0;
	polyhdr.polyRect.Ymin=Clip.top;
	polyhdr.polyRect.Ymax=Clip.bottom;
	polyhdr.polyRect.Xmin=Clip.left;
	polyhdr.polyRect.Xmax=Clip.right;
	for(i=0;i < obj->surfaces ;i++)
		if(obj->surface[i][0]!=CLEAR)
			{
			polyhdr.polyEnd=obj->surface[i][1];
			if(obj->vsurface[i] || force)
				{
				for(j=0;j<obj->surface[i][1];j++)
					{
					polypoint[j].X=obj->copy[obj->surface[i][j+2]][0];
					polypoint[j].Y=obj->copy[obj->surface[i][j+2]][2];
					}
				polypoint[j].X=obj->copy[obj->surface[i][2]][0];
				polypoint[j].Y=obj->copy[obj->surface[i][2]][2];
				if(!MonoCrome)
					{
					if(corepower[coreindex])
						{/*****polychromatic/lights on*/
						BackColor(realcolor[
							lsColor[obj->surface[i][0]][BACKCOLOR]]);
						PenColor(realcolor[
							lsColor[obj->surface[i][0]][FILLCOLOR]]);
						PenPattern(lsColor[obj->surface[i][0]][PATTERN]);
						PaintPoly(1,&polyhdr,polypoint);
						PenPattern(1);
						}
					else
						{/*****polychromatic/lights off*/
						PenColor(realcolor[vBLACK]);
						PenPattern(1);
						PaintPoly(1,&polyhdr,polypoint);
						}
					}
				else
					{
					if(corepower[coreindex])
						{/*****monochromatic/lights on*/
						BackColor(vWHITE);
						PenColor(vBLACK);
						PenPattern(lsColor[obj->surface[i][0]][MONOCHROME]);
						PaintPoly(1,&polyhdr,polypoint);
						PenPattern(1);
						}
					else/*****monochromatic/lights off*/
						{
						PenColor(vBLACK);
						PenPattern(1);
						PaintPoly(1,&polyhdr,polypoint);
						}
					}
				}
		}
	}
for(i=0;i < obj->surfaces ;i++)
	{
	if ( (!MonoCrome)&&corepower[coreindex] )
	    {
		if(polyfill)
			PenColor(realcolor[lsColor[obj->surface[i][0]][LINEFILLCOLOR]]);
		else
			PenColor(realcolor[lsColor[obj->surface[i][0]][LINECOLOR]]);
		}
	else if(corepower[coreindex])PenColor(realcolor[vBLACK]);
	else PenColor(realcolor[vINTWHITE]);
	if(obj->vsurface[i] || force)
		{
		MoveTo(obj->copy[obj->surface[i][2]][0], 
			obj->copy[obj->surface[i][2]][2]);
		for(j=1;j<obj->surface[i][1];j++)
			LineTo(obj->copy[obj->surface[i][j+2]][0],
				obj->copy[obj->surface[i][j+2]][2]);
		LineTo(obj->copy[obj->surface[i][2]][0], 
			obj->copy[obj->surface[i][2]][2]);
		}
	}
BackColor(realcolor[vWHITE]);
PenColor(realcolor[vBLACK]);
#endif
}
/*---------------------------------------------------------------------
 * Clockwise(pt)
 *---------------------------------------------------------------------
 */
int Clockwise(obj,surf)
Prism *obj;
int surf;
{
#if !defined(IBM_Clockwise)
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
#if !defined(IBM_Rotate)
register long tcos,tsin;

tcos=cost[ang];
tsin=sint[ang];
to[0] = (from[0] * tcos - from[1] * tsin) >> 7;
to[1] = (from[0] * tsin + from[1] * tcos) >> 7;
#endif
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
#if !defined(IBM_TransRotProj)
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
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
SuperPoly(pnum,length,x,y)
int pnum;
int length,x[],y[];
{
#if !defined(IBM_SuperPoly)

long i,j;
int polycount=1;
polyHead polyhdr;
point polypoint[64];

if(polyfill)
	{
	polyhdr.polyBgn=0;
	polyhdr.polyEnd=length;
	polyhdr.polyRect.Ymin=Clip.top;
	polyhdr.polyRect.Ymax=Clip.bottom;
	polyhdr.polyRect.Xmin=Clip.left;
	polyhdr.polyRect.Xmax=Clip.right;

	if(!MonoCrome)
		{
		BackColor(realcolor[lsColor[pnum][BACKCOLOR]]);
		PenColor(realcolor[lsColor[pnum][FILLCOLOR]]);
		PenPattern(lsColor[pnum][PATTERN]);
		}
	else
		{
		BackColor(vWHITE);
		PenColor(vBLACK);
		PenPattern(lsColor[pnum][MONOCHROME]);
		}
	/*  PenColor( SetPolyColors(pnum) );  */

	for(j=0;j<length;j++)
	    {
	    polypoint[j].X=x[j];
	    polypoint[j].Y=y[j];
	    }
	polypoint[j].X=x[0];
	polypoint[j].Y=y[0];
	PaintPoly(1,&polyhdr,polypoint);
	PenPattern(1);
	if(polyfill)
	    PenColor(realcolor[lsColor[pnum][LINEFILLCOLOR]]);
	else
	    PenColor(realcolor[lsColor[pnum][LINECOLOR]]);
	FramePoly(1,&polyhdr,polypoint);
	}
#endif
}
