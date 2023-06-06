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
 *	Tunnel.C														 
 *	This implements the subway system.
 *---------------------------------------------------------------------- 
 */
#define EXT extern
#include "cgamedefs.h"
#include "colordef.h"
/*---------------------------------------------------------------------
 * tunnel()
 * Where am I going?.
 *---------------------------------------------------------------------
 */
int counter;
int cnt;
int maxtrax = 50;
int xt[]={	4,8,8,15,16,16,16,17,20,22,
			22,22,25,25,28,25,25,23,20,18,
			18,16,14,14,13,12,10,9,7,3,
			1,0,0,-2,-6,-8,-10,-12,-14,-16,
			-20,-20,-23,-20,-14,-8,-4,0,0,0,0,0,0,0,0,0};
int yt[]={	2,2,3,3,4,4,5,5,6,6,
			7,8,9,10,11,12,11,9,7,6,
			5,4,3,2,1,1,0,0,-1,-2,
			-3,-4,-5,-6,-6,-6,-7,-7,-8,-8,
			-9,-9,-10,-11,-12,-12,-13,-14,
			-12,-10,-7,-4,-2,0,0,0,0,0,0,0};
int st[]={ 	2,2,2,2,2,2,2,2,2,2,
			2,2,2,2,2,2,2,2,2,2,
			2,2,2,2,2,2,2,2,2,2,
			2,2,2,2,2,2,2,2,2,2,
			2,2,2,2,2,2,2,2,2,2,
			2,2,2,2,2,2,2,2,2,2};/**/
/*int st[]={	4,4,4,4,4,4,4,4,4,4,
			3,2,2,2,2,2,2,2,2,2,
			2,2,2,2,2,2,2,2,2,2,
			2,2,2,2,2,3,3,4,4,4,
			4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,8,8,8};*/

int straight[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

extern CGrafPort metaPort;
extern int ctype;
int troy;
#define MXTROY 180
tunnel(pt,mapdata)
int pt;
char mapdata[5];
{
GrafPtr	savePort;
Point myPt;
int n,spd,mxtx,i;
int saveflip;
int val;
int mnum;

TUnLoad();
if(ctype==0)return(-1);
if(pt==TRUE)
	{
	SetPower(-level<<7,-level<<7,-level<<7);
	fadein=4;
	}
DoTunnel1Sound();
saveflip=flip;
flip=0;
GetPort( &savePort );
SetPort(&metaPort);
if(pt)mxtx=10;
else mxtx=maxtrax-1;
troy=MXTROY;
cnt=0;		
if(pt)counter=2;
else counter=st[0];
spd=MXTROY/counter;
while(mxtx)
	{
	n= (mxtx > 16)?16:mxtx;
	if(Button()&&mxtx>16)mxtx=16;
	DisplayTunnel(&xt[cnt],&yt[cnt],n,pt);
	counter--;
	troy-=spd;
	if(counter==0)
		{
		troy=MXTROY;		
		cnt++;
		if(pt) counter=2;
		else counter=st[cnt];
		spd=256/counter;
		mxtx --;
		}
	}
EndCSound();
ClipRect(&Clip);
PenPat(black);
SetPort( savePort );
flip=saveflip;
KillTSound();
DoTunnel2Sound();
mnum=mapdata[2]||mapdata[3]||mapdata[4];
if(mapdata)val=GoTo(mapdata);
while(!SoundDone());
KillTSound();
if(!mnum)Terminate(FALSE);/*you're dead*/
return(val);
}
TunnelColor()
{
RGBForeColor(&cColor[c_tunnel].f);
RGBBackColor(&cColor[c_tunnel].b);
switch(cColor[c_tunnel].pattern)
	{
	case WHITE:PenPat(white); break;
	case LTGRAY:PenPat(ltGray); break;
	case GRAY:PenPat(gray); break;
	case DKGRAY:PenPat(dkGray);break;
	case BLACK:PenPat(black);break;
	}
}
/*---------------------------------------------------------------------
 * DisplayTunnel()
 *---------------------------------------------------------------------
 */
DisplayTunnel(x,y,n,pt)
int x[],y[],n,pt;
{
Rect r;
int dl[3],dr[3];
int lt,rt,ct;
int olt,ort;
int odl[3],odr[3];
int rox,roy,i,j;
int tx,ty;
float fcnt;
char str[255];

TunnelColor();
r.left	= 0;
r.right = Width;
r.top 	= 0;
r.bottom= Height;
ClipRect(&r);
PaintRect(&r); 
PenPat(black);
rox= -100;
roy= troy;
if(pt) fcnt=(double)counter/2;
else fcnt=(double)counter/st[cnt];
ty=0;
tx=0;
for(i=0;i<n;i++)
	{
	if(i)
		{
		tx=(x[i]<<2);
		ty+=(y[i]);
		}
	else  
		{
		tx=(x[i]<<2)*fcnt;
		ty+=(y[i]*fcnt);
		}
	rox+=tx;
	perspective2(dl,rox,roy);
	perspective2(dr,rox+200,roy);
	
	/*dr[0]=(centerX*2)-dl[0];
	dr[1]=dl[1];*/
	dl[2]=Height-dl[1]; dr[2]=Height-dr[1];
	/*dl[0]+=tx; dr[0]+=tx;*/
	dl[1]+=ty; dr[1]+=ty;
	dl[2]+=ty; dr[2]+=ty;
	MoveTo(dl[0],dl[2]);	/*bottom left	*/
	LineTo(dl[0],dl[1]);	/*top left		*/
	LineTo(dr[0],dr[1]);	/*top right		*/
	LineTo(dr[0],dr[2]);	/*bottom right	*/
	if(pt)
		LineTo(dl[0],dl[2]);	/*bottom left	*/
	else
		{
		ct=(dl[0]+dr[0])>>1;	/*tracks		*/
		lt=(dl[0]+ct)>>1;
		rt=(dr[0]+ct)>>1;
		}
	if(i)
		{
		MoveTo(dl[0],dl[1]);
		LineTo(odl[0],odl[1]);
		MoveTo(dr[0],dr[1]);
		LineTo(odr[0],odr[1]);
		MoveTo(dr[0],dr[2]);
		LineTo(odr[0],odr[2]);
		MoveTo(dl[0],dl[2]);
		LineTo(odl[0],odl[2]);
		/*draw tracks*/
		if(!pt)
			{
			MoveTo(olt,odl[2]);
			LineTo(lt,dl[2]);
			LineTo(rt,dr[2]);
			LineTo(ort,odr[2]);
			}
		}
	if(r.bottom < dr[2])
		{
		MoveTo(r.left,r.bottom-1);
		LineTo(r.right,r.bottom-1);
		}

	r.left=max(r.left,dl[0]);
	r.right=min(r.right,dr[0]);
	r.top=max(r.top,dl[1]);
	r.bottom=min(r.bottom,dr[2]);
	if(r.bottom<=r.top || r.left>=r.right)i=n;
	ClipRect(&r);
	odl[0]=dl[0]; odl[1]=dl[1]; odl[2]=dl[2];
	odr[0]=dr[0]; odr[1]=dr[1]; odr[2]=dr[2];
	olt=lt; ort=rt;
	roy+=256;
	}
SetPort(theWindow);
CopyBits(*metaPort.portPixMap,
	&theWindow->portBits,
	&Clip,
	&Clip,srcCopy,NIL);
SetPort(&metaPort);
}
/*---------------------------------------------------------------------
 * TunnelAirlock()
 *---------------------------------------------------------------------
 */
TunnelAirlock()
{
GrafPtr	savePort;
int mxtx=5;
int spd;
GetPort( &savePort );
SetPort(&metaPort);

troy=MXTROY;
counter=4;
spd=MXTROY/counter;
rox= -150;

while(mxtx)
	{
	DisplayTunnel(straight,straight,mxtx,0);
	troy-=spd;
	counter--;
	if(counter==0)
		{
		troy=MXTROY;		
		counter=4;
		mxtx --;
		}
	}
ClipRect(&Clip);
PenPat(black);
SetPort( savePort );
}
