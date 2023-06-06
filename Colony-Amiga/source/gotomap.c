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
 * gotomap.c
 *----------------------------------------------------------------------* 
 * int GoToMap(mapdata,direction)
 * 		char mapdata[5];
 *		int direction;
 * OpenDoor(mapdata)
 *		char mapdata[5];
 * OpenElevator(mapdata)
 *		char mapdata[5];
 * OpenAirLock(mapdata,direction)
 *		char mapdata[5];
 *		int direction;
 * UpStairs(mapdata)
 *		char mapdata[5];
 * DownStairs(mapdata)
 *		char mapdata[5];
 * int GoTo(mapdata)
 *		unsigned char mapdata[5];
 * DoUpStairs()
 * DoDnStairs()
 *----------------------------------------------------------------------*/
#define EXT extern
#include "cgamedefs.h"
extern int ctype;

/*----------------------------------------------------------------------*/
int GoToMap(mapdata,direction)
char mapdata[5];
int direction;
{
switch(mapdata[0])
	{
	case 0:/*no wall*/
		return(FALSE);
		break;
	case 1:/*blank wall*/
		break;
	case DOOR:
		/*Inform("\pDoor");*/
		return(OpenDoor(mapdata)); 
		CUnLoad();
		break;
	case WINDOW:
		break;
	case SHELVES:
		break;
	case UPSTAIRS:
		/*Inform("\pUpstairs");*/
		return(UpStairs(mapdata));
		break;
	case DNSTAIRS:
		return(DownStairs(mapdata));
		break;
	case CHAR:
		break;
	case GLYPH:
		break;
	case ELEVATOR:
		/*Inform("\pElevator");*/
		return(OpenElevator(mapdata));
		CUnLoad();
		break;
	case TUNNEL:
		/*Inform("\pTunnel");*/
		return(tunnel(FALSE,mapdata));
		CUnLoad();
		break;
	case AIRLOCK:
		/*Inform("\pAirlock");*/
		return(OpenAirLock(mapdata,direction));
		CUnLoad();
		break;
	}		
return(FALSE);
}
/*----------------------------------------------------------------------*/
OpenDoor(mapdata)
char mapdata[5];
{
if(mapdata[1])/*closed or locked door*/
	{
	if(ctype==0)return(0);/*don't let the robots go if closed or locked*/
	if(DoDoor(mapdata[1]))return(GoTo(mapdata));
	else return(0);
	}
else /*open door*/
	{
	return(GoTo(mapdata));
	}
}
/*----------------------------------------------------------------------*/
OpenElevator(mapdata)
char mapdata[5];
{
if(ctype==0)return(0);/*don't let the robots go if closed or locked*/
if(DoElevator(mapdata))return(GoTo(mapdata));
else return(0);
}
/*----------------------------------------------------------------------*/
OpenAirLock(mapdata,direction)
char mapdata[5];
int direction;
{
if(ctype==0)
	{
	if(mapdata[1]||mapdata[2]||mapdata[3]||mapdata[4])return(0);
	else return(1);
	}
if(DoAirLock(&mapdata[1],direction))return(GoTo(mapdata));
else return(0);
}
/*----------------------------------------------------------------------*/
UpStairs(mapdata)
char mapdata[5];
{
int val;

if(ctype!=0)if(fl)return(0);
val=GoTo(mapdata);
if(ctype  != 0)DoUpStairs();
return(val);
}
/*----------------------------------------------------------------------*/
DownStairs(mapdata)
char mapdata[5];
{
int val;

val=GoTo(mapdata);
if(ctype != 0)if(fl)DoDnStairs();
return(val);
}
/*----------------------------------------------------------------------*/
int GoTo(mapdata)
unsigned char mapdata[5];
{
int xmod,ymod;
int val=1;
int map,xcell,ycell;

/*these values need to be copied because loading a new map file destroys
  their original values*/
map=mapdata[2];
xcell=mapdata[3];
ycell=mapdata[4];
if((map || xcell || ycell) && ctype==0)
	return(0);/*don't let the robots go anywhere*/
if(map==127)
	{
	TunnelAirlock();
	SaveLevel();
	BUnLoad();
	game=BATTLE;
	Me.xloc=xcell<<8;
	Me.yloc=ycell<<8;
	DrawCompass();
/*	DoCompass(1);*/
	if(orbit||!(armor||fl)){Terminate(FALSE); return(0);}
	level=0;
	return(2);
	}
else if(map==100)
	{
	Dimension8();
	return(0);
	}
if(xcell && ycell)
	{
	if((!map) && robotarray[xcell][ycell])return(0);
	robotarray[Me.xindex][Me.yindex]=0;
	xmod=Me.xloc-(Me.xindex<<8);
	ymod=Me.yloc-(Me.yindex<<8);
	Me.xloc=((int)xcell<<8)+xmod;
	Me.xindex=xcell;
	Me.yloc=((int)ycell<<8)+ymod;
	Me.yindex=ycell;
	robotarray[xcell][ycell]=MENUM;
	val=2;
	}
if(map)load_mapnum((int)mapdata[2],TRUE);
return(val);
}
/*----------------------------------------------------------------------*/
DoUpStairs()
{
}
/*----------------------------------------------------------------------*/
DoDnStairs()
{
FillRect(&Clip,black);
DoClatterSound();
fadein=4;
}
