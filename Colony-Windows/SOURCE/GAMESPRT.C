/* #define IBM_InitDejaVu */
/* #define IBM_killanim */
/* #define IBM_DrawAll */
/* #define IBM_UnPackBytes */
/* #define IBM_loadbitmap */
/* #define IBM_readanim */
/* #define IBM_FindSprite */
/* #define IBM_DrawlSprite */
/* #define IBM_DrawPlane */
/* #define IBM_WhichlSprite */
/* #define IBM_NoShowIt */
/* #define IBM_DoIt */
/* #define IBM_KeylSprite */
/* #define IBM_DrawBackground */
/* #define IBM_AnimControl */
/* #define IBM_ObjectState */
/* #define IBM_SetObjectState */
/* #define IBM_SetObjectOnOff*/
/* #define IBM_OpenAFile */
/* #define IBM_DolSprite */
/* #define IBM_MoveObject */

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
 * spritePlane.c
 *		Functions to create and edit animated displays used by THE GAME.
 *----------------------------------------------------------------------
 * InitDejaVu()
 * killanim()
 * DrawAll()
 * UnPackBytes(src,dst,len)
 *		unsigned char *src,*dst;
 *		long len;
 * BitMap* loadbitmap(pblk)
 *		IOParam *pblk;
 * readanim(pblk)
 *		IOParam *pblk;
 * int FindSprite(snum,pr)
 *		int snum;
 *		Rect *pr;
 * DrawlSprite(snum)
 *		int snum;
 * DrawPlane()
 * int WhichlSprite(p,ploc)
 * 		Point *p;
 *		int *ploc;
 * NoShowIt()
 * int DoIt(p)
 *		Point *p;
 * DolSprite(p,num)
 *		Point *p;
 *		int num;
 * int KeylSprite(key,p,ploc)
 *		int key;
 *		Point *p;
 *		int *ploc;
 * DrawBackGround(meta)
 *		GrafPort* meta;
 * OpenAFile(fname)
 *		char *fname;
 * AnimControl(item)
 *		int* item;
 * ObjectState(num)
 *		int num;
 * SetObjectState(num,state)
 *		int num,state;
 * SetObjectOnOff(num,state)
 *		int num,state;
 *----------------------------------------------------------------------
 */
#define EXT extern
#include "gamedefs.h"
#include "fcntl.h"
void HeapMerge();
int my_open_read(char *, int, int);

#define WIDTH 416
#define HEIGHT 295
#define BTOP 30
#define NIL 0L
#define TOPPAT 8
#define BOTPAT 9
extern Rect screenR;
extern int keyflag;
Rect Frame;
int oX,oY;
Rect DClip;
Pattern topBG;
Pattern bottomBG;
int divideBG;
struct {
	int active;
	imageHeader* fg;
	imageHeader* mask;
	Rect clip;
	Rect locate;
	}background;
	
struct sprite{
	imageHeader* fg;
	imageHeader* mask;
	imageHeader* bg;
	Rect clip;
	Rect locate;
	int used;
	};
imageHeader* backImage;
BitMap *offBitMap;
struct sprite *cSprite;
int locSprite;
int maxsprite;

struct Object{
	int spritenum;
	int xloc,yloc;
	};

struct oSprite{
	int size;		/*number of sprites in this object*/
	struct Object object[8];
	imageHeader* bg;	/*sprite #1 background*/
	int visible;	/*visible flag*/
	int current;	/*current visible sprite*/
	int xloc,yloc;	/*base position of object*/
	int acurrent; 	/*animation system current visible sprite*/
	int axloc,ayloc;/*animation system base position of object*/
	unsigned char type;/*key or object*/
	unsigned char frozen;
	unsigned char locked;
	int link;
	int key;
	int lock;
	int onoff;
	};
struct oSprite* lSprite;
int maxSprite;
int anum;		/*current animated object*/

BitMap* metaBM;
int animnotdone;
char *adata;
long alocate;
int keybd_drag;
int bitmap_speed;
extern Rect rScreen;
extern int share;
extern int killer;
extern int sharray[20];
unsigned int *xlateCGA;
extern int jmouse;
extern int mouse;
/*----------------------------------------------------------------------*/
AnimNextFram()
{
SetPort(metaPnt);
MovePortTo(oX,oY);
PortSize(sR.right-oX+1, sR.bottom-oY+1);
ClipRect(&DClip);
NoShowIt();
RedrawBackGround();
DrawPlane();
PenColor(realcolor[vWHITE]);
FrameRect(&Frame);
ShowNextFram();
MovePortTo(oX,oY);
PortSize(sR.right-oX+1, sR.bottom-oY+1);
ClipRect(&DClip);
}
/*----------------------------------------------------------------------*/
OpenAFile(name,disp)
char *name;
int disp;
{
#ifndef IBM_OpenAFile
int fd;
event key;
mapArray cur_map;
char fname[64];

if(disp)Display();
Catenate(fname,name,".pic");
free(rtable);
HeapMerge();
if (!jmouse) LimitMouse(sR.left,sR.top,sR.right,sR.bottom);
else LimitJMouse(sR.left,sR.top,sR.right,sR.bottom,centerX,centerY);
keyflag=FALSE;
if ((fd = my_open_read(fname, O_RDONLY|O_BINARY, TRUE)) < 0)
	return(FALSE);
readanim(fd);/*read and unpack the file at the same time*/
close(fd);
SetupDejaVu();
if(is_EGAtype)
	{
	ShowNextFram();
	SetupDejaVu();
	}
cur_map[0]=0;
cur_map[1]=0;
cur_map[2]=0;
cur_map[3]=0;
cur_map[4]=0;
cur_map[5]=0;
cur_map[6]=0;
cur_map[7]=0;
CursorMap(cur_map);
if(!mouse)ShowCursor();
/* flush event buffer */
while(KeyEvent(FALSE, &key))
    ;
bitmap_speed = 1 << ((3-1) * 2); /* speed 3 of range [1, 5] */
return(TRUE);
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#define BSIZE 22
SetupDejaVu()
{
#ifndef IBM_InitDejaVu
int wd;
Rect r;

SetPort(metaPnt);
PenPattern(1);
PenColor(0);
BackColor(realcolor[vBLACK]);
ClipRect(&sR);
PaintRect(&sR);
MovePortTo(oX,oY);
PortSize(sR.right-oX+1, sR.bottom-oY+1);
ClipRect(&DClip);

animnotdone=TRUE;
#endif
}
/*---------------------------------------------------------------------
 * Animation file i/o system.
 *---------------------------------------------------------------------
 */
killanim(int erase)
{
#ifndef IBM_killanim
int i,j;
extern int showDashBoard;
extern int drewDashBoard;
extern int mouse;

if(erase)
	{
	PenColor(0);
	ClipRect(&sR);
	PaintRect(&sR);
	ShowNextFram();
	}
MovePortTo(0,0);
PortSize(sR.right+1, sR.bottom+1);
/*reset background*/
/*free(backImage);*/
/*
if(background.active)
	{
	free(background.fg);
	free(background.mask); 
	}
for(i=0;i<maxSprite;i++)
	{
	free(lSprite[i].bg);
	}
*/
if(maxSprite)free(lSprite);
maxSprite=0;
/*remove simple sprites*/
for(i=0;i<maxsprite;i++)
	{
	if((killer&&sharray[i])||!killer)
		{
		if((share&&sharray[i]==i)||!share)free(cSprite[i].mask);
		free(cSprite[i].fg);
		}
	}
if(maxsprite)free(cSprite);
HeapMerge();
maxsprite=0;
locSprite=0;
if(!mouse)HideCursor();
CursorMap(in_cur_map);
if(showDashBoard== True)
	drewDashBoard= 0;
if (!jmouse)
	{
	LimitMouse(screenR.left,screenR.top,screenR.right,screenR.bottom);
	TrackCursor(FALSE);
	MoveCursor(centerX, centerY);
	TrackCursor(TRUE);
	}
else LimitJMouse(screenR.left,screenR.top,screenR.right,screenR.bottom,
	centerX,centerY);
if(NIL==(rtable=(int *)malloc(sizeof(int)*11585)))MemoryErr();
rtable[0]=32000;
for(i=1;i<11585;i++)rtable[i]=(Floor*128)/i;
killer=FALSE;
share=FALSE;
while(KeyEvent(FALSE, &key));
#endif
}
/*----------------------------------------------------------------------*/
MakeBackGround()
{
metaPort offPort;

HideCursor();
SetPort(metaPnt);
ClipRect(&sR);
PenColor(realcolor[vBLACK]);
PaintRect(&sR);
MovePortTo(oX,oY);
PortSize(sR.right-oX+1, sR.bottom-oY+1);
ClipRect(&DClip);
if(is_EGAtype)
	{
	InitPort(&offPort);
	SetPort(&offPort);
	PortBitmap(offBitMap);
	SetOrigin(0,0);
	ClipRect(&DClip);
	}
DrawBackGround();
PenColor(realcolor[vWHITE]);
free(background.fg);
free(background.mask);
HeapMerge();
if(!is_EGAtype)CopyBackGround();
ShowCursor();
}
/*----------------------------------------------------------------------*/
DrawAll(int frame)
{
#ifndef IBM_DrawAll

HideCursor();
SetPort(metaPnt);
ClipRect(&sR);
PenColor(realcolor[vBLACK]);
PaintRect(&sR);
MovePortTo(oX,oY);
PortSize(sR.right-oX+1, sR.bottom-oY+1);
ClipRect(&DClip);
RedrawBackGround();
DrawPlane();/*draw in the foreground*/
PenColor(realcolor[vWHITE]);
if(frame)FrameRect(&Frame);
ShowNextFram();
MovePortTo(oX,oY);
PortSize(sR.right-oX+1, sR.bottom-oY+1);
ClipRect(&DClip);
if(is_EGAtype)
	{
	SetPort(metaPnt);
	MovePortTo(oX,oY);
	PortSize(sR.right-oX+1, sR.bottom-oY+1);
	ClipRect(&DClip);
	NoShowIt();
	RedrawBackGround();
	DrawPlane();
	}
ShowCursor();
#endif
}
/*----------------------------------------------------------------------*/
UnPackBytes(src,dst,len)
unsigned char *src,*dst;
long len;
{
#ifndef IBM_UnPackBytes
long i,j=0;

for(i=0;i<len;i++)
	{
	if(*src){dst[i]=(*(src+1));(*src)--;}
	else {src+=2; dst[i]=(*(src+1));(*src)--;}
	}
#endif
}
/*----------------------------------------------------------------------*/
imageHeader* loadimage(pblk)
int pblk;
{
#ifndef IBM_loadbitmap
imageHeader bmap, *imData;
imageHeader *XlateimData;
long size,bsize;
int tf;
char *buffer;

HeapMerge();
my_read(pblk,&bmap,(long)sizeof(imageHeader));
my_read(pblk,&tf,2L);

if(tf)
	{
	my_read(pblk,&bsize,4L);
	my_read(pblk,&size,4L);
	}
else
	my_read(pblk,&size,4L);

if (scrport->portBMap->pixBits == 2 || scrport->portBMap->pixPlanes == 2)
	{
	if(0==(imData =(imageHeader *)NewPtr(2*size+sizeof(imageHeader))))
	MemoryErr();
	}
else 
	{
	if(0==(imData = (imageHeader *)NewPtr(size+sizeof(imageHeader))))
	MemoryErr();
	}
if(tf)
	{
	if(0==(buffer=NewPtr(bsize)))MemoryErr();
	*imData = bmap;
	my_read(pblk,buffer,bsize);
	UnPackBytes(buffer,imData+1,size);
	DisposPtr(buffer);
	}
else
	{
	*imData = bmap;
	my_read(pblk,imData+1,size);
	}
/*if (scrport->portBMap->pixBits == 2 || scrport->portBMap->pixPlanes == 2)
	{
	long xltable[2];
	xltable[0] = realcolor[vBLACK];
	xltable[1] = realcolor[vWHITE];
	XlateImage(imData, XlateimData,
	    scrport->portBMap->pixBits, scrport->portBMap->pixPlanes, xltable);
	free(imData);
	imData = XlateimData;
	}*/
return(imData);
#endif
}
/*----------------------------------------------------------------------*/
readanim(pblk)
int pblk;
{
#ifndef IBM_readanim
int i,j;
unsigned int s;

HeapMerge();
/*--------------------------Read background data*/
topBG.patWidth = 8;
topBG.patHeight = 8;
topBG.patAlign = 0;
topBG.patRowBytes = 1;
topBG.patBits = 1;
topBG.patPlanes = 1;
bottomBG = topBG;

SetPort(metaPnt);
my_read(pblk,topBG.patData,8L);
for (i = 0; i < 8; i++)
    topBG.patData[i] = ~topBG.patData[i];
my_read(pblk,bottomBG.patData,8L);
for (i = 0; i < 8; i++)
    bottomBG.patData[i] = ~bottomBG.patData[i];
DefinePattern(TOPPAT, &topBG);
DefinePattern(BOTPAT, &bottomBG);

my_read(pblk,&divideBG,2L);
my_read(pblk,&background.active,2L);
if(background.active)
	{
	my_read(pblk,&background.clip,(long)sizeof(Rect));
	my_read(pblk,&background.locate,(long)sizeof(Rect));
	background.mask=loadimage(pblk);
	background.fg=loadimage(pblk);
	if (scrport->portBMap->pixBits == 2 || scrport->portBMap->pixPlanes == 2)
		{
		makeCGA(background.mask);
		makeCGA(background.fg);
		}
	}
MakeBackGround();
/*-------------------------Read sprite data*/
my_read(pblk,&maxsprite,2L);
if(0==(cSprite=(struct sprite*)NewPtr(sizeof(struct sprite)*maxsprite)))
	MemoryErr();
my_read(pblk,&locSprite,2L);
for(i=0;i<maxsprite;i++)
	{
	/*cSprite[i].pict*/
	cSprite[i].fg=loadimage(pblk); 
	cSprite[i].mask=loadimage(pblk);
	if(share&&sharray[i]!=i)
		{
		free(cSprite[i].mask);
/*		cSprite[i].mask=cSprite[sharray[i]].mask;*/
		HeapMerge();
		}
	if(killer&&!sharray[i])
		{
		free(cSprite[i].mask);
		free(cSprite[i].fg);
		HeapMerge();
		}
	my_read(pblk,&cSprite[i].used,2L);
	my_read(pblk,&cSprite[i].clip,(long)sizeof(Rect));
	my_read(pblk,&cSprite[i].locate,(long)sizeof(Rect));
	}
if(share)
for(i=0;i<maxsprite;i++)cSprite[i].mask=cSprite[sharray[i]].mask;
/*-------------------------Read lSprite data*/
my_read(pblk,&maxSprite,2L);
if(0==(lSprite=(struct oSprite*)NewPtr(sizeof(struct oSprite)*maxSprite)))
	MemoryErr();
my_read(pblk,&anum,2L);
for(i=0;i<maxSprite;i++)
	{
	Rect bounds;
	my_read(pblk,&lSprite[i].size,2L);
	for(j=0;j<lSprite[i].size;j++)
		my_read(pblk,&lSprite[i].object[j],6L);
	my_read(pblk,&bounds,(long)sizeof(Rect));
/*	s=ImageSize(&bounds);
	if(0==(lSprite[i].bg=(imageHeader *)NewPtr(s)))MemoryErr();*/
	my_read(pblk,&lSprite[i].visible,2L);	/*visible flag*/
	lSprite[i].visible = FALSE;
	my_read(pblk,&lSprite[i].current,2L);	/*current visible sprite*/
	my_read(pblk,&lSprite[i].xloc,2L);
	my_read(pblk,&lSprite[i].yloc,2L);		/*base position of object*/
	my_read(pblk,&lSprite[i].acurrent,2L); 	/*animation system current visible sprite*/
	my_read(pblk,&lSprite[i].axloc,2L);
	my_read(pblk,&lSprite[i].ayloc,2L);		/*animation system base position of object*/
	my_read(pblk,&lSprite[i].type,1L);		/*key or object*/
	my_read(pblk,&lSprite[i].frozen,1L);
	my_read(pblk,&lSprite[i].locked,1L);
	my_read(pblk,&lSprite[i].link,2L);
	my_read(pblk,&lSprite[i].key,2L);
	my_read(pblk,&lSprite[i].lock,2L);
	lSprite[i].onoff=TRUE;
	}
if (scrport->portBMap->pixBits == 2 || scrport->portBMap->pixPlanes == 2)
	{ 
	if(share)
	for(i=0;i<maxsprite;i++)
		{
		makeCGA(cSprite[i].fg);
		if(sharray[i]==i)
			makeCGA(cSprite[i].mask);
		}
	else if(killer)
	for(i=0;i<maxsprite;i++)
		{
		if(sharray[i])
			{
			makeCGA(cSprite[i].fg);
			makeCGA(cSprite[i].mask);
			}
		}
	else
	for(i=0;i<maxsprite;i++)
		{
		makeCGA(cSprite[i].fg);
		makeCGA(cSprite[i].mask);
		}
	}

#endif
}
/*----------------------------------------------------------------------*/
makeCGA(im)
typedef struct /* Image Header record structure  */
   {short    imWidth;        /* Pixel width (X)              */
    short    imHeight;       /* Pixel height (Y)             */
    short    imAlign;        /* Image alignment              */
    short    imRowBytes;     /* Bytes per row                */
    char     imBits;         /* Bits per pixel               */
    char     imPlanes;       /* Planes per pixel             */
	union
		{
		unsigned char    cimData[2];	    /* (image data, variable length)*/
		unsigned short 	iimData[1];
		}data;
	} *im;
{
int i;
int nbytes=im->imRowBytes*im->imHeight;
for(i=nbytes-1;i>=0;i--)im->data.iimData[i]=xlateCGA[im->data.cimData[i]];
im->imRowBytes*=2;
im->imBits=2;
}
/*----------------------------------------------------------------------*/
int FindSprite(snum,pr)
int snum;
Rect *pr;
{
#ifndef IBM_FindSprite
int cnum,xloc,yloc;

cnum=lSprite[snum].current;
xloc=lSprite[snum].xloc + lSprite[snum].object[cnum].xloc;
yloc=lSprite[snum].yloc + lSprite[snum].object[cnum].yloc;
cnum=lSprite[snum].object[cnum].spritenum;
pr->top=cSprite[cnum].clip.top+yloc;
pr->left=cSprite[cnum].clip.left+xloc;
pr->bottom=cSprite[cnum].clip.bottom+yloc;
pr->right=cSprite[cnum].clip.right+xloc;
return(cnum);/*return the sprite number*/
#endif
}
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
DrawlSprite(snum)
int snum;
{
#ifndef IBM_DrawlSprite
int i;
int bit=1<<snum;
GrafPtr	savePort;
int cnum;
Rect locate,clip;
int sloc;

GetPort( &savePort );
SetPort(metaPnt);
/*save the current background*/
cnum=FindSprite(snum,&locate);
if(locate.top<0)
	{
	sloc=locate.top;
	clip.bottom=cSprite[cnum].clip.bottom;
	clip.left=cSprite[cnum].clip.left;
	clip.right=cSprite[cnum].clip.right;
	clip.top=-locate.top;
	locate.top=0;
	PenMode(zREPz);
/*	ReadImage(&locate, lSprite[snum].bg);*/
	locate.top=sloc;
	}
else
	{
	PenMode(zREPz);
/*	ReadImage(&locate, lSprite[snum].bg);*/
	}
SetPort(metaPnt);
PenMode(zNANDz);
WriteImage(&locate, cSprite[cnum].mask);
PenMode(zORz);
WriteImage(&locate, cSprite[cnum].fg);
lSprite[snum].visible=TRUE;
SetPort( savePort );
#endif
}
/*----------------------------------------------------------------------*/
DrawPlane()
{
#ifndef IBM_DrawPlane
GrafPtr	savePort;
int i;
struct oSprite *savesprite;
int *savemax;

GetPort( &savePort );
SetPort(metaPnt);
for(i=0;i<maxSprite;i++){lSprite[i].visible=0;}
for(i=0;i<maxSprite;i++)if(lSprite[i].onoff)DrawlSprite(i);
SetPort(savePort);
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int WhichlSprite(p,ploc)
Point *p;
int *ploc;
{
#ifndef IBM_WhichlSprite
int i;
int num;
Rect r;
int cnum;
imageHeader *maskHeader;
unsigned char maskByte;
int maskIndex;
int row, col;

*ploc=0;
for(i=(maxSprite)-1;i>=0;i--)
    if(lSprite[i].onoff)
	{
	cnum=FindSprite(i,&r);
	if (p->h>=r.left && p->h<=r.right && p->v>=r.top && p->v<=r.bottom)
	    {
	    maskHeader = cSprite[cnum].mask;
	    row = p->v - r.top;
	    col = p->h - r.left;

	    maskIndex = row * maskHeader->imRowBytes +
		    (((col + maskHeader->imAlign) * maskHeader->imBits) / 8);
	    maskByte = ((char *)(maskHeader+1))[maskIndex];
	    if (maskHeader->imPlanes == 2)
		maskByte |= ((char *)(maskHeader+1))[maskHeader->imRowBytes *
		    maskHeader->imHeight + maskIndex];
	    maskByte = maskByte >> (((col + maskHeader->imAlign) *
		maskHeader->imBits) % 8);
	    if(maskByte & ((1 << maskHeader->imBits) - 1))
		{
		num=i;
		*ploc=1;
		i = -1;
		}
	    }
	}
return(num);
#endif
}
/*----------------------------------------------------------------------*/
NoShowIt()
{
#ifndef IBM_NoShowIt
int i;

for(i=0;i<maxSprite;i++)
	{
	if(lSprite[i].onoff&&lSprite[i].type==0&&!lSprite[i].locked&&lSprite[i].size>1)
		{
/*		EraseTree(i);*/
		lSprite[i].current++;
		if(lSprite[i].current==lSprite[i].size)lSprite[i].current=0;
/*		EraseTree(i);*/
		}
	}
#endif
}
/*----------------------------------------------------------------------*/
int DoIt(p)
Point *p;
{
#ifndef IBM_DoIt
int num,loc;
num=WhichlSprite(p,&loc);
if(loc)
	{
	DolSprite(p,num);
	return(num+1);
	}
else return(0);
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int KeylSprite(key,p,ploc)
int key;
Point *p;
int *ploc;
{
#ifndef IBM_KeylSprite
imageHeader *maskHeader;
unsigned char maskByte;
int maskIndex;
int row, col;
int i;
Rect r;
int cnum;
int num=-1;
*ploc=0;
for(i=(maxSprite)-1;i>=0;i--)
if(key!=i)
if(lSprite[i].lock==lSprite[key].key)
	{
	cnum=FindSprite(i,&r);
	if( p->h>=r.left && p->h<=r.right && p->v>=r.top && p->v<=r.bottom)
		{
		maskHeader = cSprite[cnum].mask;
		row = p->v - r.top;
		col = p->h - r.left;

		maskIndex = row * maskHeader->imRowBytes +
		    (((col + maskHeader->imAlign) * maskHeader->imBits) / 8);
		maskByte = ((char *)(maskHeader+1))[maskIndex];
		if (maskHeader->imPlanes == 2)
		    maskByte |=
			((char *)(maskHeader+1))[maskHeader->imRowBytes *
			maskHeader->imHeight + maskIndex];
		maskByte = maskByte >> (((col + maskHeader->imAlign) *
		    maskHeader->imBits) % 8);
		if(maskByte & ((1 << maskHeader->imBits) - 1))
		    {
		    num=i;
		    *ploc=1;
		    break;
		    }
		}
	}
return(num);
#endif
}
/*----------------------------------------------------------------------*/
DrawBackGround()
{
#ifndef IBM_DrawBackGround
int i;
Rect r;

PenMode(zREPz);
PenColor(realcolor[vBLACK]);
BackColor(realcolor[vWHITE]);
r.top=DClip.top;
r.left=DClip.left;
r.right=DClip.right;
r.bottom=divideBG;
FillRect(&r,TOPPAT);
r.top=r.bottom;
r.bottom=DClip.bottom;
FillRect(&r,BOTPAT);
MoveTo(DClip.left,divideBG); LineTo(DClip.right,divideBG);
if(background.active)
	{
	PenMode(zNANDz);
	WriteImage(&background.locate, background.mask);
	PenMode(zORz);
	WriteImage(&background.locate, background.fg);
	}
PenColor(realcolor[vWHITE]);
SetPort(metaPnt);
if (DClip.right <= sR.right)
	Frame=DClip;
else
	{
	Frame = sR;
	Gbl2LclRect(&Frame);
    }
PenColor(realcolor[vBLACK]);
#endif
}
/*----------------------------------------------------------------------*/
CopyBackGround()
{
ReadImage(&DClip, backImage);
}
/*----------------------------------------------------------------------*/
RedrawBackGround()
{
PenMode(zREPz);
WriteImage(&DClip,backImage);
}
/*----------------------------------------------------------------------*/
extern EventRecord key;
AnimControl(item)
int* item;
{
#ifndef IBM_AnimControl
Point loc;
int dummy1, dummy2;
EventRecord key1;

*item=0;
if(KeyEvent(FALSE, &key))
	{
	if (key.ScanCode < 2 || key.ScanCode > 6)
	    {
	    /* flush event queue; 'key' will contain last event in queue */
	    while (KeyEvent(FALSE, &key1))
		{
		/* if not mouse-up event, then remember it */
		if (key1.ASCII || key1.ScanCode || (key1.State & 0x0700))
		    {
		    key = key1;

		    /* if speed change key, get out and process it */
		    if (key.ScanCode >= 2 && key.ScanCode <= 6)
			break;
		    }
		}
	    }

	if (((key.State & 0x0700) && (key.State & 0x0003)) ||
	    ((key.ASCII == 32 || key.ScanCode == 82 || key.ScanCode == 146) &&
	    (key.State & 0x0003)))
	    return(animnotdone=FALSE);

	if(keyflag)
	    {
	    if(key.ASCII >= '0' && key.ASCII <= '9' &&
			!(key.ScanCode>=2 && key.ScanCode<=11))
		*item = 1 + key.ASCII - '0';
	    else switch(key.ASCII)
		{
		case 0x0D:
		    *item=12;
		    break;
		case 0x08:
		case 0x7F:
		case 0x1B:
		    *item=11;
		    break;
		}
	    if (*item)
		return(animnotdone);
	    }
	else if(key.ASCII==0x0D) *item=101;
	if (key.ASCII || key.ScanCode)
	    {
	    /* space or Ins, ^Ins on keypad */
	    if (key.ASCII == 32 || key.ScanCode == 82 || key.ScanCode == 146)
		{
		QueryCursor(&loc.h, &loc.v, &dummy1, &dummy2);
		if (key.State & 0x04)	/* ctrl */
		    keybd_drag = True;
		else
		    keybd_drag = False;
		*item=DoIt(&loc);
		}
	    else if ( key.ScanCode>58 && key.ScanCode<63 )
		Help(key.ScanCode-58);
	    else
		{
		if (!jmouse) KeyMoveCursor(&key);
		}
	    }
	else if (key.State & 0x0400)
	    {
	    /* handle mouse button down */
	    QueryCursor(&loc.h, &loc.v, &dummy1, &dummy2);
	    keybd_drag = False;
	    *item=DoIt(&loc);
	    }
	else if (key.State & 0x0300)
	    return(animnotdone=FALSE);
	}
return(animnotdone);
#endif
}
/*----------------------------------------------------------------------*/
ObjectState(num)
int num;
{
#ifndef IBM_ObjectState
num--;
if(num<maxSprite&&num>=0)return(lSprite[num].current+1);
else return(0);
#endif
}
/*----------------------------------------------------------------------*/
SetObjectState(num,state)
int num,state;
{
#ifndef IBM_SetObjectState
num--;
/*EraseTree(num);*/
if(num<maxSprite&&num>=0)lSprite[num].current=state-1;
/*EraseTree(num);*/
/*DrawTree(num);
  ShowNextFram();*/
#endif
}
/*----------------------------------------------------------------------*/
SetObjectOnOff(num,state)
int num,state;
{
#ifndef IBM_SetObjectOnOff
num--;
if(num<maxSprite&&num>=0)lSprite[num].onoff=state;
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
DolSprite(p,num)
Point *p;
int num;
{
#ifndef IBM_DolSprite
Rect r,dummy;
Point new,old;
int xloc,yloc;
int savenum;
int i,knum,oldknum=-1;
int loc;
int dummy1, dummy2;

old.v=p->v;
old.h=p->h;
switch(lSprite[num].type)
	{
	case 0:/*displays*/
		if(!lSprite[num].frozen)MoveObject(p,num,FALSE);
		break;
	case 1:/*key and control*/
		if(lSprite[num].frozen)/*this is a control*/
			{
			/*if not locked or slightly open*/
			if((!lSprite[num].locked)||lSprite[num].current)
				/*this is a container--only can open or close*/
				{
				if(lSprite[num].current>1) 
				while(lSprite[num].current>0)
					{
					lSprite[num].current--;
					if(lSprite[num].key)
					for(i=0;i<maxSprite;i++)if(i!=num)
						if(lSprite[i].lock==lSprite[num].key)
							{
							lSprite[i].current=lSprite[num].current;
							if(lSprite[i].current>=lSprite[i].size)
								lSprite[i].current=lSprite[i].size-1;
							}
					AnimNextFram();
					}
				else 
				while(lSprite[num].current<lSprite[num].size-1)
					{
					lSprite[num].current++;
					if(lSprite[num].key)
					for(i=0;i<maxSprite;i++)if(i!=num)
						if(lSprite[i].lock==lSprite[num].key)
							{
							lSprite[i].current=lSprite[num].current;
							if(lSprite[i].current>=lSprite[i].size)
								lSprite[i].current=lSprite[i].size-1;
							}
					AnimNextFram();
					}
				}
			}
		else MoveObject(p,num,lSprite[num].key);/*this is a key - animate always*/
			/*{
			while(Button())
				{
				QueryCursor(&new.h, &new.v, &dummy1, &dummy2);
				if(new.v>0&&new.v<(HEIGHT-BTOP)&&new.h>0&&new.h<WIDTH)
					{
					lSprite[num].current++;
					if(lSprite[num].current==lSprite[num].size)lSprite[num].current=0;
					lSprite[num].xloc+=new.h-old.h;
					lSprite[num].yloc+=new.v-old.v;
					if(lSprite[num].key)
						{
						knum=KeylSprite(num,&new,&loc);
						if(loc)
						if(knum!=oldknum)
							{
							if(lSprite[knum].current==1)
								{
								lSprite[knum].current--;
								lSprite[num].current++;
								if(lSprite[num].current==lSprite[num].size)
									lSprite[num].current=0;
								AnimNextFram();
								}
							else if(lSprite[knum].current==0)
								{
								lSprite[knum].current++;
								lSprite[num].current++;
								if(lSprite[num].current==lSprite[num].size)
									lSprite[num].current=0;
								AnimNextFram();
								}
							oldknum=knum;
							}
						}
					old.h=new.h;
					old.v=new.v;
					}
				AnimNextFram();
				}
			lSprite[num].current=0;
			AnimNextFram();
			}*/
		break;
	case 2:/*container and object*/
		if(lSprite[num].frozen)
			{
			if(!lSprite[num].locked)
				/*this is a container--only can open or close*/
				{
				if(lSprite[num].current) while(lSprite[num].current>0)
					{
					lSprite[num].current--;
					AnimNextFram();
					}
				else while(lSprite[num].current<lSprite[num].size-1)
					{
					lSprite[num].current++;
					AnimNextFram();
					}
				}
			else
				/*this is a container--only can open or close*/
				{
				if(lSprite[num].current>1) while(lSprite[num].current>0)
					{
					lSprite[num].current--;
					AnimNextFram();
					}
				else if(lSprite[num].current==1)while(lSprite[num].current<lSprite[num].size-1)
					{
					lSprite[num].current++;
					AnimNextFram();
					}
				}
			}
		else MoveObject(p,num,FALSE);/*this is an object - only allow the user to move it*/
		/*	{
			QueryCursor(&new.h, &new.v, &dummy1, &dummy2);
			if(new.v>0&&new.v<(HEIGHT-BTOP)&&new.h>0&&new.h<WIDTH)
				{
				lSprite[num].xloc+=new.h-old.h;
				lSprite[num].yloc+=new.v-old.v;
				if(lSprite[num].link)
					for(i=0;i<maxSprite;i++)
						{
						if(lSprite[i].link==lSprite[num].link && num!=i)
							{
							lSprite[i].xloc+=new.h-old.h;
							lSprite[i].yloc+=new.v-old.v;
							}
						}
				old.h=new.h;
				old.v=new.v; 
				}
			AnimNextFram();
			}*/
		break;
	}
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
MoveObject(p,num,key)
Point *p;
int num;
int key;
{
#ifndef IBM_MoveObject
int i,knum,oldknum=-1;
Point new,old;
int xloc,yloc;
int loc;
int link[16];
int linknum=0;
int dummy1, dummy2;

if(lSprite[num].link)
	{
	for(i=0;i<maxSprite;i++)
		if(lSprite[num].link==lSprite[i].link)
			{
			link[linknum]=i;
			linknum++;
			}
	}
else 
	{
	link[0]=num;
	linknum=1;
	}
old.v=p->v;
old.h=p->h;
for(i=0;i<linknum;i++)SetObjectOnOff(link[i]+1,FALSE);
while(Dragging(&new))/*this is a display - animate always*/
	{
	if(lSprite[num].type!=2)
		{
		lSprite[num].current++;
		if(lSprite[num].current==lSprite[num].size)lSprite[num].current=0;
		}
	if(new.v>0&&new.v<(HEIGHT-BTOP)&&new.h>0&&new.h<WIDTH)
		{
		for(i=0;i<linknum;i++)
			{
			lSprite[link[i]].xloc+=new.h-old.h;
			lSprite[link[i]].yloc+=new.v-old.v;
			}
		if(key)
			{
			knum=KeylSprite(num,&new,&loc);
			if(loc)if(knum!=oldknum)
				{
				if(lSprite[knum].current==1)
					{
					lSprite[knum].current--;
					lSprite[num].current++;
					if(lSprite[num].current==lSprite[num].size)
						lSprite[num].current=0;
					AnimNextFram();
					}
				else if(lSprite[knum].current==0)
					{
					lSprite[knum].current++;
					lSprite[num].current++;
					if(lSprite[num].current==lSprite[num].size)
						lSprite[num].current=0;
					AnimNextFram();
					}
				oldknum=knum;
				}
			}
		old.h=new.h;
		old.v=new.v; 
		}
	SetPort(metaPnt);
	MovePortTo(oX,oY);
	PortSize(sR.right-oX+1, sR.bottom-oY+1);
	ClipRect(&DClip);
	NoShowIt();
	RedrawBackGround();
	DrawPlane();
	PenColor(realcolor[vWHITE]);
	FrameRect(&Frame);
	for(i=0;i<linknum;i++)DrawlSprite(link[i]);
	ShowNextFram();
	MovePortTo(oX,oY);
	PortSize(sR.right-oX+1, sR.bottom-oY+1);
	ClipRect(&DClip);
	}
if(lSprite[num].type!=2)lSprite[num].current=0;
for(i=0;i<linknum;i++)SetObjectOnOff(link[i]+1,TRUE);
AnimNextFram();
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
void HeapMerge()
    {
    struct _heapinfo hinfo;

    hinfo._pentry = NULL;
    while (_heapwalk(&hinfo) == _HEAPOK)
	if (hinfo._useflag == _FREEENTRY)
	    _expand((void *)hinfo._pentry, (unsigned)0xfff0);
    }
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
/* dwe ??? testing */
long HeapSize()
    {
    struct _heapinfo hinfo;
    int heapstatus;
    long freeSize = 0L, usedSize = 0L;
    int *ip, fd;


    hinfo._pentry = NULL;
    while ((heapstatus=_heapwalk(&hinfo)) == _HEAPOK)
	{
	if (hinfo._useflag == _USEDENTRY)
	    usedSize += hinfo._size;
	else
	    freeSize += hinfo._size;
	}
return(freeSize);
    }
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
HeapGreedy()
    {
    int pcount, i;
    char **p;
    char *ip;

/*    HeapSize("Before HeapGreedy"); /* dwe ??? testing */
    p=malloc(sizeof(char*)*256);
    for(i=0;i<256;i++)
	{
	p[i]=malloc(2048);
	if(p[i]==NULL){pcount=i;break;}
	}
    for(i=0;i<pcount;i++)free(p[i]);
    free(p);
    pcount++;
/*    HeapSize("After mallocs/free"); /* dwe ??? testing */
    HeapMerge();
/*    HeapSize("After HeapMerge"); /* dwe ??? testing */
    }
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
Dragging(p)
Point *p;
    {
    EventRecord key1;
    int d1, b;

    if (KeyEvent(FALSE, &key))
	{
	if (key.ScanCode < 2 || key.ScanCode > 6)
	    {
	    /* flush event queue; 'key' will contain last event in queue */
	    while (KeyEvent(FALSE, &key1))
		{
		/* if not mouse event, then remember it */
		if (key1.ASCII || key1.ScanCode)
		    {
		    key = key1;

		    /* if speed change key, get out and process it */
		    if (key.ScanCode >= 2 && key.ScanCode <= 6)
			break;
		    }
		}
	    }

	if (key.ASCII || key.ScanCode)
	    {
	    if (key.ASCII == 32 || key.ScanCode == 82 || key.ScanCode == 146)
		{
		if (key.State & 0x04)	/* ctrl */
		    keybd_drag = True;
		else
		    keybd_drag = False;
		}
	    else if ( key.ScanCode>58 && key.ScanCode<63 )
		Help(key.ScanCode-58);
	    else
		{
		if (!jmouse) KeyMoveCursor(&key);
		}
	    }
	else
	    if (key.State & 0x0700)	/* mouse button */
		keybd_drag = False;
	}

    QueryCursor(&(p->h), &(p->v), &d1, &b);
    return(keybd_drag || b);
    }
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
KeyMoveCursor(ev)
EventRecord *ev;
    {
    int moveX, moveY;
    Point loc;
    int dummy1, dummy2;

    moveX = 0;
    moveY = 0;
    switch(ev->ScanCode)
	{
	case 16:	/* q, move up & left */
	case 71:	/* home */
	case 119:	/* ctrl home */
	    moveX = -1;
	    moveY = -1;
	    break;
	case 17:	/* w, move up */
	case 72:	/* up arrow */
	case 141:	/* ctrl up arrow */
	    moveY = -1;
	    break;
	case 18:	/* e, move up & right */
	case 73:	/* page up */
	case 132:	/* ctrl page up */
	    moveX = 1;
	    moveY = -1;
	    break;
	case 30:	/* a, move left */
	case 75:	/* left arrow */
	case 115:	/* ctrl left arrow */
	    moveX = -1;
	    break;
	case 32:	/* d, move right */
	case 77:	/* right arrow */
	case 116:	/* ctrl right arrow */
	    moveX = 1;
	    break;
	case 44:	/* z, move down & left */
	case 79:	/* end */
	case 117:	/* ctrl end */
	    moveX = -1;
	    moveY = 1;
	    break;
	case 45:	/* x, move down */
	case 80:	/* down arrow */
	case 145:	/* ctrl down arrow */
	    moveY = 1;
	    break;
	case 46:	/* c, move down & right */
	case 81:	/* page down */
	case 118:	/* ctrl page down */
	    moveX = 1;
	    moveY = 1;
	    break;
	case 2:		/* 1 */
	case 3:		/* 2 */
	case 4:		/* 3 */
	case 5:		/* 4 */
	case 6:		/* 5 */
	    bitmap_speed = 1 << ((ev->ScanCode - 2) * 2);
	    break;
	}

    if (moveX || moveY)
	{
	moveX *= bitmap_speed;
	moveY *= bitmap_speed;

	QueryCursor(&loc.h, &loc.v, &dummy1, &dummy2);
	loc.h += moveX;
	loc.v += moveY;
	if (loc.h < sR.left - oX) loc.h = sR.left - oX;
	if (loc.h > sR.right - oX) loc.h = sR.right - oX;
	if (loc.v < sR.top - oY) loc.v = sR.top - oY;
	if (loc.v > sR.bottom - oY) loc.v = sR.bottom - oY;
	}
    /* s, middle key, or ctrl middle key */
    else if (ev->ScanCode == 31 || ev->ScanCode == 76 || ev->ScanCode == 143)
	{
	loc.h = (DClip.left + DClip.right) / 2;
	loc.v = (DClip.top + DClip.bottom) / 2;
	}
    else
	return;

    TrackCursor(FALSE);
    MoveCursor(loc.h, loc.v);
    TrackCursor(TRUE);
    }


/* KeyEvent ASCII and ScanCode values for keypad keys with combinations of: */
/*    Ctrl key pressed, Shift key pressed, and Numlock active */

/* NOT Ctrl AND NOT (Shift XOR Numlock) */
/*                                      */
/*  +-------+-------+-------+           */
/*  + 00 47 | 00 48 | 00 49 |           */
/*  +-------+-------+-------+           */
/*  + 00 4B | F0 4C | 00 4D |           */
/*  +-------+-------+-------+           */
/*  + 00 4F | 00 50 | 00 51 |           */
/*  +-------+-------+-------+           */
/*  +     00 52     | 00 53 |           */
/*  +---------------+-------+           */
/*                                      */
/*                                      */
/* NOT Ctrl AND (Shift XOR Numlock)     */
/*                                      */
/*  +-------+-------+-------+           */
/*  + 37 47 | 38 48 | 39 49 |           */
/*  +-------+-------+-------+           */
/*  + 34 4B | 35 4C | 36 4D |           */
/*  +-------+-------+-------+           */
/*  + 31 4F | 32 50 | 33 51 |           */
/*  +-------+-------+-------+           */
/*  +     30 52     | 2E 53 |           */
/*  +---------------+-------+           */
/*                                      */
/*                                      */
/* Ctrl                                 */
/*                                      */
/*  +-------+-------+-------+           */
/*  + 00 77 | 00 8D | 00 84 |           */
/*  +-------+-------+-------+           */
/*  + 00 73 | 00 8F | 00 74 |           */
/*  +-------+-------+-------+           */
/*  + 00 75 | 00 91 | 00 76 |           */
/*  +-------+-------+-------+           */
/*  +     00 92     | 00 93 |           */
/*  +---------------+-------+           */
