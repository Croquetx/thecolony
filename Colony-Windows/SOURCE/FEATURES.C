/* #define IBM_features   /* */
/* #define IBM_frontfeature  */
/* #define IBM_dowall	     */
/* #define IBM_ceil2hole     */
/* #define IBM_floor2hole    */
/* #define IBM_ceil1hole     */
/* #define IBM_floor1hole    */
/* #define IBM_hotfoot	     */
/* #define IBM_split7	     */
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
/*----------------------------------------------------------------------
 * features.c
 *---------------------------------------------------------------------- 
 * features(cellx,celly,xFront,yFront,left,right,rx,ry)
 *		int cellx,celly,xFront,yFront,left,right,rx,ry;
 * frontfeature(cellx,celly,xFront,yFront,left,right,rx,ry)
 *		int cellx,celly,xFront,yFront,left,right,rx,ry;
 * dowall(cellx,celly,direction,left,right)
 *		int cellx,celly,direction,left[4],right[4];
 * ceil2hole(xFront,yFront)
 *		int xFront,yFront;
 * floor2hole(xFront,yFront)
 *		int xFront,yFront;
 * ceil1hole(xFront,yFront)
 *		int xFront,yFront;
 * floor1hole(xFront,yFront)
 *		int xFront,yFront;
 * hotfoot(xFront,yFront)
 *		int xFront,yFront;
 * split7(arr,x1,x2)
 *		int arr[7];
 *		int x1,x2;
 *---------------------------------------------------------------------- 
 */
#define EXT extern
#include "gamedefs.h"

#define mn(x,y) x<y?x:y
#define mx(x,y) x>y?x:y

extern int FrntxWall;	/*first x front wall		*/
extern int FrntyWall;	/*first y front wall		*/
extern int SidexWall;	/*first x side wall			*/
extern int SideyWall;	/*first y side wall			*/
extern int Frntx    ;	/*x forward step distance	*/
extern int Frnty    ;	/*y forward step distance	*/
extern int Sidex    ;	/*x side step distance		*/
extern int Sidey    ;	/*y side step distance		*/
extern int Front    ;	/*wall in front				*/
extern int Side     ;	/*wall on side				*/
extern long count_time;
extern Thing Tank;
/*----------------------------------------------------------------------
 *---------------------------------------------------------------------- 
 */
int dir_right[4]={EAST,SOUTH,NORTH,WEST};
int dir_left[4]={WEST,NORTH,SOUTH,EAST};
features(cellx,celly,xFront,yFront,left,right,rx,ry)
int cellx,celly,xFront,yFront,left,right,rx,ry;
{
#if !defined(IBM_features)
long wallbits;
int l[4],r[4],ll[4],rr[4];

PenColor(color_wall);

rClip.top=Clip.top;
rClip.bottom=Clip.bottom;
rClip.left=Clip.left+1;
rClip.right=Clip.right-1;
ClipRect(&rClip);
/*cell center*/
if(corepower[coreindex]&&rClip.left<rClip.right)
switch((*map.data)[cellx][celly][4][0])
	{
	case 0:
		break;
	case SMHOLEFLR:
		if(flip)ceil1hole(xFront,yFront);
		else floor1hole(xFront,yFront);
		break;
	case LGHOLEFLR:
		if(flip)ceil2hole(xFront,yFront);
		else floor2hole(xFront,yFront);
		break;
	case SMHOLECEIL:
		if(flip)floor1hole(xFront,yFront);
		else ceil1hole(xFront,yFront);
		break;
	case LGHOLECEIL:
		if(flip)floor2hole(xFront,yFront);
		else ceil2hole(xFront,yFront);
		break;
	case HOTFOOT:
		hotfoot(xFront,yFront);
		break;
	}
/*---------------------front of cell*/
l[0]=drX[xFront][yFront];
l[2]=rx-tcos;
l[3]=ry+tsin;
r[0]=drX[xFront+Sidex][yFront+Sidey];
r[2]=rx+tsin-tcos;
r[3]=ry+tsin+tcos;
if(flip)	
	{
	l[1]=Height-drY[xFront][yFront];
	r[1]=Height-drY[xFront+Sidex][yFront+Sidey];
	}
else 
	{
	l[1]=drY[xFront][yFront];
	r[1]=drY[xFront+Sidex][yFront+Sidey];
	}
rClip.left=mx(Clip.left,l[0]);
rClip.left++;
rClip.right=mn(Clip.right,r[0]);
rClip.right--;
ClipRect(&rClip);
if(rClip.left<rClip.right)
if((*map.data)[cellx][celly][direction][0])
	dowall(cellx,celly,direction,l,r);
/*--------------------right of cell*/
ll[0]=r[0];
ll[1]=r[1];
ll[2]=rx+tsin+tsin;
ll[3]=ry+tcos+tcos;
rr[0]=drX[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
if(flip)rr[1]=Height-drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
else rr[1]=drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
rr[2]=rx+tsin+tsin+tcos;
rr[3]=ry+tcos+tcos-tsin;
rClip.left=mx(Clip.left,ll[0]);
rClip.right=mn(Clip.right,rr[0]);
rClip.left++;
rClip.right--;
ClipRect(&rClip);
if(rClip.left<rClip.right)
if((*map.data)[cellx][celly][dir_right[direction]][0])
	dowall(cellx,celly,dir_right[direction],ll,rr);
/*---------------------left of cell*/
ll[0]=drX[xFront-Frntx][yFront-Frnty];
if(flip)ll[1]=Height-drY[xFront-Frntx][yFront-Frnty];
else ll[1]=drY[xFront-Frntx][yFront-Frnty];
ll[2]=rx+tcos-tsin;
ll[3]=(ry-tcos)-tsin;
rr[0]=l[0];
rr[1]=l[1];
rr[2]=rx-tsin;
rr[3]=ry-tcos;
rClip.left=mx(Clip.left,ll[0]);
rClip.right=mn(Clip.right,rr[0]);
rClip.left++;
rClip.right--;
ClipRect(&rClip);
if(rClip.left<rClip.right)
if((*map.data)[cellx][celly][dir_left[direction]][0])
	dowall(cellx,celly,dir_left[direction],ll,rr);
ClipRect(&Clip);
#endif
}
/*----------------------------------------------------------------------
 *---------------------------------------------------------------------- 
 */
frontfeature(cellx,celly,xFront,yFront,left,right,rx,ry)
int cellx,celly,xFront,yFront,left,right,rx,ry;
{
#if !defined(IBM_frontfeature)
long wallbits;
int l[4],r[4],ll[4],rr[4];
Rect rClip;

rClip.top=Clip.top;
rClip.bottom=Clip.bottom;
/*---------------------front of cell*/
l[0]=drX[xFront][yFront];
l[2]=rx-tcos;
l[3]=ry+tsin;
r[0]=drX[xFront+Sidex][yFront+Sidey];
r[2]=rx+tsin-tcos;
r[3]=ry+tsin+tcos;
if(flip)
	{
	l[1]=Height-drY[xFront][yFront];
	r[1]=Height-drY[xFront+Sidex][yFront+Sidey];
	}
else
	{
	l[1]=drY[xFront][yFront];
	r[1]=drY[xFront+Sidex][yFront+Sidey];
	}
rClip.left=mx(Clip.left,l[0]);
rClip.right=mn(Clip.right,r[0]);
rClip.left++;
rClip.right--;
ClipRect(&rClip);
if(rClip.left<rClip.right)
if((*map.data)[cellx][celly][direction][0])dowall(cellx,celly,direction,l,r);
ClipRect(&Clip);
#endif
}
/*----------------------------------------------------------------------
 *---------------------------------------------------------------------- 
 */
dowall(cellx,celly,direction,left,right)
int cellx,celly,direction,left[4],right[4];
{
#if !defined(IBM_dowall)
int left2[2],right2[2];

if(corepower[coreindex])
switch((*map.data)[cellx][celly][direction][0])
	{
	case DOOR:
		if(level==1 || level==5 || level==6)
			{
			if((*map.data)[cellx][celly][direction][1]==0)
				drawOpenSSDoor(left,right);
			else drawClosedSSDoor(left,right);
			}
		else
			{
			if((*map.data)[cellx][celly][direction][1]==0)
				{
				perspective(left2,left[2],left[3]);
				perspective(right2,right[2],right[3]);
				if(flip)
					{
					left2[1]=Height-left2[1];
					right2[1]=Height-right2[1];
					}
				drawOpenDoor(left,right,left2,right2);
				}
			else drawClosedDoor(left,right);
			}
		break;
	case WINDOW:
		drawwind(left,right);
		break;
	case SHELVES:
		perspective(left2,left[2],left[3]);
		perspective(right2,right[2],right[3]);
		if(flip)
			{
			left2[1]=Height-left2[1];
			right2[1]=Height-right2[1];
			}
		drawbooks(left,right,left2,right2);
		break;
	case UPSTAIRS:
		perspective(left2,left[2],left[3]);
		perspective(right2,right[2],right[3]);
		if(flip)
			{
			left2[1]=Height-left2[1];
			right2[1]=Height-right2[1];
			}
		draw_up_stairs(left,right,left2,right2);
		break;
	case DNSTAIRS:
		perspective(left2,left[2],left[3]);
		perspective(right2,right[2],right[3]);
		if(flip)
			{
			left2[1]=Height-left2[1];
			right2[1]=Height-right2[1];
			}
		draw_dn_stairs(left,right,left2,right2);
		break;
	case CHAR:
		dodrawchar((*map.data)[cellx][celly][direction][1],left,right);
		break;
	case GLYPH:
		drawglyphs(left,right);
		break;
	case ELEVATOR:
		drawelevator(left,right);
		break;
	case TUNNEL:
		perspective(left2,left[2],left[3]);
		perspective(right2,right[2],right[3]);
		if(flip)
			{
			left2[1]=Height-left2[1];
			right2[1]=Height-right2[1];
			}
		drawTunnel(left,right,left2,right2);
		break;
	case AIRLOCK:
		if((*map.data)[cellx][celly][direction][1]==0)
			{
			drawALOpen(left,right);
			}
		else drawALClosed(left,right);
		break;
	case COLOR:
		drawColor((*map.data)[cellx][celly][direction],left,right);
	}
#endif
}
/*----------------------------------------------------------------------
 *---------------------------------------------------------------------- 
 */
ceil2hole(xFront,yFront)
int xFront,yFront;
{
#if !defined(IBM_ceil2hole)
int y;
int xx[4],yy[4];

if(flip)
	y=min(drY[xFront-Frntx][yFront-Frnty],
		drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty]);
else
	y=max(drY[xFront-Frntx][yFront-Frnty],
		drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty]);

xx[0]=drX[xFront][yFront];
yy[0]=drY[xFront][yFront];
xx[1]=drX[xFront+Sidex][yFront+Sidey];
yy[1]=drY[xFront+Sidex][yFront+Sidey];
xx[2]=drX[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
yy[2]=drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
xx[3]=drX[xFront-Frntx][yFront-Frnty];
yy[3]=drY[xFront-Frntx][yFront-Frnty];
if(polyfill)SuperPoly(cLTGRAY,4,xx,yy);
else 
	{
	MoveTo(xx[0],yy[0]);
	LineTo(xx[1],yy[1]);
	LineTo(xx[2],yy[2]);
	LineTo(xx[3],yy[3]);
	LineTo(xx[0],yy[0]);
	}
if(xx[0]>xx[3])
	{
	MoveTo(xx[0],yy[0]);
	LineTo(xx[0],y);
	}
if(xx[1]<xx[2])
	{
	MoveTo(xx[1],yy[1]);
	LineTo(xx[1],y);
	}
#endif
}
/*----------------------------------------------------------------------
 *---------------------------------------------------------------------- 
 */
floor2hole(xFront,yFront)
int xFront,yFront;
{
#if !defined(IBM_floor2hole)
int y;
int xx[4],yy[4];

if(flip)
	y=min(drY[xFront-Frntx][yFront-Frnty],
	drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty]);
else
	y=max(drY[xFront-Frntx][yFront-Frnty],
	drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty]);
xx[0]=drX[xFront][yFront];
yy[0]=Height-drY[xFront][yFront];
xx[1]=drX[xFront+Sidex][yFront+Sidey];
yy[1]=Height-drY[xFront+Sidex][yFront+Sidey];
xx[2]=drX[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
yy[2]=Height-drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
xx[3]=drX[xFront-Frntx][yFront-Frnty];
yy[3]=Height-drY[xFront-Frntx][yFront-Frnty];
if(polyfill)SuperPoly(cLTGRAY,4,xx,yy);
else
	{
	MoveTo(xx[0],yy[0]);
	LineTo(xx[1],yy[1]);
	LineTo(xx[2],yy[2]);
	LineTo(xx[3],yy[3]);
	LineTo(xx[0],yy[0]);
	}
if(xx[0]>xx[3])
	{
	MoveTo(xx[0],yy[0]);
	LineTo(xx[0],Height-y);
	}
if(xx[1]<xx[2])
	{
	MoveTo(xx[1],yy[1]);
	LineTo(xx[1],Height-y);
	}
#endif
}
/*----------------------------------------------------------------------
 *---------------------------------------------------------------------- 
 */
ceil1hole(xFront,yFront)
int xFront,yFront;
{
#if !defined(IBM_ceil1hole)
int x1,x2,x3,x4,y1,y2,y3,y4;
int xx1,xx2,xx3,xx4,yy1,yy2,yy3,yy4;
int xx[4],yy[4];
int y;

x1=drX[xFront][yFront];
x2=drX[xFront+Sidex][yFront+Sidey];
x3=drX[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
x4=drX[xFront-Frntx][yFront-Frnty];

y1=drY[xFront][yFront];
y2=drY[xFront+Sidex][yFront+Sidey];
y3=drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
y4=drY[xFront-Frntx][yFront-Frnty];

xx1=(((x1+x2)>>1)+x1)>>1;
xx2=(((x1+x2)>>1)+x2)>>1;
xx3=(((x3+x4)>>1)+x3)>>1;
xx4=(((x3+x4)>>1)+x4)>>1;

yy1=(((y1+y4)>>1)+y1)>>1;
yy2=(((y2+y3)>>1)+y2)>>1;
yy3=(((y2+y3)>>1)+y3)>>1;
yy4=(((y1+y4)>>1)+y4)>>1;

xx[0]=(((xx1+xx4)>>1)+xx1)>>1;
xx[1]=(((xx2+xx3)>>1)+xx2)>>1;
xx[2]=(((xx2+xx3)>>1)+xx3)>>1;
xx[3]=(((xx1+xx4)>>1)+xx4)>>1;

yy[0]=(((yy1+yy2)>>1)+yy1)>>1;
yy[1]=(((yy1+yy2)>>1)+yy2)>>1;
yy[2]=(((yy3+yy4)>>1)+yy3)>>1;
yy[3]=(((yy3+yy4)>>1)+yy4)>>1;

if(polyfill)SuperPoly(cLTGRAY,4,xx,yy);
else
	{
	MoveTo(xx[0],yy[0]);
	LineTo(xx[1],yy[1]);
	LineTo(xx[2],yy[2]);
	LineTo(xx[3],yy[3]);
	}
if(flip)y=min(yy[2],yy[3]);
else    y=max(yy[2],yy[3]);
if(xx[0]>xx[3])
	{
	MoveTo(xx[0],yy[1]);
	LineTo(xx[0],y);
	}
if(xx[1]<xx[2])
	{
	MoveTo(xx[1],yy[1]);
	LineTo(xx[1],y);
	}
#endif
}

/*----------------------------------------------------------------------
 *---------------------------------------------------------------------- 
 */
floor1hole(xFront,yFront)
int xFront,yFront;
{
#if !defined(IBM_floor1hole)
int x1,x2,x3,x4,y1,y2,y3,y4;
int xx1,xx2,xx3,xx4,yy1,yy2,yy3,yy4;
int y;
int xx[4],yy[4];

x1=drX[xFront][yFront];
x2=drX[xFront+Sidex][yFront+Sidey];
x3=drX[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
x4=drX[xFront-Frntx][yFront-Frnty];

y1=drY[xFront][yFront];
y2=drY[xFront+Sidex][yFront+Sidey];
y3=drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
y4=drY[xFront-Frntx][yFront-Frnty];

xx1=(((x1+x2)>>1)+x1)>>1;
xx2=(((x1+x2)>>1)+x2)>>1;
xx3=(((x3+x4)>>1)+x3)>>1;
xx4=(((x3+x4)>>1)+x4)>>1;

yy1=(((y1+y4)>>1)+y1)>>1;
yy2=(((y2+y3)>>1)+y2)>>1;
yy3=(((y2+y3)>>1)+y3)>>1;
yy4=(((y1+y4)>>1)+y4)>>1;

xx[0]=(((xx1+xx4)>>1)+xx1)>>1;
xx[1]=(((xx2+xx3)>>1)+xx2)>>1;
xx[2]=(((xx2+xx3)>>1)+xx3)>>1;
xx[3]=(((xx1+xx4)>>1)+xx4)>>1;

yy[0]=Height-((((yy1+yy2)>>1)+yy1)>>1);
yy[1]=Height-((((yy1+yy2)>>1)+yy2)>>1);
yy[2]=Height-((((yy3+yy4)>>1)+yy3)>>1);
yy[3]=Height-((((yy3+yy4)>>1)+yy4)>>1);

if(polyfill)SuperPoly(cLTGRAY,4,xx,yy);
else
	{
	MoveTo(xx[0],yy[0]);
	LineTo(xx[1],yy[1]);
	LineTo(xx[2],yy[2]);
	LineTo(xx[3],yy[3]);
	LineTo(xx[0],yy[0]);
	}
if(flip)y=max(yy[2],yy[3]);
else    y=min(yy[2],yy[3]);
if(xx[0]>xx[3])
	{
	MoveTo(xx[0],yy[0]);
	LineTo(xx[0],y);
	}
if(xx[1]<xx[2])
	{
	MoveTo(xx[1],yy[1]);
	LineTo(xx[1],y);
	}
#endif
}
/*----------------------------------------------------------------------
 *---------------------------------------------------------------------- 
 */
hotfoot(xFront,yFront)
int xFront,yFront;
{
#if !defined(IBM_hotfoot)
int xx[4],yy[4];

xx[0]=drX[xFront][yFront];
yy[0]=Height-drY[xFront][yFront];
xx[1]=drX[xFront+Sidex][yFront+Sidey];
yy[1]=Height-drY[xFront+Sidex][yFront+Sidey];
xx[2]=drX[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
yy[2]=Height-drY[xFront+Sidex-Frntx][yFront+Sidey-Frnty];
xx[3]=drX[xFront-Frntx][yFront-Frnty];
yy[3]=Height-drY[xFront-Frntx][yFront-Frnty];
if(polyfill)SuperPoly(cTELE,4,xx,yy);
else
	{
	MoveTo(xx[0],yy[0]);
	LineTo(xx[2],yy[2]);
	MoveTo(xx[1],yy[1]);
	LineTo(xx[3],yy[3]);
	}
#endif
}
/*----------------------------------------------------------------------
 *---------------------------------------------------------------------- 
 */
split7(arr,x1,x2)
int arr[7];
int x1,x2;
{
#if !defined(IBM_split7)
arr[3]=(x1+x2)>>1;
arr[1]=(x1+arr[3])>>1;
arr[0]=(x1+arr[1])>>1;
arr[2]=(arr[1]+arr[3])>>1;
arr[5]=(arr[3]+x2)>>1;
arr[6]=(arr[5]+x2)>>1;
arr[4]=(arr[3]+arr[5])>>1;
#endif
}
