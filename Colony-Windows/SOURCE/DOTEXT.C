/*#define IBM_DoText*/
/*			 */
/*
#include <Quickdraw.h>
#include <WindowMgr.h>
#include <MenuMgr.h>
#include <EventMgr.h>
#include <DialogMgr.h>
#include <ToolboxUtil.h>
#include <math.h>
#include <stdio.h>
#include <FileMgr.h>
#include <Stdfilepkg.h>
#include <SegmentLdr.h>
*/

#define EXT extern 
#include "gamedefs.h"
#include "fcntl.h"

#define TRUE 1
#define FALSE 0
#define ENTRY_NUM 3
long swab_l();
extern int Mac512;
extern Rect rScreen;
extern v_puts();
int my_open_read(char *, int, int);
/*----------------------------------------------------------------------*/
#define LINEHEIGHT 16
char *textname="t.dat";
char *kpress="-Press Any Key to Continue-";
char *epress="-Press ENTER to Continue-";
DoText(rstart,entry,center)
Rect *rstart;
int entry;
int center;
{
#if !defined(IBM_DoText)
int i,j,n;
int tmp;
struct	{
		long offset;
		int ch;
		int lines;
		}index;
unsigned char *page;
unsigned char *lines[80];
int linecount;
int pblk;
event key;
int maxlines;
int wdth,twdth;
int cX,cY;
Rect r;

if((pblk=my_open_read(textname, O_RDONLY|O_BINARY, TRUE)) < 0)
	return;
if(my_read_loc(pblk,&index,8L,4L+entry*8L))
	{
	Inform(sys_errlist[errno],TRUE);
	return;
	}
index.offset = swab_l(index.offset);
swab(&index.ch, &tmp, 2);
index.ch = tmp;
swab(&index.lines, &tmp, 2);
index.lines = tmp;

if(0==(page=(unsigned char *)NewPtr(index.ch+1)))MemoryErr();
if(my_read_loc(pblk,page,index.ch,index.offset))
	{
	Inform(sys_errlist[errno],TRUE);
	return;
	}
page[index.ch]=0;
if(close(pblk) < 0)
	{
	Inform(sys_errlist[errno],TRUE);
	return;
	}
page[index.ch-1]^='\\';			/*	start decode with '\' char	*/
for (n=index.ch-2; n>=0; n--) page[n]^=page[n+1]; /*decode	using page[n+1]*/
lines[0]=&page[0];
linecount=1;
for (n=0; n<index.ch; n++)
	{
	if (page[n]=='\r') 
		{
		page[n] = '\0';
		lines[linecount]=&page[n+1];
/*		lines[linecount][0]=0;
		i=1;
		while(lines[linecount-1][i])i++;
		i--;
		lines[linecount-1][0]=i; */
		linecount++;
		}
	}
linecount--;
wdth=0;
for(i=0;i<linecount;i++)
	{
	twdth=StringWidth(lines[i]);
	if(twdth>wdth)wdth=twdth;
	}
twdth=StringWidth(kpress);
if(twdth>wdth)wdth=twdth;
wdth+=12;
wdth>>=1;
maxlines=(sR.bottom-sR.top)/14;
maxlines--;
cX=(sR.right+sR.left)>>1;
cY=(sR.top+sR.bottom)>>1;
if(maxlines>linecount)	maxlines=linecount;
r.top=cY-(((maxlines+1)*7)+4);
r.bottom=cY+((maxlines+1)*7)+4;
r.left=cX-wdth;
r.right=cX+wdth;
r.left+=3; r.right+=3;
r.top+=3; r.bottom+=3;
DoGray();
HideCursor();
BackColor(realcolor[vINTWHITE]);
for(i=0;i<3;i++)
	{
	FrameRect(&r);
	r.top--;r.bottom--;r.left--;r.right--;
	}

EraseRect(&r);
FrameRect(&r);
TextAlign(alignLeft,alignTop);
for(i=0;i<maxlines;i++)
	{
	MoveTo(3+r.left,r.top+4+i*14);
	DrawString(lines[i]);
	if(center==2){DoDitSound();while(!SoundDone());}
	}
MoveTo((r.left+r.right)>>1,r.top+6+maxlines*14);
TextAlign(alignCenter,alignTop);
if(maxlines<linecount)
	DrawString("-Press Any Key For More...-");
else DrawString(kpress);
while(KeyEvent(FALSE,&key));
if(KeyEvent(TRUE,&key));

if(maxlines<linecount)
	{
	EraseRect(&r);
	FrameRect(&r);
	TextAlign(alignLeft,alignTop);
	for(i=maxlines-1;i<linecount;i++)
		{
		MoveTo(3+r.left,r.top+6+(1+i-maxlines)*14);
		DrawString(lines[i]);
		if(center==2){DoDitSound();while(!SoundDone());}
		}
	TextAlign(alignCenter,alignTop);
	MoveTo((r.left+r.right)>>1,r.top+6+maxlines*14);
	DrawString(kpress);
	while(KeyEvent(FALSE,&key));
	if(KeyEvent(TRUE,&key));
	}
SetPort(scrport);
PaintRect(&sR);
ShowCursor();
DisposPtr(page);
#endif
}
/*----------------------------------------------------------------------*/
DoGray()
{
extern int showDashBoard, drewDashBoard;

SetPort(scrport);
HideCursor();
BackColor(realcolor[vWHITE]);
PenColor(realcolor[vBLACK]);
ClipRect(&sR);
PenPattern(3);
PaintRect(&sR);
PenPattern(1);
ShowCursor();
if (showDashBoard) drewDashBoard = 0;
}
/*----------------------------------------------------------------------*/
union long_bytes
	{
	long l;
	char c[4];
	};
long
swab_l(l)
union long_bytes l;
    {
    union long_bytes ret;

    ret.c[0] = l.c[3];
    ret.c[1] = l.c[2];
    ret.c[2] = l.c[1];
    ret.c[3] = l.c[0];

    return(ret.l);
    }
/*----------------------------------------------------------------------*/
char *H1[]={
	"F1=Function Key Help",
	"F2=Keyboard Movement Help",
	"F3=Interact Mode Help",
	"F4=Instrument Panel Help",
	"F5=Save a Game/Quit",
	"F6=Load a Game",
	"F7=Display Instrument Panel",
	"F8=Toggle Polygon Fill",
	"F9=Toggle Sound On/Off",
	"F10=Pause"};
Help1()
{
int i,ht,wd,twd,cX;
Rect r;
Rect ssR;

SetPort(scrport);
TextAlign(alignCenter,alignMiddle);
ssR=sR;
ssR.top+=19;
cX=(ssR.right+ssR.left)>>1;
wd=0;
for(i=0;i<10;i++)
	{
	twd=StringWidth(H1[i]);
	if(twd>wd)wd=twd;
	}
r=sR;
r.bottom=15;
PenColor(realcolor[vINTWHITE]);
PaintRect(&r);
PenColor(realcolor[vBLACK]);
BackColor(realcolor[vINTWHITE]);
MoveTo(cX,7);
DrawString("FUNCTION KEYS");
if(!MonoCrome)
	{
	PenColor(realcolor[vLTBLUE]);
	FrameRect(&r);
	}
wd+=16;
wd>>=1;
ht=(ssR.bottom-ssR.top)/11;
BackColor(realcolor[vINTWHITE]);
r.left=cX-wd;
r.right=cX+wd;
for(i=0;i<10;i++)
	{
	r.top=ssR.top+ht*i+1;
	r.bottom=ssR.top+ht*(i+1)-2;
	r.left=cX-(wd+1);
	r.right=1+cX+wd;
	if(!MonoCrome)
		{
		BackColor(realcolor[vLTBLUE]);
		EraseRoundRect(&r,16,16);
		r.top++;r.bottom--;r.left++;r.right--;
		}
	BackColor(realcolor[vINTWHITE]);
	EraseRoundRect(&r,16,16);
	PenColor(realcolor[vBLACK]);
	MoveTo(cX,1+((r.top+r.bottom)>>1));
	DrawString(H1[i]);
	}
BackColor(realcolor[vBLACK]);
PenColor(realcolor[vINTWHITE]);
MoveTo(cX,ssR.bottom-10);
DrawString(kpress);
}
/*----------------------------------------------------------------------*/
char *H2[]={
	"Q/Home",
	"W/Up Arrow",
	"E/Pg Up",
	"A/Lt Arrow",
	"S/Center",
	"D/Rt Arrow",
	"Z/End",
	"X/Dn Arrow",
	"C/Pg Dn",
	"Space Bar/Ins",
	"1 - 5"};
char *H22[]={
	"Rotate Left",
	"Move Forward",
	"Rotate Right",
	"Move Left",
	"Move Back",
	"Move Right",
	"Look Left",
	"Look Back",
	"Look Right",
	"Shoot Laser",
	"Speed"};
Help2()
{
char pdata[81];
int i,j,ht,wd,twd;
Rect r;
Rect ssR;
int cX;

cX=(sR.left+sR.right)/2;
SetPort(scrport);
PenMode(zREPz);
ssR=sR;
ssR.top+=17;
r=sR;
r.bottom=15;
PenColor(realcolor[vINTWHITE]);
PaintRect(&r);
PenColor(realcolor[vBLACK]);
BackColor(realcolor[vINTWHITE]);
MoveTo(cX,7);
DrawString("FLY-BY MODE");
if(!MonoCrome)
	{
	PenColor(realcolor[vLTBLUE]);
	FrameRect(&r);
	}
TextAlign(alignCenter,alignMiddle);
wd=((ssR.right-ssR.left)+3)/3;
ht=(ssR.bottom-ssR.top)/5;
for(i=0;i<3;i++)for(j=0;j<3;j++)
	{
	r.top=ssR.top+6+ht*i;
	r.bottom=ssR.top+ht*(i+1)-2;
	r.left=6+wd*j;
	r.right=wd*(j+1)-3;
	DoButton(&r,H2[i*3+j],H22[i*3+j]);
	}
r.top=ssR.top+6+ht*3+10;
r.bottom=ssR.top+ht*(3+1)+8;
r.left=6;
r.right=wd-3;
DoButton(&r,H2[10],H22[10]);
r.top=ssR.top+6+ht*3+10;
r.bottom=ssR.top+ht*(3+1)+8;
r.left=6+wd;
r.right=wd*3-3;
DoButton(&r,H2[9],H22[9]);
BackColor(realcolor[vBLACK]);
PenColor(realcolor[vINTWHITE]);
MoveTo((ssR.right+ssR.left)>>1,ssR.bottom-10);
DrawString(kpress);
}
char *H3[]={
	"Up Left",
	"Up",
	"Up Right",
	"Left",
	"Center",
	"Right",
	"Down Left",
	"Down",
	"Down Right"};
Help3()
{
char pdata[81];
int i,j,ht,wd,twd,cX;
Rect r;
Rect ssR;


cX=(sR.left+sR.right)/2;
SetPort(scrport);
PenMode(zREPz);
ssR=sR;
ssR.top+=17;
r=sR;
r.bottom=15;
PenColor(realcolor[vINTWHITE]);
PaintRect(&r);
PenColor(realcolor[vBLACK]);
BackColor(realcolor[vINTWHITE]);
MoveTo(cX,7);
DrawString("2-D BITMAP MODE");
if(!MonoCrome)
	{
	PenColor(realcolor[vLTBLUE]);
	FrameRect(&r);
	}
TextAlign(alignCenter,alignMiddle);
wd=((ssR.right-ssR.left)+3)/3;
ht=(ssR.bottom-ssR.top)/5;
PenColor(realcolor[vBLACK]);
for(i=0;i<3;i++)for(j=0;j<3;j++)
	{
	r.top=ssR.top+6+ht*i;
	r.bottom=ssR.top+ht*(i+1)-2;
	r.left=6+wd*j;
	r.right=wd*(j+1)-3;
	DoButton(&r,H2[i*3+j],H3[i*3+j]);
	}
r.top=ssR.top+6+ht*3+10;
r.bottom=ssR.top+ht*(3+1)+8;
r.left=6;
r.right=wd-3;
DoButton(&r,"1-5","Speed");
r.top=ssR.top+6+ht*3+10;
r.bottom=ssR.top+ht*(3+1)+8;
r.left=6+wd;
r.right=wd*2-3;
DoButton(&r,"Enter","Enter Door");
r.top=ssR.top+6+ht*3+10;
r.bottom=ssR.top+ht*(3+1)+8;
r.left=6+2*wd;
r.right=wd*3-3;
DoButton(&r,"Spac/Ins","Select");
BackColor(realcolor[vBLACK]);
PenColor(realcolor[vINTWHITE]);
cX=(ssR.right+ssR.left)>>1;
MoveTo(cX,ssR.top+ht*(3+1)+18);
DrawString("Use Ctrl-Select to Move Object");
MoveTo((ssR.right+ssR.left)>>1,ssR.bottom-10);
DrawString(kpress);
}
/*----------------------------------------------------------------------*/
DoButton(Rect *r,char *t,char *b)
{
int cY,cX;
PenPattern(3);
BackColor(realcolor[vBLACK]);
PenColor(realcolor[vINTWHITE]);
PaintRoundRect(r,16,16);
PenPattern(1);
FrameRoundRect(r,16,16);
BackColor(realcolor[vINTWHITE]);
r->left-=5; r->right-=5; r->top-=5; r->bottom-=5;
cX=(r->right+r->left)>>1;
cY=(r->top+r->bottom)>>1;
EraseRoundRect(r,16,16);
if(!MonoCrome)
	{
	PenColor(realcolor[vLTBLUE]);
	FrameRoundRect(r,16,16);
	}
PenColor(realcolor[vBLACK]);
MoveTo(r->left+1,cY);
LineTo(r->right-1,cY);
MoveTo(cX,(cY+r->top)>>1);
DrawString(t);
MoveTo(cX,(cY+r->bottom)>>1);
DrawString(b);
}
/*----------------------------------------------------------------------*/
Help4()
{
Rect r;
int ht,htt;
int bottom;
int cX;
Rect ssR;
extern Rect compOval;
extern Rect floorRect;
extern Rect powerRect;
extern int powerWidth;

ssR=sR;
r.left=ssR.left+4*pix_per_Qinch_x+5;
r.right=ssR.right;
cX=(r.left+r.right)>>1;
HelpDashBoard();
TextAlign(alignLeft,alignMiddle);
BackColor(realcolor[vINTWHITE]);
r.top=powerRect.top;
r.bottom=powerRect.bottom;
EraseRoundRect(&r,16,16);
if(!MonoCrome)
	{
	PenColor(realcolor[vLTBLUE]);
	FrameRoundRect(&r,16,16);
	}
r.top=floorRect.top;
r.bottom=floorRect.bottom;
EraseRoundRect(&r,16,16);
if(!MonoCrome)
	{
	PenColor(realcolor[vLTBLUE]);
	FrameRoundRect(&r,16,16);
	}
r.top=compOval.top;
r.bottom=compOval.bottom;
EraseRoundRect(&r,16,16);
FrameRoundRect(&r,16,16);
if(!MonoCrome)
	{
	PenColor(realcolor[vLTBLUE]);
	FrameRoundRect(&r,16,16);
	}
PenColor(realcolor[vBLACK]);
ht=(powerRect.bottom-powerRect.top)/6;
htt=ht>>1;

bottom=powerRect.top+ht-4;
MoveTo(8+r.left+2,bottom-2);
LineTo(8+r.left+powerWidth-2,bottom-2);
LineTo(8+r.left+(powerWidth>>1),bottom-(powerWidth-2));
LineTo(8+r.left+2,bottom-2);
MoveTo(r.left+powerWidth*2,powerRect.top+ht-htt);
DrawString("WEAPONS");
MoveTo(r.left+8,powerRect.top+2*ht-htt);
DrawString("Laser strength indicator.");

bottom=powerRect.top+3*ht-4;
MoveTo(8+r.left+1,bottom-(powerWidth>>1));
LineTo(8+r.left+(powerWidth>>1),bottom-(powerWidth-1));
LineTo(8+r.left+powerWidth-1,bottom-(powerWidth>>1));
LineTo(8+r.left+(powerWidth>>1),bottom-1);
LineTo(8+r.left+1,bottom-(powerWidth>>1));
MoveTo(r.left+powerWidth*2,powerRect.top+3*ht-htt);
DrawString("LIFE");
MoveTo(r.left+8,powerRect.top+4*ht-htt);
DrawString("Termination if equals zero.");

bottom=powerRect.top+5*ht-4;
MoveTo(8+r.left+2,bottom-(powerWidth-2));
LineTo(8+r.left+powerWidth-2,bottom-(powerWidth-2));
LineTo(8+r.left+(powerWidth>>1),bottom-2);
LineTo(8+r.left+2,bottom-(powerWidth-2));
MoveTo(r.left+powerWidth*2,powerRect.top+5*ht-htt);
DrawString("ARMOR");
MoveTo(r.left+8,powerRect.top+6*ht-htt);
DrawString("Power space suit strength");

MoveTo(r.left+8,(compOval.top+compOval.bottom)>>1);
DrawString("COMPASS");

ht=(floorRect.bottom-floorRect.top)>>1;
MoveTo(r.left+8,floorRect.top+ht-ht/2);
DrawString("OVERHEAD VIEW: shows positions");
MoveTo(r.left+8,floorRect.top+ht+ht/2);
DrawString("of objects near you.");
BackColor(realcolor[vBLACK]);
PenColor(realcolor[vINTWHITE]);
TextAlign(alignCenter,alignMiddle);
MoveTo((r.right+r.left)>>1,(powerRect.bottom+floorRect.top)>>1);
DrawString(kpress);
}

/*----------------------------------------------------------------------*/
Help(num)
int num;
{
SetPort(scrport);
HideCursor();
ClipRect(&sR);
PenColor(realcolor[vBLACK]);
PaintRect(&sR);

switch(num)
	{
	case 1:Help1();break;
	case 2:Help2();break;
	case 3:Help3();break;
	case 4:Help4();break;
	}
while(KeyEvent(FALSE,&key));
while(KeyEvent(TRUE,&key))
	{
	ClipRect(&sR);
	PenColor(realcolor[vBLACK]);
	PaintRect(&sR);
	if ( key.ScanCode>58 && key.ScanCode<63 )
		switch(key.ScanCode-58)
			{
			case 1:Help1();break;
			case 2:Help2();break;
			case 3:Help3();break;
			case 4:Help4();break;
			}
	else break;
	while(KeyEvent(FALSE,&key));
	}
ShowCursor();
}
