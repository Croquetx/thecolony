/* #define IBM_main  /*   */
/* #define IBM_EndGame	  /*   */
/* #define IBM_MainEvent  /*   */
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
 * main.c
 *---------------------------------------------------------------------
 * main()
 * EndGame(iquit)
 * MainEvent() 
 *---------------------------------------------------------------------
 */
#define EXT 
#include "gamedefs.h"
#define WARNING 4
#define POWER 	256	/* ~= 100 */
#define SUIT 	0		/* == 0   */
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
extern int mouse;
int capslock;
main(int argc, char *argv[])
{
#if !defined(IBM_main)
rect r; /* dwe ??? testing */
int i; /* dwe ??? testing */
int qt;
putchar('\n'); /* space down one line after MetaWINDOW sign-on header */
open_mem_error = FALSE;
/*InitProfile();*/

qt=inits(argc,argv);
intro(qt);
if(mouse)ShowCursor();
if (open_mem_error)
    EndGame(TRUE);
notDone=TRUE;/*a flag that indicates what you think it does.*/
fadein=4;
/* for (i = 0; i < 256; i++) /* dwe ??? testing */
/* DoText(&r, i, 0); /* dwe ??? testing */
MainEvent();
EndGame(TRUE);
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
EndGame(iquit)
int iquit;
{
#if !defined(IBM_EndGame)
if(!iquit)
	endIBMgame();
else
	{
	KillSound();
	SetPort(scrport);
	HideCursor();
	StopMouse();
	StopEvent();
	ClearText();
	SetDisplay(TextPg0);   /* switch to text mode	*/
	EndSound();
	if (open_mem_error)
		{
	fputs("There is not enough memory to run 'The Colony' on this machine.\n", stderr);
	fputs("Remove large memory resident programs and try again.\n",stderr);
		exit(1);
		}
	exit(0);
	}
#endif
}

/*---------------------------------------------------------------------
 * int MainEvent() 
 * 
 * Main event loop. If anything is done it is done here.
 *---------------------------------------------------------------------
 */
#define ANY_BUTTON 0x0700
#define LEFT_BUTTON 0x0400
#define RIGHT_BUTTON 0x0100
MainEvent() 
{
#if !defined(IBM_MainEvent)
Rect *whichWindow;
Rect r;
int gne;
int windowpart;
int front;
int  CurLev, Butt;
char str[255];
EventRecord key2;
long loop,loop2;

change=1;
while(notDone)
	{
	if(epower[1]<=WARNING && SoundDone())DoChimeSound();
	if(game==COLONY)
		CThink();
	else  BThink();
	Display();		    /*This is wild!			*/
	count++;

	SetPort(scrport);
	ClipRect(&screenR);
	gne=KeyEvent(FALSE, &key);
	capslock = key.State & 0x40;
	myPt.h= key.CursorX;
	myPt.v= key.CursorY;
	if(!fl&&(ANY_BUTTON &key.State))
		 {
		 if (0x0100 & key.State) 	     /*  if right button  */
			 cshoot= True;
		 else
			 cshoot=False;
		 if(game==COLONY)doCShoot();
		 else BattleShoot();
		 }
	if(gne)      /*is there anything to do?*/
		{
	    if ( !key.ASCII && !key.ScanCode && (ANY_BUTTON & key.State) )
		{
		if(fl)
		    if(game==COLONY)
			 {
			 if(fl==1)
			     ExitFL();
			 else if(fl==2)
			     DropFL();
			 }
		 }
	 if ( key.ScanCode>58 && key.ScanCode<69 )
		 doFunctionKey(key.ScanCode-58);
	 else
		 movecorridor(key.ASCII, key.ScanCode);
	 } /* if */
	 if(KeyEvent(FALSE, &key))		 /*flushbuffer*/
		 {
		 do	 {
			 key2=key;
			 if(key.ScanCode>=2&&key.ScanCode<=6)break;
			 }	 while(KeyEvent(FALSE, &key));		 /*flushbuffer*/
		StoreEvent(&key2);
		}
	 action();
	 }
#endif
}
/*----------------------------------------------------------------------*/
int KeyPress(shft)
int shft;
{
#if !defined(IBM_KeyPress)
event evnt;

if(KeyEvent(0,&evnt))
	{
	if(shft){if(evnt.State&0x03)return(TRUE);else return(FALSE);}
	else return(TRUE);
	}
else return(FALSE);
#endif
}
/*----------------------------------------------------------------------*/
gameInit()
{
#if !defined(IBM_gameInit)
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

/*
SetPort(scrport);
PenMode(patCopy);
SetOrigin(0,0);
*/

game=COLONY;
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
fadein=False;
corestate[0]=0; corestate[1]=0;
coreheight[0]=256; coreheight[1]=256;
corepower[0]=0; corepower[1]=2; corepower[2]=0;
orbit=FALSE;
for(i=0;i<32;i++)for(j=0;j<32;j++)dirXY[i][j]=0;
BattleSet();
#endif
}
/*----------------------------------------------------------------------*/
MemoryErr()
{
#if !defined(IBM_MemoryErr)
open_mem_error=TRUE;
EndGame(TRUE);
#endif
}

