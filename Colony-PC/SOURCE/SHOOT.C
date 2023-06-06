/*  #define IBM_scan	   */
/*  #define IBM_shoot	/* */
/*  #define IBM_Eat	/*   */
/*  #define IBM_DestroyRobot   */
/*  #define IBM_doCShoot    /*	 */
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
 * doCShoot()
 *---------------------------------------------------------------------- 
 */
#define EXT extern
#include "gamedefs.h"
extern int SoundCount;
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
Locate far *pobject;
{
#if !defined(IBM_scan)
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
	}while(!(collide=checkwall(FireX,FireY,(Locate far *)&fire)));
if(collide==MENUM)
	{
	pobject->dx=(Me.xloc-FireX)>>1;
	pobject->dy=(Me.yloc-FireY)>>1;
	}
return(collide);
#endif
}
/*---------------------------------------------------------------------- 
 * shoot()
 * The various types of robots inflict harm upon Me in different ways.
 *---------------------------------------------------------------------- 
 */
shoot(num)
int num;
{
#if !defined(IBM_shoot)
int i;
int damage;
int weapon,life,shield;

MeGetShot();

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
		else damage=epower[2]*armor2 - (3<<level);
		if(damage>-level)damage=-(1<<level);
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
SetPort( scrport );

/*  InvertRect(&screenR);  */
/*  SetPort(theWindow);  */
/*  InvertRect(&Clip);	 */
#endif
}
/*---------------------------------------------------------------------- 
 * Eat()
 * Me eats the eggs of the robots to become big and strong. Yum, yum.
 *---------------------------------------------------------------------- 
 */
MeEat()
{
#if !defined(IBM_Eat)
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
#endif
}
/*---------------------------------------------------------------------
 * DestroyRobot()
 * Me shoots at robots to turn em back into eggs.  Then Me can eat 'em.
 *---------------------------------------------------------------------
 */
DestroyRobot(num)
int num;
{
#if !defined(IBM_DestroyRobot)
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
		DoExplodeSound();
		CopyMax(num);
		}
	else
		{
		Object[num].where.power[1] = 10 + (((Random() & 0x00F)<<level));
		Object[num].grow = -1;
		Object[num].count=0;
		}
	}
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
extern int maxrobot;
extern unsigned char drawrobot[255];
doCShoot()
{
#if !defined(IBM_doCShoot)
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

if(Me.power[0]&&weapons) /*any weapons?*/
    {
	if(SoundCount<=1)DoBangSound();
	doShootCircles(cx, cy);
    SetPower(-(1<<level),0,0);
    }
else
    return;

SetPort(scrport);

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

				doBurnHole(&r);

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

SetPort(scrport);

#endif
}





doBurnHole(Rect *r)
{
unsigned int i, j, k, l;
unsigned int i2, i4, i8, i16;
int x, y;
int ra, d, dd;
int tx, ty;
int rand_index;
int randStart;
Rect rDot;

ClipRect(&screenR);
PenSize(1,1);
x=(r->left+r->right)/2;
y=(r->top+r->bottom)/2;
ra= (x-r->left)*2;

if (ra>pix_per_Qinch_x*6)
    ra= pix_per_Qinch_x*6;

d= ra*2;
dd= d*2;

randStart=  (count&0x0F)*3;

HideCursor();

for (i=2; i<dd; i+=1+i2 )
    {
    i2=i>>1;
    i4=i2>>1;
    i8=i4>>1;
    i16=i8>>1;
    if (i8==0)
	i4=1;
    rand_index= randStart;
    if ( MonoCrome && game==BATTLE )
	PenColor(realcolor[vWHITE]);
    else
	PenColor(realcolor[vLTBLUE]);
    for (k=0; k<i16; k++)
	{
	tx= randnum[rand_index++]%(i2) - (i4);
	ty= randnum[rand_index++]%(i2) - (i4);

	if ( abs(tx)+abs(ty)<i8*3 )
	    {
	    MoveTo( x+tx, y+ty );
	    LineTo( x-tx, y-ty );
	    }
	}
    if (rand_index>200)
	rand_index=1;
    if ( MonoCrome && game==BATTLE )
	PenColor(realcolor[vWHITE]);
    else
	PenColor(realcolor[vYELLOW]);
    for (k=0; k<i16; k++)
	{
	tx= randnum[rand_index++]%i2 - (i4);
	ty= randnum[rand_index++]%i2 - (i4);

	if ( abs(tx)+abs(ty)<(i*3)>>3 )
	    {
	    MoveTo( x+tx, y+ty );
	    LineTo( x-tx, y-ty );
	    }
	}
    }

if (rand_index>800)
    rand_index=1;
    if ( MonoCrome && game==BATTLE )
	PenColor(realcolor[vBLACK]);
    else
	PenColor(realcolor[vINTWHITE]);
for (k=0; k<i8; k++)
    {
    tx= (randnum[rand_index++]%i2)/2 - (i8);
    ty= (randnum[rand_index++]%i2)/2 - (i8);

    if ( abs(tx)+abs(ty)<(i*3)>>4 )
	{
	MoveTo( x+tx, y+ty );
	LineTo( x-tx, y-ty );
	}
    }

rDot.left= x-pix_per_Qinch_x/8;
rDot.right= x+pix_per_Qinch_x/8;
rDot.top= y-pix_per_Qinch_y/8;
rDot.bottom= y+pix_per_Qinch_y/8;
PaintOval(&rDot);
ShowCursor();
}

/*************************** doShootCircles() **********************/

int RightHanded= True;

doShootCircles(int cx, int cy)
{
int StartPointX;
Rect HitPoint;

if (RightHanded)
    StartPointX= (screenR.right+cx)>>1;
else
    StartPointX= cx>>1;

HideCursor();
PenColor(realcolor[vRED]);
MoveTo(screenR.left+1,screenR.bottom);
LineTo(cx,cy-1);
LineTo(screenR.right-1,screenR.bottom);

PenColor(realcolor[vINTWHITE]);
MoveTo(screenR.left,screenR.bottom);
LineTo(cx,cy);
LineTo(screenR.right,screenR.bottom);

PenColor(realcolor[vRED]);
MoveTo(screenR.left-1,screenR.bottom);
LineTo(cx,cy+1);
LineTo(screenR.right+1,screenR.bottom);

HitPoint.left= cx-2;
HitPoint.right= cx+2;
HitPoint.top= cy-2;
HitPoint.bottom= cy+2;
PaintOval(&HitPoint);

ShowCursor();
}


MeGetShot()
{
int i, x, y;
Rect invertCircle;

SetPort(scrport);
ClipRect(&screenR);
PenMode(zXORz);
PenColor(realcolor[vINTWHITE]);

for (i=0; i<40; i++)
    {
    x= randnum[i+((count<<5)&0x00E0)]%(screenR.right-screenR.left);
    y= randnum[i+21]%(screenR.bottom-screenR.top);
    MoveTo(x-pix_per_Qinch_x, y-(pix_per_Qinch_y>>1));
    LineTo(x+pix_per_Qinch_x, y+(pix_per_Qinch_y>>1));
    MoveTo(x-(pix_per_Qinch_x>>2)*5, y);
    LineTo(x+(pix_per_Qinch_x>>2)*5, y);
    MoveTo(x-pix_per_Qinch_x, y+(pix_per_Qinch_y>>1));
    LineTo(x+pix_per_Qinch_x, y-(pix_per_Qinch_y>>1));
    }

for (i=0; i<40; i++)
    {
    x= randnum[i+20] % ((screenR.right-screenR.left)>>1) + ((screenR.right-screenR.left)>>2);
    y= randnum[i+((count<<5)&0x00E0)] % ((screenR.bottom-screenR.top)>>1) + ((screenR.bottom-screenR.top)>>2);
    MoveTo(x-pix_per_Qinch_x, y-(pix_per_Qinch_y>>1));
    LineTo(x+pix_per_Qinch_x, y+(pix_per_Qinch_y>>1));
    MoveTo(x-(pix_per_Qinch_x>>2)*5, y);
    LineTo(x+(pix_per_Qinch_x>>2)*5, y);
    MoveTo(x-pix_per_Qinch_x, y+(pix_per_Qinch_y>>1));
    LineTo(x+pix_per_Qinch_x, y-(pix_per_Qinch_y>>1));
    }

for (i=0; i<40; i++)
    {
    x= randnum[i+((count<<5)&0x00E0)]%(screenR.right-screenR.left);
    y= randnum[i+21]%(screenR.bottom-screenR.top);
    MoveTo(x-pix_per_Qinch_x, y-(pix_per_Qinch_y>>1));
    LineTo(x+pix_per_Qinch_x, y+(pix_per_Qinch_y>>1));
    MoveTo(x-(pix_per_Qinch_x>>2)*5, y);
    LineTo(x+(pix_per_Qinch_x>>2)*5, y);
    MoveTo(x-pix_per_Qinch_x, y+(pix_per_Qinch_y>>1));
    LineTo(x+pix_per_Qinch_x, y-(pix_per_Qinch_y>>1));
    }

for (i=0; i<40; i++)
    {
    x= randnum[i+20] % ((screenR.right-screenR.left)>>1) + ((screenR.right-screenR.left)>>2);
    y= randnum[i+((count<<5)&0x00E0)] % ((screenR.bottom-screenR.top)>>1) + ((screenR.bottom-screenR.top)>>2);
    MoveTo(x-pix_per_Qinch_x, y-(pix_per_Qinch_y>>1));
    LineTo(x+pix_per_Qinch_x, y+(pix_per_Qinch_y>>1));
    MoveTo(x-(pix_per_Qinch_x>>2)*5, y);
    LineTo(x+(pix_per_Qinch_x>>2)*5, y);
    MoveTo(x-pix_per_Qinch_x, y+(pix_per_Qinch_y>>1));
    LineTo(x+pix_per_Qinch_x, y-(pix_per_Qinch_y>>1));
    }
PenMode(zREPz);
}
