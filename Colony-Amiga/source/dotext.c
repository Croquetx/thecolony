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

#define TRUE 1
#define FALSE 0
#define ENTRY_NUM 3
extern int Mac512;
extern Rect rScreen;
/*----------------------------------------------------------------------*/
#define LINEHEIGHT 18
char *textname="\p:CData:Tdata";
DoText(rstart,entry,center)
Rect *rstart;
int entry;
int center;
{
OSErr err;
int vnum;
char str[255];
int i,j,n;
struct	{
		long offset;
		int ch;
		int lines;
		}index;
unsigned char* page;
unsigned char *lines[80];
int linecount;
IOParam pblk;


pblk.ioNamePtr = (StringPtr)0;
err=GetVol(str,&vnum);
if(err)
	{
	DoChimeSound();
	DoChimeSound();
	ExitToShell();
	}
pblk.ioNamePtr=(StringPtr)textname;/*file name*/
pblk.ioVRefNum=vnum;
pblk.ioVersNum=0;
pblk.ioPermssn=fsRdPerm;
pblk.ioMisc=(Ptr)0;

err=PBOpen(&pblk,FALSE);
if(err)
	{
	DoChimeSound();
	return(0);
	}

if(my_read_loc(&pblk,&index,8L,4L+entry*8L))Inform("\pError in TData");
if(0==(page=(unsigned char*)NewPtr((long)index.ch+2)))MemoryErr();
if(my_read_loc(&pblk,page+1,(long)index.ch,(long)index.offset))Inform("\pError in TData");
page[index.ch+1]=0;
err=PBClose(&pblk,FALSE);
if(err)DoChimeSound();
page[index.ch]^='\\';			/*	start decode with '\' char	*/
for (n=index.ch-1; n>=1; n--) page[n]^=page[n+1]; /*	decode	using page[n+1]*/
lines[0]=&page[0];
linecount=1;
for (n=1; n<index.ch; n++)
	{
	if (page[n]=='\r') 
		{
		lines[linecount]=&page[n];
		lines[linecount][0]=0;
		i=1;
		while(lines[linecount-1][i])i++;
		i--;
		lines[linecount-1][0]=i;
		linecount++;
		}
	}
i=1;
while(lines[linecount-1][i])i++;
i--;
lines[linecount-1][0]=i;
	{
	Rect r;
	WindowPtr aWindow;
	GrafPtr	savePort;
	WindowRecord wRecord;
	int height,width,cwidth;

	TextFont(0);
	width=0;
	for(i=0;i<index.lines;i++)if(width<(cwidth=StringWidth(lines[i])))width=cwidth;
	width+=16;
	height=4+(index.lines+1)*LINEHEIGHT;
	r.top=(rScreen.bottom-height)/2;
	r.bottom=(rScreen.bottom+height)/2;
	r.left=(rScreen.right-width)/2;
	r.right=(rScreen.right+width)/2;
	ZoomRect(rstart,&r);
	GetPort( &savePort );
	SetPort((aWindow = NewWindow( &wRecord , &r, "\p", 1, 1, -1L, 0, 0L)));
	TextFont(0);
	for(i=0;i<index.lines;i++)
		{
		if(center==1)
			{
			cwidth=StringWidth(lines[i]);
			MoveTo((width-cwidth)/2,14+i*LINEHEIGHT);
			}
		else MoveTo(8,14+i*20);
		if(center==2)PlayDiDit();
		DrawString(lines[i]);
		}
	do { /*nothing*/ } while ( Button() );
	do { /*nothing*/ } while ( !Button() );
	CloseWindow(aWindow);
	if(!center&&!Mac512)
		{
		Display();
		DrawInfo();
		DrawCompass();
		}
	SetPort(savePort);
	FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);
	ZoomRect(&r,rstart);
	}
DisposPtr(page);
}

/*----------------------------------------------------------------------*/
RLocalToGlobal(rfrom,rto)
Rect *rfrom,*rto;
{
Point p;

p.v=rfrom->top;
p.h=rfrom->left;
LocalToGlobal(&p);
rto->top=p.v;
rto->left=p.h;
p.v=rfrom->bottom;
p.h=rfrom->right;
LocalToGlobal(&p);
rto->bottom=p.v;
rto->right=p.h;
}