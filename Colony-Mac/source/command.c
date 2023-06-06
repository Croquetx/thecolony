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
 * SetButt(br,from,size,x,y)
 * infomap()
 *---------------------------------------------------------------------- 
 */
void OpenAFile();
#define EXT extern
#include "cgamedefs.h"
/*---------------------------------------------------------------------- 
 *movecorridor(key)														 
 *	sets the angle or location to be drawn next.						 
 *---------------------------------------------------------------------- 
 */
char lastchar=0;
movecorridor(key)
char key;
{
int xnew,ynew,chckang=0;
int i;
char str[255];

Me.dx=Me.dy=0;
if(key>='a'&&key<='z')key-='a'-'A';
switch(key)
	{
	case ' ':
		if(fl)return;
		if(game==COLONY)CShoot();
		else BattleShoot();
		return;
		break;
	case 'Q':/*rotate to the left*/
		Me.ang+=speed;
		Me.look+=speed;
		change=1;
		break;
	case 'E':/*rotate to the right*/
		Me.ang-=speed;
		Me.look-=speed;
		change=1;
		break;
	case 'W':/*move forwards*/
		xnew=Me.xloc+(xai[Me.ang]<<speedshift);
		ynew=Me.yloc+(yai[Me.ang]<<speedshift);
		chckang=1;
		break;
	case 'A':/*move to the left*/		
		xnew=Me.xloc-(yai[Me.ang]<<speedshift);
		ynew=Me.yloc+(xai[Me.ang]<<speedshift);
		chckang=1;
		break;
	case 'D':/*move to the right*/
		xnew=Me.xloc+(yai[Me.ang]<<speedshift);
		ynew=Me.yloc-(xai[Me.ang]<<speedshift);
		chckang=1;
		break;
	case 'S':/*move backwards*/
		xnew=Me.xloc-(xai[Me.ang]<<speedshift);
		ynew=Me.yloc-(yai[Me.ang]<<speedshift);
		chckang=1;
		break;
	case 'Z':/*look to the left*/
		Me.look=Me.ang+64;
		change=1;
		break;
	case 'C':/*look to the right*/
		Me.look=Me.ang-64;
		change=1;
		break;
	case 'X':/*look behind you*/
		Me.look=Me.ang+128;
		change=1;
		break;		
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
		speedshift=key-'0';
		speed=1<<(speedshift-1);
		return;
		break;
	case '6':
	case '7':
	case '8':
	case '9':
		break;
	case 'M':
		if(lastchar==0 && Shift())lastchar='M';
		else lastchar=0;
		break;
	case 'Y':
		if(lastchar=='M' && Shift())lastchar='Y';
		else lastchar=0;
		break;
	case 'B':
		if(lastchar=='Y' && Shift())lastchar='B';
		else lastchar=0;
		break;
	case 'H':
		if(lastchar=='B' && Shift())lastchar='H';
		else lastchar=0;
		break;
	case 'I':
		if(lastchar=='H' && Shift())lastchar='I';
		else lastchar=0;
		break;
	case 'V':
		if(lastchar=='I' && Shift())
			{
			lastchar=0;
			SetPower(32000,32000,32000);
			}
		else lastchar=0;
	default:
		lastchar=0;
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
}
/*----------------------------------------------------------------------*/
int Shift()
{
if(key.modifiers & shiftKey)return(TRUE);
return(FALSE);
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
robot=checkwall(xnew,ynew,&Me);
if(robot>0&&!(key.modifiers&optionKey))
	{
	if(Object[robot].type>=20)
	{
	switch(fl)
		{
		case 0:/*no forklift*/
		switch(Object[robot].type)
			{
			case DESK:
		DoDesk((int)(*map.data)[Object[robot].where.xindex][Object[robot].where.yindex][4][3],
			   (int)(*map.data)[Object[robot].where.xindex][Object[robot].where.yindex][4][4]);
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
					robotarray[Object[robot].where.xindex][Object[robot].where.yindex]=0;
					Object[robot].alive=0;
					checkwall(xnew,ynew,&Me);
					Me.look=Me.ang=Object[robot].where.ang;
					fl=1;
					}
				break;
			case CONSOLE:
				switch((*map.data)[Object[robot].where.xindex][Object[robot].where.yindex][4][3])
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
				switch((*map.data)[Object[robot].where.xindex][Object[robot].where.yindex][4][3])
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
				{
				Rect rstart;
				char mapdata[5];
				struct passpatch from;
				int tnum;
				from.level  = level;
				from.xindex = Object[robot].where.xindex;
				from.yindex = Object[robot].where.yindex;
				if(patchmapto(&from,mapdata))tnum = mapdata[3];
				else tnum=(*map.data)[Object[robot].where.xindex]
									 [Object[robot].where.yindex][4][3];
				SetPort(theWindow);
				RLocalToGlobal(&Clip,&rstart);
				DoText(&rstart,tnum,0);
				}
				break;
			case TV:
				{
				Rect rstart;
				
				SetPort(theWindow);
				RLocalToGlobal(&Clip,&rstart);
				if(level==1)DoText(&rstart,56,0);
				else DoText(&rstart,16,0);
				}
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
					robotarray[Object[robot].where.xindex][Object[robot].where.yindex]=0;
					Object[robot].alive=0;
					fl=2;
					}
				break;
			case REACTOR:
				if(corestate[coreindex]==1)/*the reactor is open and there is an object here*/
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
	CUnLoad();
	}
else if(robot)DoBonkSound();
robotarray[Me.xindex][Me.yindex]=MENUM;
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
ExitFL()
{
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
	if(checkwall(xnew,ynew,&Me)){DoChimeSound();Me.type=MENUM;return(0);}
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
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DropFL()
{
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
		if(checkwall(xnew,ynew,&Me)){DoChimeSound(); Me.type=MENUM; return;}
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
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
ExitTeleport()
{
int i;
int xnew,ynew,xloc,yloc,xindex,yindex;
int done=FALSE;
struct passpatch to;
int count=0;

Me.ang=48;
xloc=Me.xloc;
yloc=Me.yloc;
while(!Forward() && count<4)
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
xloc=xloc>>8; yloc=yloc>>8;
xloc=(xloc<<8)+128; yloc=(yloc<<8)+128;
for(i=MENUM+1;i<robotnum && !done;i++)
	{
	if(!Object[i].alive)	
		{CreateObject(i,TELEPORT,xloc,yloc,0);done=TRUE;}
	}
if(!done){CreateObject(robotnum,TELEPORT,xloc,yloc,0); robotnum++;}
return(1);
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int Forward()
{
int xindex,yindex,xnew,ynew;

xindex=Me.xindex; yindex=Me.yindex;
Me.type=2;
while(Me.xindex==xindex && Me.yindex==yindex)
	{
	xnew=Me.xloc+cost[Me.ang];
	ynew=Me.yloc+sint[Me.ang];
	if(checkwall(xnew,ynew,&Me)){DoChimeSound(); Me.type=MENUM; return(FALSE);}
	}
Me.type=MENUM;
return(TRUE);
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
CCenter()
{
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
		CUnLoad();
		break;
	case LGHOLEFLR:
		/*full size pit	*/
		tunnel(TRUE,(*map.data)[Me.xindex][Me.yindex][CENTER]);
		CUnLoad();
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
	if(xcheck>64&&xcheck<192&&ycheck>64&&ycheck<192)Eat();
	}
if(doorsound){ DoDoorSound(); doorsound=!doorsound;}
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
int xnew,ynew;
int av,v;
int xcheck,ycheck,inside=TRUE,chckang=0;
int windowpart;
WindowPtr		whichWindow;

avelocity=(myPt.h-centerX)/vcenterX;
velocity=(myPt.v-centerY)/vcenterY;
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
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
SetButt(br,from,size,x,y)
Rect *br,*from;
int x,y,size;
{
if(y!=0)
	{
	br->left=3+from->left+x*size;
	br->top=3+from->top+y*size;
	br->right=br->left+size-5;
	br->bottom=br->top+size-5;
	}
else
	{
	br->left=3+from->left;
	br->top=3+from->top+y*size;
	br->right=br->left+(3*size)-5;
	br->bottom=br->top+size-5;
	}
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
/*#define CSIZE 6
#define CSIZE2 3
#define TSIZE 280
infomap()
{
int x,y;

GetMouse(&myPt);
x=(myPt.h)/CSIZE;
y=(TSIZE-myPt.v)/CSIZE;
if(robotarray[x][y])showinfo(x,y,robotarray[x][y],"\pinfomap");
else if(foodarray[x][y])showinfo(x,y,foodarray[x][y],"\pinfomap");
}
*/