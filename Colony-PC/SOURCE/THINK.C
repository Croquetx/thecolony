/*  #define IBM_CThink		 */
/*  #define IBM_CubeThink	 */
/*  #define IBM_PyramidThink	 */
/*  #define IBM_UPyramidThink	 */
/*  #define IBM_EyeThink	 */
/*  #define IBM_QueenThink	 */
/*  #define IBM_DroneThink	 */
/*  #define IBM_EggThink	 */
/*  #define IBM_LayEgg		 */
/*  #define IBM_MoveThink	 */
/*  #define IBM_SnoopThink    /* */
/*  #define IBM_BigGrow 	 */
/*  #define IBM_Grow		 */
/*  #define IBM_CopyMax 	 */
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
 *	Think.c													 
 *	This file contains the functions that allow the robots to make
 *	independant motions.
 *---------------------------------------------------------------------- 
 * CThink()
 * CubeThink()
 * PyramidThink()
 * UPyramidThink()
 * EyeThink()
 * QueenThink()
 * DroneThink()
 * EggThink()
 * SnoopThink()
 * LayEgg(tp,xindex,yindex)
 *		int tp,xindex,yindex;
 * MoveThink()
 * Grow()
 * BigGrow()
 * CopyMax(num)
 *		int num;
 *---------------------------------------------------------------------- 
 */
#define EXT extern
#include "gamedefs.h"

#define LROTATE 1
#define RROTATE	2
#define FORWARD	3
#define FSHOOT	4
int queenlook=0;
int queendelta=4;
int sniff=5,csniff=0;
#define QUEENMAX 24

/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int onum;
CThink()
{
#if !defined(IBM_CThink)
int type;
long killtime,killtime2,killtime3;

for(onum=1;onum<=maxrob;onum++)
	if(Object[onum].alive)/*(*Object[onum].think)();*/
		{
		type=Object[onum].type;
		if(type<=4)
		switch(type)
			{
			case EYE:		EyeThink();		break;
			case PYRAMID:	PyramidThink();	break;
			case CUBE:		CubeThink();	break;
			case UPYRAMID: 	UPyramidThink();break;
			}
		else if(type>=17)
		switch(type)
			{
			case QUEEN:		QueenThink();	break;
			case DRONE:
			case SOLDIER:	DroneThink();	break;
			case SNOOP:		SnoopThink();	break;
			}
		else EggThink();
		}
if(is_EGAtype)/*this is to insure that the EGA screen is settled*/
	{
	for(killtime=maxrob;killtime < 35;killtime++)
		for(killtime2=0;killtime2 < 20;killtime2++)
			killtime3=killtime2*killtime2;
	}
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
CubeThink()
{
#if !defined(IBM_CubeThink)
Object[onum].where.look+=15;
MoveThink();
Object[onum].time--;
if(Object[onum].time < 0)
	if(LayEgg(M_CUBE,Object[onum].where.xindex,Object[onum].where.yindex))
		Object[onum].time=10+(Random() & 0x00FF);
if(Object[onum].grow)BigGrow();
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
PyramidThink()
{		
#if !defined(IBM_PyramidThink)
Object[onum].where.look+=15;
MoveThink();
Object[onum].time--;
if(Object[onum].time < 0)
	if(LayEgg(M_PYRAMID,Object[onum].where.xindex,Object[onum].where.yindex))
		Object[onum].time=10+(Random() & 0x00FF);
if(Object[onum].grow)BigGrow();
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
UPyramidThink()
{		
#if !defined(IBM_UPyramidThink)
Object[onum].where.look-=15;
MoveThink();
Object[onum].time--;
if(Object[onum].time < 0)
	if(LayEgg(M_UPYRAMID,Object[onum].where.xindex,Object[onum].where.yindex))
		Object[onum].time=10+(Random() & 0x00FF);
if(Object[onum].grow)BigGrow();
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
EyeThink()
{
#if !defined(IBM_EyeThink)
MoveThink();
Object[onum].time--;
if(Object[onum].time < 0)
	if(LayEgg(M_EYE,Object[onum].where.xindex,Object[onum].where.yindex))
		Object[onum].time=10+(Random() & 0x00FF);
if(Object[onum].grow)BigGrow();
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
QueenThink()
{
#if !defined(IBM_QueenThink)
int j;

MoveThink();
Object[onum].time--;
Object[onum].where.lookx+=Object[onum].where.delta;
if(Object[onum].where.lookx<-QUEENMAX||
	Object[onum].where.lookx>QUEENMAX)
		Object[onum].where.delta=-Object[onum].where.delta;
Object[onum].where.look=Object[onum].where.ang+Object[onum].where.lookx;
if(Object[onum].time < 0)
	switch(Random()&0x03)
		{
		case 0:
			if(LayEgg(M_EYE,Object[onum].where.xindex,Object[onum].where.yindex))
				Object[onum].time=10+(Random() & 0x00FF);
			break;
		case 1:
			if(LayEgg(M_CUBE,Object[onum].where.xindex,Object[onum].where.yindex))
				Object[onum].time=10+(Random() & 0x00FF);
			break;
		case 2:
			if(LayEgg(M_PYRAMID,Object[onum].where.xindex,Object[onum].where.yindex))
				Object[onum].time=10+(Random() & 0x00FF);
			break;
		case 3:
			if(LayEgg(M_UPYRAMID,Object[onum].where.xindex,Object[onum].where.yindex))
				Object[onum].time=10+(Random() & 0x00FF);
			break;
			}
if(Object[onum].grow)
	{
	HideCursor();
	while(!SoundDone());
	DoExplodeSound();
	if(soundon)while(!SoundDone())InvertRect(&Clip);
	else for(j=0;j<4;j++)InvertRect(&Clip);
	ShowCursor();
	allgrow=FALSE;
	Object[onum].alive=FALSE;/*kill the queen*/
	robotarray[Object[onum].where.xindex]
		[Object[onum].where.yindex]=0;
	for(j=1;j<=maxrob;j++)
		if(Object[j].type<5)
			Object[j].grow = -1;
	}
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
DroneThink()
{
#if !defined(IBM_DroneThink)
int j;

MoveThink();
Object[onum].time--;
Object[onum].where.lookx+=Object[onum].where.delta;
if(Object[onum].where.lookx<-QUEENMAX||
	Object[onum].where.lookx>QUEENMAX)
		Object[onum].where.delta=-Object[onum].where.delta;
Object[onum].where.look=Object[onum].where.ang+Object[onum].where.lookx;
if(Object[onum].grow)
	{
	if(Object[onum].type==DRONE)
		{
		KillSound();
		DoExplodeSound();
		HideCursor();
		for(j=0;j<4;j++)InvertRect(&Clip);
		ShowCursor();
		Object[onum].alive=FALSE;/*kill the thing*/
		robotarray[Object[onum].where.xindex]
			[Object[onum].where.yindex]=0;
		CopyMax(onum);
		}
	else 
		{
		extern void MakeDrone();
		Object[onum].type=DRONE;
		Object[onum].grow=0;
		Object[onum].where.power[1] = 10 + ((Random() & 0x00F)<<level);
		Object[onum].make=MakeDrone;
		}
	}
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
EggThink()
{
#if !defined(IBM_EggThink)
if(Object[onum].type>4)
	{
	if(allgrow)Object[onum].time--;
	else if(!foodarray[Object[onum].where.xindex][Object[onum].where.yindex])
		{
		foodarray[Object[onum].where.xindex][Object[onum].where.yindex]=
			robotarray[Object[onum].where.xindex][Object[onum].where.yindex];
		robotarray[Object[onum].where.xindex][Object[onum].where.yindex]=0;
		Object[onum].grow=-1;
		}		
	if(Object[onum].time <= 0)Object[onum].grow=1;
	}
if(Object[onum].grow)Grow();
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
LayEgg(tp,xindex,yindex)
int tp,xindex,yindex;
{
#if !defined(IBM_LayEgg)
int i,ang;

/*do not lay an egg on or directly beside another.*/
if( foodarray[xindex][yindex] ||
	foodarray[xindex+1][yindex] ||
	foodarray[xindex-1][yindex] ||
	foodarray[xindex][yindex+1] ||
	foodarray[xindex][yindex-1])return(FALSE);
for(i=1;i<=maxobjects;i++)
	if(Object[i].alive==FALSE)
		{
		ang=0x00FF & Random();
		CreateObject(i,	tp,(xindex<<8)+128,(yindex<<8)+128,ang);
		return(TRUE);
		}
return(FALSE);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
MoveThink()
{
#if !defined(IBM_MoveThink)
int r,i;
int fx,fy;
int collide;

switch(Object[onum].opcode)
	{
	case LROTATE:
		Object[onum].where.ang+=7;
		Object[onum].where.look+=7;
		Object[onum].counter--;
		if(Object[onum].counter<=0)
			{
			Object[onum].opcode=FORWARD;
			Object[onum].counter= Random() & 0x000F;
			}
		if(MENUM==scan(&Object[onum].where))
			{
			shoot(onum);
			Object[onum].opcode=FSHOOT;
			Object[onum].counter= Random() & 0x003F;
			}
		return;
		break;
	case RROTATE:
		Object[onum].where.ang-=7;
		Object[onum].where.look-=7;
		Object[onum].counter--;
		if(Object[onum].counter<=0)
			{
			Object[onum].opcode=FORWARD;
			Object[onum].counter= Random() & 0x003F;
			}
		if(MENUM==scan(&Object[onum].where))
			{
			shoot(onum);
			Object[onum].opcode=FSHOOT;
			Object[onum].counter= Random() & 0x001F;
			}
		return;
		break;
	case FORWARD:
		Object[onum].counter--;
		if(Object[onum].counter<=0)
			{
			r=Random();
			if(r>0)Object[onum].opcode=LROTATE;
			else Object[onum].opcode=RROTATE;
			Object[onum].counter=r&0x000F;
			}
		else
			{
			robotarray[Object[onum].where.xindex]
					  [Object[onum].where.yindex]=0;
			fx=Object[onum].where.xloc+(xai[Object[onum].where.ang]<<2);
			fy=Object[onum].where.yloc+(yai[Object[onum].where.ang]<<2);
			if(!(collide=checkwall(fx,fy,&Object[onum].where)))
				{
				Object[onum].where.xloc=fx;
				Object[onum].where.yloc=fy;
				Object[onum].where.xindex=fx>>8;
				Object[onum].where.yindex=fy>>8;
				}
			else
				{
				r=Random();
				if(r>0)Object[onum].opcode=LROTATE;
				else Object[onum].opcode=RROTATE;
				Object[onum].counter=r&0x000F;
				}
			robotarray[Object[onum].where.xindex]
					  [Object[onum].where.yindex]=onum;
			}
		return;
		break;					
	case FSHOOT:
		robotarray[Object[onum].where.xindex]
				  [Object[onum].where.yindex]=0;
		fx=	Object[onum].where.xloc +
			Object[onum].where.dx +
			(Me.dx>>2) +
			(cost[Object[onum].where.ang]>>2);
		fy= Object[onum].where.yloc +
			Object[onum].where.dy +
			(Me.dy>>2) +
			(sint[Object[onum].where.ang]>>2);
		/*check for walls*/
		if(!(collide=checkwall(fx,fy,&Object[onum].where)))
			{
			Object[onum].where.xloc=fx;
			Object[onum].where.yloc=fy;
			Object[onum].where.xindex=fx>>8;
			Object[onum].where.yindex=fy>>8;
			}
		else
			{
			r=Random();
			if(r>0)Object[onum].opcode=LROTATE;
			else Object[onum].opcode=RROTATE;
			Object[onum].counter=r&0x000F;
			}
		robotarray[Object[onum].where.xindex]
				  [Object[onum].where.yindex]=onum;
		/*check for objects*/
		if(MENUM==scan(&Object[onum].where))shoot(onum);
		else
			{
			Object[onum].opcode=FORWARD;
			Object[onum].counter=Random()&0x000F;
			}
		return;
		break;					
	default:
		Inform("\pDefault in MoveThink!");
		Object[onum].alive=0;
		Object[onum].opcode=FORWARD;
		Object[onum].counter=Random() & 0x000F;
		break;
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
SnoopThink()
{
#if !defined(IBM_SnoopThink)
int r,i;
int fx,fy;
int collide;
int damage;
int f=0;
int p[3];

Robot[SNOOP][1].pnt[1][2]+=sniff;
csniff++;
if(csniff==25){sniff=-sniff; csniff=0;}
switch(Object[onum].opcode)
	{
	case LROTATE:
		Object[onum].where.ang+=7;
		Object[onum].where.look+=7;
		Object[onum].counter--;
		if(Object[onum].counter<=0)
			{
			Object[onum].opcode=FORWARD;
			Object[onum].counter= Random() & 0x000F;
			}
		break;
	case RROTATE:
		Object[onum].where.ang-=7;
		Object[onum].where.look-=7;
		Object[onum].counter--;
		if(Object[onum].counter<=0)
			{
			Object[onum].opcode=FORWARD;
			Object[onum].counter= Random() & 0x003F;
			}
		break;
	case FORWARD:
		Object[onum].counter--;
		if(Object[onum].counter<=0)
			{
			r=Random();
			if(r>0)Object[onum].opcode=LROTATE;
			else Object[onum].opcode=RROTATE;
			Object[onum].counter=r&0x000F;
			}
		else
			{
			robotarray[Object[onum].where.xindex]
					  [Object[onum].where.yindex]=0;
			fx=Object[onum].where.xloc+(xai[Object[onum].where.ang]<<2);
			fy=Object[onum].where.yloc+(yai[Object[onum].where.ang]<<2);
			if(!(collide=checkwall(fx,fy,&Object[onum].where)))
				{
				Object[onum].where.xloc=fx;
				Object[onum].where.yloc=fy;
				Object[onum].where.xindex=fx>>8;
				Object[onum].where.yindex=fy>>8;
				}
			else if(collide==MENUM)
				{
				NewObject(SNOOP,onum);
				SetPort( scrport );
				HideCursor();
				DoSlugSound();
				InvertRect(&Clip);
				InvertRect(&Clip);
				ShowCursor();
				fadein=2;
				p[0]= -min(3*Me.power[0]/4,32000);
				p[1]= -min(3*Me.power[1]/4,32000);
				p[2]= -min(3*Me.power[2]/4,32000);
				SetPower(p[0],p[1],p[2]);
				/*  Display();	*/
				}
			else if(collide>0 && Object[collide].type<=BASEOBJECT&&Object[collide].type>=1)
				{
				Object[onum].where.xloc=fx;
				Object[onum].where.yloc=fy;
				Object[onum].where.xindex=fx>>8;
				Object[onum].where.yindex=fy>>8;
				robotarray[Object[onum].where.xindex]
					  	[Object[onum].where.yindex]=onum;
				NewObject(Object[collide].type,collide);	
				}
			else /*ran into a wall or something*/
				{
				r=Random();
				if(r>0)Object[onum].opcode=LROTATE;
				else Object[onum].opcode=RROTATE;
				Object[onum].counter=r&0x000F;
				}
			robotarray[Object[onum].where.xindex]
					  [Object[onum].where.yindex]=onum;
			}
		if(dirXY[Object[onum].where.xindex][Object[onum].where.yindex])
			{
			Object[onum].opcode=SNOOP;
			Object[onum].where.ang&=0xF8;
			}
		break;
	case SNOOP:
		switch(dirXY[Object[onum].where.xindex][Object[onum].where.yindex])
			{
			case 2:
				if(Object[onum].where.ang!=0)
					{
					if(Object[onum].where.ang>128)Object[onum].where.ang+=8;
					else Object[onum].where.ang-=8;
					return;
					}
				break;
			case 1:
				if(Object[onum].where.ang!=32)
					{
					if(Object[onum].where.ang>32&&Object[onum].where.ang<160)
						Object[onum].where.ang-=8;
					else Object[onum].where.ang+=8;
					return;
					}
				break;
			case 8:
				if(Object[onum].where.ang!=64)
					{
					if(Object[onum].where.ang>64&&Object[onum].where.ang<192)
						Object[onum].where.ang-=8;
					else Object[onum].where.ang+=8;
					return;
					}
				break;
			case 7:
				if(Object[onum].where.ang!=96)
					{
					if(Object[onum].where.ang>96&&Object[onum].where.ang<224)
						Object[onum].where.ang-=8;
					else Object[onum].where.ang+=8;
					return;
					}
				break;
			case 6:
				if(Object[onum].where.ang!=128)
					{
					if(Object[onum].where.ang<128)
						Object[onum].where.ang+=8;
					else Object[onum].where.ang-=8;
					return;
					}
				break;
			case 5:
				if(Object[onum].where.ang!=160)
					{
					if(Object[onum].where.ang<160 &&Object[onum].where.ang>32)
						Object[onum].where.ang+=8;
					else Object[onum].where.ang-=8;
					return;
					}
				break;
			case 4:
				if(Object[onum].where.ang!=192)
					{
					if(Object[onum].where.ang<192 &&Object[onum].where.ang>64)
						Object[onum].where.ang+=8;
					else Object[onum].where.ang-=8;
					return;
					}
				break;
			case 3:
				if(Object[onum].where.ang!=224)
					{
					if(Object[onum].where.ang<224 &&Object[onum].where.ang>96)
						Object[onum].where.ang+=8;
					else Object[onum].where.ang-=8;
					return;
					}
				break;
			}
		Object[onum].opcode=FORWARD;
		dirXY[Object[onum].where.xindex][Object[onum].where.yindex]=0;
		Object[onum].counter= 0x003F;
		break;
	default:
		Inform("\pDefault in SnoopThink!");
		Object[onum].alive=0;
		Object[onum].opcode=FORWARD;
		Object[onum].counter=Random() & 0x000F;
		break;
	}
#endif
}

/*---------------------------------------------------------------------
 * BigGrow()
 *---------------------------------------------------------------------
 */
BigGrow()
{
#if !defined(IBM_BigGrow)
int xindex,yindex;

xindex=Object[onum].where.xindex;
yindex=Object[onum].where.yindex;
Object[onum].count++;
/*if there are eggs already in place do not shrink*/
if(foodarray[xindex][yindex]==0)
	{
	if((Object[onum].where.xloc==(xindex<<8)+128) &&
		(Object[onum].where.yloc==(yindex<<8)+128))
		{
		foodarray[xindex][yindex]=robotarray[xindex][yindex];
		robotarray[xindex][yindex]=0;
		Object[onum].type+=4;
		Object[onum].count=0;
		SetObject(onum,FALSE);
		Object[onum].time=10+(Random() & 0x003F);
		}
	else
		{
		Object[onum].where.xloc=(xindex<<8)+128;
		Object[onum].where.yloc=(yindex<<8)+128;
		Object[onum].opcode=LROTATE;
		Object[onum].counter=100;
		Object[onum].count=0;
		}
	}
#endif
}
/*---------------------------------------------------------------------
 * Grow()
 *---------------------------------------------------------------------
 */
Grow()
{
#if !defined(IBM_Grow)
Object[onum].count++;
Object[onum].time=10+(Random() & 0x003F);
switch(Object[onum].type)
	{
	case F_EYE:
	case F_PYRAMID:
	case F_CUBE:
	case F_UPYRAMID:
		if(Object[onum].count>3)
			{
			if(Object[onum].grow==1)/*growing...final stage*/
				{
				Object[onum].count=0;
				Object[onum].grow=0;
				Object[onum].type-=4;
				SetObject(onum,FALSE);
				}
			else/*shrinking...first stage*/
				{
				Object[onum].count=0;
				Object[onum].type+=4;
				SetObject(onum,FALSE);
				}
			}
		break;
	case S_EYE:
	case S_PYRAMID:
	case S_CUBE:
	case S_UPYRAMID:
		if(Object[onum].count>3)
			{
			if(Object[onum].grow==1)
				{
				Object[onum].count=0;
				Object[onum].type-=4;
				SetObject(onum,FALSE);
				}
			else
				{
				Object[onum].count=0;
				Object[onum].grow=0;
				Object[onum].type+=4;
				SetObject(onum,FALSE);
				}
			}
		break;
	case M_EYE:
	case M_PYRAMID:
	case M_CUBE:
	case M_UPYRAMID:
		if(robotarray[Object[onum].where.xindex][Object[onum].where.yindex]==0)
			{
			Object[onum].count=0;
			Object[onum].type-=4;
			robotarray[Object[onum].where.xindex][Object[onum].where.yindex] =
			 foodarray[Object[onum].where.xindex][Object[onum].where.yindex];
			foodarray[Object[onum].where.xindex][Object[onum].where.yindex]=0;
			SetObject(onum,FALSE);
			}
		break;
	}
#endif
}
/*---------------------------------------------------------------------
 * CopyMax(num)
 *---------------------------------------------------------------------
 */
CopyMax(num)
int num;
{
#if !defined(IBM_CopyMax)
int i,x,y;

i=maxobjects;
while(i > maxrob)
	{
	if(Object[i].alive && i!=num)
		{
		x=Object[i].where.xindex;
		y=Object[i].where.yindex;
		if(Object[i].type<=4)robotarray[x][y]=num;
		else foodarray[x][y]=num;
		Object[i].alive=FALSE;
		Object[num].alive=TRUE;
		Object[num].type=Object[i].type;
		Object[num].time=Object[i].time;
		Object[num].grow=Object[i].grow;
		Object[num].count=Object[i].count;
		Object[num].opcode=Object[i].opcode;
		Object[num].counter=Object[i].counter;
		Object[num].make=Object[i].make;
		Object[num].think=Object[i].think;
		Object[num].visible=FALSE;
		Object[num].where.ang=Object[i].where.ang;
		Object[num].where.look=Object[i].where.look;
		Object[num].where.lookx=Object[i].where.lookx;
		Object[num].where.delta=Object[i].where.delta;
		Object[num].where.xloc=Object[i].where.xloc;
		Object[num].where.yloc=Object[i].where.yloc;
		Object[num].where.xindex=Object[i].where.xindex;
		Object[num].where.yindex=Object[i].where.yindex;
/*if(Object[num].where.xindex>32 || Object[num].where.yindex>32)showinfo(num,"\pcopymax");/*xyzzy*/
		Object[num].where.xmx=Object[i].where.xmx;
		Object[num].where.xmn=Object[i].where.xmn;
		Object[num].where.zmn=Object[i].where.zmn;
		Object[num].where.zmx=Object[i].where.zmx;
		Object[num].where.power[0]=Object[i].where.power[0];
		Object[num].where.power[1]=Object[i].where.power[1];
		Object[num].where.power[2]=Object[i].where.power[2];
		Object[num].where.type=Object[i].where.type;
		Object[num].where.dx=Object[i].where.dx;
		Object[num].where.dy=Object[i].where.dy;
		Object[num].where.dist=Object[i].where.dist;
		return;
		}
	--i;
	}
#endif
}
