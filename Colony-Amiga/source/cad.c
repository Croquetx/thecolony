#include "object.h"

window *x,*y,*z;
int xSize,ySize;
int xloc=0,yloc=0;

/*------------------------------------------------------------------------------
 * Data port of the CAD system.
 *------------------------------------------------------------------------------*/
void DataSize(pr)
Rect *pr;
{
pr->left=xSize-1;
}

void DataDisplay(scroll,pr,v,h)
int scroll;
Rect *pr;
int v,h;
{
RgnHandle updateRgn;

ClipRect(pr);
if(scroll)
	{
	if(v!=yloc || h!=xloc)
		{
		updateRgn=NewRgn();
		ScrollRect(pr,h-xloc,v-yloc,updateRgn);
		yloc=v;
		xloc=h;
		DisposeRgn(updateRgn);
		}
	}
/*EraseRect(pr);*/
MoveTo(xSize+xloc,yloc);
LineTo(xSize+xloc+10,yloc);
LineTo(xSize+xloc+10,yloc+10);
LineTo(xSize+xloc,yloc+10);
LineTo(xSize+xloc,yloc);
}

void DataAction(pt)
Point pt;
{
Inform("\pData");
}
/*------------------------------------------------------------------------------
 * Palette port of CAD window
 *------------------------------------------------------------------------------*/
void PaletteSize(pr)
Rect *pr;
{
pr->right=xSize;
}

void PaletteDisplay(scroll,pr,v,h)
int scroll;
Rect *pr;
int v,h;
{
int i;
Rect r;
PicHandle pic;

pic=GetPicture(-32000);
r.top=-1; r.left=-1; r.right=xSize-1; r.bottom=ySize-1;
ClipRect(pr);
HLock(pic);
DrawPicture(pic,&r);
HUnlock(pic);
ReleaseResource(pic);
MoveTo(r.right-1,r.bottom);
LineTo(r.right-1,pr->bottom);
}

void PaletteAction(pt)
Point pt;
{
Inform("\pPalette");
}
/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------*/
MakeWindows()
{
Rect r;
Point size;
PicHandle pic;

size.v=150;
size.h=150;

r=screenBits.bounds;
InsetRect(&r,40,40);
y=new(window);
y->cwindow(&r,"\ptest y",size,TRUE,TRUE,TRUE);

y->GetRect(&r);
y->nport(&r,100,100,TRUE,0L,0L,0L);

/*---------*/

r=screenBits.bounds;
InsetRect(&r,40,40);
pic=GetPicture(-32000);
xSize=(**pic).picFrame.right-(**pic).picFrame.left;
ySize=(**pic).picFrame.bottom-(**pic).picFrame.top;
size.v=ySize-2;
x=new(window);
x->cwindow(&r,"\ptest x",size,TRUE,TRUE,TRUE);

r.top=0; r.left=0; r.right=xSize-1; 
ReleaseResource(pic);
x->nport(&r,0,0,FALSE,PaletteSize,PaletteDisplay,PaletteAction);

x->GetRect(&r);
r.left=xSize-1;
x->nport(&r,100,100,TRUE,DataSize,DataDisplay,DataAction);
}
/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------*/

window *MakeNewWindow()
{
window *x;
Rect r,r2;
Point size;
size.v=50;
size.h=100;

r=screenBits.bounds;
InsetRect(&r,80,80);
x=new(window);
x->cwindow(&r,"\ptest x",size,TRUE,TRUE,TRUE);
return x;
}