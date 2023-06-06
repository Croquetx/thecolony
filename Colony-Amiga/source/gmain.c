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
 * int DoCommand( mResult )
 * 		long mResult;
 * Inform(str)
 *		char *str;
 * ShowNum(num)
 *		long num;
 * ShowSize()
 * About()
 * int QSave()
 *---------------------------------------------------------------------
 */
#define EXT 
#include "cgamedefs.h"
extern GrafPtr cWindow;
int cnum = -1;
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
main()
{
/*InitProfile();*/
inits();
notDone=TRUE;/*a flag that indicates what you think it does.*/
MainEvent();
EndGame(TRUE);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
EndGame(iquit)
int iquit;
{

if(!iquit)	
	{
	DialogPtr thedialog;
	int itemhit=0;

	redo:
	thedialog = GetNewDialog(24880,(Ptr)NIL,(WindowPtr)(-1));
	ModalDialog(NIL,&itemhit);
	DisposDialog(thedialog);
	switch(itemhit)
		{
		case 0:/*don't do anything...should not happen*/
			break;
		case 1:/*new game...*/
			gameInit();
			break;
		case 2:/*load old game...*/
			if(!opengame(FALSE))goto  redo;
			change=1;
			break;
		case 3:/*I quit*/
			iquit=TRUE;
			break;
		}
	}
if(iquit)
	{
	/*For appearance sake*/
	CloseWindow(theWindow);
	CloseWindow(infoWindow);
	CloseWindow(moveWindow);
	/*saveprofile();*/
	ExitToShell();
	}
}

/*---------------------------------------------------------------------
 * int MainEvent() 
 * 
 * Main event loop. If anything is done it is done here.
 *---------------------------------------------------------------------
 */
int cchange=0;
extern int colorOn;
MainEvent() 
{
WindowPtr		whichWindow;
Rect			r;
int gne;
int windowpart;
int front;

change=1;
while(notDone==TRUE)
	{	
	if(front=(FrontWindow()==theWindow))
		{
		if(game==COLONY)CThink();
		else  BThink();
		Display();	/*This is wild!						*/
		count++;
		}
	else cchange=TRUE;
	
	gne=WaitNextEvent(everyEvent, &key,0,0L);
	windowpart=FindWindow( key.where, &whichWindow );
	if(gne) /*is there anything to do?*/
		{
		switch (key.what) /*what do you want me to do*/
			{
			case mouseDown:/*mouse is selected... where*/
				switch (windowpart) 
					{
					case inContent:
						if (whichWindow == infoWindow)
							{
							if(armor)DoInfo(key.where);
							else DragWindow(whichWindow,key.where,&screenBits.bounds);
							cchange=TRUE;
							SelectWindow(theWindow);
							}
						else if(whichWindow == moveWindow)
							{
							DragWindow(whichWindow,key.where,&screenBits.bounds);
							SelectWindow(theWindow);
							}
						else if(whichWindow == cWindow)
							{
							if(cWindow!=FrontWindow())SelectWindow(cWindow);
							else CAction();
							}
						else if(whichWindow != moveWindow && whichWindow != infoWindow)
							SelectWindow(whichWindow);
						break;
					case inDesk: 
						DoChimeSound();
						break;
					case inGoAway:
						if(whichWindow==cWindow)
							if(TrackGoAway(cWindow,key.where))
								{
								CloseWindow(cWindow);
								colorOn=FALSE;
								}
						break;
					case inMenuBar:
						DoCommand(MenuSelect(key.where));
					case inSysWindow:
						SystemClick( &key, whichWindow );
						break;
					case inDrag:
						DragWindow(whichWindow,key.where,&screenBits.bounds);
						break;
					case inGrow:
						if (whichWindow==theWindow)
							{
							long    result_size;
							extern int vcenterX;
							extern int vcenterY;
							
							result_size = GrowWindow(theWindow, key.where, &screenBits.bounds);
							if (result_size)
								{
								Width=(int)(result_size & 0xffff);
								Height=(int)(result_size >> 16);
								if(Width>screenR.right-screenR.left)
									Width=screenR.right-screenR.left;
								if(Height>screenR.bottom-screenR.top)
									Height=screenR.bottom-screenR.top;
								SizeWindow(theWindow,Width,Height, -1);
								Clip.top=0;
								Clip.left=-1;
								Clip.right=Width;
								Clip.bottom=Height;
								centerX=Width>>1;
								centerY=Height>>1;
								vcenterX=centerX/6;
								vcenterY=centerY/7;
								SetPort(theWindow);
								ClipRect(&Clip);
								Display();
								}
							}
						break;
					default: ;
					} /* end switch FindWindow */
				break;
			case keyDown:
			case autoKey: 
				{
				char	theChar;
			
				theChar = key.message & charCodeMask;
				if ((key.modifiers & cmdKey) != 0) 
					 DoCommand(MenuKey( theChar ));
				else movecorridor(theChar);
				}
				break;
			case activateEvt:
				break;
			case updateEvt: 
				Update((WindowPtr)key.message);
				break;
			default: ;
			} /* end of case key.what */
		} /* if */
	if(front)
		{
		if(whichWindow==theWindow||(key.modifiers&alphaLock))
			{
			GetMouse(&myPt);
			if(Button())
				{
				if(game==COLONY)
					{
					if(fl==0)CShoot();
					else if(fl==1)ExitFL();
					else if(fl==2)DropFL();
					}
				else BattleShoot();
				}
			if(cnum||cchange){cnum=0; SetCursor(*Cross); cchange=FALSE; }
			action();
			}
		else if(cnum != -1||cchange)
			{
			if(cnum==0)DoChimeSound();
			SetCursor(&arrow);
			cnum=-1;
			cchange=0;
			}
		}
	}
}
/*----------------------------------------------------------------------*/
Update(wnum)
WindowPtr wnum;
{
if(theWindow == wnum) 
	UpdateThe();
else if (moveWindow == wnum) 
	UpdateMove();
else if (infoWindow == wnum) 
	UpdateInfo();
else if (cWindow == wnum)
	ColorUpdate();
}
/*---------------------------------------------------------------------
 * int DoCommand(mResult)
 * long mResult;
 *
 * This is actually the menu command arbitrator. It simply performs 
 * the requested menu command.
 *---------------------------------------------------------------------
 */
int presaved=FALSE;
int DoCommand( mResult )
long mResult;
{
int		theItem, temp;
Str255	name;
WindowPeek wPtr;
char s[255];
int saved;
extern int cChanged;

theItem = LoWord( mResult );
switch (HiWord(mResult)) 
	{
	case APPLEMENU:/*Desk accesories and About...*/
		switch(theItem)
			{
			case 0:
				break;
			case 1:
				About();
				break;
			case 2:
				Colorize();
				break;
			default:
				GetItem(myMenus[0], theItem,&name);
				OpenDeskAcc( &name );
				SetPort( theWindow );
				break;
			}
		break;
	case OPTIONS:
		switch(theItem)
			{
			case 1:
				soundon= (!soundon);
				CheckItem(myMenus[3],1,soundon);
				break;
			case 2:
				crosshair=(!crosshair);
				CheckItem(myMenus[3],2,crosshair);				
				break;
			case 3:
				polyfill=(!polyfill);
				CheckItem(myMenus[3],3,!polyfill);				
				break;
			case 4:
				cshoot=(!cshoot);
				CheckItem(myMenus[3],4,cshoot);				
				break;
			}
		break;
	case FILEMENU:
		switch(theItem)
			{
			case 1:/*new*/
				switch(QSave(2002))
					{
					case 1:
						saved=savegame(TRUE);
						presaved = presaved || saved;
					case 2:
						gameInit();
					case 3:
						break;
					}
				break;
			case 2:/*open*/
				switch(QSave(2002))
					{
					case 1:
						saved=savegame(TRUE);
						presaved=presaved||saved;
					case 2:
						saved=opengame(FALSE);
						presaved=presaved||saved;
					case 3:
						break;
					}
				change=1;
				break;
			case 3:/*save*/
				saved=savegame(!presaved);
				presaved=presaved||saved;
				break;
			case 4:/*save as...*/
				saved=savegame(TRUE);
				presaved=presaved||saved;
				break;
			case 5:/*----------------*/
				break;
			case 6:
				if(cChanged)
					switch(QSave(4668))
					{
					case 1:
						SaveColor();
					case 2:
						LoadColor();
					case 3:
						break;
					}
				else LoadColor();
				break;
			case 7:
				SaveColor();
				break;
			case 8:/*----------------*/
				break;
			case 9:/*quit*/
				switch(QSave(2002))
					{
					case 1:
						saved=savegame(TRUE);
						presaved=presaved||saved;
						if(saved)notDone=FALSE;
						break;
					case 2:
						notDone=FALSE;
					case 3:
						break;
					}
				if(cChanged&&notDone==FALSE)
					switch(QSave(4668))
					{
					case 1:
						SaveColor();
						break;
					case 2:
					case 3:
						break;
					}
				break;
			}
		break;
	case EDITMENU: /*This does'nt seem to work...*/
		switch(theItem)
			{
			case 1:/*undo*/
			case 2:/*----*/
			case 3:/*cut*/
			case 4:/*copy*/
			case 5:/*paste*/
			case 6:/*----*/
				SystemEdit(theItem-1);
				break;
			}
		break;
	}
HiliteMenu(0);/*Turn it off*/
cchange=TRUE;
SetCursor(*Cross);
}
/*---------------------------------------------------------------------
 * Inform(str)
 * char *str;
 * 
 * Psuedo dialog box that informs the developer about what he can not
 * see. Displays a string in a box. Make sure that the string has a
 * \p in front of it indicating that it is a Pascal string or the length 
 * must be calculated directly:
 *---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
Inform(str)
char *str;
{
Rect r;
WindowPtr aWindow;
GrafPtr	savePort;
WindowRecord wRecord;
int drawx,width;

GetPort( &savePort );
SetRect(&r, 56, 60, 426, 132);
SetPort((aWindow = NewCWindow( &wRecord , &r, "\p", 1, 1, -1L, 0, 0L)));
TextFont(0);
drawx=(426-152)/2;
width=StringWidth(str)/2;
MoveTo(drawx-width, 35 );
DrawString(str);
do { /*nothing*/ } while ( Button() );
do { /*nothing*/ } while ( !Button() );
CloseWindow(aWindow);
SetPort(savePort);
FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);
}

PowerInform(str,r1)
char *str;
Rect *r1;
{
Rect r;
WindowPtr aWindow;
GrafPtr	savePort;
WindowRecord wRecord;
int drawx,width;

GetPort( &savePort );
r.top=197;
r.bottom=215;
r.left=4;
r.right=88;
SetPort((aWindow = NewCWindow( &wRecord , &r, "\p", 1, 3, -1L, 0, 0L)));
TextSize(12);
TextFont(190);
TextMode(srcXor);
drawx=(r.right-r.left)/2;
width=StringWidth(str)/2;
MoveTo(drawx-width, 14 );
DrawString(str);
do { /*nothing*/ } while ( Button() );
CloseWindow(aWindow);
SetPort(savePort);
FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
ShowNum(num)
long num;
{
char str[255];
NumToString(num,str);
Inform(str);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
Debug(str,num)
char *str;
long num;
{
char wstr[255];
char nstr[255];
NumToString(num,nstr);
Catenate(wstr,str,nstr);
Inform(wstr);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
ShowSize()
{
long cnt;

cnt = FreeMem();
ShowNum(cnt);
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
char *about0[]={
		"\pThe Colony",
		"\pBy David A. Smith",
		"\pCopyright © 1989"};
char *about1[]={
		"\pSpecial thanks to",
		"\pMike Kahl & THINK'S LightspeedC™",
		"\pSymantec Corporation"};
About()
{
Rect r1,r2;
WindowPtr aWindow;
GrafPtr	savePort;
int *screen,*word;
int width,height,centerx,centery;
WindowRecord wRecord;
int swidth,i;

UnLoad();
r1.left=rScreen.left;
r1.right=width=rScreen.right;
r1.top=rScreen.top+20;
r1.bottom=height=rScreen.bottom;
InsetRect(&r1,8,8);
GetPort( &savePort );
SetPort((aWindow = NewCWindow( &wRecord , &r1, "\p", 1, 1, -1L, 0, 0L)));
r2.right=r1.right-r1.left;
r2.left=0;
r2.bottom=r1.bottom-r1.top;
r2.top=0;
HideCursor();
centerx=(r2.left+r2.right)/2;
centery=(r2.top+r2.bottom)/2;
TextFont(0);
TextMode(srcXor);
FillRect(&r2,black);
makestars(&r2,1);
FillRect(&r2,black);
DoPicture(-32564,&r2);
makestars(&r2,1);
FillRect(&r2,black);
for(i=0;i<3;i++)
	{
	swidth=StringWidth(about1[i])/2;
	MoveTo( centerx-swidth, (centery-20)+20*i);
	DrawString(about1[i]);
	}
makestars(&r2,1);
FillRect(&r2,black);
ShowCursor();
CloseWindow(aWindow);
SetPort(savePort);
FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);
CUnLoad();
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int QSave(dnum)
{
DialogPtr thedialog;
int itemhit=0;

thedialog = GetNewDialog(dnum,(Ptr)NIL,(WindowPtr)(-1));
ModalDialog(NIL,&itemhit);
DisposDialog(thedialog);
switch(itemhit)
	{
	case 0:/*don't do anything...should not happen*/
		break;
	case 1:/*yes...*/
		return(1);
		break;
	case 2:/*no*/
		return(2);
		break;
	case 3:/*I quit*/
		return(0);
		break;
	}
}