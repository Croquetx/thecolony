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
 * power.c
 *---------------------------------------------------------------------
 * DrawInfo()
 * DoInfo()
 * ZoomRect(pr1,pr2)
 *		Rect *pr1,*pr2;
 * SetPower(p0,p1,p2)
 *		int p0,p1,p2;
 * int qlog(x)
 *		long x;
 *---------------------------------------------------------------------
 */
#define EXT extern
#include "cgamedefs.h"
Rect info;
int trouble=FALSE;
extern RGBColor white_Color;
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
DrawInfo()
{
PicHandle inf;
Rect clr;
int xSize,ySize;
int top,lft,bot,rit,ln,i,j;
PolyHandle poly;

SetPort(infoWindow);
SetOrigin(0,0);
clr.left=infoWindow->portRect.left;
clr.top=infoWindow->portRect.top;
clr.bottom=infoWindow->portRect.bottom;
clr.right=infoWindow->portRect.right;
ClipRect(&clr);
FillRect(&clr,white);
if(epower[1]<6)trouble=TRUE;
else trouble=FALSE;
if(armor)
	{
	if(trouble)inf=GetPicture(-32760);
	else inf=GetPicture(-32755);
	SizeRect(&xSize,&ySize,&(**inf).picFrame);
	SetRect(&info,-2,-2,xSize-2,ySize-2);
	ClipRect(&info);
	DrawPicture(inf,&info);
	info.left+=3;
	info.right+=3;
	info.top-=3;
	info.bottom-=3;
	ForeColor(blueColor);
	PenPat(black);
	info.top++;
	info.bottom++;
	info.right--;
	info.left--;
	bot=info.bottom-27;
	for(i=0;i<3;i++)
		{
		for(j=0;j<epower[i];j++)
			{
			lft=3+info.left+i*23;
				{
				for(j=0;j<epower[i];j++)
					{
					ln=bot-3*j;
					MoveTo(lft+1,ln);
					LineTo(lft+16,ln);
					MoveTo(lft+1,ln-1);
					LineTo(lft+16,ln-1);
					}
				}
			}
		}
	}
else
	{
	if(FindDepth()>=8)inf=GetPicture(-32761);
	else inf=GetPicture(-32752);
	SizeRect(&xSize,&ySize,&(**inf).picFrame);
	SetRect(&info,-2,-2,xSize-2,ySize-2);
	ClipRect(&info);
	DrawPicture(inf,&info);

/*	clr.top+=8;
	clr.bottom-=8;
	clr.left+=8;
	clr.right-=8;
	
	FillRect(&clr,gray);
	poly=OpenPoly();
	MoveTo(clr.left,clr.top);
	LineTo(clr.right,clr.top);
	LineTo(clr.right+8,clr.top-8);
	LineTo(clr.left-8,clr.top-8);
	LineTo(clr.left,clr.top);
	ClosePoly();
	FillPoly(poly,ltGray);
	FramePoly(poly);
	KillPoly(poly);
	
	poly=OpenPoly();
	MoveTo(clr.left,clr.top);
	LineTo(clr.left,clr.bottom);
	LineTo(clr.left-8,clr.bottom+8);
	LineTo(clr.left-8,clr.top-8);
	LineTo(clr.left,clr.top);
	ClosePoly();
	FillPoly(poly,ltGray);
	FramePoly(poly);
	KillPoly(poly);
	
	poly=OpenPoly();
	MoveTo(clr.left,clr.bottom);
	LineTo(clr.left-8,clr.bottom+8);
	LineTo(clr.right+8,clr.bottom+8);
	LineTo(clr.right,clr.bottom);
	LineTo(clr.left,clr.bottom);
	ClosePoly();
	FillPoly(poly,dkGray);
	FramePoly(poly);
	KillPoly(poly);

	poly=OpenPoly();
	MoveTo(clr.right,clr.bottom);
	LineTo(clr.right,clr.top);
	LineTo(clr.right+8,clr.top-8);
	LineTo(clr.right+8,clr.bottom+8);
	LineTo(clr.right,clr.bottom);
	ClosePoly();
	FillPoly(poly,dkGray);
	FramePoly(poly);
	KillPoly(poly);*/
	}
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
DoInfo(where)
Point where;
{
Point pt;
int but;
Rect r1,r2;

SetPort(infoWindow);
GetMouse(&pt);
/*GlobalToLocal(&pt);*/
if(PtInRect(pt,&info))
if(pt.v>info.bottom-20)
	{
	but=pt.h/24;
	pt.v=info.bottom-24;
	pt.h=but*24;
	LocalToGlobal(&pt);
	r1.top=pt.v;
	r1.left=pt.h;
	r1.bottom=r1.top+24;
	r1.right=r1.left+24;
	switch(but)
		{
		case 0:
			PowerInform("\pWeapons",&r1);
			break;
		case 1:
			PowerInform("\pLife",&r1);
			break;
		case 2:
			PowerInform("\pArmor",&r1);
			break;
		}
	Display();
	ZoomRect(&r2,&r1);
	}
else DragWindow(infoWindow,where,&screenBits.bounds);
}
/*----------------------------------------------------------------------
 *----------------------------------------------------------------------
 */
#define ZOOM 8.0
ZoomRect(pr1,pr2)
Rect *pr1,*pr2;
{
GrafPtr	savePort;
CGrafPort metaPort;
double delta[4];
Rect r;
int i;

GetPort( &savePort );
OpenCPort(&metaPort);
SetPortPix(&screenBits);
PenMode(patXor);
SetOrigin(0,0);
HideCursor();
PenMode(patXor);
delta[0]=(pr2->top  - pr1->top)/ZOOM;
delta[1]=(pr2->left  - pr1->left)/ZOOM;
delta[2]=(pr2->bottom -pr1->bottom)/ZOOM;
delta[3]=(pr2->right -pr1->right)/ZOOM;
r.top	=pr1->top;
r.left	=pr1->left;
r.bottom=pr1->bottom;
r.right	=pr1->right;
for(i=0;i<ZOOM;i++)
	{
	FrameRect(&r);
	FrameRect(&r);
	r.top+=delta[0];
	r.left+=delta[1];
	r.bottom+=delta[2];
	r.right+=delta[3];
	}
ShowCursor();
SetPort( savePort );
}
/*----------------------------------------------------------------------
 *----------------------------------------------------------------------
 */
SetPower(p0,p1,p2)
int p0,p1,p2;
{
GrafPtr	savePort;
Rect rb;
long newpower[3];
int newepower[3];
int i,j;
int lft,bot;
int ln,m;

GetPort( &savePort );
SetPort( infoWindow );

ClipRect(&info);
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
bot=info.bottom-27;
PenPat(black);
if((trouble && newepower[1]>5) || ((!trouble)&&newepower[1]<6))
	{
	for(i=0;i<3;i++)
		{
		epower[i]=newepower[i];
		Me.power[i]=newpower[i];
		}
	DrawInfo();
	return;
	}
for(i=0;i<3;i++)
	{
	lft=3+info.left+i*23;
	if(newepower[i]>epower[i]&&armor)
		{
		ForeColor(blueColor);
		for(j=epower[i];j<newepower[i];j++)
			{
			ln=bot-3*j;
			MoveTo(lft+1,ln);
			LineTo(lft+16,ln);
			MoveTo(lft+1,ln-1);
			LineTo(lft+16,ln-1);
			}
		}
	else
		{
		m=max(newepower[i],0);
		if(armor)
			{
			RGBForeColor(&white_Color);
			for(j=epower[i]-1; j>=m ;j--)
				{
				ln=bot-3*j;
				MoveTo(lft+1,ln);
				LineTo(lft+16,ln);
				MoveTo(lft+1,ln-1);
				LineTo(lft+16,ln-1);
				}
			}
		}
	epower[i]=newepower[i];
	Me.power[i]=newpower[i];
	}
if(newpower[1]<=0)Terminate(FALSE);/*you're dead*/
SetPort( savePort );
}
/*----------------------------------------------------------------------*/
int qlog(x)
long x;
{
int i=0;

while(x){x>>=1;i++;}
return(i);
}
