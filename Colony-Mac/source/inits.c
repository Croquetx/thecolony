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
 * inits.c
 *----------------------------------------------------------------------*
 * SetUpMenus()
 * inits()
 * TObject(n)
 * 		int n;
 * SizeRect(sx,sy,r)
 *		Rect *r;
 *		int *sx,*sy;
 * UpdateMove()
 * UpdateInfo()
 * UpdateThe()
 *----------------------------------------------------------------------*/

#define EXT extern
#include "cgamedefs.h"

#define UNLOAD TRUE

int MaxApplZone();
Rect animR;

#define windowMID 13694
#define windowIID 10930
#define M1  -1L
extern int vcenterX,vcenterY;
/*----------------------------------------------------------------------*/
SetUpMenus()
{
char *appletitle;
int i;

myMenus[0]=GetMenu(APPLEMENU);
AddResMenu(myMenus[0],'DRVR');
myMenus[1]=GetMenu(FILEMENU);
myMenus[2]=GetMenu(EDITMENU);
myMenus[3]=GetMenu(OPTIONS);
for(i=0;i<LASTMENU;i++)InsertMenu(myMenus[i],0);
DrawMenuBar();
CheckItem(myMenus[3],1,soundon);
CheckItem(myMenus[3],2,crosshair);
CheckItem(myMenus[3],3,!polyfill);
CheckItem(myMenus[3],4,cshoot);
}
/*----------------------------------------------------------------------*/
#define CW 4		/*horizontal icon setoff in menu box */
#define CH1 -19		/*vertical icon setoff */
#define CH2 -20
#define FSIZE 24	/*font size in bits */
#define SOUND 	1		/* == 1   */

/*----------------------------------------------------------------------*/
inits()
{
int i,j;
int k,l;
int *pint;
unsigned char *pchar;
int message,count;
long rSeed;
DateTimeRec when;
char str[255];
SysEnvRec theWorld;
OSErr err;
long cnt;

FlushEvents(everyEvent,0);
InitGraf(&thePort);
InitFonts();
InitWindows();
InitMenus();
InitDialogs(0L);
InitCursor();
if(MaxApplZone())DoChimeSound();
for(i=0;i<50;i++)MoreMasters();
cnt = FreeMem();
if(cnt<1000000L){Mac512=TRUE; Mac2=FALSE; }
err=SysEnvirons(1,&theWorld);
if(!theWorld.hasColorQD){Inform("\pColor QuickDraw not present!"); ExitToShell();}

theDepth=FindDepth();
if(theDepth==1)
	{
	Inform("\pHey, this is COLOR Colony!");
	ExitToShell();
	}

GetDateTime(&rSeed);
Secs2Date(rSeed,&when);
if(when.month==12&&when.day==25)xmas=TRUE;
randSeed=rSeed;
CountAppFiles(&message,&count);
InitRobot();
gametest=TRUE;
soundon=SOUND;
crosshair=1;
polyfill=1;
BuildTable();
rScreen.top=screenBits.bounds.top;
rScreen.left=screenBits.bounds.left;
rScreen.right=rScreen.left+min(screenBits.bounds.right-screenBits.bounds.left,640);
rScreen.bottom=rScreen.top+min(screenBits.bounds.bottom-screenBits.bounds.top,480);
screenR.top=40; 
screenR.left=96;
screenR.right=rScreen.right;
screenR.bottom=rScreen.bottom-8;
animR.left=(screenBits.bounds.left+screenBits.bounds.right)/2-208;
animR.left=animR.left/32;
animR.left=animR.left*32;
animR.right=animR.left+416;
animR.top=(screenBits.bounds.top+screenBits.bounds.bottom)/2-147;
animR.bottom=animR.top+294;
if(Mac512)
	{
	screenR.right=screenR.left+(animR.right-animR.left);
	screenR.bottom=screenR.top+(animR.bottom-animR.top);
	}
Width=1+screenR.right-screenR.left; 
Height=1+screenR.bottom-screenR.top; 
centerX=Width/2;
centerY=Height/2;
vcenterX=centerX/6;
vcenterY=centerY/7;
if(0==(cost=(int *)NewPtr(sizeof(int)*768L)))MemoryErr();
xai= &cost[256];
yai= &xai[256];
tabsgen();
UnLoad();
/*DoText(&rScreen,0,1);*/
OptionKey();
SoundIntro(count);
if(!count)intro();
SoundInit(count);

SetUpMenus();
Cross=GetCursor(1000);
HLock(Cross);
for(i=0;i<5;i++){fl_icon[i]=GetIcon(i+1); HLock(fl_icon[i]);}
fl_rect.bottom=Height-32;
fl_rect.left=32;
fl_rect.top=fl_rect.bottom-32;
fl_rect.right=fl_rect.left+32;
if(0==(patch=(struct patchstrct*)NewPtr(sizeof(struct patchstrct)*100)))MemoryErr();
infoWindow = GetNewCWindow(windowIID,&infowRecord,M1);
moveWindow = GetNewCWindow(windowMID,&movewRecord,M1);
theWindow = NewCWindow( &wRecord , &screenR, "\pColony", 1, 0, -1L, 0, 0L);
ShowCursor();
initPixMap();
if(0==(pint=(int *)NewPtr(sizeof(int) * 1024L)))MemoryErr();
for(i=0;i<32;i++)drX[i]= &pint[i*32];
if(0==(pint=(int *)NewPtr(sizeof(int) * 1024L)))MemoryErr();
for(i=0;i<32;i++)drY[i]= &pint[i*32];
if(0==(pchar=(unsigned char *)NewPtr(sizeof(char) * 1024L)))MemoryErr();
for(i=0;i<32;i++)dirXY[i]= &pchar[i*32];
if(0==(pchar= (unsigned char *)NewPtr(sizeof(char)*1024L)))MemoryErr();
for(i=0;i<32;i++)Wall[i]=&pchar[i*32];
if(0==(pchar= (unsigned char *)NewPtr(sizeof(char)*1024L)))MemoryErr();
for(i=0;i<32;i++)robotarray[i]= &pchar[i*32];
for(i=0;i<32;i++)for(j=0;j<32;j++)robotarray[i][j]=0;
if(0==(pchar= (unsigned char *)NewPtr(sizeof(char)*1024L)))MemoryErr();
for(i=0;i<32;i++)foodarray[i]= &pchar[i*32];
for(i=0;i<32;i++)for(j=0;j<32;j++)foodarray[i][j]=0;
if(0==(Object=(Thing *)NewPtr(sizeof(Thing) * 257L)))MemoryErr();
/*ShowNum(Object);/**/
if(NIL==(map.buffer=NewPtr(25600L)))MemoryErr();
for(i=0;i<31;i++)
	for(j=0;j<31;j++)
		for(k=0;k<5;k++)
			for(l=0;l<5;l++)(*map.data)[i][j][k][l]=0;/*clear the buffer*/
if(0==(pbattle.buffer=NewPtr(sizeof(Locate)*4*4*MAXQUAD)))MemoryErr();
pwhere=pbattle.data;
ColorInit();
BattleInit();
if(count){if(!opengame(count))gameInit();}
else gameInit();
UnLoad();
}
/*---------------------------------------------------------------------- 
 * These functions are only for allocating additional memory on a Mac
 * 512K machine.  They can be ignored otherwise.
 *---------------------------------------------------------------------- 
 */
intro();
drawchar();
DoText();
MakePrism();
CThink();
tunnel();
BThink();

UnLoad()
{
#if UNLOAD
if(!Mac512)return;
UnloadSeg(intro);
UnloadSeg(drawchar);
UnloadSeg(DoText);
UnloadSeg(MakePrism);
UnloadSeg(CThink);
UnloadSeg(tunnel);
UnloadSeg(BThink);
#endif
}
AUnLoad()
{
#if UNLOAD
if(!Mac512)return;
UnloadSeg(intro);
UnloadSeg(drawchar);
UnloadSeg(MakePrism);
UnloadSeg(CThink);
UnloadSeg(BThink);
UnloadSeg(tunnel);
#endif
}
BUnLoad()
{
#if UNLOAD
if(!Mac512)return;
UnloadSeg(intro);
UnloadSeg(drawchar);
UnloadSeg(MakePrism);
UnloadSeg(CThink);
UnloadSeg(tunnel);
UnloadSeg(DoText);
#endif
}
CUnLoad()
{
#if UNLOAD
if(!Mac512)return;
UnloadSeg(intro);
UnloadSeg(DoText);
UnloadSeg(tunnel);
UnloadSeg(BThink);
#endif
}
TUnLoad()
{
#if UNLOAD
if(!Mac512)return;
UnloadSeg(intro);
UnloadSeg(drawchar);
UnloadSeg(DoText);
UnloadSeg(MakePrism);
UnloadSeg(CThink);
UnloadSeg(BThink);
#endif
}
/*---------------------------------------------------------------------- 
 * sizerect(sx,sy,pr)
 * int *sx,*sy;
 * rect *pr;
 * copies size of rect to sx and sy
 *---------------------------------------------------------------------- 
 */
SizeRect(sx,sy,r)
Rect *r;
int *sx,*sy;
{
*sy=r->bottom-r->top;
*sx=r->right-r->left;
}
/*---------------------------------------------------------------------
 * UpdateWindow(theWindow)
 * WindowPtr	theWindow;
 *
 * Updates our window as necessary (is someone dragging Desk Accesories
 * around on it?).
 *---------------------------------------------------------------------
 */
UpdateMove()
{
GrafPtr	savePort;
Rect rb;

GetPort( &savePort );
SetPort( moveWindow );
BeginUpdate( moveWindow );
DrawCompass();
EndUpdate(moveWindow);
SetPort( savePort );
}

UpdateInfo()
{
GrafPtr	savePort;
Rect rb;

GetPort( &savePort );
SetPort(infoWindow );
BeginUpdate( infoWindow );
DrawInfo();
EndUpdate(infoWindow);
SetPort( savePort );
}

UpdateThe()
{
GrafPtr	savePort;
Rect rb;
extern int animnotdone;
extern CGrafPort metaPort;

if(theDepth!=FindDepth())
	{
	theDepth=FindDepth();
	ResetOffScreen();
	/*NewColorTable(metaPort.portPixMap);*/
	}
GetPort( &savePort );
SetPort( theWindow );
BeginUpdate( theWindow );
Display();
EndUpdate(theWindow);
SetPort( savePort );
}

MemoryErr()
{
Inform("\pNot enough  memory!");
ExitToShell();
}
BuildTable()
{
int i;

if(NIL==(rtable=(int *)NewPtr(sizeof(int)*11585L)))MemoryErr();
rtable[0]=32000;
for(i=1;i<11585;i++)rtable[i]=(Floor*128)/i;
}
KillTable()
{
DisposPtr(rtable);
}

FindDepth()
{
GDHandle GDH;
GDPtr GDP;
GDH=GetMainDevice();
GDP=*GDH;
return (int)(*GDP->gdPMap)->pixelSize;
}
