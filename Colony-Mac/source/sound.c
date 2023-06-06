/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
#include <Quickdraw.h>
#include <WindowMgr.h>
#include <MenuMgr.h>
#include <EventMgr.h>
#include <FileMgr.h>
#include <SoundDvr.h>
#include <VRetraceMgr.h>
#include <OSUtil.h>
#include <DialogMgr.h>
#include <StdFilePkg.h>

extern int soundon;
int LostSound=FALSE;
#define BEAMME 5342
#define AIRLOCK 5141
#define MARS	23390
#define MARS2	32291
#define MESHOOT 24433
#define THEYSHOOT 24010
#define EXPLODE 1432
#define UGH 7970
#define TRANSPORTER 606
#define EAT 11783
#define FLOOR 11642
#define TOILET	4955
#define SINK	2920
#define	BATH	11589
#define TELEPORT 9757
#define HOLE 11208
#define DOOR 26867
#define ELEVATOR 12019
#define SLUG 8347
#define TUNNEL1 16403
#define TUNNEL2 17354
#define LIFT 28521
#define CLATTER 11208
#define GLASS	19944
#define TEST	25795
#define END		18282
#define KLAXON	27317
#define FULLSTOP 29382
#define SWISH 7089
#define DIDIT 4274
#define CHIME 24694
#define DAVE 13651
#define SCREAM 12644
#define OUCH 9924
#define PLANETSHOT 27539
#define DIT 1516
struct SoundRec *mars,*beamme,*airlock,*meshoot,
	*theyshoot,*explode,*ugh,*eat,*bzzz,*teleport,
	*door,*elevator,*end,*klaxon,*didit,*chime,*ouch;
struct SoundRec *temp;

/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
struct SoundRec
	{
	long size;
	int count;
	FFSynthRec synthRec;
	};

struct SoundRec* LoadSound(snum,speed)
int snum,speed;
{
Handle hSound;
long size;
struct SoundRec *sound;
long k;

hSound=GetResource('snd ',snum);
size=SizeResource(hSound);
if(0==(sound=(struct SoundRec*)NewPtr(size+10)))MemoryErr();
sound->size=size-42;
sound->synthRec.mode=ffMode;
sound->synthRec.count=FixRatio(1,speed);
sound->count=speed;
HLock(hSound);
for(k=0;k<size-42;k++)sound->synthRec.waveBytes[k]=(*hSound)[k+42];
HUnlock(hSound);
return(sound);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
KillSound(sound)
Ptr sound;
{
DisposPtr(sound);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
PlaySound(sound)
struct SoundRec *sound;
{
if(!soundon)return;
StopSound();
StartSound(&sound->synthRec,sound->size,(Ptr)0);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
int endCSound;
int csRepeat;
ParamBlockRec SoundBlock;
VBLTask csTask;
long csLength;

RepeatCSound()
{

SetUpA5();
if(endCSound)
	{
	endCSound=0;
	SoundBlock.ioParam.ioActCount=csLength+1;
	}
else
	{
	if(SoundBlock.ioParam.ioActCount>=csLength)
		{
		SoundBlock.ioParam.ioActCount=0;
		csRepeat++;
		}
	csTask.vblCount=1;
	}
RestoreA5();
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
EndCSound()
{
if(LostSound)return;
if(!soundon)return;
endCSound=TRUE;
while(endCSound);
VRemove(&csTask);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
NumCSound()
{
return(csRepeat);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
PlayCSound(sound)
struct SoundRec *sound;
{
unsigned int count;
long rcount;
int i;

if(LostSound)return;
if(!soundon)return;
StopSound();
endCSound=FALSE;
csRepeat=0;
rcount=sound->count*370;
count=sound->size/rcount;
csLength=rcount*count;
csTask.qType=1;
csTask.vblAddr=RepeatCSound;
csTask.vblCount=1;
csTask.vblPhase=0;
if(i=VInstall(&csTask)){Inform("\pVBInstall Err"); ShowNum((long)i);return;}
SoundBlock.ioParam.ioCompletion=0;
SoundBlock.ioParam.ioRefNum=-4;
SoundBlock.ioParam.ioBuffer=(Ptr)&sound->synthRec;
SoundBlock.ioParam.ioReqCount=sound->size;
SoundBlock.ioParam.ioActCount=0;
PBWrite(&SoundBlock,TRUE);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
char *sname="\pZounds";
SoundIntro(count)
{
DialogPtr thedialog;
int itemhit=0;
Point loc;
SFTypeList typelist;
SFReply reply;
char *sfname[255];

if(!LostSound)
	{
	if(-1==OpenResFile(sname))
		{
		Catenate(sfname,"\p:CData:",sname);
		if(-1==OpenResFile(sfname))
			{
			thedialog = GetNewDialog(993,(Ptr)0L,(WindowPtr)(-1));
			ModalDialog(0L,&itemhit);
			DisposDialog(thedialog);
			switch(itemhit)
				{
				case 0:/*don't do anything...should not happen*/
					break;
				case 1:/*find Zounds...*/
					SetPt(&loc,100,80);
					typelist[0]='ZNDS';
					SFGetFile(loc,"\pFind 'Zounds'",(Ptr)0L,1,typelist,(Ptr)0L,&reply);
					if(reply.good!=FALSE)
						{
						if(-1==OpenRFPerm(reply.fName,reply.vRefNum,fsRdPerm))
							LostSound=TRUE;
						}
					else LostSound=TRUE;
					break;
				case 2:/*Don't bother*/
					LostSound=TRUE;
					break;
				}
			}
		}
	}
explode=LoadSound(EXPLODE,4);
chime=LoadSound(CHIME,4);
if(LostSound)return;
mars=LoadSound(MARS2,1);
beamme=LoadSound(TRANSPORTER,4);
klaxon=LoadSound(KLAXON,4);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
SoundInit(cnt)
int cnt;
{

if(!LostSound)
	{
	while(!SoundDone());
	KillSound(beamme);
	KillSound(mars);
	KillSound(klaxon);
	airlock=LoadSound(AIRLOCK,4);
	ugh=LoadSound(UGH,2);
	bzzz=LoadSound(FLOOR,4);
	teleport=LoadSound(TELEPORT,2);
	door=LoadSound(DOOR,2);
	elevator=LoadSound(ELEVATOR,2);
	}
meshoot=LoadSound(MESHOOT,2);
theyshoot=LoadSound(THEYSHOOT,2);
eat=LoadSound(EAT,4);
ouch=LoadSound(OUCH,4);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
SoundEnd()
{
if(LostSound)return;
KillSound(airlock);
KillSound(meshoot);
KillSound(theyshoot);
KillSound(ugh);
KillSound(eat);
KillSound(bzzz);
KillSound(teleport);
KillSound(door);
KillSound(elevator);

mars=LoadSound(MARS2,1);
end=LoadSound(END,4);
didit=LoadSound(DIDIT,2);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
PlayMars()
{
if(LostSound)return;
PlayCSound(mars);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
PlayKlaxon()
{
if(LostSound)return;
PlaySound(klaxon);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoBeammeSound()
{
if(LostSound)return;
PlaySound(beamme);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
PlayAirlock()
{
if(LostSound){PlaySound(chime);return;}
PlaySound(airlock);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoOuchSound()
{
if(LostSound)return;
PlaySound(ouch);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
PlayDiDit()
{
if(LostSound) {PlaySound(chime);return;}
while(!SoundDone());
PlaySound(didit);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoChimeSound()
{
PlaySound(chime);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoBangSound()
{
PlaySound(meshoot);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoShootSound()
{
PlaySound(theyshoot);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoEatSound()
{
PlaySound(eat);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoBonkSound()
{
if(LostSound){PlaySound(chime); return;}
PlaySound(ugh);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoBzzzSound()
{
if(LostSound){PlaySound(chime); return;}
PlaySound(bzzz);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoExplodeSound()
{
PlaySound(explode);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoElevatorSound()
{
if(LostSound){PlaySound(chime); return;}
PlaySound(elevator);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoPShotSound()
{
struct SoundRec *temp;

if(LostSound)return;
temp=LoadSound(PLANETSHOT,3);
PlaySound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoToiletSound()
{
struct SoundRec *temp;

if(LostSound)return;
temp=LoadSound(TOILET,2);
PlaySound(temp);
while(!SoundDone());
StopSound();
KillSound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoTestSound()
{
if(LostSound)return;
temp=LoadSound(TEST,4);
StopSound();
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoDitSound()
{
if(LostSound)return;
temp=LoadSound(DIT,3);
StopSound();
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoSinkSound()
{
struct SoundRec *temp;

if(LostSound)return;
temp=LoadSound(SINK,2);
PlaySound(temp);
while(!SoundDone());
StopSound();
KillSound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoBathSound()
{
struct SoundRec *temp;

if(LostSound)return;
temp=LoadSound(BATH,2);
PlaySound(temp);
while(!SoundDone());
StopSound();
KillSound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoClatterSound()
{
struct SoundRec *temp;

if(LostSound)return;
temp=LoadSound(CLATTER,2);
PlaySound(temp);
while(!SoundDone());
StopSound();
KillSound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoSwishSound()
{
if(LostSound)return;
temp=LoadSound(SWISH,5);
PlaySound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoStopSound()
{
struct SoundRec *temp;

if(LostSound)return;
temp=LoadSound(FULLSTOP,4);
PlaySound(temp);
while(!SoundDone());
StopSound();
KillSound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoTeleportSound()
{
if(LostSound)return;
PlaySound(teleport);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoHoleSound()
{
if(LostSound)return;
temp=LoadSound(HOLE,2);
PlaySound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoSlugSound()
{
if(LostSound)return;
temp=LoadSound(SLUG,2);
PlaySound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoTunnel1Sound()
{
if(LostSound)return;
temp=LoadSound(TUNNEL1,2);
PlayCSound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoTunnel2Sound()
{
if(LostSound)return;
temp=LoadSound(TUNNEL2,2);
PlaySound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoLiftSound()
{
if(LostSound)return;
temp=LoadSound(LIFT,2);
StopSound();
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoGlassSound()
{
if(LostSound)return;
temp=LoadSound(GLASS,2);
PlaySound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
RepeatTSound()
{
if(LostSound)return;
StopSound();
PlaySound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
KillTSound()
{
if(LostSound)return;
while(!SoundDone());
StopSound();
KillSound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoEndSound()
{
if(LostSound)return;
while(!SoundDone());
StopSound();
PlaySound(end);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoDoorSound()
{
if(LostSound)return;
PlaySound(door);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoDaveSound()
{
if(LostSound)return;
StopSound();
temp=LoadSound(DAVE,1);
PlaySound(temp);
}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
DoScreamSound()
{
if(LostSound)return;
StopSound();
temp=LoadSound(SCREAM,6);
PlaySound(temp);
}