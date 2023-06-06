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
 * intro.c
 *----------------------------------------------------------------------* 
 * intro()
 * int ScrollInfo()
 * makestars(pr,btn)
 * 		Rect *pr;
 *		int btn;
 * makeplanet()
 * leaveplanet()
 * explodeplanet()
 * Makeblackhole()
 * DoPicture(pnum,r)
 *		int pnum;
 *		Rect *r;
 * gameInit()
 * tabsgen()
 * GameOver(kill)
 *		int kill;
 *----------------------------------------------------------------------*/
#define EXT extern
#include "cgamedefs.h"
#include "sintable.h"
int gameover=0;
extern int LostSound;
#define MAXCOLOR 65535
#define POWER 	256	/* ~= 100 */
#define SUIT 	0		/* == 0   */
/*----------------------------------------------------------------------*/
extern PixMapHandle ANewPixMap();
intro()
{
WindowPtr aWindow;
CGrafPtr	savePort;
WindowRecord wRecord;
int qt = FALSE;
CGrafPort metaPort;
int i,j,k;

GetPort( &savePort );
SetPort((aWindow = NewCWindow( &wRecord , &rScreen, "\p", 1, 1, -1L, 0, 0L)));
qt=ScrollInfo();
OpenCPort(&metaPort);
SetPortBits(&screenBits);
SetOrigin(0,0);
ClipRect(&rScreen);
SetOrigin(0,0);
HideCursor();
if(!qt)while(!SoundDone());
if(Button())qt=OptionKey();
if(!qt)
	{
	/*MindScape Presents*/
	SetPort(&metaPort);
	FillRect(&rScreen,black);
	if(theDepth>=4)DoPicture(-32565,&rScreen);
	else DoPicture(26194,&rScreen);
	PlayMars();
	if(!qt)qt=makestars(&rScreen,0);
	if(!qt)
		{/*The Colony by David A. Smith*/
		SetPort(&metaPort);
		FillRect(&rScreen,black);
		DoPicture(-32564,&rScreen);
		qt=makestars(&rScreen,0);
		}
	if(!qt)
		{
		SetPort(&metaPort);
		FillRect(&rScreen,black);
		qt=makestars(&rScreen,0);
		}
	if(!qt)qt=TimeSquare("\p...BLACK HOLE COLLISION...");
	if(!qt)
		{
		SetPort(&metaPort);
		FillRect(&rScreen,black);
		qt=Makeblackhole();
		}
	if(!qt)qt=TimeSquare("\p...FUEL HAS BEEN DEPLETED...");
	SetPort(&metaPort);
	if(!qt)qt=TimeSquare("\p...PREPARE FOR CRASH LANDING...");
	SetPort(&metaPort);
	if(!qt)
		{
		FillRect(&rScreen,black);
		qt=makeplanet();
		EndCSound();
		}
	}
SetPort(&metaPort);
FillRect(&rScreen,black);
if(!qt)while(!SoundDone());
if(!soundon)
	{
	int i;
	for(i=0;i<16;i++)InvertRect(&rScreen);
	}
else
	{
	DoExplodeSound();
	while(!SoundDone())InvertRect(&rScreen);
	StopSound();
	}
FillRect(&rScreen,black);
CloseWindow(aWindow);
SetPort(savePort);
ShowCursor();
FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);
}
/*----------------------------------------------------------------------*/
char *story[]={
			"\p",
			"\pMankind has left the",
			"\pcradle of earth and",
			"\pis beginning to eye",
			"\pthe galaxy. He has",
			"\pbegun to colonize",
			"\pdistant planets but has",
			"\pyet to meet any alien",
			"\plife forms.",
			0,
			"\pUntil now...",
			0,
			"\pClick to begin",
			"\pthe Adventure..."};
#define STORYLENGTH 14

int ScrollInfo()
{
PixMapHandle scrollBits;
CGrafPort scrollPort;
Rect scrollRect,stayRect;
int i,height,centerx,inc;
int swidth,ht;
CGrafPort metaPort;
int qt = FALSE;
RGBColor tColor,bColor;

OpenCPort(&metaPort);
SetPortBits(&screenBits);
SetPort(&metaPort);
SetOrigin(0,0);
ClipRect(&rScreen);
FillRect(&rScreen,black);
stayRect.top=rScreen.top;
stayRect.bottom=rScreen.bottom;
stayRect.left=0;
stayRect.right=rScreen.right/2;
centerx=(stayRect.right+stayRect.left)/2;

scrollBits=ANewPixMap(&stayRect);
OpenCPort(&scrollPort);
SetPortPix(scrollBits);
SetPort(&scrollPort);
SetOrigin(0,0);
ClipRect(&stayRect);
TextSize(12);
TextFont(190);
TextMode(srcCopy);
FillRect(&stayRect,black);

bColor.red=0; bColor.green=0; bColor.blue=0;
tColor.red=0; tColor.green=0; tColor.blue=0xFFFF;
height=(rScreen.bottom-rScreen.top);
ht=(height-(19*STORYLENGTH))/2;
RGBBackColor(&bColor);
for(i=0;i<STORYLENGTH;i++)
	if(story[i])
		{
		RGBForeColor(&tColor);
		if(theDepth>=8)tColor.blue-=4096;
		swidth=StringWidth(story[i])/2;
		MoveTo( centerx-swidth, 19*i+ht);
		DrawString(story[i]);
		}
HideCursor();
scrollRect.top=stayRect.bottom;
scrollRect.bottom=stayRect.bottom*2;
scrollRect.left=rScreen.right/4;
scrollRect.right=scrollRect.left+stayRect.right;
inc=4;
SetPort(&metaPort);
ClipRect(&rScreen);
if(Button())qt=OptionKey();
if(!qt)DoBeammeSound();
if(!qt)for(i=0;i<height && !qt;i+=inc)
	{
	if(Button())if(qt=OptionKey()){ StopSound(); break;}
	CopyBits(*scrollBits,
		&screenBits,
		&stayRect,
		&scrollRect,srcCopy,NIL);
	scrollRect.top-=inc;
	scrollRect.bottom-=inc;
	}
while(!Button());
while(Button()&&!qt);
if(!qt)for(i=0;i<height && !qt;i+=inc)
	{
	if(Button())if(qt=OptionKey()){ StopSound(); break;}
	CopyBits(*scrollBits,
		*metaPort.portPixMap,
		&stayRect,
		&scrollRect,srcCopy,NIL);
	scrollRect.top-=inc;
	scrollRect.bottom-=inc;
	}
KillPixMap(scrollBits);
ShowCursor();
return(qt);
}
/*----------------------------------------------------------------------*/
int TimeSquare(str)
char *str;
{
PixMapHandle scrollBits;
CGrafPort scrollPort;
Rect scrollRect,stayRect,invrt;
int i,width,inc,centery;
int swidth;
CGrafPort metaPort;
int qt = FALSE;
RGBColor bcolor,fcolor;

OpenCPort(&metaPort);
SetPortBits(&screenBits);
SetPort(&metaPort);
PenMode(patCopy);
SetOrigin(0,0);
ClipRect(&rScreen);
FillRect(&rScreen,black);

centery=(rScreen.bottom-rScreen.top)/2-10;
invrt.top=centery+1;
invrt.bottom=centery+16;
invrt.left=rScreen.left;
invrt.right=rScreen.right;
fcolor.red=0; fcolor.green=0; fcolor.blue=0xFFFF;
for(i=0;i<16;i++)
	{
	RGBForeColor(&fcolor);
	MoveTo(invrt.left,invrt.top-2-i*2);
	LineTo(invrt.right,invrt.top-2-i*2);
	MoveTo(invrt.left,invrt.top-2-(i*2+1));
	LineTo(invrt.right,invrt.top-2-(i*2+1));

	MoveTo(invrt.left,invrt.bottom+i*2);
	LineTo(invrt.right,invrt.bottom+i*2);
	MoveTo(invrt.left,invrt.bottom+i*2+1);
	LineTo(invrt.right,invrt.bottom+i*2+1);
	fcolor.blue-=4096;
	}
TextSize(12);
TextFont(190);
swidth=StringWidth(str);

stayRect.top=0;
stayRect.bottom=15;
stayRect.left=0;
stayRect.right=swidth+32;

scrollBits=ANewPixMap(&stayRect);
OpenCPort(&scrollPort);
SetPortPix(scrollBits);
SetPort(&scrollPort);
SetOrigin(0,0);
ClipRect(&stayRect);
FillRect(&stayRect,black);
TextSize(12);
TextFont(190);
TextMode(srcCopy);

bcolor.green=0; bcolor.blue=0; bcolor.red=0;
fcolor.red=0xFFFF; fcolor.blue=0; fcolor.green=0;

RGBBackColor(&bcolor);
RGBForeColor(&fcolor);
MoveTo( 8, 14);
DrawString(str);
HideCursor();
scrollRect.top=stayRect.top+centery;
scrollRect.bottom=stayRect.bottom+centery;
scrollRect.left=rScreen.right;
scrollRect.right=rScreen.right+swidth+32;
width=(rScreen.right-rScreen.left)/2;
width+=(stayRect.right-stayRect.left)/2;
inc=1;
SetPort(&metaPort);
ClipRect(&rScreen);
if(Button())qt=OptionKey();
if(!qt)for(i=0;i<width && !qt;i+=inc)
	{
	if(Button())if(qt=OptionKey()){ StopSound(); break;}
	CopyBits(*scrollBits,
		*metaPort.portPixMap,
		&stayRect,
		&scrollRect,srcCopy,NIL);
		scrollRect.left-=inc;
		scrollRect.right-=inc;
	}
EndCSound();
for(i=0;i<6;i++)
	{
	if(Button())if(qt=OptionKey()) break;
	while(!SoundDone());
	StopSound();
	if(LostSound||gameover)DoChimeSound();
	else PlayKlaxon();
	InvertRect(&invrt);
	}
while(!SoundDone());
StopSound();
PlayMars();
if(!qt)for(i=0;i<width && !qt;i+=inc)
	{
	if(Button())if(qt=OptionKey()){ StopSound(); break;}
	CopyBits(*scrollBits,
		*metaPort.portPixMap,
		&stayRect,
		&scrollRect,srcCopy,NIL);
		scrollRect.left-=inc;
		scrollRect.right-=inc;
	}
KillPixMap(scrollBits);
ShowCursor();
return(qt);
}

/*----------------------------------------------------------------------*/
#define PDELTA 16

makeplanet()
{
register int x,y,z,xx,yy,zz;
register long i;
int j,k,l,m,start=0,dstart=1;
int width,height,centerx,centery;
int words;
int sintheta,costheta;
int xsave[128],ysave[128],zsave[128],save;
long rt;
int xstars[400],ystars[400],starcnt=0,sindex;
Rect r;
int dec;
RGBColor sColor,pColor,bColor;

sColor.red=sColor.blue=sColor.green=MAXCOLOR;
pColor.red=0;
pColor.blue=MAXCOLOR;
pColor.green=MAXCOLOR;
bColor.red=bColor.blue=bColor.green=0;

SetPort(thePort);
PenMode(patXor);
sintheta=sint[210];
costheta=cost[210];
width=rScreen.right;
height=rScreen.bottom;
centerx=width/2;
centery=height/2;
starcnt=0;
dec=16;
/*draw the stars*/
for(i=800;i>32;i-=dec)
	{
	for(m=0;m<4;m++)
		{
		sindex=0x0FF&Random();
		xx=xstars[starcnt]=centerx+(((long)rtable[i]*sint[sindex])>>7);
		yy=ystars[starcnt]=centery+(((long)rtable[i]*cost[sindex])>>7);
		starcnt++;
		MoveTo(xx,yy); LineTo(xx,yy);
		}
	}
save=0;
rt=rtable[800];
/*draw the planet*/
for(j=0;j<256;j+=PDELTA)
	{
	for(k=start;k<128;k+=PDELTA)
		{
		xx=(((rt*sint[j])>>7)*cost[k]>>7);
		zz=(((rt*sint[j])>>7)*sint[k]>>7);
		y=(((rt*cost[j])>>7)*costheta-(long)zz*sintheta)>>7;
		zz=((long)cost[j]*sintheta+(long)zz*costheta)>>7;
		if(zsave[save]=(zz>=0))
			{
			xsave[save]=xx+=centerx;
			ysave[save]=yy=centery+y;
			MoveTo(xx,yy); LineTo(xx,yy);
			}
		save++;
		}
	}
/*rotate the planet in place*/
for(i=0;i<25;i++)
	{
	if(Button())if(OptionKey())return(TRUE);
	save=0;
	for(j=0;j<256;j+=PDELTA)
		for(k=start,l=dstart;k<128;k+=PDELTA,l+=PDELTA)
			{
			if(zsave[save])
				{
				xx=xsave[save];
				yy=ysave[save];
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			rt=rtable[800];
			/*z starts out == 0 or in the plane*/
			xx=(((rt*sint[j])>>7)*cost[l]>>7);
			zz=(((rt*sint[j])>>7)*sint[l]>>7);
			z= ((long)cost[j]*sintheta+(long)zz*costheta)>>7;
			if(zsave[save]=(z>=0))
				{
				ysave[save]=yy=
					centery+
					((((rt*cost[j])>>7)*costheta-(long)zz*sintheta)>>7);
				xsave[save]=xx+=centerx;
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			save++;
			}
	start++;
	if(start==PDELTA)start=0;
	dstart++;
	if(dstart==PDELTA)dstart=0;
	}
starcnt=0;
/*move the planet towards you*/
for(i=800;i>32;i-=dec)
	{
	if(Button())if(OptionKey())return(TRUE);
	for(m=0;m<4;m++)
		{
		xx=xstars[starcnt];
		yy=ystars[starcnt];
		starcnt++;
		MoveTo(xx,yy); LineTo(xx,yy);
		}
	save=0;
	for(j=0;j<256;j+=PDELTA)
		for(k=start,l=dstart;k<128;k+=PDELTA,l+=PDELTA)
			{
			if(zsave[save])
				{
				xx=xsave[save];
				yy=ysave[save];
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			rt=rtable[i];
			/*z starts out == 0 or in the plane*/
			xx=(((rt*sint[j])>>7)*cost[l]>>7);
			zz=(((rt*sint[j])>>7)*sint[l]>>7);
			z= ((long)cost[j]*sintheta+(long)zz*costheta)>>7;
			if(zsave[save]=(z>=0))
				{
				ysave[save]=yy=
					centery+
					((((rt*cost[j])>>7)*costheta-(long)zz*sintheta)>>7);
				xsave[save]=xx+=centerx;
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			save++;
			}
	start++;
	if(start==PDELTA)start=0;
	dstart++;
	if(dstart==PDELTA)dstart=0;
	}
return(FALSE);
}
/*----------------------------------------------------------------------*/
leaveplanet()
{
register int x,y,z,xx,yy,zz;
register long i;
int j,k,l,m,start=0,dstart=1;
int width,height,centerx,centery;
int words;
int sintheta,costheta;
int xsave[128],ysave[128],zsave[128],save;
long rt;
int xstars[400],ystars[400],starcnt=0,sindex;
Rect r;
int dec;

PenMode(patXor);
sintheta=sint[210];
costheta=cost[210];
width=rScreen.right;
height=rScreen.bottom;
centerx=width/2;
centery=height/2;

starcnt=0;
dec=16;
for(i=800;i>32;i-=dec)
	{
	for(m=0;m<4;m++)
		{
		sindex=0x0FF&Random();
		xx=xstars[starcnt]=centerx+
			(((long)rtable[i]*sint[sindex])>>7);
		yy=ystars[starcnt]=centery+
			(((long)rtable[i]*cost[sindex])>>7);
		starcnt++;
		}
	}
save=0;
rt=rtable[32];
for(j=0;j<256;j+=PDELTA)
	{
	for(k=start;k<128;k+=PDELTA)
		{
		xx=(((rt*sint[j])>>7)*cost[k]>>7);
		zz=(((rt*sint[j])>>7)*sint[k]>>7);
		y=(((rt*cost[j])>>7)*costheta-(long)zz*sintheta)>>7;
		zz=((long)cost[j]*sintheta+(long)zz*costheta)>>7;
		if(zsave[save]=(zz>=0))
			{
			xsave[save]=xx+=centerx;
			ysave[save]=yy=centery+y;
			MoveTo(xx,yy); LineTo(xx,yy);
			}
		save++;
		}
	}
for(i=0;i<25;i++)
	{
	if(Button())if(OptionKey())return(TRUE);
	save=0;
	for(j=0;j<256;j+=PDELTA)
		for(k=start,l=dstart;k<128;k+=PDELTA,l+=PDELTA)
			{
			if(zsave[save])
				{
				xx=xsave[save];
				yy=ysave[save];
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			rt=rtable[32];
			/*z starts out == 0 or in the plane*/
			xx=(((rt*sint[j])>>7)*cost[l]>>7);
			zz=(((rt*sint[j])>>7)*sint[l]>>7);
			z= ((long)cost[j]*sintheta+(long)zz*costheta)>>7;
			if(zsave[save]=(z>=0))
				{
				ysave[save]=yy=
					centery+
					((((rt*cost[j])>>7)*costheta-(long)zz*sintheta)>>7);
				xsave[save]=xx+=centerx;
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			save++;
			}
	start++;
	if(start==PDELTA)start=0;
	dstart++;
	if(dstart==PDELTA)dstart=0;
	}
for(i=32;i<=800;i+=dec)
	{
	if(Button())if(OptionKey())return(TRUE);
	for(m=0;m<4;m++)
		{
		xx=xstars[starcnt];
		yy=ystars[starcnt];
		starcnt--;
		MoveTo(xx,yy); LineTo(xx,yy);
		}
	save=0;
	for(j=0;j<256;j+=PDELTA)
		for(k=start,l=dstart;k<128;k+=PDELTA,l+=PDELTA)
			{
			if(zsave[save])
				{
				xx=xsave[save];
				yy=ysave[save];
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			rt=rtable[i];
			/*z starts out == 0 or in the plane*/
			xx=(((rt*sint[j])>>7)*cost[l]>>7);
			zz=(((rt*sint[j])>>7)*sint[l]>>7);
			z= ((long)cost[j]*sintheta+(long)zz*costheta)>>7;
			if(zsave[save]=(z>=0))
				{
				ysave[save]=yy=
					centery+
					((((rt*cost[j])>>7)*costheta-(long)zz*sintheta)>>7);
				xsave[save]=xx+=centerx;
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			save++;
			}
	start++;
	if(start==PDELTA)start=0;
	dstart++;
	if(dstart==PDELTA)dstart=0;
	}
while(!SoundDone());
StopSound();
KillTSound();
return(FALSE);
}
/*----------------------------------------------------------------------*/
#define QDELTA 16
explodeplanet()
{
register int x,y,z,xx,yy,zz;
register long i;
int j,k,l,m,start=0,dstart=1;
int width,height,centerx,centery;
int words;
int sintheta,costheta;
int xsave[128],ysave[128],zsave[128],save;
long rt;
int xstars[400],ystars[400],starcnt=0,sindex;
Rect r;
int dec;
RGBColor PColor;

PColor.red=0;
PColor.blue=0xFFFF;
PColor.green=0;

PenMode(patXor);
sintheta=sint[210];
costheta=cost[210];
width=rScreen.right;
height=rScreen.bottom;
centerx=width/2;
centery=height/2;

starcnt=0;
dec=16;
for(i=800;i>32;i-=dec)
	{
	for(m=0;m<4;m++)
		{
		sindex=0x0FF&Random();
		xx=xstars[starcnt]=centerx+
			(((long)rtable[i]*sint[sindex])>>7);
		yy=ystars[starcnt]=centery+
			(((long)rtable[i]*cost[sindex])>>7);
		MoveTo(xx,yy); LineTo(xx,yy);
		starcnt++;
		}
	}
save=0;
rt=rtable[800];
for(j=0;j<256;j+=QDELTA)
	{
	for(k=start;k<128;k+=QDELTA)
		{
		xx=(((rt*sint[j])>>7)*cost[k]>>7);
		zz=(((rt*sint[j])>>7)*sint[k]>>7);
		y=(((rt*cost[j])>>7)*costheta-(long)zz*sintheta)>>7;
		zz=((long)cost[j]*sintheta+(long)zz*costheta)>>7;
		if(zsave[save]=(zz>=0))
			{
			xsave[save]=xx+=centerx;
			ysave[save]=yy=centery+y;
			MoveTo(xx,yy); LineTo(xx,yy);
			}
		save++;
		}
	}
for(i=0;i<30;i++)
	{
	if(i>21)
		{
		InvertRect(&rScreen);	
		if(SoundDone()){StopSound();DoExplodeSound();}
		}
	if(Button())if(OptionKey())return(TRUE);
	save=0;
	for(j=0;j<256;j+=QDELTA)
		for(k=start,l=dstart;k<128;k+=QDELTA,l+=QDELTA)
			{
			if(zsave[save])
				{
				xx=xsave[save];
				yy=ysave[save];
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			rt=rtable[800];
			/*z starts out == 0 or in the plane*/
			xx=(((rt*sint[j])>>7)*cost[l]>>7);
			zz=(((rt*sint[j])>>7)*sint[l]>>7);
			z= ((long)cost[j]*sintheta+(long)zz*costheta)>>7;
			if(zsave[save]=(z>=0))
				{
				ysave[save]=yy=
					centery+
					((((rt*cost[j])>>7)*costheta-(long)zz*sintheta)>>7);
				xsave[save]=xx+=centerx;
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			save++;
			}
	start++;
	if(start==QDELTA)start=0;
	dstart++;
	if(dstart==QDELTA)dstart=0;
	}
for(i=0;i<15;i++)
	{
	if(SoundDone()){StopSound();DoExplodeSound();}
	if(Button())if(OptionKey())return(TRUE);
	save=0;
	for(j=0;j<256;j+=QDELTA)
		for(k=start,l=dstart;k<128;k+=QDELTA,l+=QDELTA)
			{
			rt=rtable[800];
			/*z starts out == 0 or in the plane*/
			xx=(((rt*sint[j])>>7)*cost[l]>>7);
			zz=(((rt*sint[j])>>7)*sint[l]>>7);
			z= ((long)cost[j]*sintheta+(long)zz*costheta)>>7;
			if(zsave[save]=(z>=0))
				{
				ysave[save]=yy=
					centery+
					((((rt*cost[j])>>7)*costheta-(long)zz*sintheta)>>7);
				xsave[save]=xx+=centerx;
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			save++;
			}
	start++;
	if(start==QDELTA)start=0;
	dstart++;
	if(dstart==QDELTA)dstart=0;
	}
starcnt=0;
StopSound();
DoEndSound();
PenMode(patCopy);
for(i=800;i>32;i-=dec)
	{
	PColor.red+=1024;
	PColor.blue-=1024;
	RGBForeColor(&PColor);

	save=0;
	for(j=0;j<256;j+=QDELTA)
		for(k=start,l=dstart;k<128;k+=QDELTA,l+=QDELTA)
			{
			rt=rtable[i];
			/*z starts out == 0 or in the plane*/
			xx=(((rt*sint[j])>>7)*cost[l]>>7);
			zz=(((rt*sint[j])>>7)*sint[l]>>7);
			z= ((long)cost[j]*sintheta+(long)zz*costheta)>>7;
			if(zsave[save]=(z>=0))
				{
				ysave[save]=yy=
					centery+
					((((rt*cost[j])>>7)*costheta-(long)zz*sintheta)>>7);
				xsave[save]=xx+=centerx;
				MoveTo(xx,yy); LineTo(xx,yy);
				}
			save++;
			}
	start++;
	if(start==QDELTA)start=0;
	dstart++;
	if(dstart==QDELTA)dstart=0;
	}
ForeColor(blackColor);
return(FALSE);
}
/*----------------------------------------------------------------------*/
Makeblackhole()
{
register int x,y,z,xx,yy,zz;
register long i;
int j,k,l,m,start=0,dstart=1;
int centerx,centery;
int xsave[128],ysave[128],zsave[128],save;
long rt;
int xstars[400],ystars[400],starcnt=0,sindex;
Rect r;
int dec;
int cCount=0;
RGBColor bcolor;
int rd,gd,bd;

SetPort(thePort);
PenMode(patCopy);

centerx=rScreen.right/2;
centery=rScreen.bottom/2;
starcnt=0;
dec=16;
for(k=0;k<17;k+=4)
	{
	bcolor.red=bcolor.green=bcolor.blue=0;
	bd=4096;
	rd=2048;
	gd=1024;
	if(theDepth>=8)
		{
		rd=2048;
		gd=1024;
		}
	else rd=gd=4096;
	for(i=1000;i>32;i-=dec)
		{
		bcolor.blue-=bd;
		bcolor.red-=rd;
		bcolor.green-=gd;
		RGBForeColor(&bcolor);
	/*	if(bd)		{if(bcolor.blue==0)	{gd=4096;bd=0;}}
		else if(gd)	{if(bcolor.green==0){rd=4096;gd=0;}}
		else if(rd)	{if(bcolor.red==0)	{bd=4096;rd=0;}}*/
		
		if(Button())if(OptionKey())return(TRUE);
		starcnt++;
		if(starcnt==8)starcnt=0;
		for(j=0;j<256;j+=8)
			{
			/*PMForeColor(cCount);
			cCount++;
			if(cCount==256)cCount=0;*/

			rt=rtable[i+k];
			/*z starts out == 0 or in the plane*/
			xx=centerx+((rt*sint[j+starcnt])>>7);
			yy=centery+((rt*cost[j+starcnt])>>7);
			MoveTo(xx,yy);
			rt=rtable[i+k+8];
			xx=centerx+((rt*sint[j+starcnt])>>7);
			yy=centery+((rt*cost[j+starcnt])>>7);
			LineTo(xx,yy);
			}
		}
	}
bcolor.red=bcolor.blue=bcolor.green=0x0000;
RGBForeColor(&bcolor);
return(FALSE);
}
/*	This is the standard rotation code.
 	It is reprinted here for reference.
tcos=cost[ang];
tsin=sint[ang];
*px = (x * tcos - y * tsin) >> 7;
*py = (x * tsin + y * tcos) >> 7;
*/
/*----------------------------------------------------------------------*/
DoPicture(pnum,r)
int pnum;
Rect *r;
{
PicHandle pic;
Rect locate;
Rect clip;
int xSize,ySize;

pic=GetPicture(pnum);
SizeRect(&xSize,&ySize,&(**pic).picFrame);
locate.top=(r->top+r->bottom-ySize)/2;
clip.top=locate.top+1;
locate.bottom=locate.top+ySize;
clip.bottom=locate.bottom-1;
locate.left=(r->left+r->right-xSize)/2;
clip.left=locate.left+1;
locate.right=locate.left+xSize;
clip.right=locate.right-1;
ClipRect(&clip);
HLock(pic);
DrawPicture(pic,&locate);
HUnlock(pic);
ReleaseResource(pic);
ClipRect(r);
}
/*----------------------------------------------------------------------*/
gameInit()
{
int i,j;

for(i=0;i<4;i++)
	{
	decode1[i]=0;
	decode2[i]=0;
	decode3[i]=0;
	}
unlocked=FALSE;
armor=SUIT;
weapons=SUIT;
armor2=armor*armor;
weapons2=weapons*weapons;
robotarray[Me.xindex][Me.yindex]=0;
Me.power[0]=POWER;
Me.power[1]=POWER;
Me.power[2]=POWER;
epower[0]=qlog((long)Me.power[0]);
epower[1]=qlog((long)Me.power[1]);
epower[2]=qlog((long)Me.power[2]);
DrawInfo();
SetPort(theWindow);
PenMode(patCopy);
SetOrigin(0,0);
game=COLONY;
FillRect(&Clip,black);
Me.ang=Me.look=32;
Me.xloc = 4400;
Me.yloc = 4400;
Me.xindex=Me.xloc >> 8;	/*divide by 256	*/
Me.yindex=Me.yloc >> 8;	/*divide by 256	*/
Me.type=MENUM;
robotarray[Me.xindex][Me.yindex]=MENUM;
speed=4;
speedshift=3;
tsin=sint[Me.look];
tcos=cost[Me.look];
leveldata[1].visit=0;
leveldata[1].size=0;
leveldata[1].count=0;
fl=0;
patchnum=0;
load_mapnum(1,TRUE);	/*	load first map		*/
for(i=0;i<8;i++)
	{
	leveldata[i].visit=0;
	leveldata[i].size=0;
	leveldata[i].count=0;
	}
leveldata[2].count=1;
fadein=4;
corestate[0]=0; corestate[1]=0;
coreheight[0]=256; coreheight[1]=256;
corepower[0]=0; corepower[1]=2; corepower[2]=0;
orbit=FALSE;
for(i=0;i<32;i++)for(j=0;j<32;j++)dirXY[i][j]=0;
BattleSet();
DrawCompass();
}
/*---------------------------------------------------------------------- 
 *	tabsgen()
 *
 *	xai[],yai[] and cost[] table generator. Uses the sint[] table.
 *	angle between 0 and 255, sin and cos tables, x and y angle increments,
 *	Wall map, x and y location, corridor Height. Grid size is 256.		
 *---------------------------------------------------------------------- 
 */
tabsgen()
{
int i;

for(i=0 ; i<256 ; i++)
  	{
	if(i < 192) cost[i] = sint[i + 64];
	else		cost[i] = sint[i - 192];
	xai[i] = cost[i] >> 4;
	yai[i] = sint[i] >> 4;
	}
SetRect(&Clip, 0, 0, Width, Height);
ClipRect(&Clip);
}
/*----------------------------------------------------------------------*/
GameOver(kill)
int kill;
{
WindowPtr aWindow;
WindowRecord wRecord;
int qt = FALSE;
CGrafPort metaPort;
int i,saved=0;

SetPort((aWindow = NewCWindow( &wRecord , &rScreen, "\p", 1, 1, -1L, 0, 0L)));
OpenCPort(&metaPort);
SetPortBits(&screenBits);
SetOrigin(0,0);
HideCursor();
ClipRect(&rScreen);
FillRect(&rScreen,black);
gameover=TRUE;
SoundEnd();
for(i=0;i<patchnum;i++)	
	if(patch[i].type==CRYO && patch[i].to.level==1)saved++;

if(kill)
	{
	DoPShotSound();	
	explodeplanet();
	FillRect(&rScreen,black);
	}
else DoSwishSound();
makestars(&rScreen,0);
FillRect(&rScreen,black);
if(kill)
	{
	if(saved==6)DoText(&rScreen,256,2);
	else if(saved>0)DoText(&rScreen,257,2);
	else DoText(&rScreen,258,2);
	}
else{
	if(saved==6)DoText(&rScreen,259,2);
	else if(saved>0)DoText(&rScreen,260,2);
	else DoText(&rScreen,261,2);
	}
SetPort(&metaPort);
PlayMars();
FillRect(&rScreen,black);
makestars(&rScreen,0);
TimeSquare("\p...THE END...");
SetPort(&metaPort);
FillRect(&rScreen,black);
makestars(&rScreen,0);
EndCSound();
if(!soundon)
	{
	int i;
	for(i=0;i<4;i++)InvertRect(&rScreen);
	}
else
	{
	DoExplodeSound();
	while(!SoundDone())InvertRect(&rScreen);
	}
StopSound();
FillRect(&rScreen,black);
CloseWindow(theWindow);
CloseWindow(infoWindow);
CloseWindow(moveWindow);
ShowCursor();
FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);
ExitToShell();
}
/*----------------------------------------------------------------------*/
TakeOff()
{
WindowPtr aWindow;
WindowRecord wRecord;
int qt = FALSE;
CGrafPort metaPort;
int i,saved=0;

SetPort((aWindow = NewCWindow( &wRecord , &rScreen, "\p", 1, 1, -1L, 0, 0L)));
OpenCPort(&metaPort);
SetPortBits(&screenBits);
SetOrigin(0,0);
ClipRect(&rScreen);
SetOrigin(0,0);
HideCursor();
FillRect(&rScreen,black);
DoSwishSound();
leaveplanet();

CloseWindow(aWindow);
ShowCursor();
FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);
DrawMenuBar();
}
/*----------------------------------------------------------------------*/
FullOfStars()
{
WindowPtr aWindow;
WindowRecord wRecord;
int qt = FALSE;
CGrafPort metaPort;
int i,saved=0;

SetPort((aWindow = NewCWindow( &wRecord , &rScreen, "\p", 1, 1, -1L, 0, 0L)));
OpenCPort(&metaPort);
SetPortBits(&screenBits);
SetOrigin(0,0);
ClipRect(&rScreen);
SetOrigin(0,0);
HideCursor();
ForeColor(blackColor);
BackColor(whiteColor);
FillRect(&rScreen,black);
DoDaveSound();
qt=makestars(&rScreen,0);
CloseWindow(aWindow);
ShowCursor();
FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);
DrawMenuBar();
KillTSound();
}
/*----------------------------------------------------------------------*/
Dimension8()
{
WindowPtr aWindow;
WindowRecord wRecord;
int qt = FALSE;
CGrafPort metaPort;
int i,saved=0;
Rect r;

DoText(&screenBits.bounds,78,0);
SetPort((aWindow = NewCWindow( &wRecord , &rScreen, "\p", 1, 1, -1L, 0, 0L)));
OpenCPort(&metaPort);
SetPortBits(&screenBits);
SetOrigin(0,0);
ClipRect(&rScreen);
SetOrigin(0,0);
HideCursor();
ForeColor(blueColor);
FillRect(&rScreen,black);
r.top=rScreen.top;
r.bottom=rScreen.bottom;
r.left=rScreen.left;
r.right=rScreen.right;
while(r.left<r.right)
	{
	r.left+=16;
	r.right-=16;
	r.top+=16;
	r.bottom-=16;
	InvertRect(&r);
	r.left+=4;
	r.right-=4;
	r.top+=4;
	r.bottom-=4;
	InvertRect(&r);
	}
r.top=rScreen.top;
r.bottom=rScreen.bottom;
r.left=rScreen.left;
r.right=rScreen.right;
while(r.left<r.right)
	{
	r.left+=16;
	r.right-=16;
	r.top+=16;
	r.bottom-=16;
	InvertOval(&r);
	r.left+=4;
	r.right-=4;
	r.top+=4;
	r.bottom-=4;
	InvertOval(&r);
	}
r.top=rScreen.top;
r.bottom=rScreen.bottom;
r.left=rScreen.left;
r.right=rScreen.right;
while(r.left<r.right)
	{
	r.left+=16;
	r.right-=16;
	r.top+=16;
	r.bottom-=16;
	InvertRect(&r);
	r.left+=4;
	r.right-=4;
	r.top+=4;
	r.bottom-=4;
	InvertRect(&r);
	}
r.top=rScreen.top;
r.bottom=rScreen.bottom;
r.left=rScreen.left;
r.right=rScreen.right;
while(r.left<r.right)
	{
	r.left+=16;
	r.right-=16;
	r.top+=16;
	r.bottom-=16;
	InvertOval(&r);
	r.left+=4;
	r.right-=4;
	r.top+=4;
	r.bottom-=4;
	InvertOval(&r);
	}
FillRect(&rScreen,black);
CloseWindow(aWindow);
ShowCursor();
FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);
DrawMenuBar();
}
/*----------------------------------------------------------------------*/
int OptionKey()
{
WaitNextEvent(everyEvent, &key,0,0L);
if(key.modifiers&(cmdKey|shiftKey|optionKey|controlKey))return(TRUE);
return(FALSE);
}
