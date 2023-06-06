/*  #define IBM_load_mapnum    */
/*  #define IBM_load_map       */
/*  #define IBM_SaveGameDaa   */
/*  #define IBM_LoadGameData   */
/*  #define IBM_Catenate    */
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
char *getInput();
/*
#include <FileMgr.h>
#include <StdFilePkg.h>
#include <SegmentLdr.h>
*/
#define EXT extern
#include <errno.h>
#include "gamedefs.h"
#include "fcntl.h"
#include "sys\types.h"
#include "sys\stat.h"
#include "io.h"

extern char* kpress;
extern char* epress;
int my_open_read(char *, int, int);
char *name;
char *type;
int map_defs[10];
int map_type;
extern char DataDir[];
/*----------------------------------------------------------------------*/
char mapnums[]={'0','1','2','3','4','5','6','7','8','9'};
char *mapname="map.x";
load_mapnum(mnum,init)
int mnum,init;
{
#if !defined(IBM_load_mapnum)
int i,j;

mapname[4]=mapnums[mnum];
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
load_map(mapname,init);
change=TRUE;
if(init)InitObject();
getwall();
#endif
}
/*----------------------------------------------------------------------*/
load_map(mapname,init)
char *mapname;
int init;
{
#if !defined(IBM_load_map)
int i, blength;
long junk;
int fd;

if ((fd=my_open_read(mapname, O_RDONLY|O_BINARY, FALSE)) < 0)
	EndGame(True);
read(fd, (char *)&junk, 4);

read(fd, (char *)map_defs, 20);
swab((char *)map_defs, (char *)map_defs, (int)20);

read(fd, (char *)&blength, 2);
swab((char *)&blength, (char *)&blength, (int)2);

if ( (buffer=(char far *)malloc(blength))==NULL )
    EndGame(True);

/*  fread( buffer, sizeof(char), blength, fd);  */
/* for (i=0; i<blength; i++)
    buffer[i]= getc(fd); */
read(fd, buffer, blength);

close(fd);

expand(init);
free(buffer);
if(init)DoPatch();
map_type=map_defs[0];
flip=map_defs[2];
change=1;
#endif
}
/*----------------------------------------------------------------------*/
int SaveGameData(pblk)
int pblk;
{
#if !defined(IBM_SaveGameData)
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
if(level<10)
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
#endif
}

/*----------------------------------------------------------------------*/
LoadGameData(pblk)
int pblk;
{
#if !defined(IBM_LoadGameData)
int i;
int err;

robotarray[Me.xindex][Me.yindex]=0;
/*-LEVEL DATA-------------------*/
if(err=my_read(pblk,&game,2L))return(err);
if(err=my_read(pblk,&level,2L))return(err);
for(i=1;i<8;i++)
	{
	if(err=my_read(pblk,&leveldata[i].visit,1L))return(err);
	if(leveldata[i].visit)
		{
		if(err = my_read(pblk,
			&leveldata[i],
			(long)sizeof(struct leveldata)))
				return(err);
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
#endif
}
/*----------------------------------------------------------------------*/
int Catenate(into,str1,str2)
unsigned char *into,*str1,*str2;
{
#if !defined(IBM_Catenate)
unsigned int length,i;

while(*into++=*str1++);
into--;
while(*into++=*str2++);
#endif
}

/************************** saveIBMgame(); *************************/

char *FileName;
int saved=0;
saveIBMgame()
{
Rect rr;
char *AskName[4];
char *outputMessage[4];
int save_file;
int testing=TRUE;
int wdth,twdth,i;
char msg[64];

AskName[0]= "   Type name of file to save.  ";
AskName[1]= " Press SPACE for last file name. ";
AskName[2]= epress;
AskName[3]= NULL;
wdth=0;
for(i=0;i<3;i++){if(wdth<(twdth=StringWidth(AskName[i])))wdth=twdth;}
rr.top= (sR.bottom+sR.top)/2 - 5*pix_per_Qinch_y;
rr.bottom= (sR.bottom+sR.top)/2 + 5*pix_per_Qinch_y;
rr.left=  (sR.right+sR.left)/2 - wdth/2 - 2*pix_per_Qinch_x;
rr.right= (sR.right+sR.left)/2 + wdth/2 + 2*pix_per_Qinch_x;
FileName= getInput(AskName, &rr);
if ( FileName[0]!=0x00 )
	{
	if ((save_file = open(FileName, O_RDONLY|O_BINARY)) >= 0)
		{
		close(save_file);
		strcpy(msg, FileName);
		strcat(msg, " already exists.");
		outputMessage[0] = msg;
		outputMessage[1] = "Press ENTER to save.";
		outputMessage[2] = "Press 'a' to abort.";
		outputMessage[3] = NULL;
		HideCursor();
		printMessage(outputMessage);

		while (1)
		    {
		    while (KeyEvent(FALSE, &key))
			;
		    while (!KeyEvent(FALSE, &key))
			;

		    if (key.ASCII == 0x0d || key.ASCII == 0x0a)
			{
			ShowCursor();
			break;
			}
		    else if (key.ASCII == 'a' || key.ASCII == 'A')
			{
			ShowCursor();
			return;
			}
		    }
		}

	if ( (save_file=open(FileName,
		O_CREAT|O_WRONLY|O_BINARY, S_IREAD|S_IWRITE))>=0)
		{
		if(SaveGameData(save_file))
			Inform("Unable to save file!",TRUE);
		if (close(save_file)<0)
			Inform("Unable to close file!",TRUE);
		saved=TRUE;
		}
	else {
		Inform(sys_errlist[errno],TRUE);
		}
	}
outputMessage[0]= "   Press 'q' to quit.    ";
outputMessage[1]= " Press 'n' for new game.";
outputMessage[2]= epress;
outputMessage[3]= NULL;
HideCursor();
printMessage(outputMessage);

while(testing)
	{
	while ( KeyEvent(FALSE, &key) );
	while ( !KeyEvent(FALSE, &key) );
	switch(key.ASCII)
		{
		case 'q':
		case 'Q':
			Inform("Quitting!",FALSE);
			notDone= False;
			testing=FALSE;
			break;
		case 'n':
		case 'N':
			Inform("New Game!",FALSE);
			gameInit();
			testing=FALSE;
			break;
		case 0x0D:
		case 0x0A:
			testing=FALSE;
			break;
		}
	}
ShowCursor();
}


/************************** loadIBMgame(); *************************/

loadIBMgame()
{
int i;
Rect rr;
char *AskName[4];
int loaded=FALSE;
int load_file;
char *FileName;
int wdth,twdth;

AskName[0]= "   Type name of file to load.  ";
AskName[1]= " Press SPACE for last file name. ";
AskName[2]= epress;
AskName[3]= NULL;
wdth=0;
for(i=0;i<3;i++){if(wdth<(twdth=StringWidth(AskName[i])))wdth=twdth;}
rr.top= (sR.bottom+sR.top)/2 - 5*pix_per_Qinch_y;
rr.bottom= (sR.bottom+sR.top)/2 + 5*pix_per_Qinch_y;
rr.left=  (sR.right+sR.left)/2 - wdth/2 - 2*pix_per_Qinch_x;
rr.right= (sR.right+sR.left)/2 + wdth/2 + 2*pix_per_Qinch_x;
HideCursor();
FileName= getInput(AskName, &rr);
if ( FileName[0]!=0x00 )
    {
	int err=0;
    if ( (load_file=open(FileName, O_RDONLY|O_BINARY))>=0)
		{
		if(!gametest){ShowCursor();DoGameSecurity();HideCursor();}
		if(!gametest){ShowCursor(); close(load_file); return(loaded);}
		for(i=1;i<255;i++)Object[i].alive=0;
		if ( err=(LoadGameData(load_file)!=0) )
			Inform(sys_errlist[errno],TRUE);
		if(err=err||(close(load_file)<0))
			Inform(sys_errlist[errno],TRUE);
		robotarray[Me.xindex][Me.yindex]=MENUM;
		if(game==COLONY)load_mapnum(level,FALSE);
		if(level<10)for(i=1;i<255;i++)
			if(Object[i].alive){SetObject(i,TRUE); robotnum=i+1; }
		}
	else {
		Inform(sys_errlist[errno],TRUE);
		err=TRUE;
		}
	if(!err)loaded=TRUE;
    }
ShowCursor();
return(loaded);
}

endIBMgame()
{
char *AskName[5];
int testing=TRUE;

AskName[0]= "   YOU HAVE BEEN TERMINATED!   ";
AskName[1]= " Type 'n' to start a new game. ";
AskName[2]= " Type 'l' to load a game.      ";
AskName[3]= " Type 'q' to quit the game.    ";
AskName[4]= NULL;
while(testing)
	{
	printMessage(AskName);
	while(KeyEvent(FALSE,&key));
	KeyEvent(TRUE, &key);
	switch(key.ASCII)
		{
		case 'n':
		case 'N':
			Inform("New Game!",FALSE);
			gameInit();
			testing=FALSE;
			break;
		case 'l':
		case 'L':
			if(loadIBMgame())
				testing=FALSE;
			break;
		case 'q':
		case 'Q':
			testing=FALSE;
			notDone=FALSE;
			break;
		}
	}
}
/*----------------------------------------------------------------------*/
int
my_open_read(name, flag, cont)
char *name;
int flag, cont;
{
int fd, m, notfound;
char *Message[6];
char name2[64], msg[64], drive[3];

strcpy(name2, DataDir);
strcat(name2, name);
strupr(name2);
if ((fd = open(name2, flag)) < 0 && errno == ENOENT)
	{
	if ((tolower(*name2) == 'a' || tolower(*name2) == 'b') &&
		*(name2+1) == ':')
		{
		drive[0] = toupper(*name2);
		drive[1] = '.';
		drive[2] = '\0';
		strcpy(msg, "Insert Disk 2 in drive ");
		strcat(msg, drive);
		Message[0] = msg;
		Message[1] = "---";
		Message[2] = kpress;
		Message[3] = NULL;
		HideCursor();
		printMessage(Message);

		while (KeyEvent(FALSE, &key))
			;
		while (!KeyEvent(FALSE, &key))
			;
		ShowCursor();
		fd = open(name2, flag);
		}
	}

while (fd < 0)
	{
	strcpy(msg, "Can't open ");
	strcat(msg, name2);

	Message[0] = msg;
	Message[1] = sys_errlist[errno];
	Message[2] = "---";
	m = 3;
	if (errno == ENOENT)
		{
		notfound = TRUE;
		Message[m++] = "Press ENTER to retry.";
		if (cont)
			Message[m++] = "Press 'q' to continue.";
		else
			Message[m++] = "Press 'q' to quit.";
		}
	else
		{
		notfound = FALSE;
		Message[m++] = "Press any key to continue.";
		}
	Message[m] = NULL;
	HideCursor();
	printMessage(Message);

	while (KeyEvent(FALSE, &key))
		;
	while (!KeyEvent(FALSE, &key))
		;
	ShowCursor();

	if (notfound)
		{
		if (key.ASCII == 0x0d || key.ASCII == 0x0a)
			{
			fd = open(name2, flag);
			continue;
			}
		else if (key.ASCII == 'q' || key.ASCII == 'Q')
			{
			if (cont)
				break;
			else
				EndGame(TRUE);
			}
		}
	else
		{
		if (cont)
			break;
		else
			EndGame(TRUE);
		}
	}

return(fd);
}
/*----------------------------------------------------------------------*/
my_write(int fd, unsigned char *buffer, long length)
{
if (write(fd, buffer, (int)length) != (int)length)
	{
	DoChimeSound();
	Inform(sys_errlist[errno],TRUE);
	return(1);
	}
return(0);
}
/*----------------------------------------------------------------------*/
my_read(int fd, unsigned char *buffer, long length)
{
if (read(fd, buffer, (int)length) != (int)length)
	{
	DoChimeSound();
	Inform(sys_errlist[errno],TRUE);
	return(1);
	}
return(0);
}
/*----------------------------------------------------------------------*/
my_read_loc(int fd, unsigned char *buffer, long length, long mark)
{
if (lseek(fd, mark, SEEK_SET) < 0 ||
	read(fd, buffer, (int)length) != (int)length)
	{
	DoChimeSound();
	Inform("Unable to load file!",TRUE);
	return(1);
	}
return(0);
}
