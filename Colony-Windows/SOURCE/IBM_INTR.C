/*	#define IBM_intro */
/*	#define IBM_ScrollInfo */
/*	#define IBM_TimeSquare */
/*	#define IBM_makestars */
/*	#define IBM_makeplanet */
/*	#define IBM_leaveplanet */
/*	#define IBM_explodeplanet */
/*	#define IBM_Makeblackhole */
/*  #define IBM_DoPicture */
/*  #define IBM_gameInit  */
/*  #define IBM_tabsgen  */
/*  #define IBM_GameOver */
/*  #define IBM_TakeOff*/
/*	#define IBM_FullOfStars*/
/*	#define IBM_KeyPress */
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
#include "gamedefs.h"
#include "sintable.h"

BitMap far *NewBitMap();

#define CX 256
#define CY 170
#define MXCX 512
#define MXCY 342
int xtest[]={  0, 50,100,150,200,250,300,100};
int ytest[]={200, 80,170, 60,125, 90,150,125};
int ltest=8;
/*----------------------------------------------------------------------*/
intro(qt)
int qt;
{
int i,j,k;
int mx,my,mbt;

if(qt==FALSE)
	{
	/*Mindscape Presents*/
	KillSound();
	PlayStars1();	
	EraseRect(&sR);
	DoPicture("logo2");
	SetPort(scrport);
 	if(!qt)qt=makestars(&sR,0);
	EraseRect(&sR);
	if(!qt)
		{/*The Colony by David A. Smith*/
		KillSound();
		PlayStars2();
		DoPicture("logo1");
		SetPort(scrport);
		qt=makestars(&sR,0);
		SetPort(metaPnt);
		MovePortTo(0,0);
		PenMode(zREPz);
		SetPort(scrport);
		EraseRect(&sR);
		}
	if(!qt)
		{
		KillSound();
		PlayStars3();
		qt=makestars(&sR,0);
		EraseRect(&sR);
		}
	if(!qt)
		{
		KillSound();
		PlayStars4();
		qt=makestars(&sR,0);
		EraseRect(&sR);
		}
	if(!qt)qt=TimeSquare("...BLACK HOLE COLLISION...");
	if(!qt)
		{
		qt=Makeblackhole();
		EraseRect(&sR);
		}
	if(!qt)qt=TimeSquare("...FUEL HAS BEEN DEPLETED...");
	if(!qt)qt=TimeSquare("...PREPARE FOR CRASH LANDING...");

	if(!qt)
		{
		KillSound();
		PlayStars4();
		qt=makeplanet();
		EraseRect(&sR);
		}
	}
KillSound();
DoExplodeSound();
SetPort(scrport);
PenMode(zREPz);
ClipRect(&sR);
PenColor(realcolor[vBLACK]);
BackColor(realcolor[vINTWHITE]);
while(!SoundDone())
	{
	EraseRect(&sR);
	PaintRect(&sR);
	}
FillRect(&sR,black);
ShowCursor();
}
/*----------------------------------------------------------------------*/
int TimeSquare(str)
char *str;
{
#if !defined(IBM_TimeSquare)
int mx,my,mbt;
BitMap far *scrollBits;
GrafPort* scrollPt;
Rect scrollRect,stayRect,invrt;
int i,j,width,inc,centery,centerx;
int swidth;
int qt = FALSE;
double fx,fy=.01;
SetOrigin(0,0);
ClipRect(&sR);
EraseRect(&sR);
centery=(sR.bottom-sR.top)/2-10;

MoveTo(sR.left,centery-1);
LineTo(sR.right,centery-1);
MoveTo(sR.left,centery-3);
LineTo(sR.right,centery-3);
MoveTo(sR.left,centery+17);
LineTo(sR.right,centery+17);
MoveTo(sR.left,centery+19);
LineTo(sR.right,centery+19);
PenPattern(GRAY);
MoveTo(sR.left,centery-2);
LineTo(sR.right,centery-2);
MoveTo(sR.left,centery+18);
LineTo(sR.right,centery+18);
PenPattern(BLACK);
invrt.top=centery+1;
invrt.bottom=centery+15;
invrt.left=sR.left;
invrt.right=sR.right;

swidth=StringWidth(str);
stayRect.top=0;
stayRect.bottom=15;
stayRect.left=0;
stayRect.right=swidth+32;

if(  NIL==(scrollPt=(GrafPort *)malloc( sizeof(GrafPort) ))  )
    return -1;
if((scrollBits=NewBitMap(&stayRect))==NULL)return(-1);
InitPort(scrollPt);
SetPort(scrollPt);
/*PortBitmap(		scrport->portBMap);*/
PortBitmap(scrollBits);
SetOrigin(0,0);
PenMode(zREPz);

centerx=(stayRect.left+stayRect.right)/2;
TextAlign(1,2);
TextMode(zREPz);
PenColor(vWHITE);
BackColor(vBLACK);
ClipRect(&stayRect);
EraseRect(&stayRect);
MoveTo(centerx ,8 );
DrawString(str);
SetPort(scrport);
scrollRect.top=stayRect.top+centery;
scrollRect.bottom=stayRect.bottom+centery;
scrollRect.left=sR.right;
scrollRect.right=sR.right+swidth+32;
width=(sR.right-sR.left)/2;
width+=(stayRect.right-stayRect.left)/2;
inc=16;
qt=KeyPress(1);
if(!qt)for(i=0;i<width && !qt;i+=inc)
	{
	if(qt=KeyPress(1)){ KillSound(); break;}
	CopyBits(scrollPt->portBMap,
		scrport->portBMap,
		&stayRect,
		&scrollRect,
		&sR,0);
	scrollRect.left-=inc;
	scrollRect.right-=inc;
	}
for(i=0;i<4;i++)
	{
	if(qt=KeyPress(1)) break;
	if(!soundon)
		{
		InvertRect(&invrt); 
		for(j=0;j<2000;j++)fx=j/fy;
		}
	else
		{
		while(!SoundDone());
		InvertRect(&invrt);
		PlayKlaxon();
		}
	}
while(!SoundDone());
if(!qt)for(i=0;i<width && !qt;i+=inc)
	{
	if(qt=KeyPress(1)){ KillSound(); break;}
	CopyBits(scrollPt->portBMap,
		scrport->portBMap,
		&stayRect,
		&scrollRect,
		&sR,0);
		scrollRect.left-=inc;
		scrollRect.right-=inc;
	}
KillBitMap(scrollBits);
free(scrollPt);

ClipRect(&sR);
EraseRect(&sR);
return(qt);

#endif
}
/*----------------------------------------------------------------------*/
Pause()
{
extern int showDashBoard;
extern int drewDashBoard;

while(KeyEvent(FALSE,&key));
HideCursor();
ClrScrn();
makestars(&sR,TRUE);
PenMode(zREPz);
EraseRect(&sR);
ShowCursor();
if(showDashBoard)drewDashBoard=0;
}
/*----------------------------------------------------------------------*/
#define MAXSTAR	 0x200
#define shift 7
makestars(pr,btn)
Rect *pr;
int btn;
{
#if !defined(IBM_makestars)
int nstars,sstars;
register int xx,yy,r;
register long i,k;
long s,c;
register int xang[200],yang[200];
int dist[200],visible[200];
register long d;
int *screen,*word;
int centerx,centery;
int words;
int deltapd;
int scount=0;
int cscount;
int mx,my,mbt;

PenMode(zXORz);
nstars=66;
sstars=100;
deltapd=0x004;

centerx=(pr->left+pr->right)/2;
centery=(pr->top+pr->bottom)/2;
for(i=0;i<sstars;i++)
	{
	xang[i]=Random()>>8;
	yang[i]=Random()>>8;
	dist[i]=0x01FF&Random();
	}
for(i=0;i<sstars;i++)
	{
	d=dist[i];
	s=xang[i];
	c=yang[i];
/*draw new one*/
	r=rtable[d];
	xx=centerx+((s*r)>>shift);
	yy=centery+((c*r)>>shift);
	SetPixel(xx,yy);
	}
if(KeyPress(1))return(TRUE);
/*cscount=NumCSound();*/
for(k=0;(k<150||btn);k++)
	{
	if(btn){if(KeyPress(0)){btn=FALSE;k=200;}}
	else if(KeyPress(1))
		{
		ClrScrn();
		return(TRUE);
		}
	for(i=0;i<nstars;i++)
		{
		d=dist[i];
		s=xang[i];
		c=yang[i];
		/*erase old one*/
		r=rtable[d];/*draw*/
		xx=centerx+((s*r)>>shift);
		yy=centery+((c*r)>>shift);
		SetPixel(xx,yy);
		dist[i]-=deltapd;
		if(dist[i]<=0x040)dist[i]=MAXSTAR;
		/*draw new one*/
		d=dist[i];
		r=rtable[d];
		xx=centerx+((s*r)>>shift);
		yy=centery+((c*r)>>shift);
		SetPixel(xx,yy);
		}
	}
scount=0;
for(k=0;(k<nstars);k++)
	{
	if(KeyPress(1)){
		ClrScrn();
		return(TRUE);
		}
	for(i=0;i<nstars;i++)
		{
		d=dist[i];
		s=xang[i];
		c=yang[i];
		dist[i]-=deltapd;
		/*draw new one*/
		if(dist[i]<=0x040)dist[i]=MAXSTAR;
		r=rtable[d];
		xx=centerx+((s*r)>>shift);
		yy=centery+((c*r)>>shift);
		SetPixel(xx,yy);
		}
	}
ClrScrn();
return(FALSE);
#endif
}
/*----------------------------------------------------------------------*/
ClrScrn()
{
SetPort(scrport);
ClipRect(&sR);
PenMode(zREPz);
PenColor(realcolor[vINTWHITE]);
BackColor(realcolor[vBLACK]);
EraseRect(&sR);
}
/*----------------------------------------------------------------------*/
#define PDELTA 16
makeplanet()
{
#if !defined(IBM_makeplanet)
register int x,y,z,xx,yy,zz;
register long i;
int j,k,l,m,start=0,dstart=1;
int *screen,*word;
int width,height,centerx,centery;
int words;
int sintheta,costheta;
int xsave[128],ysave[128],zsave[128],save;
long rt;
int xstars[400],ystars[400],starcnt=0,sindex;
Rect r;
int dec;
int mx,my,mbt;

ClrScrn();
PenMode(zXORz);
sintheta=sint[210];
costheta=cost[210];
width=sR.right;
height=sR.bottom;
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
		SetPixel(xx,yy);
		starcnt++;
		}
	}
save=0;
rt=rtable[800];
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
			SetPixel(xx,yy);
			}
		save++;
		}
	}
for(i=0;i<25;i++)
	{
	if(KeyPress(1))return(TRUE);
	save=0;
	for(j=0;j<256;j+=PDELTA)
		for(k=start,l=dstart;k<128;k+=PDELTA,l+=PDELTA)
			{
			if(zsave[save])
				{
				xx=xsave[save];
				yy=ysave[save];
				SetPixel(xx,yy);
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
				SetPixel(xx,yy);
				}
			save++;
			}
	start++;
	if(start==PDELTA)start=0;
	dstart++;
	if(dstart==PDELTA)dstart=0;
	}
starcnt=0;
for(i=800;i>32;i-=dec)
	{
	if(KeyPress(1))return(TRUE);
	for(m=0;m<4;m++)
		{
		xx=xstars[starcnt];
		yy=ystars[starcnt];
		starcnt++;
		SetPixel(xx,yy);
		}
	save=0;
	for(j=0;j<256;j+=PDELTA)
		for(k=start,l=dstart;k<128;k+=PDELTA,l+=PDELTA)
			{
			if(zsave[save])
				{
				xx=xsave[save];
				yy=ysave[save];
				SetPixel(xx,yy);
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
				SetPixel(xx,yy);
				}
			save++;
			}
	start++;
	if(start==PDELTA)start=0;
	dstart++;
	if(dstart==PDELTA)dstart=0;
	}
return(FALSE);
#endif
}
/*----------------------------------------------------------------------*/
leaveplanet()
{
#if !defined(IBM_leaveplanet)
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
int mx,my,mbt;

sintheta=sint[210];
costheta=cost[210];
width=sR.right;
height=sR.bottom;
centerx=width/2;
centery=height/2;
starcnt=0;

dec=16;
PenMode(zXORz);
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
			SetPixel(xx,yy);
			}
		save++;
		}
	}
for(i=0;i<25;i++)
	{
	if(KeyPress(1))return(TRUE);
	save=0;
	for(j=0;j<256;j+=PDELTA)
		for(k=start,l=dstart;k<128;k+=PDELTA,l+=PDELTA)
			{
			if(zsave[save])
				{
				xx=xsave[save];
				yy=ysave[save];
				SetPixel(xx,yy);
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
				SetPixel(xx,yy);
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
	if(KeyPress(1))return(TRUE);
	for(m=0;m<4;m++)
		{
		xx=xstars[starcnt];
		yy=ystars[starcnt];
		starcnt--;
		SetPixel(xx,yy);
		}
	save=0;
	for(j=0;j<256;j+=PDELTA)
		for(k=start,l=dstart;k<128;k+=PDELTA,l+=PDELTA)
			{
			if(zsave[save])
				{
				xx=xsave[save];
				yy=ysave[save];
				SetPixel(xx,yy);
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
				SetPixel(xx,yy);
				}
			save++;
			}
	start++;
	if(start==PDELTA)start=0;
	dstart++;
	if(dstart==PDELTA)dstart=0;
	}
KillSound();
return(FALSE);
#endif
}
/*----------------------------------------------------------------------*/
#define QDELTA 16
explodeplanet()
{
#if !defined(IBM_explodeplanet)
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
int mx,my,mbt;

ClrScrn();
DoPShotSound();
sintheta=sint[210];
costheta=cost[210];
width=sR.right;
height=sR.bottom;
centerx=width/2;
centery=height/2;
starcnt=0;
PenMode(zXORz);
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
		SetPixel(xx,yy);
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
			SetPixel(xx,yy);
			}
		save++;
		}
	}
for(i=0;((!soundon)&&(i<100))||!SoundDone();i++)
	{
	if(KeyPress(1))return(TRUE);
	save=0;
	for(j=0;j<256;j+=QDELTA)
		for(k=start,l=dstart;k<128;k+=QDELTA,l+=QDELTA)
			{
			if(zsave[save])
				{
				xx=xsave[save];
				yy=ysave[save];
				SetPixel(xx,yy);
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
				SetPixel(xx,yy);
				}
			save++;
			}
	start++;
	if(start==QDELTA)start=0;
	dstart++;
	if(dstart==QDELTA)dstart=0;
	}
DoExplodeSound();
if(is_EGAtype){	InvertRect(&sR); InvertRect(&sR);}
else for(i=0;i<4;i++)InvertRect(&sR);
while(!SoundDone());
DoExplodeSound();
for(i=0;i<25;i++)
	{
	if(KeyPress(1))return(TRUE);
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
				SetPixel(xx,yy);
				}
			save++;
			}
	start++;
	if(start==QDELTA)start=0;
	dstart++;
	if(dstart==QDELTA)dstart=0;
	}
starcnt=0;
for(i=800;i>32;i-=dec)
	{
	if(KeyPress(1))return(TRUE);
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
				SetPixel(xx,yy);
				}
			save++;
			}
	start++;
	if(start==QDELTA)start=0;
	dstart++;
	if(dstart==QDELTA)dstart=0;
	}
return(FALSE);
#endif
}
/*----------------------------------------------------------------------*/
Makeblackhole()
{
#if !defined(IBM_Makeblackhole)
register int x,y,z,xx,yy,zz;
register long i;
int j,k,l,m,start=0,dstart=1;
int *screen,*word;
int width,height,centerx,centery;
int words;
int sintheta,costheta;
int xsave[128],ysave[128],zsave[128],save;
long rt;
int xstars[400],ystars[400],starcnt=0,sindex;
Rect r;
int dec;
int mx,my,mbt;

PenMode(zXORz);
sintheta=sint[210];
costheta=cost[210];
width=sR.right;
height=sR.bottom;
centerx=width/2;
centery=height/2;
starcnt=0;
dec=16;
for(k=0;k<32;k+=4)
for(i=1600;i>32;i-=dec)
	{
	if(KeyPress(1))return(TRUE);
	starcnt++;
	if(starcnt==8)starcnt=0;
	for(j=0;j<256;j+=8)
			{
			rt=rtable[i+k];
			/*z starts out == 0 or in the plane*/
			xx=centerx+((rt*sint[j+starcnt])>>7);
			yy=centery+((rt*cost[j+starcnt])>>7);
			SetPixel(xx,yy);
			}
	}
return(FALSE);
#endif
}
/*	This is the standard rotation code.
 	It is reprinted here for reference.
tcos=cost[ang];
tsin=sint[ang];
*px = (x * tcos - y * tsin) >> 7;
*py = (x * tsin + y * tcos) >> 7;
*/
/*----------------------------------------------------------------------*/
DoPicture(char *pname)
{
#if !defined(IBM_DoPicture)
OpenAFile(pname,FALSE);
DrawAll(FALSE);
SetPort(scrport);
PenColor(realcolor[vINTWHITE]);
BackColor(realcolor[vBLACK]);
SetPort(metaPnt);
MovePortTo(0,0);
PenMode(zREPz);
killanim(FALSE);
ShowNextFram();
#endif
}
/*----------------------------------------------------------------------*/
GameOver(kill)
int kill;
{
#if !defined(IBM_GameOver)
int qt = FALSE;
int i,saved=0;

SetPort(scrport);
HideCursor();
ClrScrn();
for(i=0;i<patchnum;i++)	
	if(patch[i].type==CRYO && patch[i].to.level==1)saved++;
if(kill)
	{
	explodeplanet();
	PenMode(zREPz);
	}
ClrScrn();
PlayStars4();
makestars(&sR,0);
KillSound();
if(kill)
	{
	if(saved==6)DoText(&sR,256,2);
	else if(saved>0)DoText(&sR,257,2);
	else DoText(&sR,258,2);
	}
else{
	if(saved==6)DoText(&sR,259,2);
	else if(saved>0)DoText(&sR,260,2);
	else DoText(&sR,261,2);
	}
ClrScrn();
PlayStars4();
if(!makestars(&sR,0))
	{
	KillSound();
	ClrScrn();
	PlayStars3();
	if(!makestars(&sR,0))
		{
		KillSound();
		ClrScrn();
		PlayStars2();
		if(!makestars(&sR,0))
			{
			KillSound();
			ClrScrn();
			PlayStars1();
			makestars(&sR,0);
			}
		}
	}
KillSound();
ClrScrn();
DoExplodeSound();
while(!SoundDone())InvertRect(&sR);
Inform("THE END",TRUE);
EndGame(TRUE);
#endif
}
/*----------------------------------------------------------------------*/
TakeOff()
{
#if !defined(IBM_TakeOff)
int qt = FALSE;
int i,saved=0;

SetPort(scrport);
HideCursor();
ClrScrn();
PlayStars1();
leaveplanet();
KillSound();
ClrScrn();
ShowCursor();
#endif
}
/*----------------------------------------------------------------------*/
FullOfStars()
{
#if !defined(IBM_FullOfStars)
Pause();
#endif
}
