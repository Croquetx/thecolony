/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
#define IBM_PC 	(0)               /*  VSP uses codes to keep the machines */
#define TANDY	(13)
#define SS if((SoundCount>1)||(!soundon))return
typedef unsigned char byte,*bytePtr;
extern int soundon;
extern int SoundCount;

extern byte far Explode2[];
extern byte far Chime[];
extern byte far Them[];
extern byte far TTorps[];
extern byte far Eat[];
extern byte far Dit[];
extern byte far Ouch[];
extern byte far PlanetShot[];
extern byte far Test[];
extern byte far Xporter2[2];
extern byte far Airlock[];
extern byte far Ugh[];
extern byte far Floor[];
extern byte far Toilet2[];
extern byte far Bath[];
extern byte far Teleport[];
extern byte far Door1[];
extern byte far Elevator[];
extern byte far Slug2[];
extern byte far Lift[];
extern byte far Clatter[];
extern byte far Sink2[];
extern byte far Wallx[];
extern byte far Glass[];
extern byte far Tunnel2[];
extern byte far Klaxon[];
extern byte far Fullstop[];
extern byte far Drop[];
extern byte far Stars1[];
extern byte far Stars2[];
extern byte far Stars3[];
extern byte far Stars4[];

/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
int SoundDone(){return(!SoundCount);}
KillSound(){SoundCount=0; SHUTDOWNVSP(); INITVSP(IBM_PC);}
InitSound(){INITVSP(IBM_PC);}
EndSound(){SHUTDOWNVSP();}
/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
#define FLAG (char)1

PlayKlaxon()	{SS; SoundCount++; SOUNDEFFECT(Klaxon,	10+SoundCount,FLAG);}
DoBeammeSound()	{SS; SoundCount++; SOUNDEFFECT(Xporter2,10+SoundCount,FLAG);}
PlayAirlock()	{SS; SoundCount++; SOUNDEFFECT(Airlock,	10+SoundCount,FLAG);}
DoOuchSound()	{SS; SoundCount++; SOUNDEFFECT(Ouch,	10+SoundCount,FLAG);}
DoChimeSound()	{SS; SoundCount++; SOUNDEFFECT(Chime,	10+SoundCount,FLAG);}
DoBangSound()	{SS; SoundCount++; SOUNDEFFECT(Ugh,		10+SoundCount,FLAG);}
DoShootSound()	{SS; SoundCount++; SOUNDEFFECT(Them,	12+SoundCount,FLAG);}
DoEatSound()	{SS; SoundCount++; SOUNDEFFECT(Eat,		10+SoundCount,FLAG);}
DoBonkSound()	{SS; SoundCount++; SOUNDEFFECT(Ouch,	10+SoundCount,FLAG);}
DoBzzzSound()	{SS; SoundCount++; SOUNDEFFECT(Floor,	10+SoundCount,FLAG);}
DoExplodeSound(){SS; SoundCount++; SOUNDEFFECT(Explode2,10+SoundCount,FLAG);}
DoElevatorSound(){SS; SoundCount++;SOUNDEFFECT(Elevator,10+SoundCount,FLAG);}
DoPShotSound()	{SS; SoundCount++;SOUNDEFFECT(PlanetShot,10+SoundCount,FLAG);}
DoTestSound()	{SS; 				SOUNDEFFECT(Test,	10+SoundCount,FLAG);}
DoDitSound()	{SS; SoundCount++; SOUNDEFFECT(Dit,		10+SoundCount,FLAG);}
DoSinkSound()	{SS; SoundCount++; SOUNDEFFECT(Sink2,	10+SoundCount,FLAG);}
DoClatterSound(){SS; SoundCount++; SOUNDEFFECT(Clatter,	10+SoundCount,FLAG);}
DoStopSound()	{SS; SoundCount++; SOUNDEFFECT(Fullstop,10+SoundCount,FLAG);}
DoTeleportSound(){SS; SoundCount++;SOUNDEFFECT(Teleport,10+SoundCount,FLAG);}
DoSlugSound()	{SS; SoundCount++; SOUNDEFFECT(Slug2,	10+SoundCount,FLAG);}
DoTunnel2Sound(){SS; SoundCount++; SOUNDEFFECT(Tunnel2,	10+SoundCount,FLAG);}
DoLiftSound()	{SS; SoundCount++; SOUNDEFFECT(Lift,	10+SoundCount,FLAG);}
DoDropSound()	{SS; SoundCount++; SOUNDEFFECT(Drop,	10+SoundCount,FLAG);}
DoGlassSound()	{SS; SoundCount++; SOUNDEFFECT(Glass,	10+SoundCount,FLAG);}
DoDoorSound()	{SS; SoundCount++; SOUNDEFFECT(Door1,	10+SoundCount,FLAG);}
PlayStars1()		{SS; 		   SOUNDEFFECT(Stars1,10+SoundCount,FLAG);}
PlayStars2()		{SS; 		   SOUNDEFFECT(Stars2,10+SoundCount,FLAG);}
PlayStars3()		{SS; 		   SOUNDEFFECT(Stars3,10+SoundCount,FLAG);}
PlayStars4()		{SS; 		   SOUNDEFFECT(Stars4,10+SoundCount,FLAG);}
DoToiletSound()	{SS; 			   SOUNDEFFECT(Toilet2,	100,FLAG);}
DoBathSound()	{SS; 			   SOUNDEFFECT(Bath,	120,FLAG);}
