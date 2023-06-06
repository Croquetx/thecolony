/*  #define IBM_corridor  */
/*  #define IBM_drawend   */
/*			 */
/*  #define IBM_rot_init  */
/*  #define IBM_perspective  */
/*  #define IBM_perspective2  */
/*  #define IBM_quadrant  */
/*			 */
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
 * corridor.c
 *
 * Routines that do the calculation and drawing of the walls.
 *---------------------------------------------------------------------- 
 * corridor()
 *
 *	Main driver function for the graphics, corridor sets up the		 
 *	initial conditions that are specific to a diRection with the		 
 *	function quadrant, then does the search for and draws the Walls.	 
 *	This function is called diRectly from the file foobar.	
 *	The function project() is used to create the projection of the points.
 *	It is only called if there have been no changes in location by the
 *	user (change==1).
 * drawend(xstart,ystart,xFrontLeft,yFrontLeft)
 *		int xstart,ystart,xFrontLeft,yFrontLeft;
 *---------------------------------------------------------------------- 
 */
#define EXT extern
#include "gamedefs.h"

/*	n=quadrant number;
	first x Front Wall 	= Me.xindex+index[0][n];
	first y Front Wall 	= Me.yindex+index[1][n];
	first x Side Wall 	= Me.xindex+index[2][n];
	first y Side Wall  	= Me.yindex+index[3][n];
	x forward step distance	= index[4][n];
	y forward step distance	= index[5][n];
	x Side step distance	= index[6][n];
	y Side step distance	= index[7][n];
	Wall in Front 		= Wall[i][j]&index[8][n];
	Wall on Side 		= Wall[i][j]&index[9][n];*/

int index[4][10]={{0,0,	  0,0,	 0, 1,	 1, 0,	 1,2},
		  {1,0,	  0,0,	-1, 0,	 0, 1,	 2,1},
		  {0,1,	  1,0,	 0,-1,	-1, 0,	 1,2},
		  {0,0,	  0,1,	 1, 0,	 0,-1,	 2,1}};
/*quad is the number of the current primary diRection.*/
int FrntxWall=0;	/*first x front wall		*/
int FrntyWall=0;	/*first y front wall		*/
int SidexWall=0;	/*first x side wall			*/
int SideyWall=0;	/*first y side wall			*/
int Frntx    =0;	/*x forward step distance	*/
int Frnty    =1;	/*y forward step distance	*/
int Sidex    =1;	/*x side step distance		*/
int Sidey    =0;	/*y side step distance		*/
int Front    =1;	/*wall in front				*/
int Side     =2;	/*wall on side				*/
char *copyright="COPYRIGHT 1988 by DAVID A. SMITH";

/*---------------------------------------------------------------------- 
 *Me.look is the current angle I am looking in.								 
 *sint[],cost[] are the trig tables of angles in 2_/256 increments.		 
 *tsin,tcos are the current incremental values determined by			 
 *	tsin=sint[Me.look];														 
 *	tcos=cost[Me.look];														 
 *xai[],yai[] are the incremental distances I move in any particular	 
 *	direction ang														 
 *xloc,yloc are my current positions on the grid.						 
 *xindex,yindex are the current pointers into Wall[][]					 
 *should preserve the types of the DEFINED values                        
 *
 *---------------------------------------------------------------------- 
 */
#define FEATS 8
corridor()
{
#if !defined(IBM_corridor)
int length=1;			/*length of corridor counter 			*/
int xFrontLeft,yFrontLeft;	/*count wall left front of observor*/
int xFrontRight,yFrontRight;	/*count wall right front of observor*/
int xSide,ySide;		/*count side wall to left of observor	*/
int xfstart,yfstart;	/*first wall in front of observor		*/
int xsstart,ysstart;	/*first side wall to left of observor	*/
int xfbehind,yfbehind;	/*the wall behind the observor			*/
int roxsave,roysave;	/*save the original values of rox,roy	*/
int left,right;			/*save original left,right				*/
int cellxsave,cellysave;/*save the original values for l&r		*/
int there=0;
int right2,left2;
int k;
int dr[2];

/*if(gmap){	drawmap();	return;}/*draw a map instead of the location*/

quadrant();	/*initialize direction and first points.*/
right=Clip.right;
left=Clip.left;
right2=right;
left2=left;
xfstart = xFrontLeft = (xfbehind = Me.xindex + FrntxWall) + Frntx;
yfstart = yFrontLeft = (yfbehind = Me.yindex + FrntyWall) + Frnty;
xFrontRight=xFrontLeft+Sidex;
yFrontRight=yFrontLeft+Sidey; 
xsstart=Me.xindex+SidexWall;
ysstart=Me.yindex+SideyWall;
cellxsave=cellx=Me.xindex;
cellysave=celly=Me.yindex;

if(change)
	{
	perspective(dr,rox,roy);/*left starting point*/
	drY[xfbehind][yfbehind]=dr[1];
	if(dr[0]>screenR.left)  drX[xfbehind][yfbehind]=-32000;
	else 					drX[xfbehind][yfbehind]=dr[0];
	perspective(dr,rox+tsin,roy+tcos);	/*right starting point*/
	drY[xfbehind+Sidex][yfbehind+Sidey]=dr[1];
	if(dr[0]<screenR.right) drX[xfbehind+Sidex][yfbehind+Sidey]=32000;
	else 				 	drX[xfbehind+Sidex][yfbehind+Sidey]=dr[0];
	}
/*drX[xfbehind][yfbehind]= -(Width * 2);
drX[xfbehind+Sidex][yfbehind+Sidey] = Width * 3;
if(flip)
	drY[xfbehind][yfbehind]=drY[xfbehind+Sidex][yfbehind+Sidey]=400;
else
	drY[xfbehind][yfbehind]=drY[xfbehind+Sidex][yfbehind+Sidey]=-120;*/
/*save original rox,roy and set rox,roy to next wall in front*/
roxsave=rox;
roysave=roy;
rox-=tcos;
roy+=tsin;
if(change)
	{
	/*compute left starting points*/
	perspective(dr,rox,roy);
	drX[xFrontLeft][yFrontLeft]=dr[0];
	drY[xFrontLeft][yFrontLeft]=dr[1];
	/*compute right starting points*/
	perspective(dr,rox+tsin,roy+tcos);
	drX[xFrontRight][yFrontRight]=dr[0];
	drY[xFrontRight][yFrontRight]=dr[1];
	}
if(Wall[cellx + SidexWall][celly + SideyWall] & Side)
	left2=max(drX[xFrontLeft][yFrontLeft],Clip.left);
else left2=max(left,left2);
left2=max(left2,screenR.left);
if(Wall[cellx + SidexWall + Sidex][celly + SideyWall + Sidey]& Side)
	right2=drX[xFrontRight][yFrontRight];
else right2=min(right,right2);

MoveTo(drX[xFrontLeft][yFrontLeft],drY[xFrontLeft][yFrontLeft]);
LineTo(drX[xFrontRight][yFrontRight],
	drY[xFrontRight][yFrontRight]);	
if(Wall[cellx][celly] & ~0x03)
 	frontfeature(cellx,celly,xFrontLeft,yFrontLeft,left2,right2,rox,roy);
while(!(Wall[xFrontLeft][yFrontLeft]&Front))
	{
	rox-=tcos;
	roy+=tsin;
	xFrontLeft+=Frntx;
	yFrontLeft+=Frnty;
	xFrontRight+=Frntx;
	yFrontRight+=Frnty;
	if(change)
		{
		perspective(dr,rox,roy);
		drX[xFrontLeft][yFrontLeft]=dr[0];
		drY[xFrontLeft][yFrontLeft]=dr[1];
		perspective(dr,rox+tsin,roy+tcos);/*compute starting points*/
		drX[xFrontRight][yFrontRight]=dr[0];
		drY[xFrontRight][yFrontRight]=dr[1];
		}
	cellx+=Frntx;
	celly+=Frnty;
	if(robotarray[cellx][celly])
			SetRobot(left2,right2,robotarray[cellx][celly]);
	if(foodarray[cellx][celly])
			SetRobot(left2,right2,foodarray[cellx][celly]);
	if(Wall[cellx + SidexWall][celly + SideyWall] & Side)
		left2=max(Clip.left,drX[xFrontLeft][yFrontLeft]);
	else left2=max(left,left2);
	left2=max(left2,screenR.left);
	if(Wall[cellx+SidexWall+Sidex][celly+SideyWall+Sidey] & Side)
		right2=drX[xFrontRight][yFrontRight];
	else right2=min(right,right2);
	if(Wall[cellx][celly] & ~0x03)
		features(cellx,celly,xFrontLeft,yFrontLeft,left2,right2,rox,roy);
	/*draw the line from the left wall to the right wall		*/
	MoveTo(drX[xFrontLeft][yFrontLeft],drY[xFrontLeft][yFrontLeft]);
	LineTo(drX[xFrontRight][yFrontRight],
		drY[xFrontRight][yFrontRight]);	
	length++;
	}
/*Draws the two lines down the corridor and the end wall		*/
/*drawend(xfstart,yfstart,xFrontLeft,yFrontLeft);*/
drawend(xfbehind,yfbehind,xFrontLeft,yFrontLeft);
left=screenR.left;
right=min(right,drX[xFrontLeft][yFrontLeft]);
Clip.right=screenR.right;
if(left<right)
checkleft(xsstart,ysstart,xfbehind,yfbehind,left,right,roxsave,roysave,cellxsave,cellysave,length);

left=max(left,drX[xFrontRight][yFrontRight]);
if(left<screenR.left)left=screenR.left;
right=screenR.right;
xsstart+=Sidex;
ysstart+=Sidey;
xfbehind+=Sidex;
yfbehind+=Sidey;
if(left<right)
Clip.left=screenR.left;
checkright(xsstart,ysstart,xfbehind,yfbehind,left,right,roxsave+tsin,roysave+tcos,cellxsave,cellysave,length);
/*set Clip size to original size*/
Clip.left=screenR.left;
Clip.top=screenR.top;
Clip.right=screenR.right;
Clip.bottom=screenR.bottom;
change=0;
#endif
}
/*---------------------------------------------------------------------- 
 *drawend draws the end Wall in the array.				 
 *---------------------------------------------------------------------- 
 */
drawend(xstart,ystart,xFrontLeft,yFrontLeft)
int xstart,ystart,xFrontLeft,yFrontLeft;
{
#if !defined(IBM_drawend)
int xFrontRight,yFrontRight;

xFrontRight=xFrontLeft+Sidex;
yFrontRight=yFrontLeft+Sidey;

if((xstart!=xFrontLeft)||(ystart!=yFrontLeft))
	{
	if(drY[xstart+Frntx][ystart+Frnty]>0)
		{
		MoveTo(drX[xstart][ystart],drY[xstart][ystart]);
		LineTo(drX[xstart+Frntx][ystart+Frnty],
			drY[xstart+Frntx][ystart+Frnty]);
		}
	else
	MoveTo(drX[xstart+Frntx][ystart+Frnty],
		drY[xstart+Frntx][ystart+Frnty]);
	LineTo(drX[xFrontLeft][yFrontLeft],drY[xFrontLeft][yFrontLeft]);
	LineTo(drX[xFrontLeft][yFrontLeft],Height-drY[xFrontLeft][yFrontLeft]);
	LineTo(drX[xFrontRight][yFrontRight],
		Height-drY[xFrontRight][yFrontRight]);
	LineTo(drX[xFrontRight][yFrontRight],
		drY[xFrontRight][yFrontRight]);
	LineTo(drX[xstart+Frntx+Sidex][ystart+Frnty+Sidey],
		drY[xstart+Frntx+Sidex][ystart+Frnty+Sidey]);
	if(drY[xstart+Frntx+Sidex][ystart+Frnty+Sidey]>0)
		LineTo(drX[xstart+Sidex][ystart+Sidey],
			drY[xstart+Sidex][ystart+Sidey]);
	}
else	{
	MoveTo(drX[xFrontLeft][yFrontLeft],drY[xFrontLeft][yFrontLeft]);
	LineTo(drX[xFrontLeft][yFrontLeft],Height-drY[xFrontLeft][yFrontLeft]);
	LineTo(drX[xFrontRight][yFrontRight],
		Height-drY[xFrontRight][yFrontRight]);
	LineTo(drX[xFrontRight][yFrontRight],
		drY[xFrontRight][yFrontRight]);
	}
#endif
}


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

/*
#define EXT extern
#include "gamedefs.h"
*/


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
#if !defined(IBM_rot_init)
rox=((long)x * tsin - (long)y * tcos) >> 8;
roy=((long)y * tsin + (long)x * tcos) >> 8;		
#endif
}

/*----------------------------------------------------------------------
 * perpective calculates the x,z coordinates for a given point rox,roy		 
 *---------------------------------------------------------------------- 
 */
perspective(pnt,rox,roy)
int pnt[2];
register int rox,roy;
{
#if !defined(IBM_perspective)
long p;

if(roy <= 0)roy=1;		  /*insure we don't divide by zero*/
p = centerX + ((long)rox<<8) / roy;	/*compute x projection*/

if(p < (-32000)) p= -32000;	/*check for overflows*/
else if(p>32000) p=  32000;
pnt[0] = p;

if(flip)pnt[1] = centerY + rtable[roy];
else 	pnt[1] = centerY - rtable[roy];	 	/*compute z projection*/
#endif
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
#if !defined(IBM_perspective2)
long p;

if(roy <= 0)roy=1;		  /*insure we don't divide by zero*/
p = centerX + ((long)rox<<9) / roy;	/*compute x projection*/

if(p < (-32000)) p= -32000;	/*check for overflows*/
else if(p>32000) p=  32000;
pnt[0] = p;

if(flip)pnt[1] = centerY + (rtable[roy]<<1);
else 	pnt[1] = centerY - (rtable[roy]<<1);	 	/*compute z projection*/
#endif
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
#if !defined(IBM_quadrant)
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
#endif
}

