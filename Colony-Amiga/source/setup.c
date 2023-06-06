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
 * setup.c
 *---------------------------------------------------------------------- 
 * rot_init(x,y)
 *		int x,y;
 *	calculates the two initial points to the left of	 
 *	the viewer. The remainder of the points are simply calculated	 
 *	by addition using tsin and tcos.		 
 * project(pnt,rox,roy)
 *		int pnt[2];
 *		register int rox,roy;
 * project2(pnt,rox,roy)
 *		int pnt[2];
 *		register int rox,roy;
 * quadrant()															
 *		determines the primary direction and sets up the initial			
 *		rotation variables to be used in the calculations. It returns 		
 *		the global value quad to be used in indexing the array 'index'.		
 *---------------------------------------------------------------------- 
 */		
#define EXT extern
#include "cgamedefs.h"

extern int index[4][10];
/*quad is the number of the current primary direction.*/
extern int FrntxWall;	/*first x front wall		*/
extern int FrntyWall;	/*first y front wall		*/
extern int SidexWall;	/*first x side wall			*/
extern int SideyWall;	/*first y side wall			*/
extern int Frntx    ;	/*x forward step distance	*/
extern int Frnty    ;	/*y forward step distance	*/
extern int Sidex    ;	/*x side step distance		*/
extern int Sidey    ;	/*y side step distance		*/
extern int Front    ;	/*wall in front				*/
extern int Side     ;	/*wall on side				*/
/*---------------------------------------------------------------------- 
 *	rot_init(x,y)
 *	int x,y;
 *
 *	calculates the two initial points to the left of	 
 *	the viewer. The remainder of the points are simply calculated	 
 *	by addition using tsin and tcos.		 
 *---------------------------------------------------------------------- 
 */		
rot_init(x,y)		
int x,y;
{
rox=((long)x * tsin - (long)y * tcos) >> 8;
roy=((long)y * tsin + (long)x * tcos) >> 8;		
}

/*---------------------------------------------------------------------- 
 *copyright signature --- forward and backward
 *----------------------------------------------------------------------
 */
sign()
{
asm	{
	nop
	DC.B 	'c','7','o','8','p','9','y','1','r',' ','i','h','g','t','h','i'
	DC.B	't','m',' ','s','1',' ','9','a','8',' ','7','d',' ','i','b','v'
	DC.B	'y','a',' ','d','d',' ','a','y','v','b','i',' ','d','t',' ','h'
	DC.B	'a','g',' ','i','s','r','m','y','i','p','t','o','h','c'
	}
}
/*---------------------------------------------------------------------- 
 * perpective calculates the x,z coordinates for a given point rox,roy		 
 *---------------------------------------------------------------------- 
 */
perspective(pnt,rox,roy)
int pnt[2];
register int rox,roy;
{
long p;

if(roy <= 0)roy=1;		  /*insure we don't divide by zero*/
p = centerX + ((long)rox<<8) / roy;	/*compute x projection*/

if(p < (-32000)) p= -32000;	/*check for overflows*/
else if(p>32000) p=  32000;
pnt[0] = p;

if(flip)pnt[1] = centerY + rtable[roy];
else 	pnt[1] = centerY - rtable[roy];	 	/*compute z projection*/
}
/*----------------------------------------------------------------------
 *perspective2 calculates the x,z coordinates for a given point rox,roy
 *the result is double that of perspective.
 *---------------------------------------------------------------------- 
 */
perspective2(pnt,rox,roy)
int pnt[2];
register int rox,roy;
{
long p;

if(roy <= 0)roy=1;		  /*insure we don't divide by zero*/
p = centerX + ((long)rox<<9) / roy;	/*compute x projection*/

if(p < (-32000)) p= -32000;	/*check for overflows*/
else if(p>32000) p=  32000;
pnt[0] = p;

if(flip)pnt[1] = centerY + (rtable[roy]<<1);
else 	pnt[1] = centerY - (rtable[roy]<<1);	 	/*compute z projection*/
}

/*----------------------------------------------------------------------
 *quadrant()															
 *	determines the primary diRection and sets up the initial			
 *	rotation variables to be used in the calculations. It returns 		
 *	the global value quad to be used in indexing the array 'index'.		
 *----------------------------------------------------------------------
 */
quadrant()
{
int remain;
int x,y;
int quad;

quad=Me.look>>6;				/*divide by 64		*/
remain=Me.look-(quad<<6);			/*multiply by 64	*/
tsin=sint[remain];
tcos=cost[remain];
/*	NOTE: n<<8 is equivalent to n*256			*/
switch(quad)
	{
	case 0:
		rot_init((Me.xindex<<8)-Me.xloc,(Me.yindex<<8)-Me.yloc);
		direction=NORTH;
		break;
	case 1:
		rot_init((Me.yindex<<8)-Me.yloc,Me.xloc-((Me.xindex+1)<<8));
		direction=WEST;
		break;
	case 2:
		rot_init(Me.xloc-((Me.xindex+1)<<8),Me.yloc-((Me.yindex+1)<<8));
		direction=SOUTH;
		break;
	case 3:
		rot_init(Me.yloc-((Me.yindex+1)<<8),(Me.xindex<<8)-Me.xloc);
		direction=EAST;	
		break;	
	}
/*	I do these assignments to avoid the actual calculations involved with
 *	a structure like index[quad][x] which includes both a multiplication and
 *	an addition.
 */
FrntxWall=index[quad][0];
FrntyWall=index[quad][1];
SidexWall=index[quad][2];
SideyWall=index[quad][3];
Frntx 	 =index[quad][4];
Frnty 	 =index[quad][5];
Sidex	 =index[quad][6];
Sidey	 =index[quad][7];
Front	 =index[quad][8];
Side	 =index[quad][9];
}

