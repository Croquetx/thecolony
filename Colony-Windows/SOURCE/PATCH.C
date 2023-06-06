/*  #define IBM_savewall       */
/*  #define IBM_getwall        */
/*  #define IBM_newpatch       */
/*  #define IBM_patchmapto     */
/*  #define IBM_patchmapfrom   */
/*  #define IBM_DoPatch        */
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
 * Patch.c
 *---------------------------------------------------------------------- 
 * savewall(xindex,yindex,direction)
 *		int xindex,yindex,direction;
 * getwall()
 * newpatch(type,from,to,mapdata)
 *		int type;
 *		struct passpatch *from,*to;
 *		char mapdata[5];
 * patchmapto(to,mapdata)
 *		struct passpatch *to;
 *		char mapdata[5];
 * patchmapfrom(from,mapdata)
 *		struct passpatch *from;
 *		char mapdata[5];
 * DoPatch()
 *---------------------------------------------------------------------- 
 */
#define EXT extern
#include "gamedefs.h"
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
savewall(xindex,yindex,direction)
int xindex,yindex,direction;
{
#if !defined(IBM_savewall)
int i,j;

for(i=0;i<leveldata[level].size;i++)
	if(	leveldata[level].location[i][0]==xindex && 
		leveldata[level].location[i][1]==yindex &&
		leveldata[level].location[i][2]==direction)
		{
		for(j=0;j<5;j++)leveldata[level].data[i][j]=
			(*map.data)[xindex][yindex][direction][j+1];
		return;
		}
if(leveldata[level].size==9)Inform("\pError in savewall");
else 
	{
	for(j=0;j<5;j++)leveldata[level].data[leveldata[level].size][j]=
			(*map.data)[xindex][yindex][direction][j+1];
	leveldata[level].location[i][0] = xindex;
	leveldata[level].location[i][1] = yindex;
	leveldata[level].location[i][2] = direction;
	}
leveldata[level].size++;
#endif
}
/*----------------------------------------------------------------------*/
getwall()
{
#if !defined(IBM_getwall)
int i,j;
int xindex,yindex,direction;

for(i=0;i<leveldata[level].size;i++)
	{
	xindex = leveldata[level].location[i][0];
	yindex = leveldata[level].location[i][1];
	direction = leveldata[level].location[i][2];
	for(j=0;j<5;j++)
			(*map.data)[xindex][yindex][direction][j+1]=leveldata[level].data[i][j];
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
newpatch(type,from,to,mapdata)
int type;
struct passpatch *from,*to;
char mapdata[5];
{
#if !defined(IBM_newpatch)
int i;
int done=FALSE;

for(i=0;i<patchnum && !done;i++)
	{
	if(from->level   == patch[i].to.level &&
		from->xindex == patch[i].to.xindex &&
		from->yindex == patch[i].to.yindex)
		{
		patch[i].to.level=to->level;
		patch[i].to.xindex=to->xindex;
		patch[i].to.yindex=to->yindex;
		patch[i].to.xloc=to->xloc;
		patch[i].to.yloc=to->yloc;
		patch[i].to.ang=to->ang;
		done=TRUE;
		}
	}
if((!done)&&patchnum<100)/*create new patch in table*/
	{
	patch[patchnum].type=type;
	patch[patchnum].from.level=from->level;
	patch[patchnum].from.xindex=from->xindex;
	patch[patchnum].from.yindex=from->yindex;

	patch[patchnum].to.level=to->level;
	patch[patchnum].to.xindex=to->xindex;
	patch[patchnum].to.yindex=to->yindex;
	patch[patchnum].to.xloc=to->xloc;
	patch[patchnum].to.yloc=to->yloc;
	patch[patchnum].to.ang=to->ang;
	if(mapdata)for(i=0;i<5;i++)patch[patchnum].mapdata[i]=mapdata[i];
	patchnum++;
	}
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
patchmapto(to,mapdata)
struct passpatch *to;
char mapdata[5];
{
#if !defined(IBM_patchmapto)
int i,j;
int done=FALSE;

for(i=0;i<patchnum && !done;i++)
	{
	if(to->level   == patch[i].to.level &&
		to->xindex == patch[i].to.xindex &&
		to->yindex == patch[i].to.yindex)
		{
		for(j=0;j<5;j++)mapdata[j]=patch[i].mapdata[j];
		done=TRUE;
		}
	}
return(done);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
patchmapfrom(from,mapdata)
struct passpatch *from;
char mapdata[5];
{
#if !defined(IBM_patchmapfrom)
int i,j;
int done=FALSE;

for(i=0;i<patchnum && !done;i++)
	{
	if(from->level   == patch[i].from.level &&
		from->xindex == patch[i].from.xindex &&
		from->yindex == patch[i].from.yindex)
		{
		mapdata[2]=patch[i].to.level;
		mapdata[3]=patch[i].to.xindex;
		mapdata[4]=patch[i].to.yindex;
		done=TRUE;
		}
	}
return(done);
#endif
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
DoPatch()
{
#if !defined(IBM_DoPatch)
int i,j,robot;
int done;

for(i=0;i<patchnum;i++)/*remove objects*/
	if(level==patch[i].from.level)
		{
		robot=robotarray[patch[i].from.xindex][patch[i].from.yindex];
		robotarray[Object[robot].where.xindex][Object[robot].where.yindex]=0;
		Object[robot].alive=0;
		}
		
for(i=0;i<patchnum;i++)/*install moved objects*/
	{
	done=FALSE;
	if(level==patch[i].to.level)/*is this object on this level*/
		{
		for(j=MENUM+1;j<robotnum && !done;j++)
			{
			if(!Object[j].alive)	
				{
				CreateObject(j,
					(int)patch[i].type,
					(int)patch[i].to.xloc,
					(int)patch[i].to.yloc,
					(int)patch[i].to.ang);
				done=TRUE;
				}
			}
		if(!done)
			{
			CreateObject(robotnum,
				(int)patch[i].type,
				(int)patch[i].to.xloc,
				(int)patch[i].to.yloc,
				(int)patch[i].to.ang);
 			robotnum++;
 			}
		}
	}
#endif
}
