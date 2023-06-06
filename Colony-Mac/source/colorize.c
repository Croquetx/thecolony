/*----------------------------------------------------------------------*
 *----------------------------------------------------------------------*/
#include <Color.h>
#include <ColorToolbox.h>
#include "colordef.h"

#define WHITE	0
#define LTGRAY	1
#define GRAY	2
#define DKGRAY	3
#define BLACK	4
#define CLEAR 	5

#define RSIZE 	14
extern EventRecord key;
extern WindowPtr whichWindow;
extern Rect rScreen;
int cChanged=FALSE;
int colorOn=FALSE;
WindowRecord cRecord;
GrafPtr cWindow;
Rect screenC;

extern RGBColor black_Color;
extern RGBColor white_Color;
	
struct colordef cColor[]={
	{{0,0,0},{0xFFFF,0xFFFF,0xFFFF},WHITE,	0},
	{{0,0,0},{0xFFFF,0xFFFF,0xFFFF},LTGRAY,	0},
	{{0,0,0},{0xFFFF,0xFFFF,0xFFFF},GRAY,	0},
	{{0,0,0},{0xFFFF,0xFFFF,0xFFFF},DKGRAY,	0},
	{{0,0,0},{0xFFFF,0xFFFF,0xFFFF},BLACK,	0},
	{{0,0,0},{0xFFFF,0xFFFF,0xFFFF},CLEAR,	0},
	{{0,0,0},{0,0,0},WHITE,	"\pDARK WALLS"},
	{{0,0,0},{0,0,0},WHITE,	"\pFLRS,CLNGS,WALLS"},
	{{0,0,0},{0,0,0},GRAY,	"\pWALLS/CHARS S"},
	{{0,0,0},{0,0,0},GRAY,	"\pWALLS/CHARS 1"},
	{{0,0,0},{0,0,0},GRAY,	"\pWALLS/CHARS 2"},
	{{0,0,0},{0,0,0},GRAY,	"\pWALLS/CHARS 3"},
	{{0,0,0},{0,0,0},GRAY,	"\pWALLS/CHARS 4"},
	{{0,0,0},{0,0,0},GRAY,	"\pWALLS/CHARS 5"},
	{{0,0,0},{0,0,0},GRAY,	"\pWALLS/CHARS 6"},
	{{0,0,0},{0,0,0},GRAY,	"\pBULKHEAD"},
	{{0,0,0},{0,0,0},GRAY,	"\pDOOR"},
	{{0,0,0},{0,0,0},DKGRAY,"\pWINDOW"},
	{{0,0,0},{0,0,0},LTGRAY,"\pSHELVES"},
	{{0,0,0},{0,0,0},GRAY,	"\pUPSTAIRS 1"},
	{{0,0,0},{0,0,0},GRAY,	"\pUPSTAIRS 2"},
	{{0,0,0},{0,0,0},GRAY,	"\pDNSTAIRS"},
	{{0,0,0},{0,0,0},GRAY,	"\pGLYPH"},
	{{0,0,0},{0,0,0},GRAY,	"\pELEVATOR"},
	{{0,0,0},{0,0,0},GRAY,	"\pTUNNEL"},
	{{0,0,0},{0,0,0},GRAY,	"\pAIRLOCK"},
	{{0,0,0},{0,0,0},GRAY,	"\pCOLOR 1"},
	{{0,0,0},{0,0,0},GRAY,	"\pCOLOR 2"},
	{{0,0,0},{0,0,0},GRAY,	"\pCOLOR 3"},
	{{0,0,0},{0,0,0},GRAY,	"\pCOLOR 4"},
	{{0,0,0},{0,0,0},GRAY,	"\pHOLE"},
	{{0,0,0},{0,0,0},GRAY,	"\pHOTPLATE"},
	
	{{0,0,0},{0,0,0},GRAY,	"\pEYE"},
	{{0,0,0},{0,0,0},GRAY,	"\pµ EYE"},
	{{0,0,0},{0,0,0},GRAY,	"\pEYEBALL"},
	{{0,0,0},{0,0,0},GRAY,	"\pIRIS"},
	{{0,0,0},{0,0,0},GRAY,	"\pPUPIL"},
	{{0,0,0},{0,0,0},GRAY,	"\pPYRAMID"},
	{{0,0,0},{0,0,0},GRAY,	"\pµ PYRAMID"},
	{{0,0,0},{0,0,0},GRAY,	"\pDIAMOND"},
	{{0,0,0},{0,0,0},GRAY,	"\pµ DIAMOND"},
	{{0,0,0},{0,0,0},GRAY,	"\pUPYRAMID"},
	{{0,0,0},{0,0,0},GRAY,	"\pµ UPYRAMID"},
	{{0,0,0},{0,0,0},GRAY,	"\pQUEEN 1"},
	{{0,0,0},{0,0,0},GRAY,	"\pQUEEN 2"},
	{{0,0,0},{0,0,0},GRAY,	"\pQUEEN 3"},
	{{0,0,0},{0,0,0},GRAY,	"\pQUEEN 4"},
	{{0,0,0},{0,0,0},GRAY,	"\pQUEEN 5"},
	{{0,0,0},{0,0,0},GRAY,	"\pPRIME QUEEN"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ IRIS"},
	{{0,0,0},{0,0,0},GRAY,	"\pDRONE"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ IRIS"},
	{{0,0,0},{0,0,0},GRAY,	"\pSOLDIER"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ IRIS"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ JAWS1"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ JAWS2"},
	{{0,0,0},{0,0,0},GRAY,	"\pSNOOPER TOP"},
	{{0,0,0},{0,0,0},GRAY,	"\pSNOOPER BOT"},
	
	{{0,0,0},{0,0,0},GRAY,	"\pDESK"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ TOP"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ CHAIR"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ COMPUTER"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ SCREEN"},
	{{0,0,0},{0,0,0},GRAY,	"\pPLANT"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ POT"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ SOIL"},
	{{0,0,0},{0,0,0},GRAY,	"\pSMALL CHAIR"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ BASE"},
	{{0,0,0},{0,0,0},GRAY,	"\pBED-BLNKT"},
	{{0,0,0},{0,0,0},GRAY,	"\pBED-SHEET"},
	{{0,0,0},{0,0,0},GRAY,	"\pBED-HEAD"},
	{{0,0,0},{0,0,0},GRAY,	"\pTABLE"},
	{{0,0,0},{0,0,0},GRAY,	"\pPROJECTOR"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ LENS"},
	{{0,0,0},{0,0,0},GRAY,	"\pCOUCH"},
	{{0,0,0},{0,0,0},GRAY,	"\pCHAIR"},
	{{0,0,0},{0,0,0},GRAY,	"\pTV"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ SCREEN"},
	{{0,0,0},{0,0,0},GRAY,	"\pMONOLITH"},
	{{0,0,0},{0,0,0},GRAY,	"\pCONSOLE"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ TOP"},
	{{0,0,0},{0,0,0},GRAY,	"\pPOWERSUIT"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ TABLE"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ SOURCE"},
	{{0,0,0},{0,0,0},GRAY,	"\pSMALL BOX"},
	{{0,0,0},{0,0,0},GRAY,	"\pLARGE BOX"},
	{{0,0,0},{0,0,0},GRAY,	"\pFORKLIFT"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ GLASS"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ TREAD"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ TREADSIDE"},
	{{0,0,0},{0,0,0},GRAY,	"\pCRYO"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ GLASS"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ STAND"},
	{{0,0,0},{0,0,0},GRAY,	"\pTELEPORT"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ DOOR"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ GLASS"},
	{{0,0,0},{0,0,0},GRAY,	"\pVANITY"},
	{{0,0,0},{0,0,0},GRAY,	"\pTUB"},
	{{0,0,0},{0,0,0},GRAY,	"\pSINK"},
	{{0,0,0},{0,0,0},GRAY,	"\pTOILET"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ SEAT"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ BARRIER"},
	{{0,0,0},{0,0,0},GRAY,	"\pWATER"},
	{{0,0,0},{0,0,0},GRAY,	"\pMIRROR"},
	{{0,0,0},{0,0,0},GRAY,	"\pLAB BENCH"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ TOP"},
	{{0,0,0},{0,0,0},GRAY,	"\pREACTOR"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ HOT CORE1"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ HOT CORE2"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ HOT CORE3"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ HOT CORE4"},
	{{0,0,0},{0,0,0},GRAY,	"\p¥ COLD CORE"},
	{{0,0,0},{0,0,0},GRAY,	"\pXMAS TREE"}
	};
	
#define WALLNUM 26
struct colordef *cWall;
#define CREATURENUM 26	
struct colordef *cCreature;
#define OBJECT1NUM 28
struct colordef *cObject;
#define OBJECT2NUM 27
struct colordef *cObject2;
#define COLORNUM 6+WALLNUM+CREATURENUM+OBJECT1NUM+OBJECT2NUM
ControlHandle hButton;
Rect hRect;
/*----------------------------------------------------------------------*/
InitColorize()
{
int width;

if(colorOn)
	{
	BringToFront(cWindow);
	SelectWindow(cWindow);
	return;
	}
screenC.top=40; 
screenC.left=8;
screenC.right=rScreen.right-8;
screenC.bottom=rScreen.bottom-3;
cWindow = NewCWindow( &cRecord , &screenC, "\pColony Color Palette", 1, 0, -1L, 1, 0L);
SetPort(cWindow);
screenC.right-=screenC.left;
screenC.bottom-=screenC.top;
screenC.top=screenC.left=0;
width=screenC.right>>2;
hRect.left=0;
hRect.right=width;
hRect.top=screenC.bottom-30;
hRect.bottom=screenC.bottom;
ForeColor(blueColor);
PenPat(black);
PaintRect(&hRect);
ForeColor(blackColor);
InsetRect(&hRect,4,4);
ShowCursor();
PenMode(8);
SetOrigin(0,0);
TextFont(0);
colorOn=TRUE;
hButton=NewControl(cWindow,&hRect,"\pHelp",TRUE,0,0,0,0,0L);
}
/*----------------------------------------------------------------------*/
Colorize()
{
int doneflag;
GrafPtr saveport;

InitColorize();
/*DrawColor();*/
}
/*----------------------------------------------------------------------*/
ColorUpdate()
{
Rect    visablerec;
GrafPtr savePort;

GetPort(&savePort);
SetPort(cWindow);
BeginUpdate(cWindow);
InsetRect(&hRect,-4,-4);
ClipRect(&hRect);
ForeColor(blueColor);
PenPat(black);
PaintRect(&hRect);
ForeColor(blackColor);
InsetRect(&hRect,4,4);
DrawControls(cWindow);
DrawColor();
EndUpdate(cWindow);
SetPort(savePort);
}
/*----------------------------------------------------------------------*/
CAction()	/*  for mousedown in icon window */
{
int column,row,width;
int cnum;
Point loc;
ControlHandle whichControl;

SetPort(cWindow);
GetMouse(&loc);
if(FindControl(loc,cWindow,&whichControl))
	if(TrackControl(whichControl,loc,0L))
	{
	HelpColor();
	return;
	}
width=screenC.right>>2;
row=loc.v-(RSIZE+2);

column=loc.h/width;
if(column*width+(RSIZE+2)*3<loc.h)return;
cnum=(loc.h-column*width)/(RSIZE+2);

row=row/(RSIZE+1);
switch(column)
	{
	case 0:
		if(row<WALLNUM)
			{
			switch(cnum)
				{
				case 0:
					EditColor(&cWall[row].f,cWall[row].text);
					break;
				case 1:
					EditColor(&cWall[row].b,cWall[row].text);
					break;
				case 2:
					if(row>8)
					EditGray(&loc,&cWall[row].pattern,cWall[row].text);
					break;
				}
			DrawBox(2,RSIZE+2+row*(RSIZE+1),&cWall[row],row>8);
			}
		break;
	case 1:
		if(row<CREATURENUM)
			{
			switch(cnum)
				{
				case 0:
					EditColor(&cCreature[row].f,cCreature[row].text);
					break;
				case 1:
					EditColor(&cCreature[row].b,cCreature[row].text);
					break;
				case 2:
					EditGray(&loc,&cCreature[row].pattern,cCreature[row].text);
					break;
				}
			DrawBox(width+4,RSIZE+2+row*(RSIZE+1),&cCreature[row],TRUE);
			}
		break;
	case 2:
		if(row<OBJECT1NUM)
			{
			switch(cnum)
				{
				case 0:
					EditColor(&cObject[row].f,cObject[row].text);
					break;
				case 1:
					EditColor(&cObject[row].b,cObject[row].text);
					break;
				case 2:
					EditGray(&loc,&cObject[row].pattern,cObject[row].text);
					break;
				}
			DrawBox(width*2+4,RSIZE+2+row*(RSIZE+1),&cObject[row],TRUE);
			}
		break;
	case 3:
		if(row<OBJECT2NUM)
			{
			switch(cnum)
				{
				case 0:
					EditColor(&cObject2[row].f,cObject2[row].text);
					break;
				case 1:
					EditColor(&cObject2[row].b,cObject2[row].text);
					break;
				case 2:
					EditGray(&loc,&cObject2[row].pattern,cObject2[row].text);
					break;
				}
			DrawBox(width*3+4,RSIZE+2+row*(RSIZE+1),&cObject2[row],TRUE);
			}
		break;
	}
}
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
char *header[]={"\pWALLS","\pCREATURES","\pOBJECTS","\pColony Color Palette Help"};
DrawColor()
{
int i;
int width,swidth;

SetPort(cWindow);
ClipRect(&screenC);
cWall=&cColor[6];
cCreature=&cWall[WALLNUM];
cObject=&cCreature[CREATURENUM];
cObject2 = &cObject[OBJECT1NUM];

width=screenC.right>>2;

MoveTo(width-1,screenC.top);
LineTo(width-1,screenC.bottom);
MoveTo(width+1,screenC.top);
LineTo(width+1,screenC.bottom);

MoveTo(2*width-1,screenC.top);
LineTo(2*width-1,screenC.bottom);
MoveTo(2*width+1,screenC.top);
LineTo(2*width+1,screenC.bottom);

MoveTo(screenC.left,RSIZE);
LineTo(screenC.right,RSIZE);

MoveTo(screenC.left,screenC.bottom-30);
LineTo(width-1,screenC.bottom-30);

swidth=StringWidth(header[0]);
MoveTo(screenC.left+2+(width-swidth)/2,(RSIZE-2));
DrawString(header[0]);
swidth=StringWidth(header[1]);
MoveTo(screenC.left+width+3+(width-swidth)/2,RSIZE-2);
DrawString(header[1]);
swidth=StringWidth(header[2]);
MoveTo(screenC.left+2*width+3+width-swidth,RSIZE-2);
DrawString(header[2]);

for(i=0;i<WALLNUM;i++)
	DrawBox(2,RSIZE+2+i*(RSIZE+1),&cWall[i],i>8);
	
for(i=0;i<CREATURENUM;i++)
	DrawBox(width+4,RSIZE+2+i*(RSIZE+1),&cCreature[i],TRUE);

for(i=0;i<OBJECT1NUM;i++)
	DrawBox(width*2+4,RSIZE+2+i*(RSIZE+1),&cObject[i],TRUE);

for(i=0;i<OBJECT2NUM;i++)
	DrawBox(width*3+4,RSIZE+2+i*(RSIZE+1),&cObject2[i],TRUE);
}

/*----------------------------------------------------------------------*/
DrawBox(left,top,data,gdata)
int top,left;
struct colordef *data;
int gdata;
{
Rect r1,r2,r3,r4;
RGBColor f,b;

r4.top=r3.top=r2.top=r1.top = top;
r4.bottom=r3.bottom=r2.bottom=r1.bottom=top+RSIZE;
r1.left=left;
r1.right=left+RSIZE;
r2.left=r1.right+1;
r2.right=r2.left+RSIZE;
r3.left=r2.right+1;
r3.right=r3.left+RSIZE;
r4.left=r3.right+5;
r4.right=r4.left+RSIZE;

RGBForeColor(&data->f);
PenPat(black);
PaintRect(&r1);
RGBForeColor(&data->b);
PaintRect(&r2);
RGBForeColor(&data->f);
RGBBackColor(&data->b);
if(gdata)
	{
	switch(data->pattern)
		{
		case 0:
			PenPat(white);
			break;
		case 1:
			PenPat(ltGray);
			break;
		case 2:
			PenPat(gray);
			break;
		case 3:
			PenPat(dkGray);
			break;
		case 4:
			PenPat(black);
			break;
		}
	PaintRect(&r4);
	RGBForeColor(&black_Color);
	RGBBackColor(&white_Color);
	PaintRect(&r3);
	}
else
	{
	RGBForeColor(&black_Color);
	RGBBackColor(&white_Color);
	}
PenPat(black);
FrameRect(&r1);
FrameRect(&r2);
if(gdata)
	{
	FrameRect(&r3);
	RGBForeColor(&data->f);
	FrameRect(&r4);
	RGBForeColor(&black_Color);
	MoveTo(r4.right+2,r4.bottom-2);
	}
else  MoveTo(r2.right+2,r4.bottom-2);
DrawString(data->text);
}
/*----------------------------------------------------------------------*/
EditColor(color,prompt)
RGBColor *color;
char *prompt;
{
Point where;
int cc;

where.v=30;
where.h=60;
cc=GetColor(where,prompt,color,color);
cChanged=cChanged || cc;
}
/*----------------------------------------------------------------------*/
EditGray(p,gr,prompt)
Point *p;
int *gr;
char *prompt;
{
GrafPtr grayWindow;
Rect r,fr;
WindowRecord gRecord;
int val,nval;
Point mp;
WindowPtr whichWindow;

LocalToGlobal(p);
r.top=p->v-(8+*gr*16);
if(r.top<25)r.top=25;
r.left=p->h-8;
r.bottom=r.top+16*5+1;
r.right=r.left+16*5;
if(r.bottom>rScreen.bottom)
	{
	r.top=rScreen.bottom-(2+r.bottom-r.top);
	r.bottom=rScreen.bottom-2;
	}
grayWindow = NewCWindow( &gRecord , &r, "\p", 1, 2, -1L, 0, 0L);
SetPort(grayWindow);
r.right-=r.left;
r.left=0;
r.bottom-=r.top;
r.top=0;
fr.top=r.top+1;
fr.left=r.left+1;
fr.right=r.right-1;
fr.bottom=fr.top+15;
FillRect(&fr,white);
FrameRect(&fr);
fr.top+=16;
fr.bottom+=16;
FillRect(&fr,ltGray);
FrameRect(&fr);
fr.top+=16;
fr.bottom+=16;
FillRect(&fr,gray);
FrameRect(&fr);
fr.top+=16;
fr.bottom+=16;
FillRect(&fr,dkGray);
FrameRect(&fr);
fr.top+=16;
fr.bottom+=16;
FillRect(&fr,black);
FrameRect(&fr);
fr.left--;
fr.right++;
GetMouse(&mp);
val=mp.v/16;
fr.top=val*16;
fr.bottom=fr.top+17;
PenPat(black);
FrameRect(&fr);

while(Button())
	{
	GetMouse(&mp);
	LocalToGlobal(&mp);
	FindWindow(mp,&whichWindow);
	GlobalToLocal(&mp);
	if(whichWindow!=grayWindow)
		{
		if(val!=-1)
			{
			val= -1;
			PenPat(white);
			FrameRect(&fr);
			}
		}
	else
		{
		nval=mp.v/16;
		if(nval!=val)
			{
			if(val!=-1)
				{
				PenPat(white);
				FrameRect(&fr);
				}
			val=nval;
			fr.top = val*16;
			fr.bottom = fr.top+17;
			PenPat(black);
			FrameRect(&fr);
			}
		}
	}
CloseWindow(grayWindow);
SetPort(cWindow);
if(val!=-1 && *gr!=val)
	{
	*gr=val;
	cChanged=TRUE;
	}
}
/*----------------------------------------------------------------------*/
#include <FileMgr.h>
#include <StdFilePkg.h>
#include <SegmentLdr.h>
long cCtype='COLR';
extern long create;
char	cvolname[255];
char	cfilname[255];
long cVers='v1.0';

/*----------------------------------------------------------------------*/
InitBlock(cblk)
IOParam *cblk;
{
cblk->qLink=0;
cblk->qType=0;
cblk->ioTrap=0;
cblk->ioCmdAddr=0;
cblk->ioCompletion=0;
cblk->ioResult=0;
cblk->ioRefNum=0;
cblk->ioBuffer=0;
cblk->ioReqCount=0;
cblk->ioActCount=0;
cblk->ioPosMode=0;
cblk->ioPosOffset=0;
cblk->ioNamePtr = (StringPtr)0;
}
/*----------------------------------------------------------------------*/
SaveColor()
{
int i=0;
long fsize=4096L;
Point loc;
OsErr err;
VolumeParam vblk;
SFReply reply;
FileParam fblk;
int cnum;
IOParam cpblk;

InitBlock(&cpblk);
cpblk.ioNamePtr=(StringPtr)cfilname;/*file name*/
vblk.ioNamePtr=(StringPtr)cvolname;/*file name*/
SetPt(&loc,100,80);
SFPutFile(loc  ,"\pSave Color as...",cpblk.ioNamePtr,(Ptr)0,&reply);
if(reply.good==FALSE)return(FALSE);
for(i=0;i<64;i++)vblk.ioNamePtr[i]=cpblk.ioNamePtr[i]=reply.fName[i];
vblk.ioVRefNum=cpblk.ioVRefNum=reply.vRefNum;
cpblk.ioVersNum=reply.version;
cpblk.ioPermssn=fsWrPerm;
cpblk.ioMisc=(Ptr)0;
vblk.ioVolIndex= -1;
PBGetVInfo(&vblk,FALSE);
if((vblk.ioVAlBlkSiz*vblk.ioVFrBlk) < sizeof(RGBColor)*2*COLORNUM)
	{
	Inform("\pNot enough disk space!");
	return(FALSE);
	}
err=PBCreate(&cpblk,FALSE);
if(err&&err!=dupFNErr)
	{
	Inform("\pPBCreate error");
	DoText(&screenBits.bounds,151,0);
	return(FALSE);
	}
err=PBOpen(&cpblk,FALSE);
if(err)
	{
	Inform("\pPBOpen error");
	DoText(&screenBits.bounds,151,0);
	return(FALSE);
	}
err=PBSetEOF(&cpblk,FALSE);
if(err)
	{
	Inform("\pPBSetEOF error");
	DoText(&screenBits.bounds,151,0);
	return(FALSE);
	}
err=my_write(&cpblk,&cVers,4L);
if(err){Inform("\pSaveColorData error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
cnum=COLORNUM;
err=my_write(&cpblk,&cnum,2L);
if(err){Inform("\pSaveColorData error");	DoText(&screenBits.bounds,151,0);return(FALSE);}

for(i=0;i<COLORNUM;i++)
	{
	err=my_write(&cpblk,&cColor[i].f,(long)sizeof(RGBColor));
	if(err)break;
	err=my_write(&cpblk,&cColor[i].b,(long)sizeof(RGBColor));
	if(err)break;
	err=my_write(&cpblk,&cColor[i].pattern,2L);
	if(err)break;
	}
if(err){Inform("\pSaveColorData error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
err=PBFlushFile(&cpblk,FALSE);
if(err){Inform("\pPBFlushFile error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
err=PBClose(&cpblk,FALSE);
if(err){Inform("\pPBClose error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
fblk.qLink=cpblk.qLink;
fblk.qType=cpblk.qType;
fblk.ioTrap=cpblk.ioTrap;
fblk.ioCmdAddr=cpblk.ioCmdAddr;
fblk.ioCompletion=cpblk.ioCompletion;
fblk.ioResult=cpblk.ioResult;
fblk.ioNamePtr=cpblk.ioNamePtr;
fblk.ioVRefNum=cpblk.ioVRefNum;
err=PBGetFInfo(&fblk,FALSE);
if(err){Inform("\pPBGetFInfo error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
fblk.ioFlFndrInfo.fdType=cCtype;
fblk.ioFlFndrInfo.fdCreator=create;
err=PBSetFInfo(&fblk,FALSE);
if(err){Inform("\pPBSetFInfo error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
cpblk.ioNamePtr=0L;
err=PBFlushVol(&cpblk,FALSE);
if(err){Inform("\pPBFlushVol error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
cChanged=FALSE;
return(TRUE);/*indicates that data has been saved correctly*/
}
/*----------------------------------------------------------------------*/
int LoadColor()
{
OsErr err;
SFTypeList typelist;
int numtypes=1;
Point loc;
int i=0;
SFReply reply;
AppFile theFile;
IOParam cpblk;

InitBlock(&cpblk);
cpblk.ioNamePtr=(StringPtr)cfilname;/*file name*/
SetPt(&loc,100,80);
typelist[0]=cCtype;
SFGetFile(loc,"\pLoad Color",(Ptr)0,numtypes,typelist,(Ptr)0,&reply);
if(reply.good==FALSE)return(FALSE);
for(i=0;i<64;i++)cpblk.ioNamePtr[i]=reply.fName[i];
cpblk.ioVRefNum=reply.vRefNum;
cpblk.ioVersNum=reply.version;
cpblk.ioPermssn=fsRdPerm;
cpblk.ioMisc=(Ptr)0;
for(i=0;i<64;i++)reply.fName[i]=cpblk.ioNamePtr[i];
reply.vRefNum=cpblk.ioVRefNum;
reply.version=cpblk.ioVersNum;
load_color_map(&cpblk);
if(colorOn)DrawColor();
return(TRUE);
}
/*----------------------------------------------------------------------*/
extern int theDepth;

ColorInit()
{
int err;

switch(theDepth)
	{
	case 32:
	case 16:
	case 8:
		err=load_color("\pColor256");
		break;
	case 4:
		err=load_color("\pColor16");
		break;
	case 2:
		err=load_color("\pColor4");
		break;
	case 1:
		err=load_color("\pColor2");
		break;
	}
if(err){Inform("\pProblem loading color!"); ExitToShell();}
}
/*----------------------------------------------------------------------*/
load_color(fname)
char *fname;
{
OSErr err;
int vnum;
char str[255];
int i,j;
IOParam cblk;

i=0;while(fname[i]){cfilname[i]=fname[i];i++;} 
InitBlock(&cblk);

err=GetVol(str,&vnum);
if(err)
	{
	DoChimeSound();
	DoChimeSound();
	Inform("\pGetVol error");
	return(err);
	}
cblk.ioNamePtr=(StringPtr)fname;/*file name*/
cblk.ioVRefNum=vnum;
cblk.ioVersNum=0;
cblk.ioPermssn=fsRdPerm;
cblk.ioMisc=(Ptr)0;
err=load_color_map(&cblk);
if(err){Inform("\pload_color error"); return(err);}
cChanged=FALSE;
if(colorOn)DrawColor();
return(0);
}
/*----------------------------------------------------------------------*/
load_color_map(cpblk)
IOParam *cpblk;
{
OSErr err;
int blength;
long name;
int cnum,i;

err=PBOpen(cpblk,FALSE);
if(err)
	{
	DoChimeSound();
	Inform("\pPBOpen color error");
	return(err);
	}
err=my_read(cpblk,&cVers,4L);
if(err){Inform("\pSaveColorData error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
cnum=COLORNUM;
err=my_read(cpblk,&cnum,2L);
if(err){Inform("\pSaveColorData error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
for(i=0;i<cnum;i++)
	{
	err=my_read(cpblk,&cColor[i].f,(long)sizeof(RGBColor));
	if(err)break;
	err=my_read(cpblk,&cColor[i].b,(long)sizeof(RGBColor));
	if(err)break;
	err=my_read(cpblk,&cColor[i].pattern,2L);
	if(err)break;
	}
if(err)
	{
	DoChimeSound();
	Inform("\pLoadColorData error");
	return(err);
	}
err=PBClose(cpblk,FALSE);
if(err)
	{
	DoChimeSound();
	Inform("\pPBClose error");
	return(err);
	}
return(0);
}
/*----------------------------------------------------------------------*/
char *help[]={
			"\p1 Foreground Color. Used for",
			"\p  lines and mixing patterns.",
			"\p2 Background Color. Used for",
			"\p  mixing patterns.",
			"\p3 Gray pattern. Foreground=",
			"\p  black,Background=white.",
			"\p4 Colors mixed using pattern.",
			"\p5 Object to be edited.",
			"\p   ¥ = part of object."};
HelpColor()
{
WindowRecord hRecord;
GrafPtr hWindow;
Rect screenH;
GrafPtr	savePort;
int y,x,i=6;
int swidth;

GetPort( &savePort );
y=(rScreen.bottom-(rScreen.top+40))/2;
x=(rScreen.right-rScreen.left)/2;
screenH.top=40+(y-105); 
screenH.bottom=40+(y+105);
screenH.left=x-100;
screenH.right=x+100;
hWindow = NewCWindow( &hRecord , &screenH, "\p", 1, 1, -1L, 1, 0L);

SetPort(hWindow);
ShowCursor();
PenMode(8);
SetOrigin(0,0);
TextFont(0);
MoveTo(0,17);
LineTo(200,17);
ForeColor(redColor);
swidth=StringWidth(header[3])/2;
MoveTo(100-swidth,10);
DrawString(header[3]);
i=Random();
if(i<0)i=-i;
i=14+(i%(c_xmas-14));
DrawBox(10,30,&cColor[i],TRUE);
MoveTo(14,56); DrawString("\p1");
MoveTo(14+RSIZE,56); DrawString("\p2");
MoveTo(14+RSIZE+RSIZE,56); DrawString("\p3");
MoveTo(14+RSIZE+RSIZE+RSIZE+5,56);DrawString("\p4");
MoveTo(14+RSIZE+RSIZE+RSIZE+RSIZE+15,56);DrawString("\p5");
for(i=0;i<9;i++){MoveTo(6,75+i*15);DrawString(help[i]);}
do { /*nothing*/ } while ( Button() );
do { /*nothing*/ } while ( !Button() );
CloseWindow(hWindow);
SetPort(savePort);
FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);
}
