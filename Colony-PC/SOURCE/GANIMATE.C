/* #define IBM_crypt */
/* #define IBM_DoDesk */
/* #define IBM_DoVanity */
/* #define IBM_DoReactor */
/* #define IBM_DoSecurity */
/* #define IBM_DoGameSecurity */
/* #define IBM_DoTeleport */
/* #define IBM_TelePorted */
/* #define IBM_DoCreatures */
/* #define IBM_DoTeleShow */
/* #define IBM_DoControls */
/* #define IBM_DoLift */
/* #define IBM_DoPowerSuit */
/* #define IBM_DoForkLift */
/* #define IBM_DoDoor */
/* #define IBM_DoAirLock */
/* #define IBM_DoElevator */

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
 * Animate.c
 *---------------------------------------------------------------------- 
 * DoDesk(num, num2)
 * 		int num,num2;
 * DoVanity();
 * DoReactor()
 * DoSecurity()
 * DoGameSecurity()
 * DoTeleport(robot)
 *		int robot;
 * TelePorted(robot,mapdata)
 *		int robot;
 *		char mapdata[5];
 * DoCreatures()
 * DoTeleShow()
 * DoControls()
 * DoLift(up,type)
 *		int up,type;
 * DoPowerSuit()
 * DoForkLift()
 * int DoDoor(locked)
 *		char locked;
 * int DoAirLock(locked,direction)
 *		char* locked;
 *		int direction;
 * int DoElevator(mapdata)
 *		char mapdata[5];
 *---------------------------------------------------------------------- 
 */
#define EXT extern
#include "gamedefs.h"
extern GrafPtr animWindow;
int keyflag;
int share=FALSE;
int sharray[30];
int killer=FALSE;
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
crypt(sarray,i,j,k,l)
char sarray[6];
int i,j,k,l;
{
#ifndef IBM_crypt
int m;
sarray[0]=((3*l)^i^j^k)%10;
sarray[1]=((i*3)^(j*7)^(k*11)^(l*13))%10;
sarray[2]=(3+(l*17)^(j*19)^(k*23)^(i*29))%10;
sarray[3]=((l*19)^(j*23)^(k*29)^(i*31))%10;
sarray[4]=((l*17)|(j*19)|(k*23)|(i*29))%10;
sarray[5]=(29+(l*17)-(j*19)-(k*23)-(i*29))%10;
for(m=0;m<6;m++){if(sarray[m]<0)sarray[m]=-sarray[m]; sarray[m]+=2;}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoDesk(num,num2)
int num,num2;
{
#ifndef IBM_DoDesk
int item;
Rect r;
int i;
int letter=0;
int decode[4];
int ntype;

if(!OpenAFile("desk",TRUE))return;
if(!(num==11||num==18))
	for(i=1;i<6;i++)SetObjectOnOff(i,FALSE);
else switch(num)
	{
	case 11:
		for(i=0;i<4;i++)
			{
			if(decode[i]=decode2[i])SetObjectState(i+2,decode2[i]);
			else SetObjectState(i+2,1);
			}
		break;
	case 18:
		for(i=0;i<4;i++)
			{
			if(decode[i]=decode3[i])SetObjectState(i+2,decode3[i]);
			else SetObjectState(i+2,1);
			}
		break;
	}
if(num!=10)/*cigarette*/
	{
	SetObjectOnOff(23,FALSE);
	SetObjectOnOff(24,FALSE);
	}
ntype=num2/10;
switch(ntype)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		SetObjectOnOff(7,FALSE);
		SetObjectOnOff(8,FALSE);
		SetObjectOnOff(9,FALSE);
		SetObjectOnOff(22,FALSE);
		SetObjectOnOff(25,FALSE);
		break;
	case 4:/*letters*/
		SetObjectOnOff(22,FALSE);
		SetObjectOnOff(9,FALSE);
		SetObjectOnOff(25,FALSE);
		break;
	case 5:/*book*/
		SetObjectOnOff(7,FALSE);
		SetObjectOnOff(8,FALSE);
		SetObjectOnOff(9,FALSE);
		SetObjectOnOff(25,FALSE);
		break;
	case 6:/*clipboard*/
		SetObjectOnOff(22,FALSE);
		SetObjectOnOff(7,FALSE);
		SetObjectOnOff(8,FALSE);
		SetObjectOnOff(25,FALSE);
		break;
	case 7:/*postit*/
		SetObjectOnOff(22,FALSE);
		SetObjectOnOff(7,FALSE);
		SetObjectOnOff(8,FALSE);
		SetObjectOnOff(9,FALSE);
		break;
	}
if(!(num==30))/*erase teeth*/
	SetObjectOnOff(6,FALSE);
if(!(num==33))/*erase jack-in-the-box*/
	for(i=18;i<22;i++)SetObjectOnOff(i,FALSE);
DrawAll(TRUE);
while(AnimControl(&item))
	{
	if(item)
	switch(item)
		{
		case 1:break;
		case 2:
		case 3:
		case 4:
		case 5:
			if(!decode[item-2])
			for(i=0;i<3;i++)
				{
				decode[item-2]=2+((0x0F&Random())%4);
				SetObjectState(item,decode[item-2]);
				AnimNextFram();
				}
			break;
		case 7:/*letter*/
			if(2==ObjectState(7))
				{
				DoText(&r,num2,0);
				}
			break;
		case 9:/*clipboard*/
			DoText(&r,num2,0);
			break;
		case 17:/*computer screen*/
			DoText(&r,num,0);
			break;
		case 22:/*book*/
			DoText(&r,num2,0);
			break;
		case 24:/*cigarette*/
			DoText(&r,55,0);
			killanim(TRUE);
			Terminate(FALSE);
			return;
			break;
		case 25:/*post it*/
			DoText(&r,num2,0);
			break;			
		}
	AnimNextFram();
	}
killanim(TRUE);
switch(num)
	{
	case 11:
		for(i=0;i<4;i++)decode2[i]=decode[i];
		break;
	case 18:
		for(i=0;i<4;i++)decode3[i]=decode[i];
		break;
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoVanity(num)
{
#ifndef IBM_DoVanity
int item,i;
Rect r;
int spilled=FALSE;

share=TRUE;
for(i=0;i<30;i++)sharray[i]=i;
for(i=15;i<19;i++)sharray[i]=15;
if(!OpenAFile("vanity",TRUE))return;
if(weapons&&armor)SetObjectState(1,3);
else if(weapons)SetObjectState(1,2);
else if(armor)SetObjectState(1,1);
else SetObjectState(1,4);
if(level!=1)SetObjectOnOff(14,FALSE);/*badge*/
if(num<90)/*coffee cup*/
	{
	SetObjectOnOff(4,FALSE);
	SetObjectOnOff(7,FALSE);
	SetObjectOnOff(13,FALSE);
	}
else if(num<100)/*letters*/
	{
	SetObjectOnOff(12,FALSE);
	SetObjectOnOff(4,FALSE);
	SetObjectOnOff(7,FALSE);
	}
else if(num<110)/*diary*/
	{
	SetObjectOnOff(12,FALSE);
	SetObjectOnOff(13,FALSE);
	SetObjectOnOff(7,FALSE);
	}
else if(num<120)/*book*/
	{
	SetObjectOnOff(12,FALSE);
	SetObjectOnOff(13,FALSE);
	SetObjectOnOff(4,FALSE);
	}
DrawAll(TRUE);
while(AnimControl(&item))
	{
	switch(item)
		{
		case 12:/*coffee cup*/
			if(!spilled)
				for(i=1;i<6;i++)
					{
					SetObjectState(12,i);
					AnimNextFram();
					}
			spilled=TRUE;
			break;
		case 13:/*paper*/
			DoText(&r,num,0);
			break;
		case 14:/*badge*/
			DoText(&r,80,0);
			break;
		case 4:/*diary*/
			DoText(&r,num,0);
			break;
		case 7:/*book*/
			DoText(&r,num,0);
			break;
		}
			
	AnimNextFram();
	}
killanim(TRUE);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoReactor()
{
#ifndef IBM_DoReactor
int item,i;
char display[7],testarray[7];
Rect r;

if(!OpenAFile("reactor",TRUE))return;
keyflag=TRUE;
for(i=0;i<6;i++)
	{
	display[i]=1;
	SetObjectOnOff(14+i*2,FALSE);
	SetObjectState(13+i*2,1);
	}
DrawAll(TRUE);
while(AnimControl(&item))
	{
	if(item==27)
		{
		DoText(&r,12,0);
		}
	else if(item&&item<=12)
		{
		DoDitSound();
		if(item==11)
			for(i=0;i<6;i++)
				{
				display[i]=1;
				SetObjectOnOff(14+i*2,FALSE);
				SetObjectOnOff(13+i*2,TRUE);
				SetObjectState(13+i*2,1);
				}
		else if(item==12)
			{
			killanim(TRUE);
			if(level==1)
				crypt(testarray,
					(int)decode2[3]-2,
					(int)decode2[2]-2,
					(int)decode2[1]-2,
					(int)decode2[0]-2);
			else
				crypt(testarray,
					(int)decode3[3]-2,
					(int)decode3[2]-2,
					(int)decode3[1]-2,
					(int)decode3[0]-2);
			for(i=0;i<6;i++)
				if(testarray[i]!=display[5-i])
					{
					Terminate(TRUE);
					return;
					}
			switch(corestate[coreindex])
				{
				case 0:
					corestate[coreindex]=1;
					break;
				case 1:
					corestate[coreindex]=0;
					break;
				case 2: break;
				}
			gametest=TRUE;
			return;
			}
		else 	{
				for(i=5;i>=1;i--)display[i]=display[i-1];
				display[0]=item+1;
				for(i=0;i<6;i++)
					{
					if(display[i]<9)
						{
						SetObjectOnOff(13+i*2,TRUE);
						SetObjectOnOff(14+i*2,FALSE);
						SetObjectState(13+i*2,(int)display[i]);
						}
					else
						{
						SetObjectOnOff(14+i*2,TRUE);
						SetObjectOnOff(13+i*2,FALSE);
						SetObjectState(14+i*2,(int)display[i]-8);
						}
					}
				}
		SetObjectState(item,1);
		AnimNextFram();
		}
	else AnimNextFram();
	}
killanim(TRUE);
#endif
}
/*	if(item==1)
		switch(corestate[coreindex])
			{
			case 0:
				corestate[coreindex]=1;
				break;
			case 1:
				corestate[coreindex]=0;
				break;
			case 2:
				for(i=1;i<8;i++)
					{
					SetObjectState(1,i);
					ShowIt();
					}
			}*/
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoSecurity()
{
#ifndef IBM_DoSecurity
int item,i,j;
char display[6],testarray[6];
Rect r;

if(!OpenAFile("security",TRUE))return;
keyflag=TRUE;
for(i=0;i<6;i++)
	{
	display[i]=1;
	SetObjectOnOff(14+i*2,FALSE);
	SetObjectState(13+i*2,1);
	}
if(unlocked)for(i=0;i<4;i++)SetObjectState(i+27,decode1[i]);
else for(i=0;i<4;i++)SetObjectState(i+27,1);
DrawAll(TRUE);
if(!unlocked)
	{
	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
			{
			decode1[i]=2+((0x0F&Random())%4);
			SetObjectState(27+i,decode1[i]);
			AnimNextFram();
			}
	}
while(AnimControl(&item))
	{
	if(item==25)
		{
		DoText(&r,14,0);
		}
	else if(item&&item<=12)
		{
		DoDitSound();
		if(item==11)
			for(i=0;i<6;i++)
				{
				display[i]=1;
				SetObjectOnOff(14+i*2,FALSE);
				SetObjectOnOff(13+i*2,TRUE);
				SetObjectState(13+i*2,1);
				}
		else if(item==12)
			{
			crypt(testarray,
				(int)decode1[0]-2,
				(int)decode1[1]-2,
				(int)decode1[2]-2,
				(int)decode1[3]-2);
			for(i=0;i<6;i++)
				if(testarray[i]!=display[5-i])
					{
					killanim(TRUE);
					return;
					}
			for(i=1;i<=10;i++)SetObjectState(i,2);
			DoDitSound();
			AnimNextFram();
			for(i=1;i<=10;i++)SetObjectState(i,1);
			DoDitSound();
			AnimNextFram();
			AnimNextFram();
			unlocked=TRUE;
			gametest=TRUE;
			killanim(TRUE);
			return;
			}
		else 	{
				for(i=5;i>=1;i--)display[i]=display[i-1];
				display[0]=item+1;
				for(i=0;i<6;i++)
					{
					if(display[i]<9)
						{
						SetObjectOnOff(13+i*2,TRUE);
						SetObjectOnOff(14+i*2,FALSE);
						SetObjectState(13+i*2,(int)display[i]);
						}
					else
						{
						SetObjectOnOff(14+i*2,TRUE);
						SetObjectOnOff(13+i*2,FALSE);
						SetObjectState(14+i*2,(int)display[i]-8);
						}
					}
				}
		SetObjectState(item,1);
		AnimNextFram();
		}
	else AnimNextFram();
	}
killanim(TRUE);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoGameSecurity()
{
#ifndef IBM_DoGameSecurity
int item,i,j;
char decode[4];
char display[6],testarray[6];
Rect r;

if(!OpenAFile("security",FALSE))return;
keyflag=TRUE;
for(i=0;i<6;i++)
	{
	display[i]=1;
	SetObjectOnOff(14+i*2,FALSE);
	SetObjectState(13+i*2,1);
	}
DrawAll(TRUE);
for(i=0;i<4;i++)
	for(j=0;j<3;j++)
		{
		decode[i]=2+((0x0F&Random())%4);
		SetObjectState(27+i,decode[i]);
		AnimNextFram();
		}
while(AnimControl(&item))
	{
	if(item==25)
		{
		DoText(&r,52,0);
		}
	else if(item&&item<=12)
		{
		DoDitSound();
		if(item==11)
			for(i=0;i<6;i++)
				{
				display[i]=1;
				SetObjectOnOff(14+i*2,FALSE);
				SetObjectOnOff(13+i*2,TRUE);
				SetObjectState(13+i*2,1);
				}
		else if(item==12)
			{
			killanim(TRUE);
			crypt(testarray,
				(int)decode[0]-2,
				(int)decode[1]-2,
				(int)decode[2]-2,
				(int)decode[3]-2);
			for(i=0;i<6;i++)
				if(testarray[i]!=display[5-i])
					{
					DoText(&rScreen,51,0);
					return;
					}
			gametest=TRUE;
			return;
			}
		else 	{
				for(i=5;i>=1;i--)display[i]=display[i-1];
				display[0]=item+1;
				for(i=0;i<6;i++)
					{
					if(display[i]<9)
						{
						SetObjectOnOff(13+i*2,TRUE);
						SetObjectOnOff(14+i*2,FALSE);
						SetObjectState(13+i*2,(int)display[i]);
						}
					else
						{
						SetObjectOnOff(14+i*2,TRUE);
						SetObjectOnOff(13+i*2,FALSE);
						SetObjectState(14+i*2,(int)display[i]-8);
						}
					}
				}
		SetObjectState(item,1);
		AnimNextFram();
		}
	else AnimNextFram();
	}
killanim(TRUE);
crypt(testarray,
	(int)decode[0]-2,
	(int)decode[1]-2,
	(int)decode[2]-2,
	(int)decode[3]-2);
for(i=0;i<6;i++)
	if(testarray[i]!=display[5-i])
		{
		DoText(&rScreen,51,0);
		return;
		}
gametest=TRUE;
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoTeleport(robot)
int robot;
{
#ifndef IBM_DoTeleport
int item,i,transported=FALSE,s=0;
char mapdata[5];
int scount;

share=TRUE;
for(i=0;i<30;i++)sharray[i]=i;
sharray[2]=3;sharray[4]=3;
if(!OpenAFile("tele",TRUE))return;
DrawAll(TRUE);
while(AnimControl(&item))
	{
	if(item==3||(item==101 && 3==ObjectState(4)))
		{
		SetObjectOnOff(3,FALSE);
		SetObjectOnOff(1,FALSE);
		DrawAll(TRUE);
		while(AnimControl(&item))
			{
			if(item==4&&!transported)/*close the door*/
				{
				if(soundon)DoTeleportSound();
				SetPort(scrport);
				ClipRect(&sR);
				HideCursor();
				for(i=0;i<4;i++)InvertRect(&sR);   
				ShowCursor();
				SetPort(metaPnt);
				transported=TRUE;
				if(!TelePorted(robot,mapdata)){return;}
				}
			/*exit the teleporter*/
			else if(item==2||(item==101 && 3==ObjectState(4)))
				{
				killanim(TRUE);
				return;
				}
			else AnimNextFram();
			}
		}
	else AnimNextFram();
	}
killanim(TRUE);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
TelePorted(robot,mapdata)
int robot;
char mapdata[5];
{
#ifndef IBM_TelePorted
struct passpatch from,to;

from.level  = level;
from.xindex = Object[robot].where.xindex;
from.yindex = Object[robot].where.yindex;
if(patchmapto(&from,mapdata))/*has this teleporter been moved?*/
	{
	to.level  = mapdata[2];
	to.xindex = mapdata[3];
	to.yindex = mapdata[4];
	}
else/*no it has not*/
	{
	to.level  = (*map.data)[from.xindex][from.yindex][4][2];
	to.xindex = (*map.data)[from.xindex][from.yindex][4][3];
	to.yindex = (*map.data)[from.xindex][from.yindex][4][4];
	}
if(!patchmapfrom(&to,mapdata))
	{
	mapdata[2] = to.level;
	mapdata[3] = to.xindex;
	mapdata[4] = to.yindex;
	}
GoTo(mapdata);
if(!ExitTeleport())/*you're dead*/
	{
	Rect r;
	DoText(&r,65,0);
	killanim(TRUE);
	Terminate(FALSE); 
	return(FALSE);
	}
else if(mapdata[2]==100||!(mapdata[2]||mapdata[3]||mapdata[4]))
{killanim(TRUE); Terminate(TRUE); return(FALSE);}/*you're dead*/
return(TRUE);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoCreatures()
{
#ifndef IBM_DoCreatures
int item,i;
int creature=1;
Rect r;

/*if(True)
	{
	for(i=261;i<269;i++)DoText(&r,i,0);
	return;
	}*/
share=TRUE;
for(i=0;i<7;i++)sharray[i]=i;
for(i=7;i<15;i++)sharray[i]=7;
if(!OpenAFile("slides",TRUE))return;
SetObjectState(1,1);
DrawAll(TRUE);
while(AnimControl(&item))
	{
	switch(item)
		{
		case 0:
			AnimNextFram();
			SetObjectState(5,1);
			SetObjectState(6,1);
			break;
		case 2:/*speaker*/
			DoTestSound();
			DoText(&r,261+creature,0);
			break;
		case 5:
			creature--;
			if(creature==0)creature=8;
			SetObjectState(1,creature);
			AnimNextFram();
			break;
		case 6:
			creature++;
			if(creature==9)creature=1;
			SetObjectState(1,creature);
			AnimNextFram();
			break;
		}
	}
killanim(TRUE);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoTeleShow()
{
#ifndef IBM_DoTeleShow
int item,i;
int creature=1;
Rect r;

/*if(True)
	{
	for(i=269;i<276;i++)DoText(&r,i,0);
	return;
	}*/
share=TRUE;
for(i=0;i<7;i++)sharray[i]=0;
for(i=7;i<15;i++)sharray[i]=i;
if(!OpenAFile("teleshow",TRUE))return;
SetObjectState(1,1);
DrawAll(TRUE);
while(AnimControl(&item))
	{
	switch(item)
		{
		case 0:
			AnimNextFram();
			SetObjectState(5,1);
			SetObjectState(6,1);
			break;
		case 2:/*speaker*/
			DoTestSound();
			DoText(&r,269+creature,0);
			break;
		case 5:
			creature--;
			if(creature==0)creature=7;
			SetObjectState(1,creature);
			AnimNextFram();
			break;
		case 6:
			creature++;
			if(creature==8)creature=1;
			SetObjectState(1,creature);
			AnimNextFram();
			break;
		}
	}
killanim(TRUE);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoControls()
{
#ifndef IBM_DoControls
int item,i;
Rect r;
share=TRUE;
for(i=0;i<30;i++)sharray[i]=i;
for(i=1;i<9;i++)sharray[i]=1;
if(!OpenAFile("controls",TRUE))return;
switch(corepower[coreindex])
	{
	case 0:
		SetObjectState(2,1);
		SetObjectState(5,1);
		break;
	case 1:
		SetObjectState(2,1);
		SetObjectState(5,2);
		break;
	case 2:
		SetObjectState(2,2);
		SetObjectState(5,1);
		break;
	}
DrawAll(TRUE);
while(AnimControl(&item))
	{
	switch(item)
		{
		case 0:
			AnimNextFram();
			break;
		case 4:/*accelerator*/
			if(corepower[coreindex]<2)DoStopSound();
			else if(corestate[coreindex]!=0)DoStopSound();
			else if(orbit){killanim(TRUE); GameOver(FALSE);}
			else {killanim(TRUE); TakeOff(); orbit=TRUE; return;}
			for(i=6;i>0;i--)
				{
				SetObjectState(4,i);
				AnimNextFram();
				}
			break;
		case 5:/*emergency power*/
			if(corestate[coreindex]<2)
			switch(corepower[coreindex])
				{
				case 0:
					corepower[coreindex]=1;
					break;
				case 1:
					corepower[coreindex]=0;
					break;
				case 2:
					SetObjectState(5,1);
					break;
				}
			else SetObjectState(5,1);
			AnimNextFram();
			break;
		case 6:/*ships weapons*/
			if(!orbit)
				{
				DoPShotSound();
				killanim(TRUE);
				Terminate(TRUE);
				return;
				}
			else 
				{
				killanim(TRUE); 
				GameOver(TRUE);
				return;
				}
			break;
		case 7:/*damage report*/
			if(corepower[coreindex]<2)DoText(&r,15,0);
			else if(!orbit) DoText(&r,49,0);
			else DoText(&r,66,0);
			break;
		}
	}
killanim(TRUE);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoLift(up,type)
int up,type;
{
#ifndef IBM_DoLift
int item,i,object;

for(i=4;i<30;i++)sharray[i]=TRUE;
for(i=0;i<4;i++)sharray[i]=FALSE;
switch(type)
	{
	case BOX1:
	case BOX2:
		object=2;
		sharray[2]=TRUE;
		break;
	case TELEPORT:
		object=1;
		sharray[3]=TRUE;
		break;
	case REACTOR:
		object=4;
		sharray[0]=TRUE;
		break;
	case CRYO:
		object=3;
		sharray[1]=TRUE;
		break;
	}
killer=TRUE;
if(!OpenAFile("lifter",TRUE))return(up);
if(up)
	{
	SetObjectState(9,2);
	SetObjectState(8,1);
	SetObjectState(object,5);
	}
else
	{
	SetObjectState(9,1);
	SetObjectState(8,2);
	SetObjectState(object,1);
	}
for(i=1;i<=4;i++)
	if(i!=object)SetObjectOnOff(i,FALSE);
DrawAll(TRUE);
while(AnimControl(&item))
	{
	if(up)
		{
		if(item==8)
			{
			DoDropSound();
			SetObjectState(8,2);
			SetObjectState(9,1);
			for(i=5;i>=1;i--)
				{
				SetObjectState(object,i);
				AnimNextFram();
				}
			up=FALSE;
			}
		}
	else 
		{
		if(item==9)
			{
			DoLiftSound();
			SetObjectState(9,2);
			SetObjectState(8,1);
			for(i=1;i<=5;i++)
				{
				SetObjectState(object,i);
				AnimNextFram();
				}
			up=TRUE;
			}
		}
	AnimNextFram();
	}
killanim(TRUE);
return(up);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoPowerSuit()
{
#ifndef IBM_DoPowerSuit
int item,i,state;
int narmor=armor,nweapons=weapons;
int wstate,astate;
Rect r;

if(!corepower[coreindex])return;
if(!OpenAFile("suit",TRUE))return;
switch(armor)
	{
	case 0:
		astate=1;
		SetObjectState(1,1);
		SetObjectState(3,1);
		break;
	case 1:
		astate=3;
		SetObjectState(1,3);
		SetObjectState(3,2);
		break;
	case 2:
		astate=5;
		SetObjectState(1,5);
		SetObjectState(3,3);
		break;
	case 3:
		astate=7;
		SetObjectState(1,7);
		SetObjectState(3,4);
		break;
	}
switch(weapons)
	{
	case 0:
		wstate=1;
		SetObjectState(2,1);
		SetObjectState(4,1);
		break;
	case 1:
		wstate=3;
		SetObjectState(2,3);
		SetObjectState(4,2);
		break;
	case 2:
		wstate=5;
		SetObjectState(2,5);
		SetObjectState(4,3);
		break;
	case 3:
		wstate=7;
		SetObjectState(2,7);
		SetObjectState(4,4);
		break;
	}
DrawAll(TRUE);
while(AnimControl(&item))
	{
	switch(item)
		{
		case 0:
			break;
		case 1:
			narmor++;
			if(narmor==4)
				{
				narmor=0;
				astate=1;
				for(i=6;i>=1;i--)
					{
					SetObjectState(1,i);
					SetObjectState(3,i/2+1);
					AnimNextFram();
					}
				}
			else
				{
				SetObjectState(1,astate+1); AnimNextFram();
				SetObjectState(1,astate=astate+2); AnimNextFram();
				SetObjectState(3,narmor+1);
				}
			break;
		case 2:
			nweapons++;
			if(nweapons==4)
				{
				nweapons=0;
				wstate=1;
				for(i=6;i>=1;i--)
					{
					SetObjectState(2,i);
					SetObjectState(4,i/2+1);
					AnimNextFram();
					}
				}
			else
				{
				SetObjectState(2,wstate+1); AnimNextFram();
				SetObjectState(2,wstate=wstate+2); AnimNextFram();
				SetObjectState(4,nweapons+1);
				}
			break;
		case 6:
			DoText(&r,13,0);
			break;
		}
	AnimNextFram();
	}
killanim(TRUE);
if(nweapons!=weapons || narmor!=armor)
	{
	DoBzzzSound();
	fadein=2;
	}	
weapons=nweapons;
armor=narmor;
weapons2=weapons*weapons;
armor2=armor*armor;
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoForkLift()
{
#ifndef IBM_DoForkLift
int item;

if(!OpenAFile("forklift",TRUE))return(0);
DrawAll(TRUE);
while(AnimControl(&item) &&item!=1)
	{
	if(item==101 && 7==ObjectState(2))
		{
		item=1;
		break;
		}
	AnimNextFram();
	}
killanim(TRUE);
return(item==1);
#endif
}
/*----------------------------------------------------------------------*/
int DoDoor(locked)
char locked;
{
#ifndef IBM_DoDoor
int state=FALSE, notDone=TRUE,item,i;
int open=FALSE;
if(!corepower[coreindex])return(state);
if(level==1 || level==5 ||level==6){if(!OpenAFile("bulkhead",TRUE))return(state);}
else {if(!OpenAFile("door",TRUE))return(state);}
/*SetObjectState(3,1);/*indicates closed door*/
SetObjectState(2,1);/*close the door*/
DrawAll(TRUE);
while(AnimControl(&item)&&notDone)
	{
	if(item==1 || (item==101 && 3==ObjectState(2))){notDone=FALSE; state=TRUE; doorsound=TRUE;}
	if(item==3)
		{
		DoDoorSound();
		if(open)
			{for(i=3;i>=1;i--){open=!open; 
			SetObjectState(2,i);AnimNextFram();}}
		else{for(i=1;i< 4;i++){open=!open;
			SetObjectState(2,i);AnimNextFram();}}
		}
	AnimNextFram();
	}
if(3==ObjectState(2))doorsound=TRUE;
killanim(TRUE);
return(state);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int DoAirLock(locked,direction)
char* locked;
int direction;
{
#ifndef IBM_DoAirLock
int i,item,state=FALSE, notdone=TRUE;
char savelocked=*locked;

share=TRUE;
for(i=0;i<30;i++)sharray[i]=i;
sharray[3]=2; sharray[4]=2;
if(!OpenAFile("airlock",TRUE))return(0);
if(*locked)
	{
	SetObjectState(2,1);
	SetObjectState(1,1);
	}
else
	{
	SetObjectState(2,3);
	SetObjectState(1,2);
	}
DrawAll(TRUE);
while(AnimControl(&item)&&notdone)
	{
	if((item==2 || item==101) && !*locked){state=TRUE; notdone=FALSE;}
	else if(item==1&&corepower[coreindex] && unlocked)
		{
		PlayAirlock();
		if(*locked)
			{		
			for(i=1;i<4;i++)
				{
				SetObjectState(2,i);
				AnimNextFram();
				}
			if((locked[1]==127)&&!(armor||fl))
				{Terminate(FALSE); killanim(TRUE); return(0);}
			}
		else
			{
			for(i=3;i>=1;i--)
				{
				SetObjectState(2,i);
				AnimNextFram();
				}
			}
		*locked=!*locked;
		if(*locked)leveldata[level].count--;
		else leveldata[level].count++;
		if(leveldata[level].count==2)notdone=FALSE;
		}
	AnimNextFram();
	}
killanim(TRUE);
if(*locked !=savelocked)
	{
	savewall(Me.xindex,Me.yindex,direction);
	switch(direction)
		{
		case NORTH:
			(*map.data)[Me.xindex][Me.yindex+1][SOUTH][1]=*locked;
			savewall(Me.xindex,Me.yindex+1,SOUTH);
			break;
		case EAST:
			(*map.data)[Me.xindex+1][Me.yindex][WEST][1]=*locked;
			savewall(Me.xindex+1,Me.yindex,WEST);
			break;
		case WEST:
			(*map.data)[Me.xindex-1][Me.yindex][EAST][1]=*locked;
			savewall(Me.xindex-1,Me.yindex,EAST);
			break;
		case SOUTH:
			(*map.data)[Me.xindex][Me.yindex-1][NORTH][1]=*locked;
			savewall(Me.xindex,Me.yindex-1,NORTH);
			break;
		}
	}
if(leveldata[level].count==2)
	{
	Terminate(TRUE);
	return(0);
	}
return(state);
#endif
}
/*----------------------------------------------------------------------*/
int DoElevator(mapdata)
char mapdata[5];
{
#ifndef IBM_DoElevator
int i,item,state=FALSE, notdone=TRUE,fl=level-1, lvl=level-1;
int inside=FALSE;
if(!corepower[1])return(0);
if(!OpenAFile("elev",TRUE))return(0);
SetObjectOnOff(6,FALSE);
SetObjectOnOff(7,FALSE);
SetObjectOnOff(8,FALSE);
SetObjectOnOff(9,FALSE);
SetObjectOnOff(10,FALSE);
DrawAll(TRUE);
while(AnimControl(&item)&&notdone)
	{
	if(item==5)
		{
		DoElevatorSound();
		if(state==FALSE)
			{
			for(i=1;i<4;i++)
				{
				SetObjectState(3,i);
				SetObjectState(4,i);
				AnimNextFram();
				}
			KillSound();
			state=TRUE;
			}
		else 
			{
			for(i=3;i>=1;i--)
				{
				SetObjectState(4,i);
				SetObjectState(3,i);
				AnimNextFram();
				}
			KillSound();
			state=FALSE;
			}
		}
	else if(item==2||(item==101&&state==TRUE))notdone=FALSE;
	AnimNextFram();
	}
if(state==TRUE && !notdone)
	{
	notdone=TRUE;
	state=FALSE;
	SetObjectOnOff(6,TRUE);
	SetObjectOnOff(7,TRUE);
	SetObjectOnOff(8,TRUE);
	SetObjectOnOff(9,TRUE);
	SetObjectOnOff(10,TRUE);
	SetObjectOnOff(2,FALSE);
	SetObjectOnOff(5,FALSE);
	inside=TRUE;
/*	SetObjectState(2,lvl);*/
/*	SetObjectState(2,5);/*doors are set open*/
/*	SetObjectState(3,5);*/

	DrawAll(TRUE);
	while(AnimControl(&item)&&notdone)
		{
		if(item>=6 && item<=10)
			{
			fl = item - 5;
			if(lvl == fl)SetObjectState(item,1);
			else
				{
				DoElevatorSound();
				for(i=3;i>=1;i--)
					{
					SetObjectState(4,i);
					SetObjectState(3,i);
					AnimNextFram();
					}
/*				if(fl>lvl)
					{
					for(i=lvl;i<=fl;i++)
						{
						SetObjectState(2,i);
						AnimNextFram();
						}
					lvl=fl;
					}
				else
					{
					for(i=lvl;i>=fl;i--)
						{
						SetObjectState(2,i);
						AnimNextFram();
						}
					lvl=fl;
					}*/
				lvl=fl;
				if(SoundDone())DoElevatorSound();
				for(i=1;i<=3;i++)
					{
					SetObjectState(4,i);
					SetObjectState(3,i);
					AnimNextFram();
					}
				SetObjectState(item,1);
				KillSound();
				}
			}
		else if(item==1||item==101)notdone=FALSE;
		AnimNextFram();
		}
	}
killanim(TRUE);
if(level!=fl+1)
	{
	mapdata[2]=fl+1;
	state=TRUE;
	}
if(inside)
	Me.ang+=128;
return(state);
#endif
}
