#define EXT extern
#include "gamedefs.h"

/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
int ccenterx,ccentery;
int xloc,yloc;
int xcorner[8],ycorner[8];
Rect DashBoard;
Rect compOval;
Rect compRect,floorRect,powerRect;
int powerWidth,powerHeight;
int l_ext;
int s_ext;

point compStart, compLast, compLastLast;
#define WARNING 4
int doSetPower=False;

/*----------------------------------------------------------------------*/
DrawDashBoard()
{
SetPort(metaPnt);
ClipRect(&sR);
PenColor(realcolor[vBLACK]);
PenMode(zREPz);
MoveTo(screenR.left-1,screenR.top);
LineTo(screenR.left-1,screenR.bottom);
DashBoard.left=0;
DashBoard.right=4*pix_per_Qinch_x+2;
DashBoard.top= 0;
DashBoard.bottom= sR.bottom;
RConsole(&DashBoard);
RCompass(&DashBoard);
RHeadsUp(&DashBoard);
if(armor||weapons)
	RPower(&DashBoard);
ClipRect(&screenR);
doSetPower=False;
/*SetPower(0,0,0);*/
}
/*----------------------------------------------------------------------*/
HelpDashBoard()
{
SetPort(scrport);
ClipRect(&sR);
PenColor(realcolor[vBLACK]);
PenMode(zREPz);
DashBoard.left=0;
DashBoard.right=4*pix_per_Qinch_x+2;
DashBoard.top= 0;
DashBoard.bottom= sR.bottom;
RConsole(&DashBoard);
RCompass(&DashBoard);
RHeadsUp(&DashBoard);
RPower(&DashBoard);
ClipRect(&sR);
doSetPower=False;
SetPower(0,0,0);
updateDashBoard();
}
/*----------------------------------------------------------------------* 
 *----------------------------------------------------------------------*/
updateDashBoard()
{
int powerAngle;
Rect tr;
int dx,dy;
int xx,yy;

ClipRect( &DashBoard );
PenColor(realcolor[vINTWHITE]);
MoveTo(compStart.X, compStart.Y);
LineTo(compLast.X, compLast.Y);
MoveTo(compStart.X, compStart.Y);
LineTo(compLastLast.X, compLastLast.Y);
compLastLast.X= compLast.X;
compLastLast.Y= compLast.Y;
compLast.X= compStart.X+((compOval.right-compOval.left)*cost[Me.ang]>>8);
compLast.Y= compStart.Y-((compOval.bottom-compOval.top)*sint[Me.ang]>>8);
PenColor(realcolor[vBLACK]);
MoveTo(compStart.X, compStart.Y);
LineTo(compLast.X, compLast.Y);
ClipRect(&screenR);

/*-------------*/
ClipRect(&floorRect);
PenColor(realcolor[vINTWHITE]);
PaintRect(&floorRect);
PenColor(realcolor[vBLACK]);
FrameRect(&floorRect);
if(game==COLONY)
	{
	xloc=(float)l_ext*((Me.xindex<<8)-Me.xloc)/256.0;
	yloc=(float)l_ext*((Me.yindex<<8)-Me.yloc)/256.0;
	DrawHeadsUp();
	}
ClipRect(&screenR);
}
/*----------------------------------------------------------------------
 * SetPower()
 *----------------------------------------------------------------------
 */
SetPower(p0,p1,p2)
int p0,p1,p2;
{
#if !defined(IBM_SetPower)
GrafPtr	savePort;
Rect rb;
long newpower[3];
int newepower[3];
int i,j;
int lft,bot;
int ln,m;
extern int showDashBoard;

newpower[0]=Me.power[0]+p0;
newpower[1]=Me.power[1]+p1;
newpower[2]=Me.power[2]+p2;
if(newpower[0]<0)newpower[0]=0;
if(newpower[1]<0)newpower[1]=0;
if(newpower[2]<0)newpower[2]=0;
newepower[0]=qlog((long)newpower[0]);
newepower[1]=qlog((long)newpower[1]);
newepower[2]=qlog((long)newpower[2]);
if(newepower[0]<0)newepower[0]=0;
if(newpower[1] <0)newepower[1]=0;
if(newepower[2]<0)newepower[2]=0;
/*  bot=info.bottom-27;    */
if(showDashBoard&&armor)
	{
	SetPort(metaPnt);
	ClipRect(&powerRect);
	FixBarGraph(powerRect.left,
		powerRect.bottom-(powerWidth+1),epower[0],newepower[0]);
	FixBarGraph(powerRect.left+powerWidth,
		powerRect.bottom-(powerWidth+1),epower[1],newepower[1]);
	FixBarGraph(powerRect.left+powerWidth*2,
		powerRect.bottom-(powerWidth+1),epower[2],newepower[2]);
	ClipRect(&screenR);
	SetPort(scrport);
	if(is_EGAtype)
		{
		HideCursor();
		ClipRect(&powerRect);
		FixBarGraph(powerRect.left,
			powerRect.bottom-(powerWidth+1),epower[0],newepower[0]);
		FixBarGraph(powerRect.left+powerWidth,
			powerRect.bottom-(powerWidth+1),epower[1],newepower[1]);
		FixBarGraph(powerRect.left+powerWidth*2,
			powerRect.bottom-(powerWidth+1),epower[2],newepower[2]);
		ClipRect(&screenR);
		ShowCursor();
		}
	}
for (i=0; i<3; i++)
    {
	epower[i]=newepower[i];
    Me.power[i]=newpower[i];
    }
if(newpower[1]<=0)Terminate(FALSE);/*you're dead*/

#endif
}
/*----------------------------------------------------------------------*/
RConsole(r)
Rect *r;
{
int shift_x, shift_y;
polyHead polyHdr;
Point	 polyPts[9];
Rect tr;

PenColor(realcolor[vBLACK]);
BackColor(realcolor[vWHITE]);

shift_x= (pix_per_Qinch_x>>2)+1;
shift_y= (pix_per_Qinch_y>>2)+1;
ClipRect(r);
FillRect(r,3);
PenColor(realcolor[vBLUE]);
FrameRect(r);
PenColor(realcolor[vBLACK]);
return;

polyHdr.polyBgn= 0;
polyHdr.polyEnd= 6;
polyHdr.polyRect.Xmin= r->left;
polyHdr.polyRect.Xmax= r->right;
polyHdr.polyRect.Ymin= r->top;
polyHdr.polyRect.Ymax= r->bottom;

polyPts[0].h= r->left;
polyPts[0].v= r->top;
polyPts[1].h= r->left;
polyPts[1].v= r->bottom;
polyPts[2].h= r->left+shift_x;
polyPts[2].v= r->bottom-shift_y;
polyPts[3].h= r->left+shift_x;
polyPts[3].v= r->top+shift_y;
polyPts[4].h= r->right-shift_x;
polyPts[4].v= r->top+shift_y;
polyPts[5].h= r->right;
polyPts[5].v= r->top;
polyPts[6].h= r->left;
polyPts[6].v= r->top;
FillPoly(1, &polyHdr, polyPts, 7);

FrameRect(r);
MoveTo(r->left, r->top);
LineTo(r->left+shift_x, r->top+shift_y);
MoveTo(r->right, r->top);
LineTo(r->right-shift_x, r->top+shift_y);
MoveTo(r->left, r->bottom);
LineTo(r->left+shift_x, r->bottom-shift_y);
MoveTo(r->right, r->bottom);
LineTo(r->right-shift_x, r->bottom-shift_y);

BackColor(realcolor[vINTWHITE]);
tr.top=r->top+shift_y;
tr.bottom=r->bottom-shift_y;
tr.left=r->left+shift_x;
tr.right=r->right-shift_x;

FillRect(&tr,3);
FrameRect(&tr);
}
/*----------------------------------------------------------------------*
 *----------------------------------------------------------------------*/
RCompass(Rect *r)
{
BackColor(realcolor[vINTWHITE]);
compOval.bottom= r->bottom-(pix_per_Qinch_y>>2);
compOval.top= r->bottom-4*pix_per_Qinch_y;
compOval.left= 2;
compOval.right= 4*pix_per_Qinch_x;
FillOval(&compOval,1);
compOval.top+= 2;
compOval.bottom-= 2;
compOval.left+= 2;
compOval.right-= 2;
EraseOval(&compOval);
compStart.X= compLast.X= compLastLast.X= ( compOval.left+compOval.right )/2;
compStart.Y= compLast.Y= compLastLast.Y= ( compOval.top+compOval.bottom )/2;
}
/*----------------------------------------------------------------------*
 *----------------------------------------------------------------------*/
RHeadsUp(Rect *r)
{
Rect tr;

ClipRect(r);
l_ext=(r->right-r->left)>>1;
l_ext+=(l_ext>>1);
if(l_ext&0x01)l_ext--;
s_ext=l_ext>>1;
BackColor(realcolor[vINTWHITE]);

floorRect.bottom= (compOval.top-4)-(pix_per_Qinch_y>>2);
floorRect.top= (compOval.top-4)-4*pix_per_Qinch_y;
floorRect.left= 2;
floorRect.right= r->right-2;

ccenterx=(floorRect.left+floorRect.right)>>1;
ccentery=(floorRect.top+floorRect.bottom)>>1;

/*
floorRect.top++; floorRect.left++;
floorRect.bottom--; floorRect.right--;
*/
EraseRect(&floorRect);
FrameRect(&floorRect);
ClipRect(&floorRect);

xloc=(float)l_ext*((Me.xindex<<8)-Me.xloc)/256.0;
yloc=(float)l_ext*((Me.yindex<<8)-Me.yloc)/256.0;

if(game!=COLONY)return;
DrawHeadsUp();
}
/*----------------------------------------------------------------------*
 *----------------------------------------------------------------------*/
DrawHeadsUp()
{
int dx,dy,px,py;
int xx,yy;
Rect tr;
int fd;

PenColor(realcolor[vBLACK]);
tsin=sint[Me.ang];
tcos=cost[Me.ang];
xcorner[0]=ccenterx+(((long)xloc * tsin - (long)yloc * tcos) >> 8);
ycorner[0]=ccentery-(((long)yloc * tsin + (long)xloc * tcos) >> 8);		
xcorner[1]=ccenterx+(((long)(xloc+l_ext) * tsin - (long)yloc * tcos) >> 8);
ycorner[1]=ccentery-(((long)yloc * tsin + (long)((xloc+l_ext) * tcos)) >> 8);		
xcorner[2]=ccenterx+(((long)(xloc+l_ext) * tsin - (long)(yloc+l_ext) * tcos) >> 8);
ycorner[2]=ccentery-(((long)(yloc+l_ext) * tsin + (long)(xloc+l_ext) * tcos) >> 8);		
xcorner[3]=ccenterx+(((long)(xloc * tsin - (long)(yloc+l_ext) * tcos)) >> 8);
ycorner[3]=ccentery-(((long)(yloc+l_ext) * tsin + (long)xloc * tcos) >> 8);
xcorner[4]=ccenterx+(((long)(xloc+s_ext) * tsin - (long)(yloc+s_ext) * tcos) >> 8);
ycorner[4]=ccentery-(((long)(yloc+s_ext) * tsin + (long)(xloc+s_ext) * tcos) >> 8);		
xcorner[5]=ccenterx+(((long)(xloc+s_ext) * tsin - (long)(yloc) * tcos) >> 8);
ycorner[5]=ccentery-(((long)(yloc) * tsin + (long)(xloc+s_ext) * tcos) >> 8);		
dx=xcorner[1]-xcorner[0]; dy=ycorner[0]-ycorner[1];
MoveTo(xcorner[0]-dx,ycorner[0]+dy);
LineTo(xcorner[1]+dx,ycorner[1]-dy);
MoveTo(xcorner[1]+dy,ycorner[1]+dx);
LineTo(xcorner[2]-dy,ycorner[2]-dx);
MoveTo(xcorner[2]+dx,ycorner[2]-dy);
LineTo(xcorner[3]-dx,ycorner[3]+dy);
MoveTo(xcorner[3]-dy,ycorner[3]-dx);
LineTo(xcorner[0]+dy,ycorner[0]+dx);
if(fd=foodarray[Me.xindex][Me.yindex])
if(Object[fd].type<FWALL)
		{
		xx=xcorner[4];
		yy=ycorner[4];
		tr.left=xx-1;
		tr.right=xx+1;
		tr.top=yy-1;
		tr.bottom=yy+1;
		FrameRect(&tr);
		}
if(!(Wall[Me.xindex][Me.yindex]&0x01))
	{
	if(fd=foodarray[Me.xindex][Me.yindex-1])
		if(Object[fd].type<FWALL)
		{
		xx=xcorner[4]+dy;
		yy=ycorner[4]+dx;
		tr.left=xx-1;
		tr.right=xx+1;
		tr.top=yy-1;
		tr.bottom=yy+1;
		FrameRect(&tr);
		}
	if(robotarray[Me.xindex][Me.yindex-1])
		{
		xx=xcorner[4]+dy;
		yy=ycorner[4]+dx;
		tr.left=xx-2;
		tr.right=xx+2;
		tr.top=yy-2;
		tr.bottom=yy+2;
		FrameRect(&tr);
		}
	}
if(!(Wall[Me.xindex][Me.yindex]&0x02))
	{
	if(fd=foodarray[Me.xindex-1][Me.yindex])
		if(Object[fd].type<FWALL)
		{
		xx=xcorner[4]-dx;
		yy=ycorner[4]+dy;
		tr.left=xx-1;
		tr.right=xx+1;
		tr.top=yy-1;
		tr.bottom=yy+1;
		FrameRect(&tr);
		}
	if(robotarray[Me.xindex-1][Me.yindex])
		{
		xx=xcorner[4]-dx;
		yy=ycorner[4]+dy;
		tr.left=xx-2;
		tr.right=xx+2;
		tr.top=yy-2;
		tr.bottom=yy+2;
		FrameRect(&tr);
		}
	}
if(!(Wall[Me.xindex][Me.yindex+1]&0x01))
	{
	if(fd=foodarray[Me.xindex][Me.yindex+1])
		if(Object[fd].type<FWALL)
		{
		xx=xcorner[4]-dy;
		yy=ycorner[4]-dx;
		tr.left=xx-1;
		tr.right=xx+1;
		tr.top=yy-1;
		tr.bottom=yy+1;
		FrameRect(&tr);
		}
	if(robotarray[Me.xindex][Me.yindex+1])
		{
		xx=xcorner[4]-dy;
		yy=ycorner[4]-dx;
		tr.left=xx-2;
		tr.right=xx+2;
		tr.top=yy-2;
		tr.bottom=yy+2;
		FrameRect(&tr);
		}
	}
if(!(Wall[Me.xindex+1][Me.yindex]&0x02))
	{
	if(fd=foodarray[Me.xindex+1][Me.yindex])
		if(Object[fd].type<FWALL)
		{
		xx=xcorner[4]+dx;
		yy=ycorner[4]-dy;
		tr.left=xx-1;
		tr.right=xx+1;
		tr.top=yy-1;
		tr.bottom=yy+1;
		FrameRect(&tr);
		}
	if(robotarray[Me.xindex+1][Me.yindex])
		{
		xx=xcorner[4]+dx;
		yy=ycorner[4]-dy;
		tr.left=xx-2;
		tr.right=xx+2;
		tr.top=yy-2;
		tr.bottom=yy+2;
		FrameRect(&tr);
		}
	}
px=pix_per_Qinch_x>>1;
py=pix_per_Qinch_y>>2;
tr.top=ccentery-py;   tr.bottom=ccentery+py;
tr.left=ccenterx-px; tr.right=ccenterx+px;
FrameOval(&tr);
px=pix_per_Qinch_x>>2;
tr.left=ccenterx-px; tr.right=ccenterx+px;
FillOval(&tr,1);
ClipRect(&compRect);
}
/*----------------------------------------------------------------------*
 *----------------------------------------------------------------------*/
RPower(Rect *r)
{
Rect tr;
int wd,twd,l;

wd=twd=r->right-r->left;
twd/=3;
twd--;
twd>>=1;
twd<<=1;
powerWidth=twd;
twd*=3;
l=(wd-twd)>>1;

ClipRect(r);
BackColor(realcolor[vINTWHITE]);
powerRect.top= r->top+8;
powerRect.bottom= r->bottom-2*(4*pix_per_Qinch_y+8);
powerRect.left= l;
powerRect.right= l+twd;
powerHeight=(powerRect.bottom-powerRect.top)/32;
powerHeight=min(powerHeight,5);
powerRect.bottom=powerRect.top+powerHeight*32;
EraseRect(&powerRect);
FrameRect(&powerRect);
MoveTo(powerRect.left+powerWidth,powerRect.bottom);
LineTo(powerRect.left+powerWidth,powerRect.top);
MoveTo(powerRect.left+powerWidth*2,powerRect.bottom);
LineTo(powerRect.left+powerWidth*2,powerRect.top);
MoveTo(powerRect.left,powerRect.bottom-powerWidth);
LineTo(powerRect.right,powerRect.bottom-powerWidth);
/*draw the symbols*/
MoveTo(powerRect.left+2,powerRect.bottom-2);
LineTo(powerRect.left+powerWidth-2,powerRect.bottom-2);
LineTo(powerRect.left+(powerWidth>>1),powerRect.bottom-(powerWidth-2));
LineTo(powerRect.left+2,powerRect.bottom-2);

MoveTo(powerRect.left+1+powerWidth,powerRect.bottom-(powerWidth>>1));
LineTo(powerRect.left+powerWidth+(powerWidth>>1),
	powerRect.bottom-(powerWidth-1));
LineTo(powerRect.left+(2*powerWidth)-1,
	powerRect.bottom-(powerWidth>>1));
LineTo(powerRect.left+powerWidth+(powerWidth>>1),
	powerRect.bottom-1);
LineTo(powerRect.left+1+powerWidth,powerRect.bottom-(powerWidth>>1));

MoveTo(powerRect.left+2+2*powerWidth,powerRect.bottom-(powerWidth-2));
LineTo(powerRect.left+3*powerWidth-2,powerRect.bottom-(powerWidth-2));
LineTo(powerRect.left+2*powerWidth+(powerWidth>>1),powerRect.bottom-2);
LineTo(powerRect.left+2*powerWidth+2,powerRect.bottom-(powerWidth-2));

/*draw the power display*/
DrawBarGraph(powerRect.left,powerRect.bottom-(powerWidth+1),epower[0]);
DrawBarGraph(powerRect.left+powerWidth,
	powerRect.bottom-(powerWidth+1),epower[1]);
DrawBarGraph(powerRect.left+powerWidth*2,
	powerRect.bottom-(powerWidth+1),epower[2]);
}
/*----------------------------------------------------------------------*
 *----------------------------------------------------------------------*/
DrawBarGraph(x,y,height)
int x,y,height;
{
int i,j,h;
int color;

if(height<=3)color=realcolor[vRED];
else color=realcolor[vBLUE];
for(i=0;i<height;i++)
	{
	PenColor(realcolor[vBLACK]);
	for(j=0;j<powerHeight-1;j++)
		{
		h=y-(2+i*powerHeight+j);
		MoveTo(x+2,h);
		LineTo(x+powerWidth-2,h);
		PenColor(color);
		}
	}
}/*----------------------------------------------------------------------*
 *----------------------------------------------------------------------*/
FixBarGraph(x,y,oldheight,newheight)
int x,y,oldheight,newheight;
{
int i,j,h;
int color;

if(oldheight==newheight)return;
if(newheight<=WARNING&&oldheight>WARNING)/*erase it all and redraw*/
	{
	PenColor(realcolor[vINTWHITE]);
	for(i=newheight;i<oldheight;i++)
		{
		for(j=0;j<powerHeight-1;j++)
			{
			h=y-(2+i*powerHeight+j);
			MoveTo(x+2,h);
			LineTo(x+powerWidth-2,h);
			}
		}
	oldheight=0;
	color=realcolor[vRED];
	}
else if(newheight>WARNING&&oldheight<=WARNING)/*redraw it all in blue*/
	{
	oldheight=0;
	color=realcolor[vBLUE];
	}
else if(newheight<=WARNING)color=realcolor[vRED];
else color=realcolor[vBLUE];

if(oldheight<newheight)
	{
	for(i=oldheight;i<newheight;i++)
		{
		PenColor(realcolor[vBLACK]);
		for(j=0;j<powerHeight-1;j++)
			{
			h=y-(2+i*powerHeight+j);
			MoveTo(x+2,h);
			LineTo(x+powerWidth-2,h);
			PenColor(color);
			}
		}
	}
else
	{
	PenColor(realcolor[vINTWHITE]);
	for(i=newheight;i<oldheight;i++)
		{
		for(j=0;j<powerHeight-1;j++)
			{
			h=y-(2+i*powerHeight+j);
			MoveTo(x+2,h);
			LineTo(x+powerWidth-2,h);
			}
		}
	}
}
/*----------------------------------------------------------------------*/
int qlog(x)
long x;
{
#if !defined(IBM_qlog)
int i=0;

while(x){x>>=1;i++;}
return(i);
#endif
}
