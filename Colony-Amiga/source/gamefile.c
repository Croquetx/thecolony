/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
/*--------------------------------------------------------------------
 * gamefile.c
 * Map file system.
 * Used to load and save the maps that are edited.
 *--------------------------------------------------------------------
 * savegame(q)
 *		int q;
 * int opengame(load)
 *		int load;
 * my_write(pblk,buffer,length)
 * 		IOParam *pblk;
 *		Ptr buffer;
 *		long length;
 * my_read(pblk,buffer,length)
 * 		IOParam *pblk;
 *		Ptr buffer;
 *		long length;
 * my_read_loc(pblk,buffer,length,mark)
 *		IOParam *pblk;
 *		Ptr buffer;
 *		long length,mark;
 * load_mapnum(mnum,init)
 *		int mnum,init;
 * load_map(pblk)
 *		IOParam *pblk;
 * SaveGameData(pblk)
 * 		IOParam *pblk;
 * LoadGameData(pblk)
 * 		IOParam *pblk;
 *--------------------------------------------------------------------
 */
#include <FileMgr.h>
#include <StdFilePkg.h>
#include <SegmentLdr.h>
#define EXT extern
#include "cgamedefs.h"
int		filnum;
int		volnum;
char	volname[255];
char	filname[255]="\pUntitled";
long type='GAME';
long create='DAVE';
IOParam pblk;
FileParam fblk;
int map_defs[10];
int map_type;
SFReply reply;
AppFile theFile;
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
savegame(q)
int q;
{
int i=0;
long fsize=4096L;
Point loc;
OsErr err;
VolumeParam vblk;

retry:
pblk.ioNamePtr=(StringPtr)filname;/*file name*/
vblk.ioNamePtr=(StringPtr)volname;/*file name*/
if(q)
	{
	SetPt(&loc,100,80);
	SFPutFile(loc  ,"\pSave Game as...",pblk.ioNamePtr,(Ptr)NIL,&reply);
	if(reply.good==FALSE)return(FALSE);
	}
for(i=0;i<64;i++)vblk.ioNamePtr[i]=pblk.ioNamePtr[i]=reply.fName[i];
vblk.ioVRefNum=pblk.ioVRefNum=reply.vRefNum;
pblk.ioVersNum=reply.version;
pblk.ioPermssn=fsWrPerm;
pblk.ioMisc=(Ptr)NIL;
vblk.ioVolIndex= -1;
PBGetVInfo(&vblk,FALSE);
if((vblk.ioVAlBlkSiz*vblk.ioVFrBlk) < 33000L)
	{
	DoText(&screenBits.bounds,151,0);
	goto retry;
	}
err=PBCreate(&pblk,FALSE);
if(err&&err!=dupFNErr)
	{
	Inform("\pPBCreate error");
	DoText(&screenBits.bounds,151,0);
	return(FALSE);
	}
err=PBOpen(&pblk,FALSE);
if(err)
	{
	Inform("\pPBOpen error");
	DoText(&screenBits.bounds,151,0);
	return(FALSE);
	}
err=PBSetEOF(&pblk,FALSE);
if(err)
	{
	Inform("\pPBSetEOF error");
	DoText(&screenBits.bounds,151,0);
	return(FALSE);
	}
err=SaveGameData(&pblk);
if(err){Inform("\pSaveGameData error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
err=PBFlushFile(&pblk,FALSE);
if(err){Inform("\pPBFlushFile error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
err=PBClose(&pblk,FALSE);
if(err){Inform("\pPBClose error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
fblk.qLink=pblk.qLink;
fblk.qType=pblk.qType;
fblk.ioTrap=pblk.ioTrap;
fblk.ioCmdAddr=pblk.ioCmdAddr;
fblk.ioCompletion=pblk.ioCompletion;
fblk.ioResult=pblk.ioResult;
fblk.ioNamePtr=pblk.ioNamePtr;
fblk.ioVRefNum=pblk.ioVRefNum;
err=PBGetFInfo(&fblk,FALSE);
if(err){Inform("\pPBGetFInfo error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
fblk.ioFlFndrInfo.fdType=type;
fblk.ioFlFndrInfo.fdCreator=create;
err=PBSetFInfo(&fblk,FALSE);
if(err){Inform("\pPBSetFInfo error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
pblk.ioNamePtr=0l;
err=PBFlushVol(&pblk,FALSE);
if(err){Inform("\pPBFlushVol error");	DoText(&screenBits.bounds,151,0);return(FALSE);}
return(TRUE);/*indicates that data has been saved correctly*/
}
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
#if 0
saveprofile()
{
int i=0;
long fsize=4096L;
Point loc;
OsErr err;


pblk.ioNamePtr=(StringPtr)filname;/*file name*/
SetPt(&loc,100,80);
SFPutFile(loc  ,"\pSave Game as...",pblk.ioNamePtr,(Ptr)NIL,&reply);
if(reply.good==FALSE)return;
for(i=0;i<64;i++)pblk.ioNamePtr[i]=reply.fName[i];
pblk.ioVRefNum=reply.vRefNum;
pblk.ioVersNum=reply.version;
pblk.ioPermssn=fsWrPerm;
pblk.ioMisc=(Ptr)NIL;
err=PBCreate(&pblk,FALSE);
if(err&&err!=dupFNErr)
	{
	Inform("\pPBCreate error");
	return(FALSE);
	}
err=PBOpen(&pblk,FALSE);
if(err)
	{
	Inform("\pPBOpen error");
	return(FALSE);
	}
err=PBSetEOF(&pblk,FALSE);
if(err)
	{
	Inform("\pPBSetEOF error");
	return(FALSE);
	}
DumpProfile();
err=PBFlushFile(&pblk,FALSE);
if(err){Inform("\pPBFlushFile error");return(FALSE);}
err=PBClose(&pblk,FALSE);
if(err){Inform("\pPBClose error");return(FALSE);}
fblk.qLink=pblk.qLink;
fblk.qType='TEXT';
fblk.ioTrap=pblk.ioTrap;
fblk.ioCmdAddr=pblk.ioCmdAddr;
fblk.ioCompletion=pblk.ioCompletion;
fblk.ioResult=pblk.ioResult;
fblk.ioNamePtr=pblk.ioNamePtr;
fblk.ioVRefNum=pblk.ioVRefNum;
err=PBGetFInfo(&fblk,FALSE);
if(err){Inform("\pPBGetFInfo error");return(FALSE);}
fblk.ioFlFndrInfo.fdType='TEXT';
fblk.ioFlFndrInfo.fdCreator=create;
err=PBSetFInfo(&fblk,FALSE);
if(err){Inform("\pPBSetFInfo error");return(FALSE);}
return(TRUE);/*indicates that data has been saved correctly*/
}
#endif
/*----------------------------------------------------------------------*/
char name[64];
int opengame(load)
int load;
{
OsErr err;
SFTypeList typelist;
int numtypes=1;
Point loc;
int i=0;
extern long cCtype;
pblk.ioNamePtr=(StringPtr)filname;/*file name*/
if(!load)
	{
	SetPt(&loc,100,80);
		typelist[0]=type;
	SFGetFile(loc,"\pLoad Map",(Ptr)NIL,numtypes,typelist,(Ptr)NIL,&reply);
	if(reply.good==FALSE)return(FALSE);
	if(!gametest)DoGameSecurity();
	for(i=0;i<64;i++)pblk.ioNamePtr[i]=reply.fName[i];
	pblk.ioVRefNum=reply.vRefNum;
	pblk.ioVersNum=reply.version;
	pblk.ioPermssn=fsRdPerm;
	pblk.ioMisc=(Ptr)NIL;
	}
else{
	if(!gametest)DoGameSecurity();
	GetAppFiles(1,&theFile);
	if(theFile.fType==cCtype)
		{
		err=load_color(theFile.fName);
		if(err){Inform("\pProblem loading color!"); ExitToShell();}
		return(FALSE);
		}
	for(i=0;i<64;i++)pblk.ioNamePtr[i]=theFile.fName[i];
	pblk.ioVRefNum=theFile.vRefNum;
	pblk.ioVersNum=theFile.versNum;
	pblk.ioPermssn=fsRdPerm;
	pblk.ioMisc=(Ptr)NIL;
	}
for(i=0;i<64;i++)reply.fName[i]=pblk.ioNamePtr[i];
reply.vRefNum=pblk.ioVRefNum;
reply.version=pblk.ioVersNum;
err=PBOpen(&pblk,FALSE);
if(err){Inform("\pPBOpen error"); 	DoText(&screenBits.bounds,150,0);return(FALSE);}
for(i=1;i<255;i++)Object[i].alive=0;
err=LoadGameData(&pblk);
if(err){Inform("\pLoadGameData error"); DoText(&screenBits.bounds,150,0);return(FALSE);}
pblk.ioNamePtr=reply.fName;
pblk.ioVRefNum=reply.vRefNum;
pblk.ioVersNum=reply.version;
pblk.ioPermssn=fsWrPerm;
pblk.ioMisc=(Ptr)NIL;
err=PBFlushFile(&pblk,FALSE);
if(err){Inform("\pPBFlushFile error"); DoText(&screenBits.bounds,150,0);return(FALSE);}
err=PBClose(&pblk,FALSE);
if(err){Inform("\pPBClose error"); DoText(&screenBits.bounds,150,0);return(FALSE);}
/*-RESET DATA AND LOAD MAPS*/
DrawInfo();
if(game==COLONY)
	{
	robotarray[Me.xindex][Me.yindex]=MENUM;
	if(load_mapnum(level,FALSE))
		{
		DoText(&screenBits.bounds,152,0);
		ExitToShell();
		}
	}
else DrawCompass();
if(level<10 && level!=0)for(i=1;i<255;i++)if(Object[i].alive){SetObject(i,TRUE); robotnum=i+1; }
return(TRUE);
}
/*----------------------------------------------------------------------*/
my_write(pblk,buffer,length)
IOParam *pblk;
Ptr buffer;
long length;
{
OsErr err;

pblk->ioBuffer=buffer;
pblk->ioReqCount=length;
pblk->ioPosMode=fsAtMark;
pblk->ioPosOffset=NIL;
err=PBWrite(pblk,FALSE);
if(err)
	{
	DoChimeSound();
	}
if(pblk->ioActCount!=pblk->ioReqCount)
	{
	if(!err)err=TRUE;
	DoChimeSound();
	}
return(err);
}
/*----------------------------------------------------------------------*/
my_read(pblk,buffer,length)
IOParam *pblk;
Ptr buffer;
long length;
{
OsErr err;

pblk->ioBuffer=buffer;
pblk->ioReqCount=length;
pblk->ioPosMode=fsAtMark;
pblk->ioPosOffset=NIL;
err=PBRead(pblk,FALSE);
if(err)
	{
	DoChimeSound();
	}
if(pblk->ioActCount!=pblk->ioReqCount)
	{
	DoChimeSound();
	if(!err)err=TRUE;
	}
return(err);
}
/*----------------------------------------------------------------------*/
my_read_loc(pblk,buffer,length,mark)
IOParam *pblk;
Ptr buffer;
long length,mark;
{
OsErr err;

pblk->ioBuffer=buffer;
pblk->ioReqCount=length;
pblk->ioPosMode=fsFromStart;
pblk->ioPosOffset=mark;
err=PBRead(pblk,FALSE);
if(err)
	{
	DoChimeSound();
	}
if(pblk->ioActCount!=pblk->ioReqCount)
	{
	if(!err)err=TRUE;
	DoChimeSound();
	}
return err;
}
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
char *mapnums[]={"\p0","\p1","\p2","\p3","\p4","\p5","\p6","\p7","\p8","\p9"};
char *mapname="\p:CData:map.";
load_mapnum(mnum,init)
int mnum,init;
{
OSErr err;
int vnum;
char str[255];
char fname[255];
int i,j;
IOParam mblk;

Catenate(fname,mapname,mapnums[mnum]);
mblk.qLink=0;
mblk.qType=0;
mblk.ioTrap=0;
mblk.ioCmdAddr=0;
mblk.ioCompletion=0;
mblk.ioResult=0;
mblk.ioRefNum=0;
mblk.ioBuffer=0;
mblk.ioReqCount=0;
mblk.ioActCount=0;
mblk.ioPosMode=0;
mblk.ioPosOffset=0;
mblk.ioNamePtr = (StringPtr)0;

err=GetVol(str,&vnum);
if(err)
	{
	DoChimeSound();
	DoChimeSound();
	Inform("\pGetVol error");
	return(err);
	}
/*sprintf(str," map.%d",mnum);
i=0; while(str[i])i++;	str[0]=i-1;
mblk.ioNamePtr=(StringPtr)str;/*file name*/
/*mapname[11]=mapnums[mnum];*/
mblk.ioNamePtr=(StringPtr)fname;/*file name*/
mblk.ioVRefNum=vnum;
mblk.ioVersNum=0;
mblk.ioPermssn=fsRdPerm;
mblk.ioMisc=(Ptr)NIL;
if(init && level!=0)SaveLevel();
if(init)for(i=0;i<255;i++)
	Object[i].alive = FALSE;
for(i=0;i<32;i++)
	for(j=0;j<32;j++)
		{
		if(robotarray[i][j]!=MENUM)robotarray[i][j]=0;
		foodarray[i][j]=0;
		if(init)dirXY[i][j]=0;
		}
level=mnum;
if(level==1)coreindex=0;
else coreindex=1;
err=load_map(&mblk,init);
if(err){Inform("\pload_map error"); return(err);}
change=TRUE;
if(init)InitObject();
getwall();
DrawCompass();
return(0);
}
/*----------------------------------------------------------------------*/
load_map(pblk,init)
IOParam *pblk;
int init;
{
OSErr err;
int blength;
long name;
err=PBOpen(pblk,FALSE);
if(err)
	{
	DoChimeSound();
	Inform("\pPBOpen error");
	return(err);
	}
if(err=my_read(pblk,&name,4L))return(err);
if(name!='DAVE')ExitToShell();
if(err=my_read(pblk,(Ptr)map_defs,(long)20))return(err);
if(err=my_read(pblk,(Ptr)(&blength),2L))return(err);
if(0==(buffer=NewPtr((long)blength)))MemoryErr();
if(err=my_read(pblk,(Ptr)buffer,(long)blength))return(err);
err=PBClose(pblk,(char)FALSE);
if(err)
	{
	DoChimeSound();
	Inform("\pPBClose error");
	return(err);
	}
expand(init);
DisposPtr(buffer);
if(init)DoPatch();
map_type=map_defs[0];
flip=map_defs[2];
change=1;
return(0);
}
/*----------------------------------------------------------------------*/
int SaveGameData(pblk)
ParamBlockRec *pblk;
{
int i;
int err;
/*-LEVEL DATA-------------------*/
leveldata[level].visit=TRUE;
leveldata[level].queen=allgrow;
err=my_write(pblk,&game,2L);
if(err)return(err);
err=my_write(pblk,&level,2L);
if(err)return(err);
for(i=1;i<8;i++)
	{
	err=my_write(pblk,&leveldata[i].visit,1L);
	if(err)return(err);
	if(leveldata[i].visit)
		{
		err=my_write(pblk,&leveldata[i],(long)sizeof(struct leveldata));
		if(err)return(err);
		}
	}
/*-OBJECTS----------------------*/
if(level!=0 && level<10)
	{
	err=my_write(pblk,Object,(long)sizeof(Thing) * 255L);
	if(err)return(err);
	}
#ifdef debug
Debug("\pmaxobjects: ",(long)maxobjects);
#endif
if(err=my_write(pblk,&maxobjects,2L))return(err);
#ifdef debug
Debug("\pmaxrob: ",(long)maxrob);
#endif
if(err=my_write(pblk,&maxrob,2L))return(err);
/*-PATCHES----------------------*/
#ifdef debug
Debug("\ppatchnum: ",(long)patchnum);
#endif
if(err=my_write(pblk,&patchnum,2L))return(err);
for(i=0;i<patchnum;i++)
	{
#ifdef debug
	Debug("\ppatch type: ",(long)patch[i].type);
	Debug("\plevel: ",(long)patch[i].to.level);
#endif
	if(err=my_write(pblk,&patch[i],(long)sizeof(struct  patchstrct)))
		return(err);
	}
#ifdef debug
Debug("\pcarrytype:",(long)carrytype);
#endif
if(err=my_write(pblk,carrypatch,sizeof(struct passpatch)*2L))return(err);
if(err=my_write(pblk,&carrytype,2L))return(err);

/*-ME---------------------------*/
if(err=my_write(pblk,&armor,2L))return(err);
if(err=my_write(pblk,&weapons,2L))return(err);
if(err=my_write(pblk,&fl,2L))return(err);
if(err=my_write(pblk,&orbit,2L))return(err);
if(err=my_write(pblk,&Me,(long)sizeof(Locate)))return(err);
if(err=my_write(pblk,epower,6L))return(err);

/*-REACTOR----------------------*/
if(err=my_write(pblk,corestate,4L))return(err);
if(err=my_write(pblk,coreheight,4L))return(err);
if(err=my_write(pblk,corepower,6L))return(err);
if(err=my_write(pblk,decode1,4L))return(err);
if(err=my_write(pblk,decode2,4L))return(err);
if(err=my_write(pblk,decode3,4L))return(err);
if(err=my_write(pblk,&unlocked,2L))return(err);

/*-SNOOP PATH-------------------*/
for(i=0;i<32;i++)if(err=my_write(pblk,dirXY[i],32L))return(err);

/*-BATTLE-----------------------*/
if(err=my_write(pblk,bfight,sizeof(Locate)*16L))return(err);
if(err=my_write(pblk,&Enter,(long)sizeof(Locate)))return(err);
if(err=my_write(pblk,&Ship,(long)sizeof(Locate)))return(err);
if(err=my_write(pblk,&projon,2L))return(err);
if(projon)
	{
	if(err=my_write(pblk,&pcount,2L))return(err);
	if(err=my_write(pblk,&Proj,(long)sizeof(Locate)))return(err);
	}
if(err=my_write(pblk,pbattle.buffer,(long)sizeof(Locate)*4*4*MAXQUAD))return(err);
return(0);/*everything is OK*/
}

/*----------------------------------------------------------------------*/
LoadGameData(pblk)
IOParam *pblk;
{
int i;
int err;

robotarray[Me.xindex][Me.yindex]=0;
/*-LEVEL DATA-------------------*/
if(err=my_read(pblk,&game,2L))return(err);
if(err=my_read(pblk,&level,2L))return(err);
if(game==BATTLE)level=0;
for(i=1;i<8;i++)
	{
	if(err=my_read(pblk,&leveldata[i].visit,1L))return(err);
	if(leveldata[i].visit)
		{
		if(err=my_read(pblk,&leveldata[i],(long)sizeof(struct leveldata)))return(err);
		}
	else 
		{
		leveldata[i].size=0;
		leveldata[i].count=0;
		if(i==2)leveldata[2].count=1;
		}
	}
if(level)allgrow=leveldata[level].queen;
else allgrow=0;
/*-OBJECTS----------------------*/
if(level!=0 && level<10)
	if(err=my_read(pblk,Object,(long)sizeof(Thing) * 255L))return(err);
if(err=my_read(pblk,&maxobjects,2L))return(err);
#ifdef debug
Debug("\pmaxobjects: ",(long)maxobjects);
#endif
if(err=my_read(pblk,&maxrob,2L))return(err);
#ifdef debug
Debug("\pmaxrob: ",(long)maxrob);
#endif

/*-PATCHES----------------------*/
if(err=my_read(pblk,&patchnum,2L))return(err);
#ifdef debug
Debug("\ppatchnum: ",(long)patchnum);
#endif
for(i=0;i<patchnum;i++)
	{
	if(err=my_read(pblk,&patch[i],(long)sizeof(struct  patchstrct)))return(err);
#ifdef debug
	Debug("\ppatch type: ",(long)patch[i].type);
	Debug("\plevel: ",(long)patch[i].to.level);
#endif
	}
if(err=my_read(pblk,carrypatch,sizeof(struct passpatch)*2L))return(err);
if(err=my_read(pblk,&carrytype,2L))return(err);
#ifdef debug
Debug("\pcarrytype:",(long)carrytype);
#endif

/*-ME---------------------------*/
if(err=my_read(pblk,&armor,2L))return(err);
if(err=my_read(pblk,&weapons,2L))return(err);
armor2=armor*armor;
weapons2=weapons*weapons;
if(err=my_read(pblk,&fl,2L))return(err);
if(err=my_read(pblk,&orbit,2L))return(err);
if(err=my_read(pblk,&Me,(long)sizeof(Locate)))return(err);
if(err=my_read(pblk,epower,6L))return(err);

/*-REACTOR----------------------*/
if(err=my_read(pblk,corestate,4L))return(err);
if(err=my_read(pblk,coreheight,4L))return(err);
if(err=my_read(pblk,corepower,6L))return(err);
if(err=my_read(pblk,decode1,4L))return(err);
if(err=my_read(pblk,decode2,4L))return(err);
if(err=my_read(pblk,decode3,4L))return(err);
if(err=my_read(pblk,&unlocked,2L))return(err);

/*-SNOOP PATH-------------------*/
for(i=0;i<32;i++)if(err=my_read(pblk,dirXY[i],32L))return(err);

/*-BATTLE-----------------------*/
if(err=my_read(pblk,bfight,sizeof(Locate)*16L))return(err);
if(err=my_read(pblk,&Enter,(long)sizeof(Locate)))return(err);
if(err=my_read(pblk,&Ship,(long)sizeof(Locate)))return(err);
if(err=my_read(pblk,&projon,2L))return(err);
if(projon)
	{
	if(err=my_read(pblk,&pcount,2L))return(err);
	if(err=my_read(pblk,&Proj,(long)sizeof(Locate)))return(err);
	}
if(err=my_read(pblk,pbattle.buffer,(long)sizeof(Locate)*4*4*MAXQUAD))return(err);
return(0);/*everything is ok*/
}
/*----------------------------------------------------------------------*/
int Catenate(into,str1,str2)
unsigned char *into,*str1,*str2;
{
unsigned int length,i;

length=str1[0]+str2[0];
if(length>255)return(1);
for(i=1;i<=str1[0];i++)
	into[i]=str1[i];
for(i=1;i<=str2[0];i++)
	into[i+str1[0]]=str2[i];
into[0]=length;
}
