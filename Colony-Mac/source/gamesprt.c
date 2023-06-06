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
 * DejaCopy()
 * DejaDCopy()
 * animupdate()
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
 * int Overlap(i,j)
 *		int i,j;
 * DrawlSprite(snum)
 *		int snum;
 * EraselSprite(snum)
 *		int snum;
 * EraseTree(snum)
 *		int snum;
 * DrawTree(snum)
 *		int snum;
 * DrawPlane()
 * int WhichlSprite(p,ploc)
 * 		Point *p;
 *		int *ploc;
 * ShowIt()
 * NoShowIt()
 * int DoIt(p)
 *		Point *p;
 * DolSprite(p,num)
 *		Point *p;
 *		int num;
 * int InsideControl(p,num)
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
 * ObjectRect(num,r)
 *		int num;
 *		Rect *r;
 * SetObjectState(num,state)
 *		int num,state;
 * SetObjectOnOff(num,state)
 *		int num,state;
 *----------------------------------------------------------------------
 */
#define EXT extern 
#include "cgamedefs.h"
#include "colordef.h"

#define WIDTH 416
#define HEIGHT 295
#define BTOP 30
extern CursHandle Cross;
extern Rect screenR;
extern RGBColor white_Color;
extern RGBColor black_Color;
int *BMColor;

Rect size;
Rect ebutton;
Rect DClip;
Pattern topBG;
Pattern bottomBG;
int divideBG;
struct {
	int active;
	PicHandle pict;
	BitMap* fg;
	BitMap* mask;
	Rect clip;
	Rect locate;
	}background;
	
struct sprite{
	PicHandle pict;
	BitMap* fg;
	BitMap* mask;
	BitMap* bg;
	Rect clip;
	Rect locate;
	int used;
	};
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
	BitMap* bg;		/*sprite #1 background*/
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

WindowRecord theRecord;
GrafPtr animWindow;
int animnotdone;
char *adata;
long alocate;
extern Rect rScreen;
extern Rect animR;
extern CGrafPort metaPort;
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#define BSIZE 22
InitDejaVu()
{
Rect r;
SetRect(&size,0,0,416,294);
DClip.top=size.top;
DClip.bottom=size.bottom-BTOP;
DClip.left=size.left;
DClip.right=size.right;
/*SetRect(&r, 92, 40, 509, 334);*/
r=animR;
animWindow = NewCWindow( &theRecord , &r, "\pScene",1, 2, -1L, 1, 0L);
SetPort(animWindow);
PenMode(patCopy);
SetOrigin(0,0);
DrawButton();
SetPort(&metaPort);
animnotdone=TRUE;
}

DrawButton()
{
Rect r;
int wd;

r=size;
r.top=HEIGHT-BTOP;
ClipRect(&r);
RGBForeColor(&black_Color);
RGBBackColor(&white_Color);
FillRect(&r,white);
MoveTo(0,HEIGHT-BTOP);
LineTo(WIDTH,HEIGHT-BTOP);
TextFont(0);
wd=StringWidth("\pEXIT")/2;
MoveTo(WIDTH/2-wd,HEIGHT+20-BTOP);
DrawString("\pEXIT");
ebutton.left=WIDTH/2-(wd+15);
ebutton.right=WIDTH/2+(wd+15);
ebutton.top=HEIGHT+6-BTOP;
ebutton.bottom=HEIGHT+24-BTOP;
FrameRoundRect(&ebutton,8,8);
r.top=ebutton.top-3;
r.bottom=ebutton.bottom+3;
r.left=ebutton.left-3;
r.right=ebutton.right+3;
PenSize(2,2);
FrameRoundRect(&r,11,11);
PenSize(1,1);
ClipRect(&size);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
DejaDCopy()
{
GrafPtr	savePort;

GetPort( &savePort );
SetPort(animWindow);
CopyBits(*metaPort.portPixMap,&animWindow->portBits,
	&DClip,&DClip,srcCopy,NIL);
SetPort( savePort );
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
animupdate()
{
GrafPtr	savePort;

GetPort( &savePort );
SetPort(animWindow);
BeginUpdate(animWindow);
DrawButton();
SetPort(&metaPort);
DrawAll();
DejaDCopy();
EndUpdate(animWindow);
SetPort( savePort );
}
BitMap* NewBitMap();
/*---------------------------------------------------------------------
 * Animation file i/o system.
 *---------------------------------------------------------------------
 */
extern int cchange;
killanim()
{
int i,j;

/*reset background*/
if(background.active)
	{
	KillBitMap(background.fg);
	KillBitMap(background.mask); 
	}
/*for(i=0;i<maxSprite;i++)
	{
	KillBitMap(lSprite[i].bg);
	}*/
if(maxSprite)DisposPtr(lSprite);
maxSprite=0;
/*remove simple sprites*/
for(i=0;i<maxsprite;i++)
	{
	KillBitMap(cSprite[i].fg); 
	KillBitMap(cSprite[i].mask); 
	}
if(maxsprite)DisposPtr(cSprite);
maxsprite=0;
locSprite=0;
CloseWindow(animWindow);
SetCursor(*Cross);
cchange=TRUE;
/*BuildTable();*/
SetPort(&metaPort);
ClipRect(&Clip);
}
/*----------------------------------------------------------------------*/
DrawAll()
{
DrawBackGround();
if(Button())if(ButtonDown())return;
if(!DrawPlane())return;/*draw in the foreground*/
if(Button())if(ButtonDown())return;
DejaDCopy();
}
DrawSome()
{
DrawBackGround();
DrawPlane();/*draw in the foreground*/
}

/*----------------------------------------------------------------------*/
UnPackBytes(src,dst,len)
unsigned char *src,*dst;
long len;
{
long i,j=0;

for(i=0;i<len;i++)
	{
	if(*src){dst[i]=(*(src+1));(*src)--;}
	else {src+=2; dst[i]=(*(src+1));(*src)--;}
	}
}
/*----------------------------------------------------------------------*/
BitMap* loadbitmap(pblk)
IOParam *pblk;
{
BitMap *bmap;
long size,bsize;
int tf;
char *buffer;

if(0==(bmap=(BitMap *)NewPtr((long)sizeof(BitMap))))MemoryErr();
my_read(pblk,bmap,(long)sizeof(BitMap));
my_read(pblk,&tf,2L);
if(tf)
	{
	my_read(pblk,&bsize,4L);
	my_read(pblk,&size,4L);
	if(0==(bmap->baseAddr = (QDPtr)NewPtr(size)))MemoryErr();;
	if(0==(buffer=NewPtr(bsize+8)))MemoryErr();
	my_read(pblk,buffer,bsize);
	UnPackBytes(buffer,bmap->baseAddr,size);
	DisposPtr(buffer);
	}
else
	{
	my_read(pblk,&size,4L);
	if(0==(bmap->baseAddr = (QDPtr)NewPtr(size)))MemoryErr();
	my_read(pblk,bmap->baseAddr,size);
	}
return(bmap);
}
/*----------------------------------------------------------------------*/
BitMap* unpackbitmap()
{
BitMap *bmap;
long size,bsize;
int tf;
char *buffer;

if(0==(bmap=(BitMap *)NewPtr((long)sizeof(BitMap))))MemoryErr();
unpack(bmap,(long)sizeof(BitMap));
unpack(&tf,2L);
if(tf)
	{
	unpack(&bsize,4L);
	unpack(&size,4L);
	if(0==(bmap->baseAddr = (QDPtr)NewPtr(size)))MemoryErr();
	if(0==(buffer=NewPtr(bsize+8)))MemoryErr();
	unpack(buffer,bsize);
	UnPackBytes(buffer,bmap->baseAddr,size);
	DisposPtr(buffer);
	}
else
	{
	unpack(&size,4L);
	if(0==(bmap->baseAddr = (QDPtr)NewPtr(size)))MemoryErr();
	unpack(bmap->baseAddr,size);
	}
return(bmap);
}
/*----------------------------------------------------------------------*/
readanim(pblk)
IOParam *pblk;
{
int i,j;

/*--------------------------Read background data*/
my_read(pblk,topBG,8L);
my_read(pblk,bottomBG,8L);
my_read(pblk,&divideBG,2L);
my_read(pblk,&background.active,2L);
if(background.active)
	{
	my_read(pblk,&background.clip,(long)sizeof(Rect));
	my_read(pblk,&background.locate,(long)sizeof(Rect));
	background.mask=loadbitmap(pblk);
	background.fg=loadbitmap(pblk);
	}
/*-------------------------Read sprite data*/
my_read(pblk,&maxsprite,2L);
if(0==(cSprite=(struct sprite*)NewPtr((long)sizeof(struct sprite)*maxsprite)))MemoryErr();
my_read(pblk,&locSprite,2L);
for(i=0;i<maxsprite;i++)
	{
	/*cSprite[i].pict*/
	cSprite[i].fg=loadbitmap(pblk); 
	cSprite[i].mask=loadbitmap(pblk);
	my_read(pblk,&cSprite[i].used,2L);
	my_read(pblk,&cSprite[i].clip,(long)sizeof(Rect));
	my_read(pblk,&cSprite[i].locate,(long)sizeof(Rect));
	}
/*-------------------------Read lSprite data*/
my_read(pblk,&maxSprite,2L);
if(0==(lSprite=(struct oSprite*)NewPtr((long)sizeof(struct oSprite)*maxSprite)))MemoryErr();
my_read(pblk,&anum,2L);
for(i=0;i<maxSprite;i++)
	{
	Rect bounds;
	my_read(pblk,&lSprite[i].size,2L);
	for(j=0;j<lSprite[i].size;j++)
		my_read(pblk,&lSprite[i].object[j],6L);
	my_read(pblk,&bounds,(long)sizeof(Rect));
	/*lSprite[i].bg=NewBitMap(&bounds);*/
	my_read(pblk,&lSprite[i].visible,2L);	/*visible flag*/
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
}
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
unpackanim()
{
int i,j;
/*--------------------------Read background data*/
alocate=0;
unpack(topBG,8L);
unpack(bottomBG,8L);
unpack(&divideBG,2L);
unpack(&background.active,2L);
if(background.active)
	{
	unpack(&background.clip,(long)sizeof(Rect));
	unpack(&background.locate,(long)sizeof(Rect));
	background.mask=unpackbitmap();
	background.fg=unpackbitmap();
	}
/*-------------------------Read sprite data*/
unpack(&maxsprite,2L);
if(0==(cSprite=(struct sprite*)NewPtr((long)sizeof(struct sprite)*maxsprite)))MemoryErr();
unpack(&locSprite,2L);
for(i=0;i<maxsprite;i++)
	{
	/*cSprite[i].pict*/
	cSprite[i].fg=unpackbitmap(); 
	cSprite[i].mask=unpackbitmap();
	unpack(&cSprite[i].used,2L);
	unpack(&cSprite[i].clip,(long)sizeof(Rect));
	unpack(&cSprite[i].locate,(long)sizeof(Rect));
	}
/*-------------------------Read lSprite data*/
unpack(&maxSprite,2L);
if(0==(lSprite=(struct oSprite*)NewPtr((long)sizeof(struct oSprite)*maxSprite)))MemoryErr();
unpack(&anum,2L);
for(i=0;i<maxSprite;i++)
	{
	Rect bounds;
	unpack(&lSprite[i].size,2L);
	for(j=0;j<lSprite[i].size;j++)
		unpack(&lSprite[i].object[j],6L);
	unpack(&bounds,(long)sizeof(Rect));
	/*lSprite[i].bg=NewBitMap(&bounds);*/
	unpack(&lSprite[i].visible,2L);	/*visible flag*/
	unpack(&lSprite[i].current,2L);	/*current visible sprite*/
	unpack(&lSprite[i].xloc,2L);
	unpack(&lSprite[i].yloc,2L);		/*base position of object*/
	unpack(&lSprite[i].acurrent,2L); 	/*animation system current visible sprite*/
	unpack(&lSprite[i].axloc,2L);
	unpack(&lSprite[i].ayloc,2L);		/*animation system base position of object*/
	unpack(&lSprite[i].type,1L);		/*key or object*/
	unpack(&lSprite[i].frozen,1L);
	unpack(&lSprite[i].locked,1L);
	unpack(&lSprite[i].link,2L);
	unpack(&lSprite[i].key,2L);
	unpack(&lSprite[i].lock,2L);
	lSprite[i].visible=FALSE;
	lSprite[i].onoff=TRUE;
	}
}
/*----------------------------------------------------------------------*/
unpack(to,length)
register char *to;
register long length;
{
register long i;

for(i=0;i<length;i++)
	to[i]=adata[i+alocate];
alocate+=length;
}
/*----------------------------------------------------------------------*/
int FindSprite(snum,pr)
int snum;
Rect *pr;
{
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
}
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*int Overlap(i,j)
int i,j;
{
Rect r0,r1,dummy;
int cnum;
int xloc,yloc;

FindSprite(i,&r0);
FindSprite(j,&r1);
return(SectRect(&r0,&r1,&dummy));
}*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
DrawlSprite(snum)
int snum;
{
int i;
int bit=1<<snum;
GrafPtr	savePort;
Rect locate,clip;
int sloc;
int cnum=BMColor[snum+2];

GetPort( &savePort );
SetPort(&metaPort);
if(cnum<0)BackColor((long)-cnum);
else if(cnum>0)RGBBackColor(&cColor[cnum].b);
else
	{
	if(corepower[coreindex])RGBBackColor(&cColor[c_char0+level-1].f);
	else RGBBackColor(&cColor[c_dwall].b);
	}
	
/*save the current background*/
cnum=FindSprite(snum,&locate);
/*if(locate.top<0)
	{
	sloc=locate.top;
	clip.bottom=cSprite[cnum].clip.bottom;
	clip.left=cSprite[cnum].clip.left;
	clip.right=cSprite[cnum].clip.right;
	clip.top=-locate.top;
	locate.top=0;
	CopyBits(*metaPort.portPixMap,lSprite[snum].bg,
		&locate,&clip,
		srcCopy,NIL);
	locate.top=sloc;
	}
else
	{
	CopyBits(*metaPort.portPixMap,lSprite[snum].bg,
		&locate,&cSprite[cnum].clip,
		srcCopy,NIL);
	}*/
SetPort(&metaPort);
ClipRect(&DClip);
CopyBits(cSprite[cnum].mask,
	*metaPort.portPixMap,
	&cSprite[cnum].clip,&locate,
	srcBic,NIL);
CopyBits(cSprite[cnum].fg,
	*metaPort.portPixMap,
	&cSprite[cnum].clip,&locate,
	srcOr,NIL);
ClipRect(&size);
lSprite[snum].visible=TRUE;
ClipRect(&size);
SetPort( savePort );
}
/*----------------------------------------------------------------------*/
/*EraselSprite(snum)
int snum;
{
int j;
GrafPtr	savePort;
Rect locate;
int bit=~(1<<snum);
int cnum;

GetPort( &savePort );
SetPort(&metaPort);
lSprite[snum].visible=FALSE;
cnum=FindSprite(snum,&locate);
ClipRect(&DClip);
CopyBits(lSprite[snum].bg,
	*metaPort.portPixMap,
	&cSprite[cnum].clip,
	&locate,
	srcCopy,NIL);
ClipRect(&size);
SetPort( savePort );
}*/
/*----------------------------------------------------------------------*/
/*EraseTree(snum)
int snum;
{
int i;
	
for(i=(maxSprite-1);i>snum;i--)
	if(lSprite[i].visible&&lSprite[i].onoff)
		if(Overlap(snum,i))
			EraseTree(i);
if(lSprite[snum].visible)if(lSprite[snum].onoff)EraselSprite(snum);
}*/
/*----------------------------------------------------------------------*/
/*DrawTree(snum)
int snum;
{
int i;

for(i=snum;i<maxSprite;i++)if((!lSprite[i].visible) &&lSprite[i].onoff)DrawlSprite(i);
}*/
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int DrawPlane()
{
GrafPtr	savePort;
int i;
struct oSprite *savesprite;
int *savemax;

GetPort( &savePort );
SetPort(&metaPort);
for(i=0;i<maxSprite;i++){lSprite[i].visible=0;}
for(i=0;i<maxSprite;i++)
	{
	if(Button())if(ButtonDown()){SetPort(savePort);return FALSE;}
	if(lSprite[i].onoff)DrawlSprite(i);
	}
SetPort(savePort);
return(TRUE);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int WhichlSprite(p,ploc)
Point *p;
int *ploc;
{
int i;
int num;
GrafPtr temp;
GrafPtr	savePort;
Rect r;
int cnum;

GetPort( &savePort );
if(0==(temp=(GrafPtr)NewPtr((long)sizeof(GrafPort))))MemoryErr();
OpenPort(temp);
*ploc=0;
for(i=(maxSprite)-1;i>=0;i--)
	if(lSprite[i].onoff)
	{
	cnum=FindSprite(i,&r);
	if( p->h>=r.left &&
		p->h<=r.right &&
		p->v>=r.top &&
		p->v<=r.bottom)
		{
		SetPortBits(cSprite[cnum].mask);
		if(GetPixel(p->h-r.left,
					p->v-r.top))
			{
			num=i;
			*ploc=1;
			i = -1;
			}
		}
	}
ClosePort(temp);
DisposPtr(temp);
SetPort(savePort);
return(num);
}
/*----------------------------------------------------------------------*/
ShowIt()
{
int i;
	
for(i=0;i<maxSprite;i++)
	if(lSprite[i].onoff && lSprite[i].type==0 && !lSprite[i].locked)
		{
		if(Button())if(ButtonDown())return;
		/*EraseTree(i);*/
		lSprite[i].current++;
		if(lSprite[i].current==lSprite[i].size)lSprite[i].current=0;
		/*EraseTree(i);*/
		}
DrawAll();
}
/*----------------------------------------------------------------------*/
NoShowIt()
{
int i;

for(i=0;i<maxSprite;i++)
	{
	if(lSprite[i].onoff&&lSprite[i].type==0&&!lSprite[i].locked&&lSprite[i].size>1)
		{
		/*EraseTree(i);*/
		lSprite[i].current++;
		if(lSprite[i].current==lSprite[i].size)lSprite[i].current=0;
		/*EraseTree(i);*/
		}
	}
}
/*----------------------------------------------------------------------*/
int DoIt(p)
Point *p;
{
int num,loc,current;

if(TestButton(p))return(FALSE);
else
	{
	num=WhichlSprite(p,&loc);
	if(loc)
		{
		DolSprite(p,num);
		return(num+1);
		}
	else return(0);
	}
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int ButtonDown()
{
Point pt;
GrafPtr savePort;

GetPort(&savePort);
SetPort(animWindow);
GetMouse(&pt);
SetPort(savePort);
if(pt.v>HEIGHT-BTOP)return(TRUE);
return(FALSE);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int TestButton(p)
Point *p;
{
Point new;
int pressed=FALSE;

if(p->v>HEIGHT-BTOP)
	{
	while(Button())
		{
		GetMouse(&new);
		if(PtInRect(new,&ebutton))
			{
			if(!pressed)
				{
				InvertRoundRect(&ebutton,8,8);
				pressed=TRUE;
				}
			}
		else
			{
			if(pressed)
				{
				InvertRoundRect(&ebutton,8,8);
				pressed=FALSE;
				}
			}
		}
	if(pressed)animnotdone=FALSE;
	return(0);
	}
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int InsideControl(p,num)
Point *p;
int num;
{
GrafPtr temp;
GrafPtr	savePort;
Rect r;
int cnum;
int inside=FALSE;

GetPort( &savePort );
if(0==(temp=(GrafPtr)NewPtr((long)sizeof(GrafPort))))MemoryErr();
OpenPort(temp);
cnum=FindSprite(num,&r);

if( p->h>=r.left &&
	p->h<=r.right &&
	p->v>=r.top &&
	p->v<=r.bottom)
	{
	SetPortBits(cSprite[cnum].mask);
	if(GetPixel(p->h-r.left,p->v-r.top))inside=TRUE;
	}
ClosePort(temp);
DisposPtr(temp);
SetPort(savePort);
return(inside);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int KeylSprite(key,p,ploc)
int key;
Point *p;
int *ploc;
{
int i;
GrafPtr temp;
GrafPtr	savePort;
Rect r;
int cnum;
int num=-1;
GetPort( &savePort );
if(0==(temp=(GrafPtr)NewPtr((long)sizeof(GrafPort))))MemoryErr();
OpenPort(temp);
*ploc=0; 
for(i=(maxSprite)-1;i>=0;i--)
if(key!=i)
if(lSprite[i].lock==lSprite[key].key)
	{
	cnum=FindSprite(i,&r);
	if( p->h>=r.left &&
		p->h<=r.right &&
		p->v>=r.top &&
		p->v<=r.bottom)
		{
		SetPortBits(cSprite[cnum].mask);
		if(GetPixel(p->h-r.left,
					p->v-r.top))
			{
			num=i;
			*ploc=1;
			break;
			}
		}
	}
ClosePort(temp);
DisposPtr(temp);
SetPort(savePort);
return(num);
}
/*----------------------------------------------------------------------*/
DrawBackGround()
{
int i;
GrafPtr	savePort;
Rect r;
int cc;
extern int level;

GetPort( &savePort );
SetPort(&metaPort);
RGBForeColor(&black_Color);
if(BMColor[0]<0)BackColor((long)-BMColor[0]);
else
	{
	if(corepower[coreindex])RGBBackColor(&cColor[c_char0+level-1].f);
	else RGBBackColor(&cColor[c_dwall].b);
	}
r.top=DClip.top;
r.left=DClip.left;
r.right=DClip.right;
r.bottom=divideBG;
FillRect(&r,topBG);
if(corepower[coreindex])RGBBackColor(&cColor[c_lwall].f);
r.top=r.bottom;
r.bottom=DClip.bottom;
FillRect(&r,bottomBG);
MoveTo(DClip.left,divideBG); LineTo(DClip.right,divideBG);
if(corepower[coreindex])
	{
	if(BMColor[1]<0)BackColor((long)-BMColor[1]);
	else RGBBackColor(&cColor[BMColor[1]].b);
	}
if(background.active)
	{
	ClipRect(&DClip);
	CopyBits(background.mask,
		*metaPort.portPixMap,
		&background.clip,&background.locate,
		srcBic,NIL);
	CopyBits(background.fg,
		*metaPort.portPixMap,
		&background.clip,&background.locate,
		srcOr,NIL);
	ClipRect(&size);
	}
RGBBackColor(&white_Color);
SetPort(savePort);
}
/*----------------------------------------------------------------------*/
extern EventRecord key;
extern int Mac512;
extern int keyflag;
WindowPtr whichWindow;
AnimControl(item)
int* item;
{
int gne;
int windowpart;
Point loc; 

*item=0;
gne=WaitNextEvent(everyEvent,&key,0,0L);
windowpart=FindWindow( key.where, &whichWindow );
if(gne)
	switch(key.what)
		{
		case mouseDown:
			switch(windowpart)
				{	
				case inContent:			
					if (whichWindow != FrontWindow())
						DoChimeSound();
					else if(whichWindow==animWindow)
						{SetPort(animWindow); GetMouse(&loc); *item=DoIt(&loc);}
					break;
				case inSysWindow:
					SystemClick(&key,whichWindow);
					break;
				case inDrag:
					DragWindow(whichWindow,key.where,&rScreen);
					break;
				case inGrow:
					break;
				case inGoAway:
					if(TrackGoAway(animWindow,key.where))animnotdone=FALSE;
					break;
				}
			break;
		case keyDown:
		case autoKey: 
			if((key.message & charCodeMask)==13)return(animnotdone=FALSE);
			if(keyflag)
			{
			char	theChar;
			
			theChar = key.message & charCodeMask;
			if ((key.modifiers & cmdKey) == 0) 
			if(theChar>='0'&&theChar<='9')
				*item=1+theChar-'0';
			else switch(theChar)
				{
				case 0x03:
				case 'E':
				case 'e':
					*item=12;
					break;
				case 0x08:
				case 0x1B:
				case 'C':
				case 'c':
					*item=11;
					break;
				}
			}
			break;
		case activateEvt:
			/*doactivate(key.modifiers);*/
			break;
		case updateEvt:
			if((WindowPtr)key.message==animWindow)animupdate();
			else Update((WindowPtr)key.message);
			break;
		}
return(animnotdone);
}
/*----------------------------------------------------------------------*/
ObjectState(num)
int num;
{
num--;
if(num<maxSprite&&num>=0)return(lSprite[num].current+1);
else return(0);
}
/*----------------------------------------------------------------------*/
ObjectRect(num,r)
int num;
Rect *r;
{
num--;
FindSprite(num,r);
}
/*----------------------------------------------------------------------*/
SetObjectState(num,state)
int num,state;
{
num--;
/*EraseTree(num);*/
if(num<maxSprite&&num>=0)lSprite[num].current=state-1;
/*EraseTree(num);*/
/*DrawTree(num);
  DejaDCopy();*/
}
/*----------------------------------------------------------------------*/
SetObjectOnOff(num,state)
int num,state;
{
num--;
if(num<maxSprite&&num>=0)lSprite[num].onoff=state;
}
/*----------------------------------------------------------------------*/
extern int Mac512;
OpenAFile(fname,bmc)
char *fname;
int *bmc;
{
OSErr err;
int vnum;
char str[255];
int i,j;
IOParam pblk;
FileParam fblk;
char filename[255];

BMColor=bmc;
/*KillTable();*/
keyflag=FALSE;
AUnLoad();
Catenate(filename,"\p:CData:",fname);
pblk.qLink=0;
pblk.qType=0;
pblk.ioTrap=0;
pblk.ioCmdAddr=0;
pblk.ioCompletion=0;
pblk.ioResult=0;
pblk.ioRefNum=0;
pblk.ioBuffer=0;
pblk.ioReqCount=0;
pblk.ioActCount=0;
pblk.ioPosMode=0;
pblk.ioPosOffset=0;
pblk.ioNamePtr = (StringPtr)0;

fblk.ioNamePtr = pblk.ioNamePtr = (StringPtr)filename;
err=GetVol(str,&vnum);
fblk.ioVRefNum=pblk.ioVRefNum=vnum;
fblk.ioFVersNum=pblk.ioVersNum=0;
pblk.ioPermssn=fsRdPerm;
pblk.ioMisc=(Ptr)NIL;
fblk.ioFDirIndex=0;
fblk.ioCompletion=0;
err=PBGetFInfo(&fblk,FALSE);
err=PBOpen(&pblk,FALSE);
if(err)
	{
	DoChimeSound();
	Inform("\pError in file open!");
	ExitToShell();
	}
if(Mac512)readanim(&pblk);/*read and unpack the file at the same time*/
else/*read the entire file into memory then unpack it*/
	{
	if(0==(adata=NewPtr(fblk.ioFlLgLen)))MemoryErr();/*size of entire file*/
	if(adata!=0)
		{
		my_read(&pblk,adata,fblk.ioFlLgLen);
		unpackanim();
		DisposPtr(adata);
		}
	else readanim(&pblk);
	}
err=PBClose(&pblk,FALSE);
if(err)
	{
	DoChimeSound();
	Inform("\pError in file close!");
	ExitToShell();
	}
InitDejaVu();
SetCursor(&arrow);
return(TRUE);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
DolSprite(p,num)
Point *p;
int num;
{
Rect r,dummy;
Point new,old;
int xloc,yloc;
int savenum;
int i,knum,oldknum=-1;
int loc;

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
					NoShowIt();
					/*EraseTree(num);*/
					lSprite[num].current--;
					if(lSprite[num].key)
					for(i=0;i<maxSprite;i++)if(i!=num)
						if(lSprite[i].lock==lSprite[num].key)
							{
							/*EraseTree(i);*/
							lSprite[i].current=lSprite[num].current;
							if(lSprite[i].current>=lSprite[i].size)
								lSprite[i].current=lSprite[i].size-1;
							/*EraseTree(i);*/
							}
					/*EraseTree(num);*/
					DrawAll();
					}
				else 
				while(lSprite[num].current<lSprite[num].size-1)
					{
					NoShowIt();
					/*EraseTree(num);*/
					lSprite[num].current++;
					if(lSprite[num].key)
					for(i=0;i<maxSprite;i++)if(i!=num)
						if(lSprite[i].lock==lSprite[num].key)
							{
							/*EraseTree(i);*/
							lSprite[i].current=lSprite[num].current;
							if(lSprite[i].current>=lSprite[i].size)
								lSprite[i].current=lSprite[i].size-1;
							/*EraseTree(i);*/
							}
					/*EraseTree(num);*/
					DrawAll();
					}
				}
			}
		else MoveObject(p,num,lSprite[num].key);/*this is a key - animate always*/
		#ifdef JOEBOB
			/*{
			while(Button())
				{
				GetMouse(&new);
				NoShowIt();
				if(new.v>0&&new.v<(HEIGHT-BTOP)&&new.h>0&&new.h<WIDTH)
					{
					/*EraseTree(num);*/
					lSprite[num].current++;
					if(lSprite[num].current==lSprite[num].size)lSprite[num].current=0;
					lSprite[num].xloc+=new.h-old.h;
					lSprite[num].yloc+=new.v-old.v;
					/*EraseTree(num);*/
					if(lSprite[num].key)
						{
						knum=KeylSprite(num,&new,&loc);
						if(loc)
						if(knum!=oldknum)
							{
							if(lSprite[knum].current==1)
								{
								NoShowIt();
								/*EraseTree(knum);*/
								lSprite[knum].current--;
								/*EraseTree(knum);*/
								/*EraseTree(num);*/
								lSprite[num].current++;
								if(lSprite[num].current==lSprite[num].size)
									lSprite[num].current=0;
								/*EraseTree(num);*/
								/*DrawAll();*/
								}
							else if(lSprite[knum].current==0)
								{
								NoShowIt();
								/*EraseTree(knum);*/
								lSprite[knum].current++;
								/*EraseTree(knum);
								EraseTree(num);*/
								lSprite[num].current++;
								if(lSprite[num].current==lSprite[num].size)
									lSprite[num].current=0;
								/*EraseTree(num);*/
								/*DrawAll();*/
								}
							oldknum=knum;
							}
						}
					old.h=new.h;
					old.v=new.v;
					}
				DrawAll();
				}
			NoShowIt();
			/*EraseTree(num);*/
			lSprite[num].current=0;
			/*EraseTree(num);*/
			DrawAll();
			}*/
		#endif
		break;
	case 2:/*container and object*/
		if(lSprite[num].frozen)
			{
			if(!lSprite[num].locked)
				/*this is a container--only can open or close*/
				{
				if(lSprite[num].current) while(lSprite[num].current>0)
					{
					NoShowIt();
					/*EraseTree(num);*/
					lSprite[num].current--;
					/*EraseTree(num);*/
					DrawAll();
					}
				else while(lSprite[num].current<lSprite[num].size-1)
					{
					NoShowIt();
					/*EraseTree(num);*/
					lSprite[num].current++;
					/*EraseTree(num);*/
					DrawAll();
					}
				}
			else
				/*this is a container--only can open or close*/
				{
				if(lSprite[num].current>1) while(lSprite[num].current>0)
					{
					NoShowIt();
					/*EraseTree(num);*/
					lSprite[num].current--;
					/*EraseTree(num);*/
					DrawAll();
					}
				else if(lSprite[num].current==1)while(lSprite[num].current<lSprite[num].size-1)
					{
					NoShowIt();
					/*EraseTree(num);*/
					lSprite[num].current++;
					/*EraseTree(num);*/
					DrawAll();
					}
				}
			}
		else while(Button())MoveObject(p,num,FALSE);/*this is an object - only allow the user to move it*/
#ifdef JOEBOB
		/*	{
			GetMouse(&new);
			NoShowIt();
			if(new.v>0&&new.v<(HEIGHT-BTOP)&&new.h>0&&new.h<WIDTH)
				{
				/*EraseTree(num);*/
				lSprite[num].xloc+=new.h-old.h;
				lSprite[num].yloc+=new.v-old.v;
				/*EraseTree(num);*/
				if(lSprite[num].link)
					for(i=0;i<maxSprite;i++)
						{
						if(lSprite[i].link==lSprite[num].link && num!=i)
							{
							/*EraseTree(i);*/
							lSprite[i].xloc+=new.h-old.h;
							lSprite[i].yloc+=new.v-old.v;
							/*EraseTree(i);*/
							}
						}
				old.h=new.h;
				old.v=new.v; 
				}
			DrawAll();
			}*/
#endif
		break;
	}
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
MoveObject(p,num,key)
Point *p;
int num;
int key;
{
int i,knum,oldknum=-1;
Point new,old;
int xloc,yloc;
int loc;
int link[16];
int linknum=0;

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
/*for(i=0;i<linknum;i++)EraseTree(link[i]);*/
for(i=0;i<linknum;i++)SetObjectOnOff(link[i]+1,FALSE);
DrawSome();
for(i=0;i<linknum;i++)DrawlSprite(link[i]);
DejaDCopy();
while(Button())/*this is a display - animate always*/
	{
	GetMouse(&new);
	/*for(i=linknum-1;i>=0;i--)EraselSprite(link[i]);*/
	if(lSprite[num].type!=2)
		{
		lSprite[num].current++;
		if(lSprite[num].current==lSprite[num].size)lSprite[num].current=0;
		}
	NoShowIt();
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
					NoShowIt();
					/*EraseTree(knum);*/
					lSprite[knum].current--;
					/*EraseTree(knum);
					EraseTree(num);*/
					lSprite[num].current++;
					if(lSprite[num].current==lSprite[num].size)
						lSprite[num].current=0;
					/*EraseTree(num);*/
					DrawAll();
					}
				else if(lSprite[knum].current==0)
					{
					NoShowIt();
					/*EraseTree(knum);*/
					lSprite[knum].current++;
					/*EraseTree(knum);
					EraseTree(num);*/
					lSprite[num].current++;
					if(lSprite[num].current==lSprite[num].size)
						lSprite[num].current=0;
					/*EraseTree(num);*/
					DrawAll();
					}
				oldknum=knum;
				}
			}
		old.h=new.h;
		old.v=new.v; 
		}
	DrawSome();
	for(i=0;i<linknum;i++)DrawlSprite(link[i]);
	DejaDCopy();
	}
/*for(i=linknum-1;i>=0;i--)EraselSprite(link[i]);
EraseTree(num);/*reset key to original state*/
if(lSprite[num].type!=2)lSprite[num].current=0;
for(i=0;i<linknum;i++)SetObjectOnOff(link[i]+1,TRUE);
DrawAll();
}
