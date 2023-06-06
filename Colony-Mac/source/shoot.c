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
 *	shoot.c														 
 *---------------------------------------------------------------------- 
 * int scan(pobject)
 *		Locate *pobject;
 * 		robot search for me.
 * shoot(num)
 *		int num;
 *		robot shoots me.
 * Eat()
 *		I eat eggs.
 * DestroyRobot(num)
 * 		int num;
 * 		I hurt robots.
 * CShoot()
 *---------------------------------------------------------------------- 
 */
#define EXT extern
#include "cgamedefs.h"

#define LROTATE 1
#define RROTATE	2
#define FORWARD	3
#define FSHOOT	4


/*---------------------------------------------------------------------- 
 * scan()
 * The robot searches for Me in the direction that it is facing.
 *---------------------------------------------------------------------- 
 */
int scan(pobject)
Locate *pobject;
{
int FireX,FireY,collide;
Locate fire;

FireX = pobject->xloc;
FireY = pobject->yloc;
fire.ang = pobject->ang;
fire.type=2;

do	{
	fire.xloc=FireX;
	fire.yloc=FireY;
	fire.xindex=FireX>>8;
	fire.yindex=FireY>>8;
	FireX+=(xai[fire.ang]<<5);
	FireY+=(yai[fire.ang]<<5);
	}while(!(collide=checkwall(FireX,FireY,&fire)));
if(collide==MENUM)
	{
	pobject->dx=(Me.xloc-FireX)>>1;
	pobject->dy=(Me.yloc-FireY)>>1;
	}
return(collide);
}
/*---------------------------------------------------------------------- 
 * shoot()
 * The various types of robots inflict harm upon Me in different ways.
 *---------------------------------------------------------------------- 
 */
shoot(num)
int num;
{
int i;
int damage;
int weapon,life,shield;
GrafPtr	savePort;

GetPort( &savePort );
SetPort( theWindow );
InvertRect(&Clip);
SetPort( savePort );
Object[num].opcode=FSHOOT;
DoShootSound();
switch(Object[num].type)
	{
	case EYE:
		damage=epower[2]*armor2 - (1<<level);
		if(damage>-level)damage=-level;
		SetPower(damage,damage,damage);
		break;
	case PYRAMID:
		damage=epower[2]*armor2 - (1<<level);
		if(damage > -level)damage = -level;
		SetPower(damage,-level,-level);
		break;
	case CUBE:
		damage=epower[2]*armor2 - (1<<level);
		if(damage > -level)damage= -level;
		SetPower(-level,damage,-level);
		break;
	case UPYRAMID:
		damage=epower[2]*armor2 - (1<<level);
		if(damage > -level)damage = -level;
		SetPower(-level,-level,damage);
		break;
	case QUEEN:
		if(level== 1 || level==7) damage=epower[2]*armor2 - (3<<10);
		else damage=epower[2]*armor2 - (7<<level);
		if(damage> -level)damage=-(1<<level);
		SetPower(damage,damage,damage);
		break;
	case DRONE:
		damage=epower[2]*armor2 - (4<<level);
		if(damage>-level)damage=-(level<<1);
		SetPower(damage,damage,damage);
		break;
	case SOLDIER:
		damage=epower[2]*armor2 - (5<<level);
		if(damage>-level)damage=-(level<<1);
		SetPower(damage,damage,damage);
		break;
	}
SetPort(theWindow);
InvertRect(&Clip);
}
/*---------------------------------------------------------------------- 
 * Eat()
 * Me eats the eggs of the robots to become big and strong. Yum, yum.
 *---------------------------------------------------------------------- 
 */
Eat()
{
int f;

f=foodarray[Me.xindex][Me.yindex];
foodarray[Me.xindex][Me.yindex]=0;
Object[f].alive=FALSE;
DoEatSound();
switch(Object[f].type)
	{
	case M_UPYRAMID:
	case F_UPYRAMID:
	case S_UPYRAMID:
		SetPower(7<<level,7<<level,15<<level);
		break;
	case M_EYE:
	case F_EYE:
	case S_EYE:
		SetPower(15<<level,15<<level,15<<level);
		break;
	case M_PYRAMID:
	case F_PYRAMID:
	case S_PYRAMID:
		SetPower(15<<level,7<<level,7<<level);
		break;
	case M_CUBE:
	case F_CUBE:
	case S_CUBE:
		SetPower(7<<level,15<<level,7<<level);
		break;
	}
if(f<=maxrob)CopyMax(f);
}
/*---------------------------------------------------------------------
 * DestroyRobot()
 * Me shoots at robots to turn em back into eggs.  Then Me can eat 'em.
 *---------------------------------------------------------------------
 */
DestroyRobot(num)
int num;
{
int o=Object[num].type;
		
if(!Object[num].grow)Object[num].opcode=FSHOOT;
Object[num].where.look=Object[num].where.ang=Me.ang+128;
Object[num].where.power[1] -= ((epower[0]*weapons2)<<1);
if(Object[num].where.power[1] <= 0)
	{
	if(Object[num].count!=0)
		{
		Object[num].alive=FALSE;
		robotarray[Object[num].where.xindex][Object[num].where.yindex]=0;
		while(!SoundDone());
		if(!soundon)
			{
			int i;
			for(i=0;i<16;i++)InvertRect(&Clip);
			}
		else
			{
			DoExplodeSound();
			while(!SoundDone())InvertRect(&Clip);
			StopSound();
			}
		CopyMax(num);
		}
	else
		{
		Object[num].where.power[1] = 10 + (((Random() & 0x00F)<<level));
		Object[num].grow = -1;
		Object[num].count=0;
		}
	}
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
extern int maxrobot;
extern unsigned char drawrobot[255];
CShoot()
{
int s0,s1;
register long i;	
GrafPtr	savePort;
int collide,psize=10,pcount=0;
int o;
Rect r;

if(cshoot)
	{
	cx=myPt.h;
	cy=myPt.v;
	}
else
	{
	cx=centerX;
	cy=centerY;
	}
if(Me.power[0]&&weapons)/*any weapons?*/
	{
	DoBangSound();
	GetPort( &savePort );
	SetPort( theWindow );
	PenMode(patXor);
	for(i=100;i<900;i+=200)
		{
		PenSize(psize,psize);
		psize--;
		s0=rtable[i];
		s1=rtable[i+100];
		MoveTo(cx-s0,cy-s0);
		LineTo(cx-s1,cy-s1);
		MoveTo(cx-s0,cy+s0);
		LineTo(cx-s1,cy+s1);
		MoveTo(cx+s0,cy+s0);
		LineTo(cx+s1,cy+s1);
		MoveTo(cx+s0,cy-s0);
		LineTo(cx+s1,cy-s1);
		MoveTo(cx-s0,cy-s0);
		LineTo(cx-s1,cy-s1);
		MoveTo(cx-s0,cy+s0);
		LineTo(cx-s1,cy+s1);
		MoveTo(cx+s0,cy+s0);
		LineTo(cx+s1,cy+s1);
		MoveTo(cx+s0,cy-s0);
		LineTo(cx+s1,cy-s1);
		} 
	PenMode(patCopy);
	PenSize(1,1);
	SetPower(-(1<<level),0,0);
	SetPort(savePort);
	}
else return;
for(i=0;i<maxrobot;i++)
	{
	collide=drawrobot[i];
	o=Object[collide].type;
	if(	Object[collide].alive && 
		Object[collide].where.xmn <= cx &&
		Object[collide].where.xmx >= cx &&
		Object[collide].where.zmn <= cy &&
		Object[collide].where.zmx >= cy)
			{
			if(o <= 4 || o==QUEEN || o==DRONE ||o==SOLDIER)
				{
				s0=rtable[Object[collide].where.dist];
				if(s0>100)s0=100;
				r.top=cy-s0;
				r.bottom=cy+s0;
				r.left=cx-s0;
				r.right=cx+s0;
				InvertOval(&r);
				DestroyRobot(collide);
				return;
				}
			/*can not shoot through these objects*/
			else if(o==FORKLIFT	||
					o==TELEPORT	||
					o==PTOILET	||
					o==BOX2		||
					o==REACTOR	||
					o==SCREEN)return;
			}
	}
}
