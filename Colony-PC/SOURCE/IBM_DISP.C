/* #define IBM_NewBitMap    /*	*/
/* #define IBM_KillBitMap /*	*/
/* #define IBM_initBitMap   /*	*/
/* #define IBM_Display	    /*	*/
/* #define IBM_Terminate   */
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
 * Display.c
 *---------------------------------------------------------------------
 * BitMap *NewBitMap(cr)
 * 		Rect *cr;
 * KillBitMap(offScreen)
 *		BitMap *offScreen;
 * initBitMap()
 * Display()
 * Terminate(blowup)
 *  	int blowup;
 *---------------------------------------------------------------------
 */
#define EXT extern 
#include "gamedefs.h"

/*  BitMap *offScreen;	    /*off screen bit map to write to */
/*  GrafPort metaPort;	*/
/*---------------------------------------------------------------------
 * NewBitMap()
 *---------------------------------------------------------------------
 */
BitMap far *NewBitMap(cr)
Rect *cr;
{
#if !defined(IBM_NewBitMap)
int i, j;
BitMap *offScreen;
int pxWidth,pxHeight;

pxWidth=1+cr->right - cr->left;
pxHeight=1+cr->bottom - cr->top;
offScreen = (BitMap *)malloc( sizeof(BitMap) );
if ( offScreen == NULL )MemoryErr();
(*offScreen) = *(scrport->portBMap);
offScreen->devClass    = scrport->portBMap->devClass;
offScreen->devType     =0;     /* scrport->portBMap->devType;  */
offScreen->pixWidth    =pxWidth;
offScreen->pixHeight   =pxHeight;
offScreen->pixResX     =scrport->portBMap->pixResX;
offScreen->pixResY     =scrport->portBMap->pixResY;
offScreen->pixBits     =scrport->portBMap->pixBits;
offScreen->pixPlanes   =scrport->portBMap->pixPlanes;
offScreen->rowBytes    =(pxWidth*offScreen->pixBits+7 )/8 ;

for (i=0; i<offScreen->pixPlanes; i++)
    {
    offScreen->mapTable[i] =
		(rlmap *)malloc((sizeof(char *))*offScreen->pixHeight);
    if ( offScreen->mapTable[i] == NULL )MemoryErr();

    offScreen->mapTable[i]->rowTable[0] =
		(char *)malloc((size_t)offScreen->rowBytes*pxHeight);
    if ( offScreen->mapTable[i]->rowTable[0] == NULL )MemoryErr();
/*
    for (j=0; j<offScreen->pixHeight ;j++)
	{
	offScreen->mapTable[i]->rowTable[j] =
	    (char far *)_fmalloc((size_t)offScreen->rowBytes);
	if ( offScreen->mapTable[i]->rowTable[j] == NULL )
	    { fputs("memory allocation error3\n", stderr); return NULL; }
	}
*/

    }
InitRowTable(offScreen, 0, 0, 0);     /*  */
return(offScreen);
#endif
}
/*---------------------------------------------------------------------
 * KillBitMap()
 *---------------------------------------------------------------------
 */
KillBitMap(offScreen)
BitMap far *offScreen;
{
#if !defined(IBM_NewBitMap)
int i, j;

for (i=0; i<offScreen->pixPlanes; i++)
    {
    _ffree(offScreen->mapTable[i]->rowTable[0]);
	_ffree(offScreen->mapTable[i]);
	}
_ffree(offScreen);
#endif
}
/*---------------------------------------------------------------------
 * Display()
 *---------------------------------------------------------------------
 */
char *fltext[]={
	"EMPTY",
	 "BOX",
	"CRYO",
	"TELEPORT",
	"REACTOR"};
int showDashBoard= True;
int drewDashBoard= False;
extern int maxrobot;
#define FCOUNT 32
Display()
{
#if !defined(IBM_Display)
long cnt;
int tx2,tx1;
Rect r;
int pix_per_Finch_x, pix_per_Finch_y;
int i,fnum;
  
SetPort(metaPnt);
PenMode(zREPz);
PenPattern(1);		    /* bits on */
ClipRect(&screenR);
switch(game)
	{
	case BATTLE:
	    PenColor(realcolor[vWHITE]);
	    Battlebackdrop();
	    BattlePyramid();
	    if (MonoCrome){
			color_cursor=realcolor[vWHITE];
			PenColor(realcolor[vWHITE]);
			}
		else {
			color_cursor=realcolor[vLTRED];
			PenColor(realcolor[vBLUE]);
			}
	    FrameRect(&screenR);
	    break;
	case COLONY:
	    if(corepower[coreindex])
			{
			color_wall=vwall_Light;
			color_cursor=realcolor[vBLACK];
			if(fadein)
				{
				BackColor(realcolor[vBLACK]);
				PenColor(realcolor[vWHITE]);
				PenPattern(fadein+2);
				PaintRect(&screenR);
				PenPattern(1);
				fadein--;
				}
			else
				{
				BackColor(realcolor[vWHITE]);
				PenColor(realcolor[vBLACK]);
				EraseRect(&screenR);
				}
			}
	    else
			{
			color_wall=realcolor[vINTWHITE];
			color_cursor=realcolor[vWHITE];
			if(fadein)
				{
				PenColor(realcolor[vBLACK]);
				BackColor(realcolor[vWHITE]);
				PenPattern(fadein+2);
				PaintRect(&screenR);
				PenPattern(1);
				fadein--;
				}
			else
				{
				PenColor(realcolor[vWHITE]);
				BackColor(realcolor[vBLACK]);
				EraseRect(&screenR);
				}
			}
	    maxrobot=0;

	    PenColor(color_wall);
	    corridor();
	    PenColor(realcolor[vRED]);
	    MakeRobot();
	    ClipRect(&screenR);
	    if(MonoCrome)PenColor(realcolor[vWHITE]);
		else PenColor(realcolor[vBLUE]);
		PenMode(zREPz);
	    FrameRect(&screenR);
	    break;
	}
PenColor(color_cursor);

if(fl)
	{
	if(game==BATTLE)PenPattern(1);	    /* white); */
	PenSize(2,2);
	tx2=(centerX-screenR.left)>>2;
	tx1=(centerX-screenR.left)>>1;
	MoveTo(screenR.left+tx2,0);
	LineTo(screenR.left+tx1,Height);
	MoveTo(screenR.right-tx2,0);
	LineTo(screenR.right-tx1,Height);
	PenSize(1,1);
	PenPattern(1);	    /* black); */
	if(fl==1)fnum=0;
	else switch(carrytype)
	    {
	    case BOX1:
	    case BOX2: fnum=1;	break;
		case CRYO: fnum=2;  break;
	    case TELEPORT: fnum=3; break;
	    case REACTOR: fnum=4; break;
	    }
	PenColor(realcolor[vBLACK]);
	BackColor(realcolor[vINTWHITE]);
	TextAlign(alignCenter,alignMiddle);
	i=4+StringWidth(fltext[fnum])/2;
	r.bottom=screenR.bottom-1;
	r.top=screenR.bottom-15;
	r.left=centerX-i;
	r.right=centerX+i;
	EraseRect(&r);
	FrameRect(&r);
	MoveTo(centerX,screenR.bottom-8);
	DrawString(fltext[fnum]);
	}
else if(crosshair)
	{
	if(weapons)
	    {
		pix_per_Finch_x= (pix_per_Qinch_x*3)>>1;
		pix_per_Finch_y= (pix_per_Qinch_y*3)>>1;
	    if(insight)
			{
			MoveTo(centerX-pix_per_Qinch_x,centerY-pix_per_Qinch_y);
			LineTo(centerX-pix_per_Finch_x,centerY-pix_per_Finch_y);
			LineTo(centerX-pix_per_Finch_x,centerY+pix_per_Finch_y);
			LineTo(centerX-pix_per_Qinch_x,centerY+pix_per_Qinch_y);
			MoveTo(centerX+pix_per_Qinch_x,centerY-pix_per_Qinch_y);
			LineTo(centerX+pix_per_Finch_x,centerY-pix_per_Finch_y);
			LineTo(centerX+pix_per_Finch_x,centerY+pix_per_Finch_y);
			LineTo(centerX+pix_per_Qinch_x,centerY+pix_per_Qinch_y);
	        insight=FALSE;
	        }
	    else
	        {
			MoveTo(centerX-pix_per_Qinch_x,centerY-pix_per_Finch_y);
			LineTo(centerX-pix_per_Finch_x,centerY-pix_per_Finch_y);
			LineTo(centerX-pix_per_Finch_x,centerY+pix_per_Finch_y);
			LineTo(centerX-pix_per_Qinch_x,centerY+pix_per_Finch_y);
			MoveTo(centerX+pix_per_Qinch_x,centerY-pix_per_Finch_y);
			LineTo(centerX+pix_per_Finch_x,centerY-pix_per_Finch_y);
			LineTo(centerX+pix_per_Finch_x,centerY+pix_per_Finch_y);
			LineTo(centerX+pix_per_Qinch_x,centerY+pix_per_Finch_y);
	        }
	    }
	else
	    {
	    MoveTo(centerX-pix_per_Qinch_x,centerY);
	    LineTo(centerX+pix_per_Qinch_x,centerY);
	    MoveTo(centerX,centerY-pix_per_Qinch_y);
	    LineTo(centerX,centerY+pix_per_Qinch_y);
	    }
	PenMode(zREPz);
	}
if(Me.look!=Me.ang)
	{
	Me.look=Me.ang;
	change=1;
	}

if( showDashBoard && drewDashBoard<=0)
    {
    DrawDashBoard();
    if (drewDashBoard==-1)
	drewDashBoard= 1;
    else
	drewDashBoard=-1;
    }
else if( showDashBoard )
    updateDashBoard();
ShowNextFram();

ClipRect(&screenR);

if(game==COLONY)
	{
	CCenter();
	if(doorsound)
	    {DoDoorSound();doorsound=FALSE;}
	}
#endif
}
/*----------------------------------------------------------------------*/
Terminate(blowup)
int blowup;
{
#if !defined(IBM_Terminate)
int i;

SetPort(scrport);
ClipRect(&sR);
HideCursor();
FillRect(&sR,black);
if(blowup)	DoExplodeSound();
else DoOuchSound();
for(i=0;i<4;i++)InvertRect(&sR);
KillSound();
ShowCursor();
EndGame(FALSE);
if(showDashBoard)drewDashBoard= 0;
#endif
}
/*----------------------------------------------------------------------*/
ShowNextFram()
{
SetPort(scrport);
MovePortTo(0,0);
HideCursor();
if(is_EGAtype)
    {
    if (my_graf_page==1)
		{
		SetBitmap(GrafPg0);
		SetPort(metaPnt);
		SetDisplay(GrafPg0);
		PortBitmap(EGA_board1);
		my_graf_page=0;
		}
    else
		{
		SetBitmap(GrafPg1);
		SetPort(metaPnt);
		SetDisplay (GrafPg1);
		PortBitmap(EGA_board0);
		my_graf_page=1;
		}
    }
else
    CopyBits( metaPnt->portBMap, scrport->portBMap,
	      &sR, &sR, &sR, 0);
SetPort(scrport);
ShowCursor();
SetPort(metaPnt);
}
