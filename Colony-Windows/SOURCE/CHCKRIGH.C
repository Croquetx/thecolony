/*  #define IBM_checkright  */
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
 * checkright.c
 *---------------------------------------------------------------------- 
 * checkright(xs,ys,xf,yf,left,right,rx,ry,cellx,celly,len)
 *		int xs,ys;		Side start	
 *		int xf,yf;		Front start	
 *		int rx,ry;		rotate	
 *		int left,right;	min and max values for x-Clipping	
 *		int cellx,celly;
 *		int len;
 *	determines the start and end points of the Side missing		 
 *	Walls and then draws them. 					 
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

extern int index[4][10];
/*quad is the number of the current primary diRection.*/
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
 *checkright(xs,ys,xf,yf,left,right,rx,ry,cellx,celly,len)				 
 *	determines the start and end points of the Side missing		 
 *	Walls and then draws them. 					 
 *---------------------------------------------------------------------- 
 */
checkright(xs,ys,xf,yf,left,right,rx,ry,cellx,celly,len)
int xs,ys;/*Side start	*/
int xf,yf;/*Front start	*/
int rx,ry;/*rotate	*/
int left,right;/*min and max values for x-Clipping*/
int cellx,celly;
int len;
{
#if !defined(IBM_checkright)
int i=0,j,k;
int xf2,yf2;
int rox,roy;
int xsstart,ysstart;
int xfstart,yfstart;
int xestart,yestart;
int cellxsave,cellysave;
Rect r;
int saveClip;
int dr[2];

cellx+=Sidex;
celly+=Sidey;
/*Clip.left=left;*/
Clip.right=right;
r.top=Clip.top;
r.bottom=Clip.bottom;
ClipRect(&Clip);
/*move the rotates one cell right*/
rx=rx+tsin;
ry=ry+tcos;
/*go until we hit the front wall to the right or run off the screen */
while(i<len&&left<right)
	{
	if(Wall[xs][ys]&Side)
		{
		if(flip)
			{
			MoveTo(drX[xf][yf],0);
			LineTo(drX[xf][yf],Height-drY[xf][yf]);
			}
		/*draw the side walls*/
		while((Wall[xs][ys]&Side)&&i<len&&left<right)
			{
			/* Draw a side wall
			 * 1) line up and down
			 * 2) line forward on floor (or ceiling)
			 */
			MoveTo(drX[xf][yf],drY[xf][yf]);
			LineTo(drX[xf][yf],Height-drY[xf][yf]);
			LineTo(drX[xf+Frntx][yf+Frnty],
					Height-drY[xf+Frntx][yf+Frnty]);

			right=min(drX[xf][yf],right);
			xf+=Frntx;
			yf+=Frnty;
			xs+=Frntx;
			ys+=Frnty;
			cellx+=Frntx;
			celly+=Frnty;
			rx-=tcos;
			ry+=tsin;
			i++;
			}
		/*Draw the end of this string of walls*/
		if(flip)
			{
			MoveTo(drX[xf][yf],0);
			LineTo(drX[xf][yf],Height-drY[xf][yf]);
			}
		MoveTo(drX[xf][yf],Height-drY[xf][yf]);
		LineTo(drX[xf][yf],drY[xf][yf]);
		Clip.right=(right=min(drX[xf][yf],right));
		ClipRect(&Clip);
		}
	/*We now hit an open area where there are no walls to our left.
	 *We must compute the corridor positions and prepare for a
	 *recursive call to checkleft.
	 */
	if(i<len&&left<right)
		{
		j=0;
		xf2=xf+Sidex;
		yf2=yf+Sidey;
		xfstart=xf2;
		yfstart=yf2;
		xsstart=xs+Sidex;
		ysstart=ys+Sidey;
		cellxsave=cellx;
		cellysave=celly;
	
		rox=rx;
		roy=ry;
		if(change)
			{
			perspective(dr,rx,ry);
			drX[xf2][yf2]=dr[0];
			drY[xf2][yf2]=dr[1];
			}
		while((!(Wall[xs][ys]&Side))&&i<len)
			{
			rx-=tcos;
			ry+=tsin;
			if(change)
				{
				perspective(dr,rx,ry);
				drX[xf2+Frntx][yf2+Frnty]=dr[0];
				drY[xf2+Frntx][yf2+Frnty]=dr[1];
				}
			if(drX[xf+Frntx][yf+Frnty]<right)
				{
				MoveTo(drX[xf2][yf2],drY[xf2][yf2]);
				LineTo(drX[xf2+Frntx][yf2+Frnty],
					drY[xf2+Frntx][yf2+Frnty]);
				LineTo(drX[xf+Frntx][yf+Frnty],
					drY[xf+Frntx][yf+Frnty]);
				if(Wall[cellx][celly] & ~0x03)
					features(cellx,celly,
					xf+Frntx,yf+Frnty,
					Clip.left,right,rx-tsin,ry-tcos);
				if(robotarray[cellx][celly])
						SetRobot(Clip.left,right,robotarray[cellx][celly]);
				if(foodarray[cellx][celly])
						SetRobot(Clip.left,right,foodarray[cellx][celly]);
				}
			else
				{
				j=0;
				xfstart=xf2;
				yfstart=yf2;
				xsstart=xs+Sidex;
				ysstart=ys+Sidey;
				rox=rx+tcos;
				roy=ry-tsin;
				cellxsave=cellx;
				cellysave=celly;
				}
			xf2+=Frntx;
			yf2+=Frnty;
			xf+=Frntx;
			yf+=Frnty;
			xs+=Frntx;
			ys+=Frnty;
			cellx+=Frntx;
			celly+=Frnty;
			i++;
			j++;
			}
		/*We arrive at a wall in front of the left corridor.
		 *We must draw it and then continue if possible.
		 */
		if(Wall[xf][yf]&Front) 
			{
			MoveTo(drX[xf2][yf2],drY[xf2][yf2]);
			LineTo(drX[xf2][yf2],Height-drY[xf2][yf2]);
			LineTo(drX[xf][yf],Height-drY[xf][yf]);

			saveClip=Clip.left;
			if((max(drX[xf2][yf2],left))<right)
			checkright(xsstart,
				ysstart,
				xfstart,
				yfstart,
				max(left,drX[xf2][yf2]),
				right,
				rox,roy,cellxsave,cellysave,j);
			/*Clip.left=left;*/
			Clip.left=saveClip;
			Clip.right=right;
			ClipRect(&Clip);
			}
		else
			{
			Clip.left=left;
			Clip.right=right;
			ClipRect(&Clip);
			if(flip)
				{
				MoveTo(drX[xf][yf],0);
				LineTo(drX[xf][yf],Height-drY[xf][yf]);
				}
			xestart=xf2;
			yestart=yf2;
			while(!(Wall[xf][yf]&Front))
				{
				rx-=tcos;
				ry+=tsin;
				cellx+=Frntx;
				celly+=Frnty;
				xf2+=Frntx;
				yf2+=Frnty;
				xf+=Frntx;
				yf+=Frnty;
				xs+=Frntx;
				ys+=Frnty;
				if(change)
					{
					perspective(dr,rx,ry);
					drX[xf2][yf2]=dr[0];
					drY[xf2][yf2]=dr[1];
					}
				if(change)
					{
					perspective(dr,rx-tsin,ry-tcos);
					drX[xf][yf]=dr[0];
					drY[xf][yf]=dr[1];
					}
				MoveTo(drX[xf2][yf2],drY[xf2][yf2]);
				LineTo(drX[xf][yf],drY[xf][yf]);
				if(Wall[cellx-Frntx][celly-Frnty] & ~0x03)
					features(cellx-Frntx,
					celly-Frnty,
					xf,yf,
					Clip.left,right,rx-tsin,ry-tcos);
				if(robotarray[cellx-Frntx][celly-Frnty])
						SetRobot(Clip.left,right,
						robotarray[cellx-Frntx][celly-Frnty]);
				if(foodarray[cellx-Frntx][celly-Frnty])
						SetRobot(Clip.left,right,
						foodarray[cellx-Frntx][celly-Frnty]);
				i++;
				j++;
				}
			/*draw right end*/
			MoveTo(drX[xestart][yestart],drY[xestart][yestart]);
			LineTo(drX[xf2][yf2],drY[xf2][yf2]);
			LineTo(drX[xf2][yf2],Height-drY[xf2][yf2]);
			LineTo(drX[xf2-Sidex][yf2-Sidey],
				Height-drY[xf2-Sidex][yf2-Sidey]);
				
			if((max(drX[xf2][yf2],left))<right)
				checkright(xsstart,
					ysstart,
					xfstart,
					yfstart,
					max(drX[xf2][yf2],left),right,
					rox,roy,cellxsave,cellysave,j);
			Clip.left=left;
			Clip.right=right;
			ClipRect(&Clip);
			}
		}
	}	
#endif
}
