/*  #define IBM_MakeQueen  */
/*  #define IBM_seteyes    /*	*/
/*  #define IBM_draweyes   /*	*/
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
#define EXT extern 
#include "gamedefs.h"
/*---------------------------------------------------------------------
 * MakeQueen()
 *---------------------------------------------------------------------
 */
int faraway;
int lr;
extern int qAbdomensurface[9][SURFSIZE];
extern int qThoraxsurface[8][SURFSIZE];
void MakeQueen(num)
int num;
{
#if !defined(IBM_MakeQueen)
int tp,i;
int body;

if(level==7)
	{
	if ( MonoCrome )
	    {
	    for(i=0;i<9;i++)qAbdomensurface[i][0]=WHITE;
	    for(i=0;i<8;i++)qThoraxsurface[i][0]=WHITE;
	    }
	else
	    {
		for (i=0; i<Robot[QUEEN][3].surfaces; i++)
		Robot[QUEEN][3].surface[i][0]= 78;
	    for (i=0; i<Robot[QUEEN][4].surfaces; i++)
		Robot[QUEEN][4].surface[i][0]= 78;
	    for (i=0; i<Robot[QUEEN][5].surfaces; i++)
		Robot[QUEEN][5].surface[i][0]= REDWING;
	    for (i=0; i<Robot[QUEEN][6].surfaces; i++)
		Robot[QUEEN][6].surface[i][0]= REDWING;
	    }
	}
tp=Object[num].type;
MakePrism(&Robot[tp][3],&Object[num].where,0);
MakePrism(&Robot[tp][4],&Object[num].where,0);
MakePrism(&Robot[tp][5],&Object[num].where,0);
MakePrism(&Robot[tp][6],&Object[num].where,0);
body=1;
if(Robot[tp][3].vsurface[0]&&Robot[tp][3].vsurface[4])body=1;
if(Robot[tp][3].vsurface[1]&&Robot[tp][3].vsurface[5])body=1;
if(Robot[tp][3].vsurface[0]&&Robot[tp][3].vsurface[1])body=0;
if(Robot[tp][3].vsurface[4]&&Robot[tp][3].vsurface[5])body=2;
if(body==0 && Robot[tp][3].visible)
	{
	DrawPrism(&Robot[tp][4],0);
	DrawPrism(&Robot[tp][3],0);
	}
seteyes(num);
if(faraway>=0)
	{
	if(lr)DrawPrism(&Robot[tp][5],1);
	else DrawPrism(&Robot[tp][6],1);
	draweyes(num);
	}
if(body==1 && Robot[tp][3].visible)
	{
	if(Robot[tp][3].vsurface[8])
		{
		DrawPrism(&Robot[tp][3],0);
		DrawPrism(&Robot[tp][4],0);
		}
	else
		{
		DrawPrism(&Robot[tp][4],0);
		DrawPrism(&Robot[tp][3],0);
		}
	}
if(faraway>=0)
	{
	if(lr)DrawPrism(&Robot[tp][5],1);
	else DrawPrism(&Robot[tp][6],1);
	draweyes(num);
	}
if(body==2 && Robot[tp][3].visible)
	{
	DrawPrism(&Robot[tp][3],0);
	DrawPrism(&Robot[tp][4],0);
	}
Object[num].visible=FALSE;
if(level==7)
    {
    if( MonoCrome )
	{
	for(i=0;i<9;i++)qAbdomensurface[i][0]=GRAY; /*	 */
	for(i=0;i<8;i++)qThoraxsurface[i][0]=GRAY;  /*	 */
	}
    else
	{
	for(i=0; i<Robot[QUEEN][3].surfaces; i++)
	    Robot[QUEEN][3].surface[i][0]= QUEEN;
	for(i=0; i<Robot[QUEEN][4].surfaces; i++)
	    Robot[QUEEN][4].surface[i][0]= QUEEN;
	for(i=0; i<Robot[QUEEN][5].surfaces; i++)
	    Robot[QUEEN][5].surface[i][0]= WING;
	for(i=0; i<Robot[QUEEN][6].surfaces; i++)
	    Robot[QUEEN][6].surface[i][0]= WING;
	}
    }
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
int tleft[3],tright[3],bleft[3],bright[3];
int sxloc,syloc;
int dleft,dright;
int lxloc,lyloc,rxloc,ryloc;
seteyes(num)
int num;
{
#if !defined(IBM_seteyes)
int s1,s2,c1,c2,i;
long xd,yd;

s1=sint[Object[num].where.ang]>>1;
c1=cost[Object[num].where.ang]>>1;
s2=s1>>1;
c2=c1>>1;
xd=Object[num].where.xloc+c1;
yd=Object[num].where.yloc+s1;
sxloc=Object[num].where.xloc;/*save current location*/
syloc=Object[num].where.yloc;

lxloc= xd-s2;
lyloc= yd+c2;
tleft[0] = lxloc+Robot[QUEEN][0].pnt[0][0];
tleft[1] = lyloc+Robot[QUEEN][0].pnt[0][1];
tleft[2] =       Robot[QUEEN][0].pnt[0][2];
TransRotProj(&tleft);
bleft[0] = lxloc+Robot[QUEEN][0].pnt[1][0];
bleft[1] = lyloc+Robot[QUEEN][0].pnt[1][1];
bleft[2] =       Robot[QUEEN][0].pnt[1][2];
TransRotProj(&bleft);
dleft=tleft[2]-bleft[2];

rxloc=xd+s2;
ryloc=yd-c2;
tright[0] = rxloc+Robot[QUEEN][0].pnt[0][0];
tright[1] = ryloc+Robot[QUEEN][0].pnt[0][1];
tright[2] =       Robot[QUEEN][0].pnt[0][2];
TransRotProj(&tright);
bright[0] = rxloc+Robot[QUEEN][0].pnt[1][0];
bright[1] = ryloc+Robot[QUEEN][0].pnt[1][1];
bright[2] =       Robot[QUEEN][0].pnt[1][2];
TransRotProj(&bright);
dright=tright[2]-bright[2];

if(dleft<dright)lr=1;
else lr=0;
yd-=Me.yloc;
xd-=Me.xloc;
if((yd*yd+xd*xd)<=64*64)faraway=0;
else faraway=1;
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
draweyes(num)
int num;
{
#if !defined(IBM_draweyes)
Rect r;
int rWidth, rHeight;

if(lr)
	{
	r.bottom=tleft[2];
	r.top=bleft[2]-dleft;
	r.left=bleft[0]-dleft;
	r.right=bleft[0]+dleft;
	Object[num].where.xloc=lxloc;
	Object[num].where.yloc=lyloc;
	lr=0;
	}
else
	{
	r.bottom=tright[2];
	r.top=bright[2]-dright;
	r.left=bright[0]-dright;
	r.right=bright[0]+dright;
	Object[num].where.xloc=rxloc;
	Object[num].where.yloc=ryloc;
	lr=1;
	}
if(r.left<Object[num].where.xmn)Object[num].where.xmn=r.left;
if(r.right>Object[num].where.xmx)Object[num].where.xmx=r.right;


/*  if(level==1 || level==7)  */

PenColor(realcolor[vRED]);
if(faraway)FillOval(&r,1);
PenColor(realcolor[vINTWHITE]);
FrameOval(&r);

/*
PenColor(realcolor[vINTWHITE]);
if(faraway)FillOval(&r,1);
PenColor(realcolor[vBLACK]);
if ( !is_EGAtype )
    FrameOval(&r);
*/

MakePrism(&Robot[QUEEN][1],&Object[num].where,1);/*iris*/
MakePrism(&Robot[QUEEN][2],&Object[num].where,1);/*pupil*/
if(Robot[QUEEN][1].vsurface[0])
	{
	r.bottom=Robot[QUEEN][1].copy[0][2];
	r.top=Robot[QUEEN][1].copy[2][2];
	r.left=Robot[QUEEN][1].copy[3][0];
	r.right=Robot[QUEEN][1].copy[1][0];

	if( !MonoCrome && level==7 )
	    {
	    PenColor(realcolor[vGREEN]);
	    BackColor(realcolor[vYELLOW]);
	    if(faraway)FillOval(&r,4);
	    FrameOval(&r);
	    }
	else
	    {
	    PenColor(realcolor[vGREEN]);
	    BackColor(realcolor[vINTWHITE]);
	    if(faraway)FillOval(&r,3);
	    FrameOval(&r);
	    }
	PenColor(realcolor[vBLACK]);

	if ( level==7 )
	    {
	    rHeight=  r.bottom-r.top-((r.bottom-r.top)>>4);
	    r.bottom-= rHeight;
	    r.top+= rHeight;
	    rWidth=  ((r.right-r.left)>>3)+1;
	    r.right=r.left= (r.right+r.left)>>1;
	    /*	r.right-= rWidth;		   */
	    /*	r.left+= rWidth;		  */
	    /*	r.right= Robot[QUEEN][2].copy[1][0]*3/4+Robot[QUEEN][2].copy[3][0]/4; */
	    /*	r.left= Robot[QUEEN][2].copy[1][0]/4+Robot[QUEEN][2].copy[3][0]*3/4;  */
	    PenSize(rWidth, 1);
	    /*	PenCap(capFlat);  */
	    MoveTo(r.left, r.top);
	    LineTo(r.left, r.bottom);
	    PenSize(1, 1);
	    }
	else
	    {
	    r.bottom=Robot[QUEEN][2].copy[0][2];
	    r.top=Robot[QUEEN][2].copy[2][2];
	    r.left=Robot[QUEEN][2].copy[3][0];
	    r.right=Robot[QUEEN][2].copy[1][0];
	    if(faraway)FillOval(&r,1);
	    FrameOval(&r);
	    }

	}/* Round Eye */
Object[num].where.xloc=sxloc;
Object[num].where.yloc=syloc;
#endif
}
