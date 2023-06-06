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
 * packit.c
 * Map maker system.
 * Used to compress and expand the map definitions that are edited.
 *--------------------------------------------------------------------
 * expand()
 *--------------------------------------------------------------------
 * Input:
 * 		char Wall[32][32];
 *		char mapdata[31][31][5][5];
 * Output:
 *		char cell data
 *			bit 0:wall
 *			bit 1:wall
 *			bit 2:north wall on/off
 *			bit 3:east wall on/off
 *			bit 4:west wall on/off
 *			bit 5:south wall on/off
 *			bit 6:central on/off
 *			bit 7:unused
 *		char north[5];
 *		char east[5];
 *		char west[5];
 *		char south[5];
 *		char central[5];
 *		... repeat...
 *--------------------------------------------------------------------
 */
#define EXT extern
#include "cgamedefs.h"

/*--------------------------------------------------------------------
 *--------------------------------------------------------------------
 */
#define N_BIT	0x04
#define E_BIT	0x08
#define W_BIT	0x10
#define S_BIT	0x20
expand(init)
int init;
{
int i,j,k,l,c=0;

robotnum=MENUM+1;
for(i=0;i<32;i++)
	for(j=0;j<32;j++)
		{
		Wall[i][j]=buffer[c];
		c++;
		if(i<31 && j<31)
			for(k=0;k<5;k++)
				{
				if(Wall[i][j] & (1<<(k+2)))
					{
					for(l=0;l<5;l++)
						(*map.data)[i][j][k][l]=buffer[c++];
					if(k==4 && (*map.data)[i][j][4][0]==6)
					if(robotarray[i][j]!=MENUM && init)
						{
						CreateObject(robotnum,(*map.data)[i][j][4][1]+BASEOBJECT,
							(i<<8)+128,(j<<8)+128,
							(*map.data)[i][j][4][2]+32);
						robotnum++;
						}
					}
				else (*map.data)[i][j][k][0]=0;
				}
		}
for(i=0;i<31;i++)
	for(j=0;j<31;j++)
		{
		if((Wall[i][j]&0x02)	&&	!(Wall[i][j]&W_BIT))
			{Wall[i][j]|=W_BIT;(*map.data)[i][j][WEST][0]=-1;}
			
		if((Wall[i+1][j]&0x02)	&&	!(Wall[i][j]&E_BIT))
			{Wall[i][j]|=E_BIT;(*map.data)[i][j][EAST][0]=-1;}
			
		if((Wall[i][j]&0x01)	&&	!(Wall[i][j]&S_BIT))
			{Wall[i][j]|=S_BIT;(*map.data)[i][j][SOUTH][0]=-1;}
			
		if((Wall[i][j+1]&0x01)	&&	!(Wall[i][j] & N_BIT))
			{Wall[i][j]|=N_BIT;(*map.data)[i][j][NORTH][0]=-1;}
		}
}