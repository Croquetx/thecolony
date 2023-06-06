/*----------------------------------------------------------------------*/
#include <Color.h>
#include <ColorToolbox.h>
/*----------------------------------------------------------------------*/
#define MAXSTAR	 0x1FF
#define NSTARS	75
#define MAXCOLOR 65535
extern int LostSound;

makestars(pr,btn)
Rect *pr;
int btn;
{
int nstars,sstars;
register int xx,yy,r;
register long i,k,d;
long s,c;
int *xang,*yang,*dist,*xsave1,*xsave2,*ysave1,*ysave2;
int centerx,centery;
int deltapd;
int scount=0;
int cscount;
RGBColor cColor,tColor;
int *rtable;

PenMode(patXor);
ClipRect(pr);

rtable=(int*)NewPtr((long)2*(MAXSTAR+1));
rtable[0]=32000;
for(i=1;i<(MAXSTAR+1);i++)rtable[i]=(128*128)/i;

xang=(int*)NewPtr(sizeof(int)*7*NSTARS);
yang=&xang[NSTARS];
dist=&yang[NSTARS];
xsave1=&dist[NSTARS];
xsave2=&xsave1[NSTARS];
ysave1=&xsave2[NSTARS];
ysave2=&ysave1[NSTARS];
nstars=NSTARS;
sstars=150;
deltapd=0x008;

cColor.blue=cColor.green=cColor.red=MAXCOLOR;
centerx=(pr->right-pr->left)/2;
centery=(pr->bottom-pr->top)/2;
for(i=0;i<sstars;i++)
	{
	s=Random()>>7;
	c=Random()>>7;
	d=Random()& 0x01FF;
	r=rtable[d];
	xx=centerx+((s*r)>>7);
	yy=centery+((c*r)>>7);
	GetCPixel(xx,yy,&tColor);
	if(!(tColor.red||tColor.blue||tColor.green))
		SetCPixel(xx,yy,&cColor);
	}

/*create the first frame of the moving stars*/	
for(i=0;i<NSTARS;i++)
	{
	d=dist[i]=Random()&0x1FF;
	if(dist[i]<=0x030)d=dist[i]=MAXSTAR;
	s=xang[i]=Random()>>7;
	c=yang[i]=Random()>>7;
/*draw new one*/
	r=rtable[d];
	MoveTo(	xsave1[i]=centerx+((s*r)>>7),
			ysave1[i]=centery+((c*r)>>7));
		
	d=dist[i]-deltapd;
	r=rtable[d];/*draw*/
	LineTo(	xsave2[i]=centerx+((s*r)>>7),
			ysave2[i]=centery+((c*r)>>7));
	}
cscount=NumCSound();
for(k=0;(k<200||btn)&&((!LostSound)&&(scount<2));k++)
	{
	if(!btn){scount = NumCSound()-cscount;}
	if(Button())if(btn||OptionKey())
		{if(!btn){DisposPtr(xang); DisposPtr(rtable); return(TRUE);}
		else scount=2;
		}
	for(i=0;i<NSTARS;i++)
		{
		MoveTo(xsave1[i],ysave1[i]);
		LineTo(xsave2[i],ysave2[i]);
		
		/*start new star*/
		s=xang[i];
		c=yang[i];
		if(dist[i]<=0x030)/*reset star*/
			{
			dist[i]=MAXSTAR;
			r=rtable[MAXSTAR];
			MoveTo(	xsave1[i]=centerx+((s*r)>>7),
					ysave1[i]=centery+((c*r)>>7));
			}
		else
			{
			xsave1[i]=xsave2[i];
			ysave1[i]=ysave2[i];
			}
		/*calculate and draw new star*/
		d=dist[i]-=deltapd;
		r=rtable[d];
		LineTo(	xsave2[i]=centerx+((s*r)>>7),
				ysave2[i]=centery+((c*r)>>7));
		}
	}
scount=0;
cscount=NumCSound();
nstars=2*((MAXSTAR-0x030)/deltapd);
for(k=0;k<nstars;k++)
	{
	if(!btn)
		{
		if(Button())if(OptionKey()){DisposPtr(xang); DisposPtr(rtable);return(TRUE);};
		}
	for(i=0;i<NSTARS;i++)
		{
		d=dist[i];
		s=xang[i];
		c=yang[i];
		dist[i]-=deltapd;
		/*draw new one*/
		if(dist[i]<=0x030)dist[i]=MAXSTAR;
		r=rtable[d];
		MoveTo(	centerx+((s*r)>>7),
				centery+((c*r)>>7));
		r=rtable[d-deltapd];/*draw*/
		LineTo(	centerx+((s*r)>>7),
				centery+((c*r)>>7));
		}
	}
PenMode(patCopy);
DisposPtr(xang);
DisposPtr(rtable);
return(FALSE);
}
