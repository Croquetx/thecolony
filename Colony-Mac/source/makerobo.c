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
 * MakeRobot1.c
 *---------------------------------------------------------------------
 * void MakeRobot()
 * SetObject(num,flag)
 *		int num,flag;
 * InitRobot()
 * void SetRobot(l,r,num)
 *		int l,r,num;
 * void MakeRobot()
 * SaveLevel()
 * void InitObject()
 * NewObject(type,count)
 *		int type,count;
 * CreateObject(num,type,xloc,yloc,ang)
 *		int num,type,xloc,yloc,ang;
 *---------------------------------------------------------------------
 */
#define EXT extern 
#include "cgamedefs.h"
/*---------------------------------------------------------------------
 * MakeRobot()
 *---------------------------------------------------------------------
 */
extern int maxrobot;
extern unsigned char drawrobot[255];
void MakeRobot()
{
int i,n;

i=maxrobot;
while(--i >= 0)
	{
	n=drawrobot[i];
	if(Object[n].alive)
		{
		ClipRect(&Object[n].clip);
		Object[n].where.xmn=Width;
		Object[n].where.xmx=0;
		Object[n].where.zmn=Height;
		Object[n].where.zmx=0;
		Object[n].where.dist=11500;
		(*Object[n].make)(n);
		if(Object[n].clip.left > Object[n].where.xmn)
			Object[n].where.xmn = Object[n].clip.left;
		if(Object[n].clip.right< Object[n].where.xmx)
			Object[n].where.xmx = Object[n].clip.right;
		if(Object[n].type<=UPYRAMID || (Object[n].type>=QUEEN&&Object[n].type<=SOLDIER))
		if(Object[n].where.xmn<centerX && Object[n].where.xmx>centerX)insight=TRUE;
		}
	}
}
/*---------------------------------------------------------------------
 * SetObject()
 *---------------------------------------------------------------------
 */
extern void MakePyramid();
extern void MakeUPyramid();
extern void MakeEye();
extern void MakeCube();
extern void MakeQueen();
extern void MakeDrone();
extern void MakeSoldier();
extern void MakeSnoop();
extern void MakeDesk();
extern void MakePlant();
extern void MakeCChair();
extern void MakeBed();
extern void MakeTable();
extern void MakeProjector();
extern void MakeScreen();
extern void MakeConsole();
extern void MakePowerSuit();
extern void MakeCryo();
extern void MakeForkLift();
extern void MakeBox1();
extern void MakeBox2();
extern void MakeCouch();
extern void MakeChair();
extern void MakeTV();
extern void MakeDrawer();
extern void MakeTele();
extern void MakeTub();
extern void MakeSink();
extern void MakeToilet();
extern void MakeBench();
extern void MakeBBed();
extern void MakePToilet();
extern void MakeCBench();
extern void MakeReactor();
extern void MakeFWall();
extern void MakeCWall();

extern void CubeThink();
extern void PyramidThink();
extern void UPyramidThink();
extern void EyeThink();
extern void QueenThink();
extern void DroneThink();
extern void EggThink();
extern void SnoopThink();

SetObject(num,flag)
int num,flag;
{
int rob=0;

switch(Object[num].type)
	{
	case PYRAMID:
		Object[num].make=MakePyramid;
		Object[num].think=PyramidThink;
		rob=1;
		break;
	case F_PYRAMID:
	case S_PYRAMID:
	case M_PYRAMID:
		Object[num].make=MakePyramid;
		Object[num].think=EggThink;
		break;
	case UPYRAMID:
		rob=1;
		Object[num].think=UPyramidThink;
		Object[num].make=MakeUPyramid;
		break;
	case F_UPYRAMID:
	case S_UPYRAMID:
	case M_UPYRAMID:
		Object[num].make=MakeUPyramid;
		Object[num].think=EggThink;
		break;
	case EYE:
		rob=1;
		Object[num].make=MakeEye;
		Object[num].think=EyeThink;
		break;
	case F_EYE:
	case S_EYE:
	case M_EYE:
		Object[num].make=MakeEye;
		Object[num].think=EggThink;
		break;
	case CUBE:
		rob=1;
		Object[num].make=MakeCube;
		Object[num].think=CubeThink;
		break;
	case F_CUBE:
	case S_CUBE:
	case M_CUBE:
		Object[num].make=MakeCube;
		Object[num].think=EggThink;
		break;
	case QUEEN:
		rob=1;
		Object[num].make=MakeQueen;
		Object[num].think=QueenThink;
		break;
	case DRONE:
		rob=1;
		Object[num].make=MakeDrone;
		Object[num].think=DroneThink;
		break;
	case SOLDIER:
		rob=1;
		Object[num].make=MakeSoldier;
		Object[num].think=DroneThink;
		break;
	case SNOOP:
		rob=1;
		Object[num].make=MakeSnoop;
		Object[num].think=SnoopThink;
		break;
	case DESK:
		rob=1;
		Object[num].make=MakeDesk;
		break;
	case PLANT:
		Object[num].make=MakePlant;
		break;
	case CCHAIR:
		Object[num].make=MakeCChair;
		break;
	case COUCH:
		rob=1;
		Object[num].make=MakeCouch;
		break;
	case CHAIR:
		rob=1;
		Object[num].make=MakeChair;
		break;
	case BED:
		rob=1;
		Object[num].make=MakeBed;
		break;
	case TABLE:
		rob=1;
		Object[num].make=MakeTable;
		break;
	case PROJECTOR:
		rob=1;
		Object[num].make=MakeProjector;
		break;
	case SCREEN:
		rob=1;
		Object[num].make=MakeScreen;
		break;
	case CONSOLE:
		rob=1;
		Object[num].make=MakeConsole;
		break;
	case POWERSUIT:
		rob=1;
		Object[num].make=MakePowerSuit;
		break;
	case CRYO:
		rob=1;
		Object[num].make=MakeCryo;
		break;
	case FORKLIFT:
		rob=1;
		Object[num].make=MakeForkLift;
		break;
	case BOX1:
		rob=1;
		Object[num].make=MakeBox1;
		break;
	case BOX2:
		rob=1;
		Object[num].make=MakeBox2;
		break;
	case TELEPORT:
		rob=1;
		Object[num].make=MakeTele;
		break;
	case TUB:
		rob=1;
		Object[num].make=MakeTub;
		break;
	case SINK:
		rob=1;
		Object[num].make=MakeSink;
		break;
	case TOILET:
		rob=1;
		Object[num].make=MakeToilet;
		break;
	case PTOILET:
		rob=1;
		Object[num].make=MakePToilet;
		break;
	case BENCH:
		rob=1;
		Object[num].make=MakeBench;
		break;
	case CBENCH:
		rob=1;
		Object[num].make=MakeCBench;
		break;
	case BBED:
		rob=1;
		Object[num].make=MakeBBed;
		break;
	case FWALL:
		Object[num].make=MakeFWall;
		break;
	case CWALL:
		Object[num].make=MakeCWall;
		break;
	case TV:
		rob=1;
		Object[num].make=MakeTV;
		break;
	case DRAWER:
		rob=1;
		Object[num].make=MakeDrawer;
		break;
	case REACTOR:
		rob=1;
		Object[num].make=MakeReactor;
		break;
	default:
		rob=1;
		Object[num].make=MakeTable;
		break;
	}
if(flag)
	{
	if(rob)robotarray[Object[num].where.xindex][Object[num].where.yindex]=num;
	else    foodarray[Object[num].where.xindex][Object[num].where.yindex]=num;
	}
}
/*---------------------------------------------------------------------
 * InitRobot()
 *---------------------------------------------------------------------
 */
InitRobot()
{
int i,j,k;
int RobotSize[50];
for(i=0;i<50;i++)RobotSize[i]=0;
for(i=0;i<50;i++)if(Robot[i])DoChimeSound();
/*-Pyramid---------------*/
InitPyramid(RobotSize);
/*-Upside Down Pyramid---*/
InitUPyramid(RobotSize);
/*-Eye-------------------*/
InitEye(RobotSize);
/*-Cube------------------*/
InitCube(RobotSize);
/*-Queen-----------------*/
InitQueen(RobotSize);
/*-Drone-----------------*/
InitDrone(RobotSize);
/*-Snoop-----------------*/
InitSnoop(RobotSize);
/*-Desk------------------*/
InitDesk(RobotSize);
/*-Plant-----------------*/
InitPlant(RobotSize);
/*-CChair----------------*/
InitCChair(RobotSize);
/*-Bed-------------------*/
InitBed(RobotSize);
/*-Table-----------------*/
InitTable(RobotSize);
/*-Screen----------------*/
InitScreen(RobotSize);
/*-PowerSuit-------------*/
InitPowerSuit(RobotSize);
/*-Cryogenic Chamber-----*/
InitCryo(RobotSize);
/*-ForkLift--------------*/
InitForkLift(RobotSize);
/*-Boxes-----------------*/
InitBox(RobotSize);
/*-Couch-----------------*/
InitCouch(RobotSize);
/*-Bathroom--------------*/
InitBathroom(RobotSize);
/*-TelePorter------------*/
InitTele(RobotSize);
/*-Console---------------*/
InitConsole(RobotSize);
/*-Walls-----------------*/
InitWall(RobotSize);
/*-----------------------*/
for(i=1;i<MAXROB;i++)
	for(j=0;j<RobotSize[i];j++)
		for(k=0;k<Robot[i][j].points;k++)
			Robot[i][j].pnt[k][2]-=Floor;
}
/*---------------------------------------------------------------------
 * SetRobot()
 *---------------------------------------------------------------------
 */
int maxrobot=0;
unsigned char drawrobot[255];
void SetRobot(l,r,num)
int l,r,num;
{
Object[num].visible=TRUE;
Object[num].clip.left  = l+1;
Object[num].clip.right = r;
Object[num].clip.top   = Clip.top;
Object[num].clip.bottom= Clip.bottom;
drawrobot[maxrobot]=num;
maxrobot++;
}
/*---------------------------------------------------------------------
 * SaveLevel()
 *---------------------------------------------------------------------
 */
SaveLevel()
{
int i;

leveldata[level].visit=TRUE;
leveldata[level].queen=allgrow;
for(i=1;i<=BASEOBJECT;i++)
	leveldata[level].object[i]=0;
for(i=1;i<=maxobjects;i++)
	if(Object[i].type<=BASEOBJECT)
		if(Object[i].alive)
			leveldata[level].object[Object[i].type]++;
}
/*---------------------------------------------------------------------
 * InitObject()
 *---------------------------------------------------------------------
 */
int robotType[]={0,QUEEN,SNOOP,DRONE,SOLDIER,
	  EYE,  PYRAMID,  UPYRAMID,  CUBE,
	M_EYE,M_PYRAMID,M_UPYRAMID,M_CUBE,
	F_EYE,F_PYRAMID,F_UPYRAMID,F_CUBE,
	S_EYE,S_PYRAMID,S_UPYRAMID,S_CUBE};
void InitObject()
{
int i,j,k;
int xloc,yloc,ang;
int rnd;
int counter=1;
int lvl=level-1;

if(lvl==-1)Inform("\pLevel == 0");
if(lvl>5)lvl=5;
if(level==1)
	{
	maxobjects=maxrob=0;
	return;
	}
switch(level)
	{
	case 2:
		maxrob=25;
		break;
	case 3:
	case 4:
		maxrob=30;
		break;
	case 5:
	case 6:
	case 7:
	default:
		maxrob=35;
		break;
	}
maxobjects=MENUM-1;
if(leveldata[level].visit) 
	{
	allgrow=leveldata[level].queen;
	for(i=1;i<=BASEOBJECT;i++)
	for(j=0;j<leveldata[level].object[robotType[i]];j++)
		{
		NewObject(robotType[i],counter);
		counter++;
		}
	counter++;
	if(!leveldata[level].queen)
		{
		for(j=1;j<=maxrob;j++)
			if(Object[j].type<5)Object[j].grow = -1;
		}
	}
else 
	{
	allgrow=TRUE;
	for(i=1;i<=maxrob;i++)
		{
		ang=0x00FF & Random();
		do	{
			if(level==7 && i==1)
				{
				xloc=27;
				yloc=10;
				}
			else
				{
				xloc = 0x001F & Random();
				yloc = 0x001F & Random();
				}
			if(xloc<2)xloc=2;
			if(yloc<2)yloc=2;
			if(xloc>28)xloc=28;
			if(yloc>28)yloc=28;
			}while(robotarray[xloc][yloc]);
		if(xloc>=32||yloc>=32)Inform("\perror in xloc or yloc");
		xloc=(xloc<<8)+128;
		yloc=(yloc<<8)+128;
		rnd=Random();
		rnd=abs(rnd)%(lvl+1);
		rnd=min(rnd,5);
		/* 	level 1 = 0,1
			level 2 = 0,1,2
			level 3 = 0,1,2,3
			level 4 = 0,1,2,3,4
			level 5 = 0,1,2,3,4,5
			level 6 = 0,1,2,3,4,5
		*/
		if(i==1)CreateObject(i,QUEEN,	xloc,yloc,ang);
		else if(i==2)CreateObject(i,SNOOP,	xloc,yloc,ang);
		else switch(rnd)
			{
			case 0:
				CreateObject(i,	CUBE,	xloc,yloc,ang);
				break;
			case 1:
				CreateObject(i, PYRAMID,xloc,yloc,ang);
				break;
			case 2:
				CreateObject(i,UPYRAMID,xloc,yloc,ang);
				break;
			case 3:
				CreateObject(i,	EYE,	xloc,yloc,ang);
				break;
			case 4:
				CreateObject(i,	DRONE,	xloc,yloc,ang);
				break;
			case 5:
				CreateObject(i,	SOLDIER,xloc,yloc,ang);
				break;
			}
		}
	}
}
/*---------------------------------------------------------------------
 * NewObject(type,count)
 *---------------------------------------------------------------------
 */
NewObject(type,count)
int type,count;
{
int ang,xloc,yloc;

ang=0x00FF & Random();
do	{
	if(level==7 && type==QUEEN)
		{
		xloc=27;
		yloc=10;
		}
	else
		{
		xloc = 0x001F & Random();
		yloc = 0x001F & Random();
		}
	if(xloc<2)xloc=2;
	if(yloc<2)yloc=2;
	if(xloc>28)xloc=28;
	if(yloc>28)yloc=28;
	}while(robotarray[xloc][yloc]||foodarray[xloc][yloc]);
if(xloc>=32||yloc>=32)Inform("\perror in xloc or yloc");
xloc=(xloc<<8)+128;
yloc=(yloc<<8)+128;
CreateObject(count,type,xloc,yloc,ang);
}
/*---------------------------------------------------------------------
 * CreateObject()
 *---------------------------------------------------------------------
 */
#define FORWARD	3
#define FSHOOT	4
CreateObject(num,type,xloc,yloc,ang)
int num,type,xloc,yloc,ang;
{
int rob=0;
int lvl=level-1;

if(num==-1)Inform("\pCreateObject -1 ERROR!");
while(ang<0)ang+=256;
while(ang>255)ang-=256;
Object[num].opcode=FORWARD;
Object[num].visible = FALSE;
Object[num].alive = TRUE;
Object[num].count = 0;
Object[num].type=type;
Object[num].where.xloc = xloc;
Object[num].where.yloc = yloc;
Object[num].where.delta=4;
Object[num].where.lookx=0;
Object[num].where.ang = ang;
Object[num].where.look= ang;
Object[num].where.xindex=Object[num].where.xloc >> 8;	/*divide by 256	*/
Object[num].where.yindex=Object[num].where.yloc >> 8;	/*divide by 256	*/
if(type==QUEEN)
	{
	if(level==1 || level==7)
		{
		Object[num].where.power[0]=32000L;
		Object[num].where.power[1]=32000L;
		Object[num].where.power[2]=32000L;
		}
	else
		{
		Object[num].where.power[0]=40+((int)(Random() & 0x005F)<<lvl);
		Object[num].where.power[1]=40+((int)(Random() & 0x005F)<<lvl);
		Object[num].where.power[2]=40+((int)(Random() & 0x005F)<<lvl);
		}
	}
else if(type==SOLDIER)
	{
	Object[num].where.power[0]=30+((int)(Random() & 0x001F)<<lvl);
	Object[num].where.power[1]=30+((int)(Random() & 0x001F)<<lvl);
	Object[num].where.power[2]=30+((int)(Random() & 0x001F)<<lvl);
	}	
else
	{
	Object[num].where.power[0]=20+((int)(Random() & 0x000F)<<lvl);
	Object[num].where.power[1]=20+((int)(Random() & 0x000F)<<lvl);
	Object[num].where.power[2]=20+((int)(Random() & 0x000F)<<lvl);
	}
Object[num].where.type=0;
Object[num].time=10+(Random() & 0x003F);
Object[num].grow=0;
SetObject(num,TRUE);
}
