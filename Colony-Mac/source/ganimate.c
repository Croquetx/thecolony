/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
int keyflag;
extern int LostSound;


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
#include "cgamedefs.h"
extern GrafPtr animWindow;
#include "colordef.h"
extern CGrafPort metaPort;

/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
crypt(sarray,i,j,k,l)
char sarray[6];
int i,j,k,l;
{
int m;
sarray[0]=((3*l)^i^j^k)%10;
sarray[1]=((i*3)^(j*7)^(k*11)^(l*13))%10;
sarray[2]=(3+(l*17)^(j*19)^(k*23)^(i*29))%10;
sarray[3]=((l*19)^(j*23)^(k*29)^(i*31))%10;
sarray[4]=((l*17)|(j*19)|(k*23)|(i*29))%10;
sarray[5]=(29+(l*17)-(j*19)-(k*23)-(i*29))%10;
for(m=0;m<6;m++){if(sarray[m]<0)sarray[m]=-sarray[m]; sarray[m]+=2;}
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int CDesk[]={0,c_desktop,
	-redColor,-cyanColor,-cyanColor,-cyanColor,-cyanColor,
	-whiteColor,-whiteColor,-magentaColor,-yellowColor,c_desk,
	c_desk,c_desk,c_desk,c_desk,c_desk,
	-whiteColor,c_screen,-magentaColor,-cyanColor,-cyanColor,
	-blueColor,-whiteColor,-redColor,-whiteColor,-yellowColor};
DoDesk(num,num2)
int num,num2;
{
int item;
Rect r;
int i;
int letter=0;
int decode[4];
int ntype;

if(!OpenAFile("\pdesk",CDesk))return;
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
DrawAll();
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
				ShowIt();
				}
			break;
		case 7:/*letter*/
			if(2==ObjectState(7))
				{
				ObjectRect(7,&r);
				RLocalToGlobal(&r,&r);
				SetPort(animWindow);
				DoText(&r,num2,0);
				}
			break;
		case 9:/*clipboard*/
			ObjectRect(9,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,num2,0);
			break;
		case 17:/*computer screen*/
			ObjectRect(17,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,num,0);
			break;
		case 22:/*book*/
			ObjectRect(22,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,num2,0);
			break;
		case 24:/*cigarette*/
			ObjectRect(24,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,55,0);
			killanim();
			Terminate(FALSE);
			return;
			break;
		case 25:/*post it*/
			ObjectRect(25,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,num2,0);
			break;			
		}
	ShowIt();
	}
killanim();
switch(num)
	{
	case 11:
		for(i=0;i<4;i++)decode2[i]=decode[i];
		break;
	case 18:
		for(i=0;i<4;i++)decode3[i]=decode[i];
		break;
	}
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int CVanity[]={0,c_vanity,
	c_mirror,-redColor,-cyanColor,-whiteColor,-yellowColor,
	-greenColor,-blueColor,-redColor,-magentaColor,-redColor,
	c_vanity,-whiteColor,-yellowColor,c_mirror};
DoVanity(num)
{
int item,i;
Rect r;
int spilled=FALSE;

if(!OpenAFile("\pvanity",CVanity))return;
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
DrawAll();
while(AnimControl(&item))
	{
	switch(item)
		{
		case 12:/*coffee cup*/
			if(!spilled)
				for(i=1;i<6;i++)
					{
					SetObjectState(12,i);
					ShowIt();
					}
			spilled=TRUE;
			break;
		case 13:/*paper*/
			ObjectRect(13,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,num,0);
			break;
			break;
		case 14:/*badge*/
			ObjectRect(14,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,80,0);
			break;
		case 4:/*diary*/
			ObjectRect(4,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,num,0);
			break;
			break;
		case 7:/*book*/
			ObjectRect(7,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,num,0);
			break;
		}
			
	ShowIt();
	}
killanim();
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int CReactor[]={0,c_console,
	-yellowColor,-yellowColor,-yellowColor,-yellowColor,-yellowColor,
	-yellowColor,-yellowColor,-yellowColor,-yellowColor,-yellowColor,
	-yellowColor,-yellowColor,-redColor,-redColor,-redColor,
	-redColor,-redColor,-redColor,-redColor,-redColor,
	-redColor,-redColor,-redColor,-redColor,-cyanColor,
	-magentaColor,-whiteColor};
DoReactor()
{
int item,i;
char display[7],testarray[7];
Rect r;

DoDitSound();
if(!OpenAFile("\preactor",CReactor))return;
keyflag=TRUE;
for(i=0;i<6;i++)
	{
	display[i]=1;
	SetObjectOnOff(14+i*2,FALSE);
	SetObjectState(13+i*2,1);
	}

DrawAll();
while(AnimControl(&item))
	{
	if(item==27)
		{
		ObjectRect(27,&r);
		RLocalToGlobal(&r,&r);
		SetPort(animWindow);
		DoText(&r,12,0);
		}
	else if(item&&item<=12)
		{
		if(LostSound)DoChimeSound();
		else RepeatTSound();
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
			killanim();
			KillTSound();
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
		ShowIt();
		}
	else ShowIt();
	}
killanim();
KillTSound();
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
int CSecurity[]={0,c_console,
	-yellowColor,-yellowColor,-yellowColor,-yellowColor,-yellowColor,
	-yellowColor,-yellowColor,-yellowColor,-yellowColor,-yellowColor,
	-yellowColor,-yellowColor,-redColor,-redColor,-redColor,
	-redColor,-redColor,-redColor,-redColor,-redColor,
	-redColor,-redColor,-redColor,-redColor,-whiteColor,
	-redColor,-cyanColor,-cyanColor,-cyanColor,-cyanColor};
DoSecurity()
{
int item,i,j;
char display[6],testarray[6];
Rect r;

DoDitSound();
if(!OpenAFile("\psecurity",CSecurity))return;
keyflag=TRUE;
for(i=0;i<6;i++)
	{
	display[i]=1;
	SetObjectOnOff(14+i*2,FALSE);
	SetObjectState(13+i*2,1);
	}
if(unlocked)for(i=0;i<4;i++)SetObjectState(i+27,decode1[i]);
else for(i=0;i<4;i++)SetObjectState(i+27,1);
DrawAll();
if(!unlocked)
	{
	for(i=0;i<4;i++)
		for(j=0;j<3;j++)
			{
			decode1[i]=2+((0x0F&Random())%4);
			SetObjectState(27+i,decode1[i]);
			ShowIt();
			}
	}
while(AnimControl(&item))
	{
	if(item==25)
		{
		ObjectRect(25,&r);
		RLocalToGlobal(&r,&r);
		SetPort(animWindow);
		DoText(&r,14,0);
		}
	else if(item&&item<=12)
		{
		if(LostSound)DoChimeSound();
		else RepeatTSound();
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
					killanim();
					KillTSound();
					return;
					}
			for(i=1;i<=10;i++)SetObjectState(i,2);
			if(LostSound)DoChimeSound();
			else RepeatTSound();
			ShowIt();
			for(i=1;i<=10;i++)SetObjectState(i,1);
			if(LostSound)DoChimeSound();
			else RepeatTSound();
			ShowIt();
			unlocked=TRUE;
			gametest=TRUE;
			killanim();
			KillTSound();
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
		ShowIt();
		}
	else ShowIt();
	}
killanim();
KillTSound();
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoGameSecurity()
{
int item,i,j;
char decode[4];
char display[6],testarray[6];
Rect r;

DoDitSound();
if(!OpenAFile("\psecurity",CSecurity))return;
keyflag=TRUE;
for(i=0;i<6;i++)
	{
	display[i]=1;
	SetObjectOnOff(14+i*2,FALSE);
	SetObjectState(13+i*2,1);
	}
DrawAll();
for(i=0;i<4;i++)
	for(j=0;j<3;j++)
		{
		decode[i]=2+((0x0F&Random())%4);
		SetObjectState(27+i,decode[i]);
		ShowIt();
		}
while(AnimControl(&item))
	{
	if(item==25)
		{
		ObjectRect(25,&r);
		RLocalToGlobal(&r,&r);
		SetPort(animWindow);
		DoText(&r,52,0);
		}
	else if(item&&item<=12)
		{
		if(LostSound)DoChimeSound();
		else RepeatTSound();
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
			killanim();
			KillTSound();
			crypt(testarray,
				(int)decode[0]-2,
				(int)decode[1]-2,
				(int)decode[2]-2,
				(int)decode[3]-2);
			for(i=0;i<6;i++)
				if(testarray[i]!=display[5-i])
					{
					DoText(&rScreen,51,0);
					ExitToShell();
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
		ShowIt();
		}
	else ShowIt();
	}
killanim();
KillTSound();
crypt(testarray,
	(int)decode[0]-2,
	(int)decode[1]-2,
	(int)decode[2]-2,
	(int)decode[3]-2);
for(i=0;i<6;i++)
	if(testarray[i]!=display[5-i])
		{
		DoText(&rScreen,51,0);
		ExitToShell();
		}
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int CTeleport[]={0,c_teleport,0,c_teledoor};
DoTeleport(robot)
int robot;
{
int item,i,transported=FALSE,s=0;
char mapdata[5];

if(!OpenAFile("\pteleporter",CTeleport))return;
DrawAll();
while(AnimControl(&item))
	{
	if(item==1)
		{
		killanim();
		if(!OpenAFile("\pteleporter2",CTeleport))return;
		SetObjectState(2,6);		
		DrawAll();
		while(AnimControl(&item))
			{
			if(item==2&&!transported)/*close the door*/
				{
				SetPort(animWindow);
				if(soundon&&!LostSound)
					{
					DoTeleportSound();
					while(!SoundDone()){InvertRect(&Clip);s=!s;}
					if(s)InvertRect(&Clip);
					}
				else{
					int i;
					for(i=0;i<16;i++)InvertRect(&Clip);
					}
				transported=TRUE;
				if(!TelePorted(robot,mapdata)){return;}
				}
			else if(item==1 && 6==ObjectState(2) )
				{
				killanim();
				return;
				}
			else ShowIt();
			}
		}
	else ShowIt();
	}
killanim();
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
TelePorted(robot,mapdata)
int robot;
char mapdata[5];
{
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
	RLocalToGlobal(&r,&r);
	SetPort(animWindow);
	DoText(&r,65,0);
	killanim(); 
	Terminate(FALSE); 
	return(FALSE);
	}
else if(mapdata[2]==100||!(mapdata[2]||mapdata[3]||mapdata[4]))
	{killanim(); Terminate(TRUE); return(FALSE);}/*you're dead*/
return(TRUE);
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int CCreatures[]={-whiteColor,0,-whiteColor,-cyanColor,c_proj,
	-blueColor,-magentaColor,-magentaColor};
DoCreatures()
{
int item,i;
int creature=1;
Rect r;

/*if(Mac512)
	{
	for(i=261;i<269;i++)DoText(&r,i,0);
	return;
	}*/
DoTestSound();
if(!OpenAFile("\pslideshow",CCreatures))return;
SetObjectState(1,1);
DrawAll();
while(AnimControl(&item))
	{
	switch(item)
		{
		case 0:
			ShowIt();
			SetObjectState(5,1);
			SetObjectState(6,1);
			break;
		case 2:/*speaker*/
			ObjectRect(2,&r);
			RepeatTSound();
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,261+creature,0);
			break;
		case 5:
			creature--;
			if(creature==0)creature=8;
			SetObjectState(1,creature);
			ShowIt();
			break;
		case 6:
			creature++;
			if(creature==9)creature=1;
			SetObjectState(1,creature);
			ShowIt();
			break;
		}
	}
killanim();
KillTSound();
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoTeleShow()
{
int item,i;
int creature=1;
Rect r;

/*if(Mac512)
	{
	for(i=269;i<276;i++)DoText(&r,i,0);
	return;
	}*/
DoTestSound();
if(!OpenAFile("\pteleshow",CCreatures))return;
SetObjectState(1,1);
DrawAll();
while(AnimControl(&item))
	{
	switch(item)
		{
		case 0:
			ShowIt();
			SetObjectState(5,1);
			SetObjectState(6,1);
			break;
		case 2:/*speaker*/
			ObjectRect(2,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			RepeatTSound();
			DoText(&r,269+creature,0);
			break;
		case 5:
			creature--;
			if(creature==0)creature=7;
			SetObjectState(1,creature);
			ShowIt();
			break;
		case 6:
			creature++;
			if(creature==8)creature=1;
			SetObjectState(1,creature);
			ShowIt();
			break;
		}
	}
killanim();
KillTSound();
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int CControls[]={0,c_console,
	-redColor,-yellowColor,-yellowColor,-blueColor,-yellowColor,-greenColor,c_screen};
DoControls()
{
int item,i;
Rect r;
if(!OpenAFile("\pcontrols",CControls))return;
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
DrawAll();
while(AnimControl(&item))
	{
	switch(item)
		{
		case 0:
			ShowIt();
			break;
		case 4:/*accelerator*/
			if(corepower[coreindex]<2)DoStopSound();
			else if(corestate[coreindex]!=0)DoStopSound();
			else if(orbit){killanim(); GameOver(FALSE);}
			else {TakeOff(); orbit=TRUE;}
			for(i=6;i>0;i--)
				{
				SetObjectState(4,i);
				ShowIt();
				}
			break;
		case 5:/*emergency power*/
			if(corestate[coreindex]<2)
			switch(corepower[coreindex])
				{
				case 0:
					corepower[coreindex]=1;
Clip.left=0;Clip.top=0;Clip.right=Width;Clip.bottom=Height;
					SetPort(&metaPort);
					ClipRect(&Clip);
					Display();
					SetPort(animWindow);
					break;
				case 1:
					corepower[coreindex]=0;
Clip.left=0;Clip.top=0;Clip.right=Width;Clip.bottom=Height;
					SetPort(&metaPort);
					ClipRect(&Clip);
					Display();
					SetPort(animWindow);
					break;
				case 2:
					SetObjectState(5,1);
					break;
				}
			else SetObjectState(5,1);
			ShowIt();
			break;
		case 6:/*ships weapons*/
			if(!orbit)
				{
				DoPShotSound();
				killanim();
				Terminate(TRUE);
				return;
				}
			else 
				{
				killanim(); 
				GameOver(TRUE);
				return;
				}
			break;
		case 7:/*damage report*/
			ObjectRect(7,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			if(corepower[coreindex]<2)DoText(&r,15,0);
			else if(!orbit) DoText(&r,49,0);
			else DoText(&r,66,0);
			break;
		}
	}
killanim();
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int CLift[]={0,c_flglass,
	c_teleport,c_box1,c_cryo,c_ccore,0,
	-redColor,-redColor,-cyanColor,-cyanColor};
DoLift(up,type)
int up,type;
{
int item,i,object;

switch(type)
	{
	case BOX1:
	case BOX2:
		object=2;
		break;
	case TELEPORT:
		object=1;
		break;
	case REACTOR:
		object=4;
		break;
	case CRYO:
		object=3;
		break;
	}
if(!LostSound)DoLiftSound();
if(!OpenAFile("\plifter",CLift))return(up);
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
DrawAll();
while(AnimControl(&item))
	{
	if(up)
		{
		if(item==8)
			{
			if(!LostSound)RepeatTSound();
			SetObjectState(8,2);
			SetObjectState(9,1);
			for(i=5;i>=1;i--)
				{
				SetObjectState(object,i);
				ShowIt();
				}
			up=FALSE;
			}
		}
	else 
		{
		if(item==9)
			{
			if(!LostSound)RepeatTSound();
			SetObjectState(9,2);
			SetObjectState(8,1);
			for(i=1;i<=5;i++)
				{
				SetObjectState(object,i);
				ShowIt();
				}
			up=TRUE;
			}
		}
	ShowIt();
	}
killanim();
if(!LostSound)KillTSound();
return(up);
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int CPowersuit[]={0,c_powerbase,
	-magentaColor,-magentaColor,-yellowColor,-yellowColor,c_powerbase,-whiteColor};
DoPowerSuit()
{
int item,i,state;
int narmor=armor,nweapons=weapons;
int wstate,astate;
Rect r;

if(!corepower[coreindex])return;
if(!OpenAFile("\pspacesuit",CPowersuit))return;
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
DrawAll();
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
					ShowIt();
					}
				}
			else
				{
				SetObjectState(1,astate+1); ShowIt();
				SetObjectState(1,astate=astate+2); ShowIt();
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
					ShowIt();
					}
				}
			else
				{
				SetObjectState(2,wstate+1); ShowIt();
				SetObjectState(2,wstate=wstate+2); ShowIt();
				SetObjectState(4,nweapons+1);
				}
			break;
		case 6:
			ObjectRect(6,&r);
			RLocalToGlobal(&r,&r);
			SetPort(animWindow);
			DoText(&r,13,0);
			break;
		}
	ShowIt();
	}
killanim();
if(nweapons!=weapons || narmor!=armor)
	{
	if(!LostSound)DoBzzzSound();
Clip.left=0;Clip.top=0;Clip.right=Width;Clip.bottom=Height;
	SetPort(&metaPort);
	ClipRect(&Clip);
	Display();
	for(i=0;i<10;i++)InvertRect(&Clip);
	}	
weapons=nweapons;
armor=narmor;
weapons2=weapons*weapons;
armor2=armor*armor;
DrawInfo();
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
int CForklift[]={0,c_forklift,c_forklift,c_forklift};
DoForkLift()
{
int item;

if(!OpenAFile("\pforklift",CForklift))return(0);
DrawAll();
while(AnimControl(&item) &&item!=1)
	{
	ShowIt();
	}
killanim();
return(item==1);
}
/*----------------------------------------------------------------------*/
int CDoor[]={0,c_bulkhead,0,c_door,-yellowColor};
int CBulkhead[]={0,c_bulkhead,0,c_bulkhead,-yellowColor};
int DoDoor(locked)
char locked;
{
int state=FALSE, notDone=TRUE,item,i;

if(!corepower[coreindex])return(state);
if(level==1 || level==5 ||level==6){if(!OpenAFile("\pbulkhead",CBulkhead))return(state);}
else {if(!OpenAFile("\pdoor",CDoor))return(state);}
SetObjectState(3,2);/*indicates closed door*/
SetObjectState(2,1);/*close the door*/
DrawAll();
while(AnimControl(&item)&&notDone)
	{
	if(5==ObjectState(2) && item==1){notDone=FALSE; state=TRUE; doorsound=TRUE;}
	if(item==3)
		{
		if(!LostSound)DoDoorSound();
		if(5==ObjectState(2))for(i=4;i>=1;i--){SetObjectState(2,i);ShowIt();}
		else for(i=2;i<6;i++){SetObjectState(2,i);ShowIt();}
		}
	ShowIt();
	}
if(5==ObjectState(2) && !LostSound)doorsound=TRUE;
killanim();
return(state);
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
 int CAirlock[]={0,c_bulkhead,c_bulkhead,-redColor,c_airlock};
int DoAirLock(locked,direction)
char* locked;
int direction;
{
int i,item,state=FALSE, notdone=TRUE;
char savelocked=*locked;

if(!OpenAFile("\pairlock",CAirlock))return(0);
if(*locked)
	{
	SetObjectState(3,1);
	SetObjectState(2,2);
	}
else
	{
	SetObjectState(3,5);
	SetObjectState(2,1);
	}
DrawAll();
while(AnimControl(&item)&&notdone)
	{
	if(item==3 && !*locked){state=TRUE; notdone=FALSE;}
	else if(item==2&&corepower[coreindex] && unlocked)
		{
		PlayAirlock();
		if(*locked)
			{		
			for(i=2;i<6;i++)
				{
				SetObjectState(3,i);
				ShowIt();
				}
			if((locked[1]==127)&&!(armor||fl)){Terminate(FALSE); killanim(); return(0);}
			}
		else
			{
			for(i=4;i>=1;i--)
				{
				SetObjectState(3,i);
				ShowIt();
				}
			}
		*locked=!*locked;
		if(*locked)leveldata[level].count--;
		else leveldata[level].count++;
		if(leveldata[level].count==2)notdone=FALSE;
		}
	ShowIt();
	}
killanim();

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
}
/*----------------------------------------------------------------------*/
int CElevator[]={0,c_bulkhead,0,c_elevator,c_elevator,-yellowColor};
int CElevator2[]={0,c_bulkhead,0,-magentaColor,c_elevator,c_elevator,
	-yellowColor,-yellowColor,-yellowColor,-yellowColor,-yellowColor};
int DoElevator(mapdata)
char mapdata[5];
{
int i,item,state=FALSE, notdone=TRUE,fl=level-1, lvl=level-1;
int savelevel=level;
int inside=FALSE;
if(!corepower[1])return(0);
if(!OpenAFile("\pelevator",CElevator))return(0);
DrawAll();
while(AnimControl(&item)&&notdone)
	{
	if(item==4)
		{
		if(!LostSound)DoElevatorSound();
		if(state==FALSE)
			{
			for(i=2;i<6;i++)
				{
				SetObjectState(2,i);
				SetObjectState(3,i);
				ShowIt();
				}
			state=TRUE;
			}
		else 
			{
			for(i=4;i>=1;i--)
				{
				SetObjectState(2,i);
				SetObjectState(3,i);
				ShowIt();
				}
			state=FALSE;
			}
		}
	else if(item==1)notdone=FALSE;
	ShowIt();
	}
killanim();
if(state==TRUE && !notdone)
	{
	notdone=TRUE;
	state=FALSE;
	if(!OpenAFile("\pelevator2",CElevator2))return(0);
	inside=TRUE;
	SetObjectState(2,lvl);
	SetObjectState(3,5);/*doors are set open*/
	SetObjectState(4,5);
	DrawAll();
	while(AnimControl(&item)&&notdone)
		{
		if(item>=5 && item<=9)
			{
			fl=item-4;
			if(lvl==fl)SetObjectState(item,1);
			else
				{
				if(!LostSound)DoElevatorSound();
				for(i=4;i>=1;i--)
					{
					SetObjectState(3,i);
					SetObjectState(4,i);
					ShowIt();
					}
				if(fl>lvl)
					{
					for(i=lvl;i<=fl;i++)
						{
						level=i+1;
						SetObjectState(2,i);
						ShowIt();
						}
					lvl=fl;
					}
				else
					{
					for(i=lvl;i>=fl;i--)
						{
						level=i+1;
						SetObjectState(2,i);
						ShowIt();
						}
					lvl=fl;
					}
				if(!LostSound)DoElevatorSound();
				for(i=2;i<=5;i++)
					{
					SetObjectState(3,i);
					SetObjectState(4,i);
					ShowIt();
					}
				SetObjectState(item,1);
				}
			}
		else if(item==1)notdone=FALSE;
		ShowIt();
		}
	killanim();
	}
level=savelevel;
if(level!=fl+1)
	{
	mapdata[2]=fl+1;
	state=TRUE;
	}
if(inside)
	Me.ang+=128;
return(state);
}
