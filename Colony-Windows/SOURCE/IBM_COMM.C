/*  #define IBM_movecorridor  */
/*  #define IBM_CCommand   /*	*/
/*  #define IBM_ExitFL */
/*  #define IBM_DropFL */
/*  #define IBM_ExitTeleport*/
/*  #define IBM_CCenter  /*  */
/*  #define IBM_action	 /*  */
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
 /*---------------------------------------------------------------------- 
 *	Command.c														 
 *	This file contains the functions that deal with the users move ments.
 *---------------------------------------------------------------------- 
 * movecorridor(key)
 * 		char key;
 * CCommand(xnew,ynew)
 *		int xnew,ynew;
 * ExitFL()
 * DropFL()
 * ExitTeleport()
 * CCenter()
 * action()
 *---------------------------------------------------------------------- 
 */
void OpenAFile();
#define EXT extern
#include "gamedefs.h"
/*---------------------------------------------------------------------- 
 *movecorridor(key)
 *	sets the angle or location to be drawn next.
 *---------------------------------------------------------------------- 
 */
movecorridor(ASCII, ScanCode)
unsigned char ASCII, ScanCode; /* ASCII, ScanCode values of pressed key */
{
#if !defined(IBM_movecorridor)
int xnew,ynew,chckang=0;
int i;
char str[255];

Me.dx=Me.dy=0;
switch(ScanCode)
	{
	/* Shoot */
	case 57: /* space */
	case 82: /* 0/Ins */
	case 146: /* ctrl 0/Ins */
		if(fl)
			 {
			 if(fl==1)
			     ExitFL();
			 else if(fl==2)
			     DropFL();
			 }
		else
			{
			cshoot=FALSE;
			if(game==COLONY)doCShoot();
			else BattleShoot();
			}
		return;
		break;
	/* Rotate to the left */
	case 16: /* q */
	case 71: /* 7/home */
	case 119: /* ctrl 7/home */
		Me.ang+=speed;
		Me.look+=speed;
		change=1;
		break;
	/* Rotate to the right */
	case 18: /* e */
	case 73: /* 9/page up */
	case 132: /* ctrl 9/page up */
		Me.ang-=speed;
		Me.look-=speed;
		change=1;
		break;
	/* Move forward */
	case 17: /* w */
	case 72: /* 8/up arrow */
	case 141: /* ctrl 8/up arrow */
		xnew=Me.xloc+(xai[Me.ang]<<speedshift);
		ynew=Me.yloc+(yai[Me.ang]<<speedshift);
		chckang=1;
		break;
	/* Move to the left */
	case 30: /* a */
	case 75: /* 4/left arrow */
	case 115: /* ctrl 4/left arrow */
		xnew=Me.xloc-(yai[Me.ang]<<speedshift);
		ynew=Me.yloc+(xai[Me.ang]<<speedshift);
		chckang=1;
		break;
	/* Move to the right */
	case 32: /* d */
	case 77: /* 6/right arrow */
	case 116: /* ctrl 6/right arrow */
		xnew=Me.xloc+(yai[Me.ang]<<speedshift);
		ynew=Me.yloc-(xai[Me.ang]<<speedshift);
		chckang=1;
		break;
	/* Move backwards */
	case 31: /* s */
	case 76: /* 5 */
	case 143: /* ctrl 5 */
		xnew=Me.xloc-(xai[Me.ang]<<speedshift);
		ynew=Me.yloc-(yai[Me.ang]<<speedshift);
		chckang=1;
		break;
	/* Look to the left */
	case 44: /* z */
	case 79: /* 1/end */
	case 117: /* ctrl 1/end */
		Me.look=Me.ang+64;
		change=1;
		break;
	/* Look to the right */
	case 46: /* c */
	case 81: /* 3/page down */
	case 118: /* ctrl 3/page down */
		Me.look=Me.ang-64;
		change=1;
		break;
	/* Look behind you */
	case 45: /* x */
	case 80: /* 2/down arrow */
	case 145: /* ctrl 2/down arrow */
		Me.look=Me.ang+128;
		change=1;
		break;
	/* Change speed */
	case 2: /* 1 */
	case 3:	/* 2 */
	case 4:	/* 3 */
	case 5: /* 4 */
	case 6: /* 5 */
		speedshift = ScanCode - 1; /* convert ScanCode to number: 1-5 */
		speed=1<<(speedshift-1);
		return;
		break;
	case 7: /* 6 */
	case 8: /* 7 */
	case 9: /* 8 */
	case 10: /* 9 */
	case 11: /* 0 */
		break;
	}
if(chckang)
	{
	if(game==COLONY)CCommand(xnew,ynew);
	else BattleCommand(xnew,ynew);
	}
#endif
}

/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
CCommand(xnew,ynew)
int xnew,ynew;
{


int xcheck,ycheck;
int robot,i;
char str[255];
struct passpatch from,to;

robotarray[Me.xindex][Me.yindex]=0;
robot=checkwall(xnew,ynew,(Locate far *)&Me);


#if !defined(IBM_CCommand)


if(robot>0&&!(key.State&0x04))
	{
	if(Object[robot].type>=20)
	{
	switch(fl)
		{
		case 0:/*no forklift*/
		switch(Object[robot].type)
			{
			case DESK:
		DoDesk((int)(*map.data)[Object[robot].where.xindex]
							   [Object[robot].where.yindex][4][3],
			   (int)(*map.data)[Object[robot].where.xindex]
							   [Object[robot].where.yindex][4][4]);
				break;
			case FORKLIFT:
				if(DoForkLift())
					{
					from.level=level;
					from.xindex=Object[robot].where.xindex;
					from.yindex=Object[robot].where.yindex;
					carrypatch[0].level=100;
					carrypatch[0].xindex=0;
					carrypatch[0].yindex=0;
					carrypatch[0].xloc=0;
					carrypatch[0].yloc=0;
					carrypatch[0].ang=0;
					newpatch(FORKLIFT,&from,&carrypatch[0],
						(*map.data)[from.xindex][from.yindex][4]);
					robotarray[Object[robot].where.xindex]
						[Object[robot].where.yindex]=0;
					Object[robot].alive=0;
					checkwall(xnew,ynew,(Locate far *)&Me);
					Me.look=Me.ang=Object[robot].where.ang;
					fl=1;
					}
				break;
			case CONSOLE:
				switch((*map.data)[Object[robot].where.xindex]
					[Object[robot].where.yindex][4][3])
					{
					case 0:
						break;
					case 1:/*Reactor console*/
						DoReactor();
						break;
					case 2:/*Main ship controls*/
						DoControls();
						break;
					case 3:/*Security console*/
						DoSecurity();
						break;
					}
				break;
			case PROJECTOR:
				switch((*map.data)[Object[robot].where.xindex]
					[Object[robot].where.yindex][4][3])
					{
					case 0:
						break;
					case 1:/*creature feature*/
						DoCreatures();
						break;
					case 2:/*Teleporters*/
						DoTeleShow();
						break;
					}
				break;
			case POWERSUIT:
				DoPowerSuit();
				break;
			case TELEPORT:
				DoTeleport(robot);
				break;
			case DRAWER:
				DoVanity((int)(*map.data)[Object[robot].where.xindex]
										 [Object[robot].where.yindex][4][3]);
				break;
			case PLANT:
			case CCHAIR:
			case BED:
			case COUCH:
			case CHAIR:
				break;
			case SCREEN:
				FullOfStars();
				break;
			case TABLE: break;
			case PTOILET:
			case TOILET:
				DoToiletSound();
				break;
			case TUB:
				DoBathSound();
				break;
			case SINK:
				DoSinkSound();
				break;
			case CRYO:
				DoText((char*)NULL,
				(int)(*map.data)[Object[robot].where.xindex]
								[Object[robot].where.yindex][4][3],0);
				break;
			case TV:
				if(level==1)DoText((char*)NULL,56,0);
				else DoText((char*)NULL,16,0);
				break;
			}	
		break;
	case 1:/*empty forklift*/
		switch(Object[robot].type)
			{
			case CRYO:
			case BOX1:
			case BOX2:
			case TELEPORT:
				if(DoLift(0,Object[robot].type))
					{
					from.level=level;
					from.xindex=Object[robot].where.xindex;
					from.yindex=Object[robot].where.yindex;
					carrypatch[1].level=100;
					carrypatch[1].xindex=1;
					carrypatch[1].yindex=1;
					carrypatch[1].xloc=1;
					carrypatch[1].yloc=1;
					carrypatch[1].ang=1;
					newpatch(Object[robot].type,&from,&carrypatch[1],
						(*map.data)[from.xindex][from.yindex][4]);
					carrytype=Object[robot].type;
					robotarray[Object[robot].where.xindex]
						[Object[robot].where.yindex]=0;
					Object[robot].alive=0;
					fl=2;
					}
				break;
			case REACTOR:
				/*the reactor is open and there is an object here*/
				if(corestate[coreindex]==1)
				if(DoLift(0,Object[robot].type))
					{
					carrytype=Object[robot].type;
					corepower[2]=corepower[coreindex];
					corepower[coreindex]=0;
					corestate[coreindex]=2;
					fl=2;
					}
				break;
			case SCREEN:
				FullOfStars();
				break;
			}
			break;
	case 2:/*carrying object*/
		switch(Object[robot].type)
			{
			case  REACTOR:
				if(carrytype==REACTOR)
					{
					if(corestate[coreindex]==2)
						if(!DoLift(1,carrytype))
						{
						carrytype=0;
						corestate[coreindex]=1;
						corepower[coreindex]=corepower[2];
						fl=1;
						}
					}
				break;
			case TELEPORT:
				DoTeleport(robot);
				break;
			case SCREEN:
				FullOfStars();
				break;
			default:
				DoBonkSound();
				break;
			}
		break;
		}
	}
	/*   randy did this	 if(Mac512)CUnLoad();  */
	}
else if(robot)DoBonkSound();

#endif

robotarray[Me.xindex][Me.yindex]=MENUM;

}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
ExitFL()
{
#if !defined(IBM_ExitFL)
int i;
int xnew,ynew,xloc,yloc,xindex,yindex;
int done=FALSE;
struct passpatch to;

xloc=Me.xloc; yloc=Me.yloc;
xindex=Me.xindex; yindex=Me.yindex;
while(Me.xindex==xindex && Me.yindex==yindex)
	{
	xnew=Me.xloc-cost[Me.ang];
	ynew=Me.yloc-sint[Me.ang];
	Me.type=2;
	if(checkwall(xnew,ynew,(Locate far *)&Me)){DoChimeSound();Me.type=MENUM;return(0);}
	Me.type=MENUM;
	}
xloc=xloc>>8;
xloc=(xloc<<8)+128;
yloc=yloc>>8;
yloc=(yloc<<8)+128;
for(i=MENUM+1;i<robotnum && !done;i++)
	{
	if(!Object[i].alive)	
		{CreateObject(i,FORKLIFT,xloc,yloc,Me.ang);done=TRUE;}
	}
if(!done){CreateObject(robotnum,FORKLIFT,xloc,yloc,Me.ang); robotnum++;}
to.level=level;
to.xindex=xindex;
to.yindex=yindex;
to.xloc=xloc;
to.yloc=yloc;
to.ang=Me.ang;
newpatch(FORKLIFT,&carrypatch[0],&to,0L);
fl=FALSE;
return(1);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DropFL()
{
#if !defined(IBM_DropFL)
int i;
int xnew,ynew,xloc,yloc,xindex,yindex,ang;
int done=FALSE;
struct passpatch to;

if(!DoLift(1,carrytype))
	{
	if(carrytype==REACTOR)
		{
		DoGlassSound();
		carrytype=0;
		fl=1;
		return;
		}
	xloc=Me.xloc; yloc=Me.yloc;
	xindex=Me.xindex; yindex=Me.yindex;
	while(Me.xindex==xindex && Me.yindex==yindex)
		{
		xnew=Me.xloc-cost[Me.ang];
		ynew=Me.yloc-sint[Me.ang];
		Me.type=2;
		if(checkwall(xnew,ynew,(Locate far *)&Me)){DoChimeSound(); Me.type=MENUM; return;}
		Me.type=MENUM;
		}
	if(carrytype==TELEPORT)ang=0;
	else ang=Me.ang;
	xloc=xloc>>8;
	xloc=(xloc<<8)+128;
	yloc=yloc>>8;
	yloc=(yloc<<8)+128;
	for(i=MENUM+1;i<robotnum && !done;i++)
		{
		if(!Object[i].alive)	
			{CreateObject(i,carrytype,xloc,yloc,ang);done=TRUE;}
		}
	if(!done){CreateObject(robotnum,carrytype,xloc,yloc,ang); robotnum++;}
	to.level=level;
	to.xindex=xindex;
	to.yindex=yindex;
	to.xloc=xloc;
	to.yloc=yloc;
	to.ang=Me.ang;
	newpatch(carrytype,&carrypatch[1],&to,0L);
	fl=1;
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
ExitTeleport()
{
#if !defined(IBM_ExitTeleport)
int i;
int done=FALSE;
struct passpatch to;
int count=0;
int xloc,yloc;

Me.ang=48;
xloc=Me.xloc;
yloc=Me.yloc;
while(!Forward()&&count<4)
	{
	Me.xloc=xloc;
	Me.yloc=yloc;
	Me.ang+=64;
	count++;
	}
if(count==4)
	{
	DoChimeSound();
	Me.type=MENUM;
	return(0);
	}
xloc=xloc>>8;  yloc=yloc>>8;
xloc=(xloc<<8)+128; yloc=(yloc<<8)+128;

for(i=MENUM+1;i<robotnum && !done;i++)
	{
	if(!Object[i].alive)	
		{CreateObject(i,TELEPORT,xloc,yloc,0);done=TRUE;}
	}
if(!done){CreateObject(robotnum,TELEPORT,xloc,yloc,0); robotnum++;}
return(1);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
Forward()
{
int xindex,yindex,xnew,ynew;

xindex=Me.xindex; yindex=Me.yindex;
Me.type=2;
while(Me.xindex==xindex&&Me.yindex==yindex)
	{
	xnew=Me.xloc+cost[Me.ang];
	ynew=Me.yloc+sint[Me.ang];
	if(checkwall(xnew,ynew,&Me))
		{Me.type=MENUM;return(FALSE);}
	}
Me.type=MENUM;
return(TRUE);
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
CCenter()
{
#if !defined(IBM_CCenter)
int xcheck,ycheck;

switch((*map.data)[Me.xindex][Me.yindex][4][0])
	{
	case 0:
		break;
	case SMHOLEFLR:
		xcheck=abs(Me.xloc-(Me.xindex<<8));
		ycheck=abs(Me.yloc-(Me.yindex<<8));
		if(xcheck>64&&xcheck<192&&ycheck>64&&ycheck<192)
			tunnel(TRUE,(*map.data)[Me.xindex][Me.yindex][CENTER]);
		/*  if(Mac512)CUnLoad();  */
		break;
	case LGHOLEFLR:
		/*full size pit	*/
		tunnel(TRUE,(*map.data)[Me.xindex][Me.yindex][CENTER]);
		/*  if(Mac512)CUnLoad();  */
		break;
	case HOTFOOT:
		DoBzzzSound();
		SetPower(-(5<<level),-(5<<level),-(5<<level));
		break;
	}
if(foodarray[Me.xindex][Me.yindex]&&!fl)
if(Object[foodarray[Me.xindex][Me.yindex]].type<BASEOBJECT)
	{
	xcheck=abs(Me.xloc-(Me.xindex<<8));
	ycheck=abs(Me.yloc-(Me.yindex<<8));
	if(xcheck>64&&xcheck<192&&ycheck>64&&ycheck<192)MeEat();
	}
if(doorsound){ DoDoorSound(); doorsound=!doorsound;}
#endif
}
/*---------------------------------------------------------------------
 * action()
 * Where am I going?.
 *---------------------------------------------------------------------
 */
int velocity,avelocity;
int vcenterX,vcenterY;
action()
{
#if !defined(IBM_action)
int xnew,ynew;
int av,v;
int xcheck,ycheck,inside=TRUE,chckang=0;
int windowpart;
/* WindowPtr  whichWindow; */
extern int capslock;

avelocity=(myPt.h-centerX)/vcenterX;
velocity=(myPt.v-centerY)/vcenterY;
if(velocity>6)velocity=6;
if(velocity<-6)velocity=-6;
if(avelocity>7)avelocity=7;
if(avelocity<-7)avelocity=-7;
if(capslock)
	{
	avelocity=(avelocity>>1);
	velocity=(velocity>>1);
	}
/*move forward*/
if(velocity)
	{
	chckang=TRUE;
	if(myPt.v >= centerY)
		{
		velocity--;
		if(velocity>4)velocity=4;
		xnew=Me.xloc-(xai[Me.ang]<<velocity);
		ynew=Me.yloc-(yai[Me.ang]<<velocity);
		}
	else
		{
		v = -velocity;
		v--;
		if(v>5)v=5;
		xnew=Me.xloc+(xai[Me.ang]<<v);
		ynew=Me.yloc+(yai[Me.ang]<<v);
		}
	}
if(avelocity)
	{
	if(avelocity>0)
		{
		if(avelocity>6)avelocity=6;
		av=1<<(avelocity-1);
		Me.ang-=av;
		Me.look-=av;
		}
	else
		{
		av= -avelocity;
		if(av>6)av=6;
		av=1<<(av-1);
		Me.ang+=av;
		Me.look+=av;
		}
	}
switch(game)
	{
	case BATTLE:
		if(chckang)BattleCommand(xnew,ynew);
		break;
	case COLONY:
		if(chckang)CCommand(xnew,ynew);
		break;
	case SPACEWAR:
		break;
	}
change=1;
#endif
}
extern int RightHanded;
extern int drewDashBoard, showDashBoard;
extern int gametest;
extern int jmouse;
doFunctionKey(int numfkey)
{
int i;
int ocenterX, ocenterY;

DoDitSound();
if (showDashBoard)drewDashBoard= 0;
switch(numfkey)
    {
    case 1:		    /*	  help key   */
		Help(1);
		break;
	case 2:			/*save game - newgame/quitgame*/
		Help(2);
		break;
	case 3:
		Help(3);
		break;
	case 4:
		Help(4);
		break;
	case 5:/*save game*/
		saveIBMgame();
		break;
	case 6:		    /*load game*/
		loadIBMgame();
		if (showDashBoard)drewDashBoard= 0;
		break;
    case 7:		/*	  dashboard key   */
		if (showDashBoard)
			{
			drewDashBoard= 0;
			showDashBoard= False;
			screenR.left= sR.left;
			}
		else
			{
			showDashBoard= True;
			screenR.left= sR.left+4*pix_per_Qinch_x+4;
			}
		Width=screenR.right-screenR.left;
		Height=screenR.bottom-screenR.top;
		ocenterX = centerX;
		ocenterY = centerY;
		centerX=(screenR.right+screenR.left)>>1;
		centerY=(screenR.bottom+screenR.top)>>1;
		vcenterX=(Width/2)/6;
		vcenterY=(Height/2)/7;
		TrackCursor(FALSE);
		if (!jmouse)
			MoveCursor(centerX, centerY);
		else
			{
			int cursorX, cursorY;
			int dummy1, dummy2;
			QueryCursor(&cursorX, &cursorY, &dummy1, &dummy2);
			MoveCursor(cursorX+(centerX-ocenterX),
				cursorY+(centerY-ocenterY));
			}
		TrackCursor(TRUE);
		ClipRect(&screenR);
		Clip.left=screenR.left;
		Clip.right=screenR.right;
		Clip.top=screenR.top;
		Clip.bottom=screenR.bottom;
		if (!jmouse)
			LimitMouse(screenR.left, screenR.top,
				screenR.right, screenR.bottom);
		else
			LimitJMouse(screenR.left, screenR.top,
				screenR.right, screenR.bottom,
				centerX, centerY);
		break;
    case 8:		    /* toggle poly fill	*/
		polyfill= !polyfill;
		break;
    case 9:		    /*	     */
		soundon=!soundon;
		DoDitSound();
		break;
    case 10:		     /*  more power please   */
		Pause();
		break;
    default:
		break;
    }
}
