/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
/*----------------------------------------------------------------------*  
 * FadeIn.c
 *----------------------------------------------------------------------* 
 * FadeIn(from,to)
 *		BitMap *from;
 *		BitMap *to;
 *----------------------------------------------------------------------*/ 
#define EXT extern 
#include "cgamedefs.h"

/*----------------------------------------------------------------------*/ 
FadeIn(from,to)
BitMap *from;
BitMap *to;
{
long k;
char *temp;
register long i,j;
long height;
register int order[1024];
long *pto[512],*pfrom[512];
int width,t,r1,r2;
register long bit,word;
long mask;

temp=to->baseAddr+to->rowBytes*(-to->bounds.top) + ((-to->bounds.left) >> 3);
height=screenR.bottom-screenR.top;
width=screenR.right-screenR.left;
for(i=0;i<height;i++)
	{
	pto[i]=(long *)temp;
 	temp+=to->rowBytes;
	}
temp=from->baseAddr+from->rowBytes*from->bounds.top+
	(from->bounds.left >> 3);
for(i=0;i<from->bounds.bottom-from->bounds.top;i++)
	{
	pfrom[i]=(long *)temp;
	temp+=from->rowBytes;
	}
for(i=0;i<width;i++)order[i]=i;
for(i=0;i<1000;i++)
	{r1=Random();r1=abs(r1)%width; 
	 r2=Random();r2=abs(r2)%width; 
	 t=order[r1];order[r1]=order[r2];order[r2]=t;}
HideCursor();
for(k=0;k<width;k++)
	{
	j=k;
	for(i=height-1;i>=0;i--)
		{
		word=order[j]>>5;
		bit=order[j]-(word<<5);
		mask=1L<<bit;
		pto[i][word]=(pto[i][word]&~mask)|(mask & pfrom[i][word]);
		j++; if(j==width)j=0;
		}
	}
ShowCursor();
}
