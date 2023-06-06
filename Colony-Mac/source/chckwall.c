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
 * checkwall.c
 *---------------------------------------------------------------------- 
 * int checkwall(xnew,ynew,pobject)
 *		int xnew,ynew;
 *		Locate *pobject;
 * checks whether we are running into a wall or not.
 * returns:
 *	 0 == everything is OK
 *	-1 == there is a wall here
 * 1000== you can't go through (you didn't open the door)
 *	 robotarray[xind][yind] == there is an object here		
 * the variable ctype:
 * 		0 = robot
 *		2 = scanning path of robot
 *		MENUM = Me				 
 *---------------------------------------------------------------------- 
 */
#define EXT extern
#include "cgamedefs.h"
int ctype;

int checkwall(xnew,ynew,pobject)
int xnew,ynew;
Locate *pobject;
{
int num,rnum;
int xind2,yind2;

ctype=pobject->type;
change=1;
xind2=xnew>>8;
yind2=ynew>>8;
if(xind2 == pobject->xindex)
	{
	if(yind2 == pobject->yindex)/*same cell ... everything is ok*/
		{
		pobject->dx=xnew-pobject->xloc;
		pobject->dy=ynew-pobject->yloc;
		pobject->xloc = xnew;
		pobject->yloc = ynew;
		return(0);
		}
	else/*change in cells in the Y direction only*/	
		{
		if(yind2 > pobject->yindex)/*positive change in Y dir*/
			{
			if(!(Wall[pobject->xindex][yind2]&1))
				{
				if(rnum=robotarray[xind2][yind2])
					{
					if(ctype==MENUM&&Object[rnum].type<=BASEOBJECT)
						Object[rnum].where.look = Object[rnum].where.ang=Me.ang+128;
					return(rnum);
					}
				if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=1;
				pobject->yindex = yind2;
				pobject->xindex = xind2;
				pobject->dx=xnew-pobject->xloc;
				pobject->dy=ynew-pobject->yloc;
				pobject->xloc = xnew;
				pobject->yloc = ynew;
				return(0);
				}
			else	/*there is a wall here*/
				{
				if(ctype==2)return(-1);
				if(num=(*map.data)[pobject->xindex][pobject->yindex][NORTH][0])
					{
					switch(GoToMap((*map.data)[pobject->xindex][pobject->yindex][NORTH],NORTH))
						{
						case 0:/*real wall*/
							return(-1);
							break;
						case 1:
							if(robotarray[xind2][yind2])
								{
								if(ctype==MENUM)DoText(&rScreen,75,0);
								return((int)robotarray[xind2][yind2]);
								}
							if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=1;
							pobject->yindex = yind2;
							pobject->xindex = xind2;
							pobject->dx=xnew-pobject->xloc;
							pobject->dy=ynew-pobject->yloc;
							pobject->xloc=xnew;
							pobject->yloc=ynew;
							return(0);
							break;
						case 2:/*you can go through*/
							return(0);
							break;
						}
					}
				return(-1);
				/*mac_say("oops, I ran into a wall!");*/
				}
			}
		else 	{/*negative change in the Y direction*/
			if(!(Wall[pobject->xindex][pobject->yindex]&1))
				{
				if(rnum=robotarray[xind2][yind2])
					{
					if(ctype==MENUM&&Object[rnum].type<=BASEOBJECT)
						Object[rnum].where.look = Object[rnum].where.ang=Me.ang+128;
					return(rnum);
					}
				if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=5;
				pobject->yindex = yind2;
				pobject->xindex = xind2;
				pobject->dx=xnew-pobject->xloc;
				pobject->dy=ynew-pobject->yloc;
				pobject->xloc=xnew;
				pobject->yloc=ynew;
				return(0);
				}
			else	
				{
				if(ctype==2)return(-1);
				if(num=(*map.data)[pobject->xindex][pobject->yindex][SOUTH][0])
					{
					switch(GoToMap((*map.data)[pobject->xindex][pobject->yindex][SOUTH],SOUTH))
						{
						case 0:
							return(-1);
							break;
						case 1:
							if(robotarray[xind2][yind2])
								{
								if(ctype==MENUM)DoText(&rScreen,75,0);
								return((int)robotarray[xind2][yind2]);
								}
							if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=5;
							pobject->yindex = yind2;
							pobject->xindex = xind2;
							pobject->dx=xnew-pobject->xloc;
							pobject->dy=ynew-pobject->yloc;
							pobject->xloc=xnew;
							pobject->yloc=ynew;
							return(0);
							break;
						case 2:
							return(0);
							break;
						}
					}
				return(-1);
				}
			}
		}
	}
else/*oops... definite change in at least the X dir*/
	{
	if(yind2 == pobject->yindex)/* change in X direction only*/
		{
		if(xind2>pobject->xindex)
			{
			if(!(Wall[xind2][pobject->yindex]&2))
				{
				if(rnum=robotarray[xind2][yind2])
					{
					if(ctype==MENUM&&Object[rnum].type<=BASEOBJECT)
						Object[rnum].where.look = Object[rnum].where.ang=Me.ang+128;
					return(rnum);
					}
				if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=3;
				pobject->yindex = yind2;
				pobject->xindex = xind2;
				pobject->dx=xnew-pobject->xloc;
				pobject->dy=ynew-pobject->yloc;
				pobject->xloc=xnew;
				pobject->yloc=ynew;
				return(0);
				}
			else	
				{
				if(ctype==2)return(-1);
				if(num=(*map.data)[pobject->xindex][pobject->yindex][EAST][0])
					{
					switch(GoToMap((*map.data)[pobject->xindex][pobject->yindex][EAST],EAST))
						{
						case 0:
							return(-1);
							break;
						case 1:
							if(robotarray[xind2][yind2])
								{
								if(ctype==MENUM)DoText(&rScreen,75,0);
								return((int)robotarray[xind2][yind2]);
								}
							if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=3;
							pobject->yindex = yind2;
							pobject->xindex = xind2;
							pobject->dx=xnew-pobject->xloc;
							pobject->dy=ynew-pobject->yloc;
							pobject->xloc=xnew;
							pobject->yloc=ynew;
							return(0);
							break;
						case 2:
							return(0);
							break;
						}
					}
				return(-1);
				}
			}
		else 	{
			if(!(Wall[pobject->xindex][pobject->yindex]&2))
				{
				if(rnum=robotarray[xind2][yind2])
					{
					if(ctype==MENUM&&Object[rnum].type<=BASEOBJECT)
						Object[rnum].where.look = Object[rnum].where.ang=Me.ang+128;
					return(rnum);
					}
				if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=7;
				pobject->yindex = yind2;
				pobject->xindex = xind2;
				pobject->dx=xnew-pobject->xloc;
				pobject->dy=ynew-pobject->yloc;
				pobject->xloc=xnew;
				pobject->yloc=ynew;
				return(0);
				}
			else{
				if(ctype==2)return(-1);
				if(num=(*map.data)[pobject->xindex][pobject->yindex][WEST][0])
					{
					switch(GoToMap((*map.data)[pobject->xindex][pobject->yindex][WEST],WEST))
						{
						case 0:
							return(-1);
							break;
						case 1:
							if(robotarray[xind2][yind2])
								{
								if(ctype==MENUM)DoText(&rScreen,75,0);
								return((int)robotarray[xind2][yind2]);
								}
							if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=7;
							pobject->yindex = yind2;
							pobject->xindex = xind2;
							pobject->dx=xnew-pobject->xloc;
							pobject->dy=ynew-pobject->yloc;
							pobject->xloc=xnew;
							pobject->yloc=ynew;
							return(0);
							break;
						case 2:
							return(0);
							break;
						}
					}
					return(-1);
					}
			}
		}
	else/*oh,oh... change in both directions at once*/	
		{
		/*there are four cases with each case having	 
		 *to check for four walls, we are trying to  	 
		 *walk thru a corner here... bad shit. If this	 
		 *is done incorrectly there is a chance that 	 
		 *someone might get himself into a column and  
		 *NEVER GET OUT AGAIN! It may be argued that 	 
		 *this is where one belongs. I do not check for
		 *wall features here.					
		 */
		if(xind2 > pobject->xindex)
			{
			if(yind2 > pobject->yindex)/*FIRST case*/
				{
				if((Wall[pobject->xindex][yind2]&1) || 
					(Wall[xind2][pobject->yindex]&2)||
					(Wall[xind2][yind2]&3))
					{
					return(-1);
					}
				else{
					if(rnum=robotarray[xind2][yind2])
						{
						if(ctype==MENUM&&Object[rnum].type<=BASEOBJECT)
							Object[rnum].where.look = Object[rnum].where.ang=Me.ang+128;
						return(rnum);
						}
					if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=2;
					pobject->xindex=xind2;
					pobject->yindex=yind2;
					pobject->dx=xnew-pobject->xloc;
					pobject->dy=ynew-pobject->yloc;
					pobject->xloc=xnew;
					pobject->yloc=ynew;
					return(0);
					}
				}
			else /*SECOND case*/
					{
					if((Wall[pobject->xindex][pobject->yindex]&1) ||
						(Wall[xind2][yind2]&2) ||
						(Wall[xind2][pobject->yindex]&3))
						{
						return(-1);
						}
				else{
					if(rnum=robotarray[xind2][yind2])
						{
						if(ctype==MENUM&&Object[rnum].type<=BASEOBJECT)
							Object[rnum].where.look = Object[rnum].where.ang=Me.ang+128;
						return((int)robotarray[xind2][yind2]);
						}
					if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=4;
					pobject->xindex=xind2;
					pobject->yindex=yind2;
					pobject->dx=xnew-pobject->xloc;
					pobject->dy=ynew-pobject->yloc;
					pobject->xloc=xnew;
					pobject->yloc=ynew;
					return(0);
					}
				}
			}
		else	
			{
			if(yind2 > pobject->yindex)/*THIRD case*/
				{
				if((Wall[xind2][yind2]&1) ||
					(Wall[pobject->xindex][pobject->yindex]&2) ||
					(Wall[pobject->xindex][yind2]&3))
					{
					return(-1);
					}
				else{
					if(rnum=robotarray[xind2][yind2])
						{
						if(ctype==MENUM&&Object[rnum].type<=BASEOBJECT)
							Object[rnum].where.look = Object[rnum].where.ang=Me.ang+128;
						return(rnum);
						}
					if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=8;
					pobject->xindex=xind2;
					pobject->yindex=yind2;
					pobject->dx=xnew-pobject->xloc;
					pobject->dy=ynew-pobject->yloc;
					pobject->xloc=xnew;
					pobject->yloc=ynew;
					return(0);
					}
				}
			else/*FOURTH case*/
				{
				if((Wall[xind2][pobject->yindex]&1) ||
					(Wall[pobject->xindex][yind2]&2) ||
					(Wall[pobject->xindex][pobject->yindex]&3))
					{
					return(-1);
					}
				else{
					if(rnum=robotarray[xind2][yind2])
						{
						if(ctype==MENUM&&Object[rnum].type<=BASEOBJECT)
							Object[rnum].where.look = Object[rnum].where.ang=Me.ang+128;
						return(rnum);
					 	}
					if(ctype==MENUM)dirXY[pobject->xindex][pobject->yindex]=6;
					pobject->xindex=xind2;
					pobject->yindex=yind2;
					pobject->dx=xnew-pobject->xloc;
					pobject->dy=ynew-pobject->yloc;
					pobject->xloc=xnew;
					pobject->yloc=ynew;
					return(0);
					}
				}
			}
		}
	}
}
