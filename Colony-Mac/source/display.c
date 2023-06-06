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
 * Display.c
 *---------------------------------------------------------------------
 * PixMapHandle ANewPixMap(cr)
 * 		Rect *cr;
 * KillPixMap(offScreen)
 *		PixMap *offScreen;
 * BitMap *NewBitMap(cr)
 * 		Rect *cr;
 * KillBitMap(offScreen)
 *		BitMap *offScreen;
 * MakeGrafPort(pr,meta,bm)
 *		Rect *pr;
 * 		GrafPtr meta;
 *		PixMap **bm;
 * KillGrafPort(meta,bm)
 * 		PixMap* bm;
 * 		GrafPtr meta;
 * initBitMap()
 * Display()
 * CopyRect(r1,r2)
 * 		Rect *r1,*r2;
 * drawmap()
 * Terminate(blowup)
 *  	int blowup;
 *---------------------------------------------------------------------
 */
#define EXT extern 
#include "cgamedefs.h"
#include "colordef.h"
PixMapHandle offScreen;	/*off screen bit map to write to */
CGrafPort metaPort;
/*---------------------------------------------------------------------
 * ANewPixMap()
 *---------------------------------------------------------------------
 */
PixMapHandle ANewPixMap(cr)
Rect *cr;
{
PixMapHandle offScreen;
int offRowBytes;	/*number of bytes in one row*/
Size sizeOfOff;		/*size in bytes of the off screen bit map*/
Rect brect;
QDPtr pixMap=0;

CopyRect(cr,&brect);
OffsetRect(&brect,-cr->left,-cr->top);
offRowBytes = (((int)(((theDepth*(cr->right-cr->left))+15)>>4)))<<1;
sizeOfOff = (long)(offRowBytes)*(cr->bottom-cr->top);
if(0==(offScreen=NewPixMap()))MemoryErr();
if(0==(pixMap = (QDPtr)NewPtr((long)sizeOfOff)))MemoryErr();
(*offScreen)->baseAddr = pixMap;
(*offScreen)->rowBytes = offRowBytes | 0x8000;
(*offScreen)->bounds = brect;
SetColorTable(offScreen);
return(offScreen);
}
/*---------------------------------------------------------------------
 * SetColorTable(offScreen)
 *---------------------------------------------------------------------
 */
SetColorTable(offScreen)
PixMapHandle offScreen;
{
CTabHandle ourCMHandle;
GDHandle theDevice;

theDevice=GetGDevice();
ourCMHandle=(**(**theDevice).gdPMap).pmTable;
HandToHand((Handle)&ourCMHandle);
(*offScreen)->pmTable=ourCMHandle;
}

NewColorTable(offScreen)
PixMapHandle offScreen;
{
DisposHandle((*offScreen)->pmTable);
SetColorTable(offScreen);
}

/*---------------------------------------------------------------------
 * NewBitMap()
 *---------------------------------------------------------------------
 */
BitMap *NewBitMap(cr)
Rect *cr;
{
BitMap *offScreen;
int offRowBytes;	/*number of bytes in one row*/
Size sizeOfOff;		/*size in bytes of the off screen bit map*/
Rect brect;

CopyRect(cr,&brect);
OffsetRect(&brect,-cr->left,-cr->top);
offRowBytes = (((int)(((cr->right-cr->left)+15)/16)))*2;
sizeOfOff = (offRowBytes)*(cr->bottom-cr->top);

if(0==(offScreen=(BitMap*)NewPtr((long)sizeof(BitMap))))MemoryErr();
if(0==(offScreen->baseAddr = (QDPtr)NewPtr((long)sizeOfOff)))MemoryErr();
offScreen->rowBytes = offRowBytes;
offScreen->bounds.top = brect.top;
offScreen->bounds.left = brect.left;
offScreen->bounds.bottom = brect.bottom;
offScreen->bounds.right = brect.right;
return(offScreen);
}
/*---------------------------------------------------------------------
 * KillBitMap()
 *---------------------------------------------------------------------
 */
KillBitMap(offScreen)
BitMap *offScreen;
{
DisposPtr(offScreen->baseAddr);
DisposPtr(offScreen);
}
/*---------------------------------------------------------------------
 * KillPixMap()
 *---------------------------------------------------------------------
 */
KillPixMap(offScreen)
PixMapHandle offScreen;
{
DisposHandle((*offScreen)->pmTable);
DisposPtr((*offScreen)->baseAddr);
DisposPixMap(offScreen);
}
/*---------------------------------------------------------------------
 * Rect r;
 * GrafPort meta;
 * MakeGrafPort(&r,&meta)
 * Set up the offscreen bit map for use in drawing the sensor.
 *---------------------------------------------------------------------
 */
MakeGrafPort(pr,meta,bm)
Rect *pr;
CGrafPtr meta;
BitMap* bm;
{
bm=NewBitMap(pr);
OpenPort(meta);
SetPortBits(bm);
SetOrigin(0,0);
PenMode(patCopy);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
KillGrafPort(meta,offScreen)
PixMap* offScreen;
CGrafPtr meta;
{
KillPixMap(offScreen);
ClosePort(meta);
}
/*---------------------------------------------------------------------
 * initPixMap()
 * Set up the offscreen bit map for use in drawing the sensor.
 *---------------------------------------------------------------------
 */
initPixMap()
{
Rect r;
offScreen=ANewPixMap(&screenR);
OpenCPort(&metaPort);
SetPortPix(offScreen);
SetPort(&metaPort);
SetOrigin(0,0);
r.top=0;
r.left=0;
r.right=screenR.right-screenR.left;
r.bottom=screenR.bottom-screenR.top;
FillRect(&r,white);
SetPort(theWindow);
}

ResetOffScreen()
{
KillGrafPort(&metaPort,offScreen);
initPixMap();
}
/*---------------------------------------------------------------------
 * Display()
 *---------------------------------------------------------------------
 */
extern int maxrobot;
#define FCOUNT 32
int foodcount=FCOUNT;
RGBColor wallColor,lineColor;
RGBColor black_Color={0,0,0};
RGBColor white_Color={0xFFFF,0xFFFF,0xFFFF};
Display()
{
long cnt;
int tx2,tx1;
Rect r;
int lvl;

SetPort(&metaPort);
foodcount--;
if(foodcount==0)
	{
	SetPower(-level*armor2,-level*(armor2+weapons2),-level*weapons2);
	foodcount=FCOUNT;
	}
switch(game)
	{
	case BATTLE:
		Battlebackdrop();
		BattlePyramid();
		break;
	case COLONY:
		PenMode(patCopy);
		if(corepower[coreindex])
			{
			wallColor.blue=	cColor[c_lwall].b.blue;
			wallColor.green=cColor[c_lwall].b.green;
			wallColor.red=	cColor[c_lwall].b.red;
			lineColor.blue=0;
			lineColor.green=0;
			lineColor.red=0;
			}
		else 
			{
			wallColor.blue=	cColor[c_dwall].b.blue;
			wallColor.green=cColor[c_dwall].b.green;
			wallColor.red=	cColor[c_dwall].b.red;
			lineColor.blue=	cColor[c_dwall].f.blue;
			lineColor.green=cColor[c_dwall].f.green;
			lineColor.red=	cColor[c_dwall].f.red;
			}
		RGBBackColor(&wallColor);
		RGBForeColor(&lineColor);
		if(polyfill&&corepower[coreindex])
			{
			r.top=Clip.top;
			r.left=Clip.left;
			r.right=Clip.right;
			r.bottom=centerY;
			EraseRect(&r);
			RGBBackColor(&cColor[c_lwall].f);
			r.top=centerY;
			r.bottom=Clip.bottom;
			EraseRect(&r);
			wallColor=cColor[c_char0+level-1].f;
			}
		else EraseRect(&Clip);
		maxrobot=0;
		corridor();
		MakeRobot();
		ClipRect(&Clip);
		break;
	}
if(fl)
	{
	if(game==BATTLE)PenPat(white);
	RGBForeColor(&black_Color);
	PenSize(2,2);
	tx2=centerX>>2;
	tx1=centerX>>1;
	MoveTo(tx2,0);
	LineTo(tx1,Height);
	MoveTo(Width-tx2,0);
	LineTo(Width-tx1,Height);
	PenSize(1,1);
	PenPat(black);
	if(fl==1){RGBBackColor(&white_Color); PlotIcon(&fl_rect,fl_icon[0]);}
	else switch(carrytype)
		{
		case BOX1:
		case BOX2: RGBBackColor(&cColor[c_box1].b); PlotIcon(&fl_rect,fl_icon[1]);break;
		case CRYO: RGBBackColor(&cColor[c_cryo].b); PlotIcon(&fl_rect,fl_icon[2]);break;
		case TELEPORT: RGBBackColor(&cColor[c_teleport].b); PlotIcon(&fl_rect,fl_icon[3]);break;
		case REACTOR: RGBBackColor(&cColor[c_ccore].b); PlotIcon(&fl_rect,fl_icon[4]);break;
		}
	}
else if(crosshair)
	{
	PenMode(patCopy);
	PenPat(black);
	if(weapons&&!cshoot)
		{
		if(insight)
			{
			MoveTo(centerX-20,centerY-20);
			LineTo(centerX-30,centerY-30);
			LineTo(centerX-30,centerY+30);
			LineTo(centerX-20,centerY+20);
			MoveTo(centerX+20,centerY-20);
			LineTo(centerX+30,centerY-30);
			LineTo(centerX+30,centerY+30);
			LineTo(centerX+20,centerY+20);
			insight=FALSE;
			}
		else
			{
			MoveTo(centerX-20,centerY-30);
			LineTo(centerX-30,centerY-30);
			LineTo(centerX-30,centerY+30);
			LineTo(centerX-20,centerY+30);
			MoveTo(centerX+20,centerY-30);
			LineTo(centerX+30,centerY-30);
			LineTo(centerX+30,centerY+30);
			LineTo(centerX+20,centerY+30);
			}
		PenMode(patCopy);
		}
	else
		{
		MoveTo(centerX-20,centerY);
		LineTo(centerX+20,centerY);
		MoveTo(centerX,centerY-20);
		LineTo(centerX,centerY+20);
		}
	}
DoCompass(0);
if(Me.look!=Me.ang)
	{
	Me.look=Me.ang;
	change=1;
	}
SetPort(theWindow);

if(fadein){fadein--;}
CopyBits(*metaPort.portPixMap,
	&theWindow->portBits,
	&Clip,
	&Clip,srcCopy,NIL);
if(game==COLONY)
	{
	CCenter();
	if(doorsound)
		{DoDoorSound();doorsound=FALSE;}
	}
}
/*---------------------------------------------------------------------
 * CopyRect()
 *---------------------------------------------------------------------
 */
CopyRect(r1,r2)
Rect *r1,*r2;
{
r2->top=r1->top;
r2->bottom=r1->bottom;
r2->left=r1->left;
r2->right=r1->right;
}
/*----------------------------------------------------------------------
 * drawmap() creates a 2-dimensional map for the developer. This will
 * not be in the final product.
 *----------------------------------------------------------------------
 */
#if 0
#define CSIZE 6
#define CSIZE2 3
#define TSIZE 280
drawmap()
{
int xx,yy;
int i,j,k,o;

PenMode(patXor);
for(i=1;i<=maxrob;i++)
	if(Object[i].alive)
		{
		o=Object[i].type;
		if(o<=4)
			{
			MoveTo(10+i*CSIZE,4);
			LineTo(10+i*CSIZE,8);
			MoveTo(8+i*CSIZE,6);
			LineTo(12+i*CSIZE,6);
			}
		else if(o==DRONE||o==SOLDIER)
			{
			MoveTo(8+i*CSIZE,4);
			LineTo(12+i*CSIZE,8);
			MoveTo(12+i*CSIZE,4);
			LineTo(8+i*CSIZE,8);
			}
		else if(o==QUEEN||o==SNOOP)
			{
			MoveTo(8+i*CSIZE,4);
			LineTo(12+i*CSIZE,4);
			LineTo(12+i*CSIZE,8);
			LineTo(8+i*CSIZE,8);
			LineTo(8+i*CSIZE,4);
			}
		else
			{
			MoveTo(10+i*CSIZE,6);
			LineTo(10+i*CSIZE,6);
			}
		}
for(i=0;i<20;i++)
	for(j=0;j<10;j++)
		{
		k=i*10+j+maxrob+1;
		if(k<=maxobjects)
		if(Object[k].alive)
			{
			MoveTo(250+i*4,10+j*4);
			LineTo(250+i*4,10+j*4);
			}
		}
xx=(Me.xloc*(long)CSIZE)>>8;
yy=(Me.yloc*(long)CSIZE)>>8;
MoveTo(xx-3,TSIZE-yy);
LineTo(xx,TSIZE-(yy-3));
LineTo(xx+3,TSIZE-yy);
LineTo(xx,TSIZE-(yy+3));
LineTo(xx-3,TSIZE-yy);
MoveTo(xx,TSIZE-yy);
LineTo(xx+(cost[Me.ang]>>5),TSIZE-(yy+(sint[Me.ang]>>5)));
for(i=0;i<32;i++)
	for(j=0;j<32;j++)
		{
		/*switch(dirXY[i][j])
			{
			case 0:
				break;
			case 1:
				MoveTo(i*CSIZE+CSIZE2,(TSIZE)-(j*CSIZE+CSIZE2));
				LineTo(i*CSIZE+CSIZE2,(TSIZE-3)-(j*CSIZE+CSIZE2));
				break;
			case 2:
				MoveTo(i*CSIZE+CSIZE2,(TSIZE)-(j*CSIZE+CSIZE2));
				LineTo(i*CSIZE+3+CSIZE2,(TSIZE-3)-(j*CSIZE+CSIZE2));
				break;
			case 3:
				MoveTo(i*CSIZE+CSIZE2,(TSIZE)-(j*CSIZE+CSIZE2));
				LineTo(i*CSIZE+3+CSIZE2,(TSIZE)-(j*CSIZE+CSIZE2));
				break;
			case 4:
				MoveTo(i*CSIZE+CSIZE2,(TSIZE)-(j*CSIZE+CSIZE2));
				LineTo(i*CSIZE+3+CSIZE2,(TSIZE+3)-(j*CSIZE+CSIZE2));
				break;
			case 5:
				MoveTo(i*CSIZE+CSIZE2,(TSIZE)-(j*CSIZE+CSIZE2));
				LineTo(i*CSIZE+CSIZE2,(TSIZE+3)-(j*CSIZE+CSIZE2));
				break;
			case 6:
				MoveTo(i*CSIZE+CSIZE2,(TSIZE)-(j*CSIZE+CSIZE2));
				LineTo(i*CSIZE-3+CSIZE2,(TSIZE+3)-(j*CSIZE+CSIZE2));
				break;
			case 7:
				MoveTo(i*CSIZE+CSIZE2,(TSIZE)-(j*CSIZE+CSIZE2));
				LineTo(i*CSIZE-3+CSIZE2,(TSIZE)-(j*CSIZE+CSIZE2));
				break;
			case 8:
				MoveTo(i*CSIZE+CSIZE2,(TSIZE)-(j*CSIZE+CSIZE2));
				LineTo(i*CSIZE-3+CSIZE2,(TSIZE-3)-(j*CSIZE+CSIZE2));
				break;
			}*/
		if(Wall[i][j]&1)
			{
			MoveTo(i*CSIZE,TSIZE-j*CSIZE);
			LineTo((i+1)*CSIZE,TSIZE-j*CSIZE);
			}
		if(Wall[i][j]&2)
			{
			MoveTo(i*CSIZE,TSIZE-j*CSIZE);
			LineTo(i*CSIZE,TSIZE-(1+j)*CSIZE);
			}
		if(robotarray[i][j]&&robotarray[i][j]!=MENUM)
			{
			if(Object[robotarray[i][j]].type==QUEEN)
				{
				MoveTo(i*CSIZE+CSIZE2-1,TSIZE-(j*CSIZE+CSIZE2)-1);
				LineTo(i*CSIZE+CSIZE2+1,TSIZE-(j*CSIZE+CSIZE2)-1);
				MoveTo(i*CSIZE+CSIZE2+1,TSIZE-(j*CSIZE+CSIZE2)+1);
				LineTo(i*CSIZE+CSIZE2-1,TSIZE-(j*CSIZE+CSIZE2)+1);
				LineTo(i*CSIZE+CSIZE2-1,TSIZE-(j*CSIZE+CSIZE2)-1);
				}
			else if(Object[robotarray[i][j]].type==SNOOP)
				{
				xx=(Object[robotarray[i][j]].where.xloc*(long)CSIZE)>>8;
				yy=(Object[robotarray[i][j]].where.yloc*(long)CSIZE)>>8;
				MoveTo(xx-3,TSIZE-yy);
				LineTo(xx,TSIZE-(yy-3));
				LineTo(xx+3,TSIZE-yy);
				LineTo(xx,TSIZE-(yy+3));
				LineTo(xx-3,TSIZE-yy);
				MoveTo(xx,TSIZE-yy);
				LineTo(xx+(cost[Object[robotarray[i][j]].where.ang]>>5),
					TSIZE-(yy+(sint[Object[robotarray[i][j]].where.ang]>>5)));
				}
			else if(Object[robotarray[i][j]].type==DRONE ||Object[robotarray[i][j]].type==SOLDIER )
				{
				MoveTo(i*CSIZE+CSIZE2-1,TSIZE-(j*CSIZE+CSIZE2)-1);
				LineTo(i*CSIZE+CSIZE2+1,TSIZE-(j*CSIZE+CSIZE2)+1);
				MoveTo(i*CSIZE+CSIZE2-1,TSIZE-(j*CSIZE+CSIZE2)+1);
				LineTo(i*CSIZE+CSIZE2+1,TSIZE-(j*CSIZE+CSIZE2)-1);
				}
			else
				{
				MoveTo(i*CSIZE+CSIZE2-1,TSIZE-(j*CSIZE+CSIZE2));
				LineTo(i*CSIZE+CSIZE2+1,TSIZE-(j*CSIZE+CSIZE2));
				MoveTo(i*CSIZE+CSIZE2,TSIZE-(j*CSIZE+CSIZE2)-1);
				LineTo(i*CSIZE+CSIZE2,TSIZE-(j*CSIZE+CSIZE2)+1);
				}
			}
		if(foodarray[i][j])
			{
			MoveTo(i*CSIZE+CSIZE2,TSIZE-(j*CSIZE+CSIZE2));
			LineTo(i*CSIZE+CSIZE2,TSIZE-(j*CSIZE+CSIZE2));
			}
		}
PenMode(patCopy);
}
#endif
/*----------------------------------------------------------------------*/
extern int cchange;
Terminate(blowup)
int blowup;
{
SetPort(theWindow);
ClipRect(&Clip);
FillRect(&Clip,black);
while(!SoundDone());
if(blowup)
	{
	if(!soundon)
		{
		int i;
		for(i=0;i<16;i++)InvertRect(&Clip);
		}
	else
		{
		DoExplodeSound();
		while(!SoundDone())InvertRect(&Clip);
		}
	}
else DoOuchSound();
while(!SoundDone())InvertRect(&Clip);
EndGame(FALSE);
cchange=TRUE;
}
