#define EXT extern 
#include "gamedefs.h"

/*  #include <GRfonts.h>  */
extern char *kpress;
extern char *epress;
extern int showDashBoard;
extern int drewDashBoard;

Inform(char *text,int hold)
{
char *outputMessage[3];

outputMessage[0]= text;
if(hold)outputMessage[1]=kpress;
else outputMessage[1]=NULL;
outputMessage[2]= NULL;
printMessage(outputMessage);
if(hold)
	{
	while ( KeyEvent(FALSE, &key) );
	while ( !KeyEvent(FALSE, &key) );
	}
if(showDashBoard)drewDashBoard=0;
}


/************************** getInput() ********************************/
/* Read a file name.  Allow only valid DOS names including drive and */
/* directory specifiers.  Don't allow a file extention.  If a space is */
/* entered, use the last entered name.  The returned string will be the */
/* string entered with .COL appended. */
char NewString[50]={0};
char OldString[50]={0};
int strlength=0;
char *getInput(char **stringToPrint, Rect *rr)
{
int i;
int wasCR;
int numLines, start, step;
Rect r;
char string[40];

DoGray();
HideCursor();
string[0]=0;
strlength=0;
for(numLines=0; stringToPrint[numLines]!=NULL; numLines++);
start=rr->top+ pix_per_Qinch_y*2;
step= (rr->bottom-rr->top-(pix_per_Qinch_y)*5 )/numLines;
MakeRect(rr);
r.left=rr->left+8;
r.right=rr->right-8;
r.top=rr->bottom-(2*step);
r.bottom=rr->bottom-(step/2);
PenColor(realcolor[vBLACK]);
FrameRect(&r);
r.top++; r.bottom--; r.left++; r.right--;

TextAlign(1,2);
for (i=0; i<numLines; i++)
    {
    MoveTo( (rr->right+rr->left)>>1, start+i*step );
    DrawString(stringToPrint[i]);
    }
while( KeyEvent(FALSE, &key) );
wasCR= False;
while( !wasCR )
    {
    if( KeyEvent(FALSE, &key) && key.ASCII )
	{
	if(key.ASCII==' ')
		{

		i=0; while(string[i]=OldString[i]){i++;}
		strlength=i;
		PenColor(realcolor[vINTWHITE]);
		PaintRect(&r);
		PenColor(realcolor[vBLACK]);
		}
	else if( key.ASCII==0x0D )
	    wasCR=True;
	else if( key.ASCII==0x08 || key.ASCII==0x7F )
	    {
		PenColor(realcolor[vINTWHITE]);
		PaintRect(&r);
		if ( --strlength<0 )strlength=0;
	    string[strlength]='\0';
		PenColor(realcolor[vBLACK]);
		}
	else if(NameOk(string, strlength, key.ASCII, 36))
	    {
	    string[strlength++]=key.ASCII;
	    string[strlength]= '\0';
	    }
	else
	    putchar(0x07);
	MoveTo( (r.right+r.left)>>1, (r.bottom+r.top)>>1);
    DrawString(string);
	}
    }

BackColor(realcolor[vWHITE]);
PenColor(realcolor[vBLACK]);
ShowCursor();
if(string[0])
	for(i=0;i<50;i++)OldString[i]=string[i];
strcpy(NewString, string);
if(string[0])
	strcat(NewString, ".col");
return NewString;
}


/************************** printMessage() ********************************/

printMessage(char **stringToPrint)
{
int i;
int numLines, start, step;
int width = 0;
char **stringIndex;
Rect rr;

for (stringIndex = stringToPrint; *stringIndex != NULL; stringIndex++)
    if (StringWidth(*stringIndex) > width)
	width = StringWidth(*stringIndex);

numLines = stringIndex - stringToPrint;

rr.top= (sR.bottom+sR.top)/2 - (numLines+1)*pix_per_Qinch_y;
rr.bottom= (sR.bottom+sR.top)/2 + (numLines+1)*pix_per_Qinch_y;
rr.left=  (sR.right+sR.left)/2 - width/2 - 2*pix_per_Qinch_x;
rr.right= (sR.right+sR.left)/2 + width/2 + 2*pix_per_Qinch_x;

DoGray();
HideCursor();

MakeRect(&rr);

if (numLines>1)
    {
    start=rr.top+ pix_per_Qinch_y*2;
    step= ( rr.bottom-rr.top-(pix_per_Qinch_y)*4 )/(numLines-1);
    }
else
    {
    start= (rr.top+rr.bottom)/2;
    step= 0;
    }

TextAlign(1,2);
PenColor(realcolor[vBLACK]);
for (i=0; i<numLines; i++)
    {
    MoveTo( (rr.right+rr.left)>>1, start+i*step );
    DrawString(stringToPrint[i]);
    }
BackColor(realcolor[vWHITE]);
PenColor(realcolor[vBLACK]);
ShowCursor();
}


/************************** MakeRect() ********************************/

MakeRect(Rect *rr)
{
Rect r;

r.left=rr->left;
r.right=rr->right;
r.top=rr->top;
r.bottom=rr->bottom;
PenColor(realcolor[vBLACK]);	    /*	makes message rectangle for  */
BackColor(realcolor[vINTWHITE]);
ClipRect(rr);
EraseRect(rr);
FrameRect(rr);
r.left+=2;
r.right-=2;
r.top+=2;
r.bottom-=2;
FrameRect(&r);
}
/* ----------- */
/* check if 'old' will be a valid DOS file name after 'new' is concatenated */
NameOk(old, size, new, maxlen)
char *old;
int size;
char new;
	{
	int namesize = 0;

	if (size >= maxlen || !isascii(new))
		return(FALSE);

	while (*old)
		{
		if (*old == '\\' || *old == ':')
			namesize = 0;
		else
			namesize++;
		old++;
		}

	if (new == ':')
		{
		if (size == 1 && isalpha(*(old-1)))
			return(TRUE);
		}
	else if (new == '\\')
		{
		if (size == 0 || *(old-1) != '\\')
			return(TRUE);
		}
	else if (new == '.')
		{
		if (namesize == 0 || *(old-1) == '.')
			return(TRUE);
		}
	else if (isalnum(new) || new == '_')
		{
		if (namesize < 8)
			return(TRUE);
		}

	return(FALSE);
	}
