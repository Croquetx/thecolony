/*  #define IBM_inits  /* */
/* #define IBM_MemoryErr*/
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
/*----------------------------------------------------------------------*
 * inits.c
 *----------------------------------------------------------------------*
 * inits()
 * TObject(n)
 * 		int n;
 *----------------------------------------------------------------------*/

#define EXT extern
#include "gamedefs.h"
#include <time.h>
#include <dos.h>

int MaxApplZone();
Ptr restartProc=0;
#define windowMID 13694
#define windowIID 10930
#define M1  -1L

extern int vcenterX,vcenterY;
/*----------------------------------------------------------------------*/
#define CW 4		/*horizontal icon setoff in menu box */
#define CH1 -19		/*vertical icon setoff */
#define CH2 -20
#define FSIZE 24	/*font size in bits */
#define SOUND 	1		/* == 1   */

/*----------------------------------------------------------------------*/

cursor curScr, curMask;

extern int showDashBoard;
char DataDir[80];
int colornum=0;
int mouse=FALSE;
int jmouse=FALSE;
int showConfig=TRUE;
int MouseScaleX, MouseScaleY;

int inits(int argc, char *argv[])
{
#if !defined(IBM_inits)
int i,j;
int k,l;
int *pint;
unsigned char *pchar;
/* GDHandle GDH;   */
/* GDPtr GDP;	   */
int message,count;
long rSeed;
char *tstr;
time_t tm;
long HeapSize();

/*HeapGreedy(); /* dwe ??? testing */
soundon= True;
polyfill=False;
showDashBoard=True;
GetConfig(argc, argv);
InitGrafix(-GrafixCard);
InitMouse(CommPort);
Setup_Colors();
InitSound();

ScreenRect (&sR);
GetPort((GrafPort *)&scrport);

if (!jmouse)
	ScaleMouse(24,16);
else
	{
	/* width of screen plus 1 inch to handle different center positions */
	/* add an additional 1/2 inch to ensure cursor can move all the way */
	/* to the edge */
	MouseScaleX = (sR.right-sR.left+1) + (3*scrport->portBMap->pixResX)/2;
	MouseScaleY = (sR.bottom-sR.top+1) + (scrport->portBMap->pixResY)/2;
	/* joystick has a range of approx. +/- 128 */
	/* set scale for entire range computed above */
	MouseScaleX = (MouseScaleX * 16) / 256;
	MouseScaleY = (MouseScaleY * 16) / 256;
	ScaleMouse(MouseScaleX, MouseScaleY);
	}

SetDisplay (GrafPg0);
EraseRect (&sR);
aspect=(float)scrport->portBMap->pixResX/scrport->portBMap->pixResY;
pix_per_Qinch_x=scrport->portBMap->pixResX/4;
pix_per_Qinch_y=scrport->portBMap->pixResY/4;

if (showDashBoard)
	screenR.left= sR.left+4*pix_per_Qinch_x+4;
else
	screenR.left= sR.left;
screenR.top= sR.top;
screenR.right= sR.right;
screenR.bottom= sR.bottom;
Width=screenR.right-screenR.left;
Height=screenR.bottom-screenR.top;
centerX=(screenR.left + screenR.right)/2;
centerY=(screenR.top + screenR.bottom)/2;
vcenterX=(Width/2)/6;
vcenterY=(Height/2)/7;
if (!jmouse) LimitMouse(screenR.left,screenR.top,screenR.right,screenR.bottom);
else LimitJMouse(screenR.left,screenR.top,screenR.right,screenR.bottom,
	centerX, centerY);

ClipRect(&screenR);
doGrafCardInit();

time(&tm);
tstr=ctime(&tm);
if(tstr[4]=='D'&&tstr[8]=='2'&&(tstr[9]=='5'||tstr[9]=='4'))xmas=TRUE;
srand(tm);
InitRobot();
crosshair=1;


		     /*  ShowCursor();	*/

curScr.curWidth= curMask.curWidth= 16;
curScr.curHeight= curMask.curHeight= 16;
curScr.curAlign= curMask.curAlign= 0;
curScr.curRowBytes= curMask.curRowBytes= 2;
curScr.curBits= curMask.curBits= 1;
curScr.curPlanes= curMask.curPlanes= 1;

for (i=0; i<32; i++)
    curScr.curData[i]= curMask.curData[i]= 0;

DefineCursor(7,0,0,&curScr,&curMask);

in_cur_map[0]=2;
in_cur_map[1]=7;
in_cur_map[2]=2;
in_cur_map[3]=7;
in_cur_map[4]=2;
in_cur_map[5]=7;
in_cur_map[6]=2;
in_cur_map[7]=7;
CursorMap(in_cur_map);

/* DoText(&screenBits.bounds,0,1);  */
/* SoundIntro(count); 				*/
/* SoundInit(count);  				*/
/* SetUpMenus();  					*/

fl_rect.bottom=Height-32;
fl_rect.left=32;
fl_rect.top=fl_rect.bottom-32;
fl_rect.right=fl_rect.left+32;


if(NIL==(map.buffer=malloc(25600)))return;
for(i=0;i<31;i++)
	for(j=0;j<31;j++)
	    for(k=0;k<5;k++)
		for(l=0;l<5;l++)(*map.data)[i][j][k][l]=0;/*clear the buffer*/

	
if (( pint=(int *)malloc(sizeof(int) * 1024L) )==NULL)
	{ open_mem_error = TRUE; return; }
for(i=0;i<32;i++)drX[i]= &pint[i*32];
if (( pint=(int *)malloc(sizeof(int) * 1024L) )==NULL)
	{ open_mem_error = TRUE; return; }
for(i=0;i<32;i++)drY[i]= &pint[i*32];
if (( pchar=(unsigned char *)malloc(sizeof(char) * 1024L) )==NULL)
	{ open_mem_error = TRUE; return; }
for(i=0;i<32;i++)dirXY[i]= &pchar[i*32];
if (( pchar= (unsigned char *)malloc(sizeof(char)*1024L) )==NULL)
	{ open_mem_error = TRUE; return; }
for(i=0;i<32;i++)Wall[i]=&pchar[i*32];
if (( pchar= (unsigned char *)malloc(sizeof(char)*1024L) )==NULL)
	{ open_mem_error = TRUE; return; }
for(i=0;i<32;i++)robotarray[i]= &pchar[i*32];
for(i=0;i<32;i++)for(j=0;j<32;j++)robotarray[i][j]=0;
if (( pchar= (unsigned char *)malloc(sizeof(char)*1024L) )==NULL)
	{ open_mem_error = TRUE; return; }
for(i=0;i<32;i++)foodarray[i]= &pchar[i*32];
for(i=0;i<32;i++)for(j=0;j<32;j++)foodarray[i][j]=0;

patch=(struct patchstrct*)malloc(sizeof(struct patchstrct)*100);

if (( Object=(Thing far *)malloc(sizeof(Thing) * 257) )==NULL)
	{ open_mem_error = TRUE; return; }

if (( pbattle.buffer=malloc(sizeof(Locate)*4*4*MAXQUAD))==NULL)
	{ open_mem_error = TRUE; return; }
pwhere=pbattle.data;
/*
open_mem_error=False;
EndGame(True);
*/

EventQueue(True);

/*ShowNum(Object);/**/
InitDejaVu();

if (showConfig) ShowConfig();

BattleInit();
cshoot= False;
gameInit();
init_rand_array();
cost=(int *)malloc(sizeof(int)*768L);
xai= &cost[256];
yai= &xai[256];
tabsgen();

MoveCursor(centerX, centerY);
TrackCursor(True);

HeapGreedy();
if (scrport->portBMap->pixBits == 2 || scrport->portBMap->pixPlanes == 2)
{if(HeapSize()<80000L)MemoryErr();}
else if(HeapSize()<40000L)MemoryErr();
if(NIL==(rtable=(int far *)malloc(sizeof(int)*11585)))return;
rtable[0]=32000;
for(i=1;i<11585;i++)rtable[i]=(Floor*128)/i;
return (ScrollInfo());
#endif
}

Setup_Colors()
{
int vblack,vwhite,vred,vblue;
int i;

switch(colornum)
   {
   case 0: case 2:/*Monochrome*/
	   realcolor[vBLACK]=0;
	   realcolor[vBLUE]= 0;
	   realcolor[vGREEN]=0;
	   realcolor[vCYAN]=0;
	   realcolor[vRED]=0;	
	   realcolor[vMAGENTA]=0;
	   realcolor[vBROWN]=0;
	   realcolor[vWHITE]=1;
	   realcolor[vDKGRAY]= 0;	
	   realcolor[vLTBLUE]= 0;	
	   realcolor[vLTGREEN]= 0; 
	   realcolor[vLTCYAN]= 0; 
	   realcolor[vLTRED]= 0;
	   realcolor[vLTMAGENTA]= 0;	
	   realcolor[vYELLOW]=0; 
	   realcolor[vINTWHITE]= 1;    
	   vwall_Light=0; 
	   vwall_noLight=1;
	   MonoCrome= True;
	   break;
	case 4:
	   vblack=0; vblue=1; vred=2; vwhite=3;
	   realcolor[vBLACK]=vblack;
	   realcolor[vBLUE]= vblue;
	   realcolor[vGREEN]=vblue;
	   realcolor[vCYAN]=vred;
	   realcolor[vRED]=vred;	
	   realcolor[vMAGENTA]=vblue;
	   realcolor[vBROWN]=vred;
	   realcolor[vWHITE]=vwhite;
	   realcolor[vDKGRAY]= vblack;	
	   realcolor[vLTBLUE]= vblue;	
	   realcolor[vLTGREEN]= vblue; 
	   realcolor[vLTCYAN]= vblue; 
	   realcolor[vLTRED]= vred;
	   realcolor[vLTMAGENTA]= vred;	
	   realcolor[vYELLOW]=vred; 
	   realcolor[vINTWHITE]= vwhite;    
	   vwall_Light=0; 
	   vwall_noLight=0;
	   MonoCrome= False;
	   break;
	case 16:
	   for(i=0;i<16;i++)realcolor[i]=i;
	   vwall_Light=0;
	   vwall_noLight=0;
	   MonoCrome= False;
	   break;
/*   case 'i': case 'e':
   case 'n': case 'm': case 'g': case 'h':
   case 'c':	*/
   }
}

doGrafCardInit()
{
if(is_EGAtype)
	{
	initEGA_BitMap();
	SetBitmap(GrafPg0);
	SetDisplay(GrafPg0);
	}
else
	initBitMap();
}



init_rand_array()
{
int i;

if ( (randnum=(int *)malloc(408))==NULL )
    EndGame(True);

for (i=0; i<204; i++)
    randnum[i]=rand();

}

typedef struct _device
    {
    char *devslash;
    int devnum;
    char *devdesc;
    int devvres, devhres;
    int devcolors;
    int	twopages;
    } device;

device o_dev[] =
    {              
    { "a",     ATT640x400,     "AT&T & Compaq III", 640, 400, 0,FALSE},    
    { "c",     CGA320x200,     "IBM Color Graphics", 320,200, 4,FALSE},    
    { "e1",    EGAMono,        "IBM EGA", 640,350, 0,TRUE},
    { "e2",    EGA320x200,     "IBM EGA", 320,200, 16,TRUE},
    { "e3",    EGA640x350,     "IBM EGA", 640,350, 16,TRUE},
    { "e4",    MGA640x480,     "IBM MCGA",640,480, 2,FALSE}, 
    { "e5",    MGA640x350,     "IBM EGA", 640,350, 2,TRUE}, 
    { "h",     HER720x348,     "Hercules", 720,348, 2,FALSE},
    /* The last entry should always be 0,  no device located  */
    { "",      0,              "Error", 0, 0, 0, FALSE}
    };


static device i_dev[] =
    {
    { "m",     MsMouse,        "Microsoft bus mouse",0,0,0},      
    { "m1",    MsCOM1,         "Microsoft serial mouse, COM1",0,0,0},      
    { "m2",    MsCOM2,         "Microsoft serial mouse, COM2",0,0,0},      
    { "md",    MsDriver,       "Microsoft compatible mouse driver",0,0,0},    
    { "1",     1,              "Mouse Systems serial mouse, COM1",0,0,0},    
    { "2",     2,              "Mouse Systems serial mouse, COM2",0,0,0},    
    /* The last entry should always be 0, no device located  */
    { "",      0,              "Error", 0, 0, 0}
    };


GetConfig(int argc, char *argv[])
    {
    char ConfigBuf[256];
    char name[80];
    FILE *fp;
    int i;
    int diddisplay = FALSE, didmouse = FALSE;
    char *token, *s, c;
    char *cfgargs;
	int config=FALSE;
	int data=FALSE;
	int mous=-1,disp=-1;
	
    GrafixCard = 0;
    CommPort = 0;

    if (QueryComm() < 0)
	{
	fputs("--\n", stderr);
	fputs("MetaWINDOW driver is not loaded.\n", stderr);
	fputs("Invoke using \"colony\".\n", stderr);
	fputs("--\n", stderr);
	exit(1);
	}

    getcwd(name, sizeof(name)-1);
    if (name[strlen(name)-1] != '\\')
	strcat(name, "\\");
    strcpy(DataDir, name);
	strcat(name, "colony.cfg");
	
    ConfigBuf[0] = 0;

    if ((fp = fopen("colony.cfg", "r")) == NULL)
	fp = fopen(name, "r");

    if (fp != NULL)
	{
	for (s = ConfigBuf;
	    s - ConfigBuf < sizeof(ConfigBuf)-1 && (c = getc(fp)) != EOF;
	    *s++ = c)
	    ;

	*s++ = ' ';
	*s = '\0';

	fclose(fp);
	}

    cfgargs = ConfigBuf + strlen(ConfigBuf);

    for (i = 1;
	strlen(ConfigBuf)+strlen(argv[i])+1 < sizeof(ConfigBuf) && i < argc;
	i++)
	{
	strcat(ConfigBuf, argv[i]);
	strcat(ConfigBuf, " ");
	}

    for (token = strtok(ConfigBuf, " \t\n"); 
		token != NULL;
		token = strtok(NULL, " \t\n"))
	{
	strlwr(token);
	if (strcmp(token, "/?") == 0)
	    {
	    usage();
	    exit(0);
	    }
	else if (strncmp(token, "/display:", 9) == 0)
	    {
		if ((disp=LookupDisplay(strchr(token, ':')+1)) < 0)
		{
		fputs("--\n", stderr);
		fputs("Display \"", stderr);
		fputs(strchr(token, ':')+1, stderr);
		fputs("\" is not supported.\n", stderr);
		fputs
		    ("Use \"colony /?\" to get a list of supported displays.\n",
		    stderr);
		fputs("--\n", stderr);
		exit(1);
		}
	    diddisplay = TRUE;
	    }
	else if (strncmp(token, "/mouse:", 7) == 0)
	    {
	    if ((mous=LookupMouse(strchr(token, ':')+1)) < 0)
		{
		fputs("--\n", stderr);
		fputs("Mouse \"", stderr);
		fputs(strchr(token, ':')+1, stderr);
		fputs("\" is not supported.\n", stderr);
		fputs
		    ("Use \"colony /?\" to get a list of supported mice.\n",
		    stderr);
		fputs("--\n", stderr);
		exit(1);
		}
	    didmouse = TRUE;
	    }
	else if (strncmp(token, "/data:", 6) == 0)
	    {
	    strcpy(DataDir, strchr(token, ':')+1);
	    if ((i = strlen(DataDir)) > 0 && DataDir[i-1] != ':' &&
		DataDir[i-1] != '\\' && DataDir[i-1] != '/')
		strcat(DataDir, "\\");
		data=TRUE;
		}
	else if (strcmp(token, "/quiet") == 0)
	    soundon = FALSE;
	else if (strcmp(token, "/noquiet") == 0)
	    soundon = TRUE;
	else if (strcmp(token, "/dash") == 0)
	    showDashBoard = TRUE;
	else if (strcmp(token, "/nodash") == 0)
	    showDashBoard = FALSE;
	else if (strcmp(token, "/fill") == 0)
	    polyfill = TRUE;
	else if (strcmp(token, "/nofill") == 0)
	    polyfill = FALSE;
	else if (strcmp(token, "/show") == 0)
	    showConfig = TRUE;
	else if (strcmp(token, "/noshow") == 0)
	    showConfig = FALSE;
	else if (strncmp(token, "/config", 7) == 0)
		config=TRUE;
	else
	    {
	    if (token < cfgargs)
		{
		fputs("--\n", stderr);
		fputs("Unrecognized argument in colony.cfg: ", stderr);
		fputs(token, stderr);
		fputs(".\n", stderr);
		}
	    else
		{
		fputs("--\n", stderr);
		fputs("Unrecognized argument: ", stderr);
		fputs(token, stderr);
		fputs(".\n", stderr);
		}
	    fputs("Use \"colony /?\" to get a list of valid arguments.\n",
		stderr);
	    fputs("--\n", stderr);
	    exit(1);
	    }
	}

    if (!diddisplay)
	{
	if (QueryDisplay() < 0)
	    {
	    fputs("--\n", stderr);
	    fputs("No display device was found.\n", stderr);
	    fputs("Use \"colony /?\" to get a list of supported displays.\n",
		stderr);
	    fputs("--\n", stderr);
	    exit(1);
	    }
	}

    if (!didmouse)
	QueryMouse();

    if (mouse)
	{
	void (interrupt far *MouseInt)();
	char far *p;
	char buf[10];
	int i;

	/* get address of mouse driver */
	MouseInt = _dos_getvect(0x33);

	/* get address of ID message (if JMouse) */
	p = (char far *)MouseInt + 3;

	for (i = 0; i < sizeof(buf); i++)
	    buf[i] = *p++;

	if (strncmp(buf, "JMouse", 6) == 0)
	    jmouse = TRUE;
	}

    if(config)
	    {
	    if(NULL==(fp = fopen("colony.cfg", "w")))
		    {
		    fputs("--\n",stderr);
		    fputs("Can't save colony.cfg config file.\n",stderr);
		    fputs("--\n",stderr);
		    exit(1);
		    }
	    if(disp>=0)
		    {
		    fwrite(" /display:",1,10,fp);
		    fwrite(o_dev[disp].devslash,1,strlen(o_dev[disp].devslash),fp);
		    }
	    if(mous>=0)
		    {
		    fwrite(" /mouse:",1,8,fp);
		    fwrite(i_dev[mous].devslash,1,strlen(i_dev[mous].devslash),fp);
		    }
	    if(data)
		    {
		    fwrite(" /data:",1,7,fp);
		    fwrite(DataDir,1,strlen(DataDir),fp);
		    }
	    if(!soundon)fwrite(" /quiet",1,7,fp);
	    if(!showDashBoard)fwrite(" /nodash",1,8,fp);
		if(!showConfig)fwrite(" /noshow",1,8,fp);
		if(polyfill)fwrite(" /fill",1,6,fp);
	    fclose(fp);
	    }
	}


LookupDisplay(token)
char *token;
    {
    int i;
    char *s, *d;

    for (i = 0; o_dev[i].devnum; i++)
	{
	s = o_dev[i].devslash;
	d = token;
	while (*s && *s == *d)
	    { s++; d++; }
	if (*s == '\0' && *d == '\0')
	    {
	    GrafixCard = o_dev[i].devnum;
	    DisplayParms();
	    return(i);
	    }
	}
    
    return(-1);
    }


QueryDisplay()
    {
    int qGraf;

    qGraf = QueryGrafix();

    if (qGraf < 0)
	return(-2);

    if (qGraf == NDI640x480x4D)
	GrafixCard = qGraf;
    else if (qGraf == MET1024x768x4S)
	GrafixCard = qGraf;
    else if (qGraf == NEC640x400)
	GrafixCard = qGraf;
    else if ((qGraf & VGA640x480) == VGA640x480)
	{
	if ((qGraf & 0x0030) == 0x0010)
	    GrafixCard = EGAMono;
	else
	    GrafixCard = EGA640x350;
	}
    else if ((qGraf & EVA640x480) == EVA640x480)
	{
	if ((qGraf & 0x0030) == 0x0010)
	    GrafixCard = EGAMono;
	else
	    GrafixCard = EGA640x350;
	}
    else if (qGraf & EGAMono)
	{
	if (qGraf & 0x0100)
	    {
	    if (qGraf & 0x10)
		GrafixCard=MGA640x480;
	    else
		GrafixCard=EGA640x350;
	    }
	else if ((qGraf & 0x0030) == 0x0010)
	    GrafixCard = EGAMono;
	else if (((qGraf & 0x0030) == 0x0030) && (qGraf & 0xC0))
	    GrafixCard=EGA640x350;
	else
	    GrafixCard=EGA640x200;
	}
    else if (qGraf & ATT640x400)
	{
	if (qGraf & 1)
	    GrafixCard=DEB640x400;     
	else
	    GrafixCard=ATT640x400; 
	}
    else if (qGraf & TOS640x400)
	GrafixCard = TOS640x400;
    else if (qGraf & CGA320x200)
	GrafixCard = CGA640x200;
    else if (qGraf & HER720x348)
	GrafixCard = HER720x348;
    else if (qGraf & TEC720x352)
	{ 
	if (qGraf & 2)
	    GrafixCard=TEC640x200;         
	else
	    GrafixCard=TEC720x352;
	}
    else if (qGraf & EVR640x200)
	GrafixCard = EVR640x200;
    else if (qGraf & CON640x400)
	GrafixCard = CON640x400;
    else if (qGraf & STB640x352)
	GrafixCard = STB640x352;
    else if (qGraf & TTS720x350)
	{ 
	if (qGraf & 1)
	    GrafixCard=TTS360x350;           
	else
	    GrafixCard=TTS720x350; 
	}
    else if (qGraf & SIG640x400)
	GrafixCard = SIG640x400;
    else if (qGraf & TOS640x400)
	GrafixCard = TOS640x400;
    else if (qGraf & WYS640x400)
	GrafixCard = WYS640x400;
    else if (qGraf & MDS736x1008)
	GrafixCard = MDS736x1008;
    else
	return(-1);

    DisplayParms();
    return(0);
    }


DisplayParms()
    {
    int i;

    for (i = 0; o_dev[i].devnum; i++)
	if (o_dev[i].devnum == GrafixCard)   
	    break;

    is_EGAtype = o_dev[i].twopages;
    colornum = o_dev[i].devcolors;
    }


LookupMouse(token)
char *token;
    {
    int i;
    char *s, *d;

    for (i = 0; i_dev[i].devnum; i++)
	{
	s = i_dev[i].devslash;
	d = token;
	while (*s && *s == *d)
	    { s++; d++; }
	if (*s == '\0' && *d == '\0')
	    {
	    CommPort = i_dev[i].devnum;
	    mouse = TRUE;
	    return(i);
	    }
	}

    return(-1);
    }


QueryMouse()
    {
    int qComm;

    qComm = QueryComm();

    if (qComm < 0)
	return(-2);

    if (qComm & MsDriver)
	{
	CommPort = MsDriver;
	mouse=TRUE;
	}
    else if (qComm & MsMouse)
	{
	CommPort = MsMouse;
	mouse=TRUE;
	}
    else
	return(-1);

    return(0);
    }


ShowConfig()
    {
    char *Message[10], DisplayMsg[50], MouseMsg[50], DataMsg[80], SoundMsg[15];
    char DashMsg[15], FillMsg[20];
    int i, done;

    for (i = 0; o_dev[i].devnum; i++)
	if (o_dev[i].devnum == GrafixCard)   
	    break;
    
    DisplayInfo(i, DisplayMsg);

    if (mouse)
	{
	for (i = 0; i_dev[i].devnum; i++)
	    if (i_dev[i].devnum == CommPort)   
		break;
	MouseInfo(i, MouseMsg);
	}
    else
	strcpy(MouseMsg, "No mouse");

    strcpy(DataMsg, "Data path:  ");
    strcat(DataMsg, DataDir);

    strcpy(SoundMsg, "Sound ");
    strcat(SoundMsg, (soundon ? "on" : "off"));
    strcpy(DashMsg, "Dashboard ");
    strcat(DashMsg, (showDashBoard ? "on" : "off"));
    strcpy(FillMsg, "Polygon fill ");
    strcat(FillMsg, (polyfill ? "on" : "off"));

    Message[0] = DisplayMsg;
    Message[1] = MouseMsg;
    Message[2] = DataMsg;
    Message[3] = SoundMsg;
    Message[4] = DashMsg;
    Message[5] = FillMsg;
    Message[6] = "---";
    Message[7]= "Press 'q' to quit.";
    Message[8]= "Press ENTER to continue.";
    Message[9] = NULL;

    printMessage(Message);

    while (KeyEvent(FALSE, &key))
	;

    done = FALSE;
    while (!done)
	{
	while (!KeyEvent(FALSE, &key))
	    ;

	switch(key.ASCII)
	    {
	    case 'q':
	    case 'Q':
		Inform("Quitting!",FALSE);
		EndGame(TRUE);
		break;
	    case 0x0D:
	    case 0x0A:
		ClrScrn();
		done = TRUE;
		break;
	    }
	}
    }


usage()
    {
    int i, j;
    char line[80];

    fputs("--\n", stderr);
    fputs("Options:\n", stderr);
    fputs("    /display:<display type>    Specify display type\n", stderr);
    for (i = 0; o_dev[i].devnum; i++)
	{
	for (j = 0; j < sizeof(line)-1; j++)
	    line[j] = ' ';
	line[j] = '\0';
	strcpy(line+8, o_dev[i].devslash);
	line[strlen(line)] = ' ';
	DisplayInfo(i, line+16);
	strcat(line, "\n");
	fputs(line, stderr);
	}
    fputs("    /mouse:<mouse type>        Specify mouse type\n", stderr);
    for (i = 0; i_dev[i].devnum; i++)
	{
	for (j = 0; j < sizeof(line)-1; j++)
	    line[j] = ' ';
	line[j] = '\0';
	strcpy(line+8, i_dev[i].devslash);
	line[strlen(line)] = ' ';
	MouseInfo(i, line+16);
	strcat(line, "\n");
	fputs(line, stderr);
	}
    fputs("    /data:<data dir>           Specify drive/directory of game data files\n", stderr);
    fputs("    /noquiet                   Sound on (default)\n", stderr);
    fputs("    /quiet                     Sound off\n", stderr);
    fputs("    /dash                      Dashboard on (default)\n", stderr);
    fputs("    /nodash                    Dashboard off\n", stderr);
    fputs("    /fill                      Polygon fill on\n", stderr);
    fputs("    /nofill                    Polygon fill off (default)\n", stderr);
    fputs("    /show                      Show config information before starting\n", stderr);
    fputs("    /noshow                    Don't show config information\n", stderr);
	fputs("    /config                    Save configuration\n", stderr);
    fputs("    /?                         Show help\n", stderr);
	fputs("--\n", stderr);
    }


DisplayInfo(i, str)
int i;
char *str;
    {
    strcpy(str, o_dev[i].devdesc);
    strcat(str, " ");
    itoa(o_dev[i].devvres, str+strlen(str), 10);
    strcat(str, "x");
    itoa(o_dev[i].devhres, str+strlen(str), 10);
    strcat(str, " ");

    if (o_dev[i].devcolors > 2)
	{
        itoa(o_dev[i].devcolors, str+strlen(str), 10);
	strcat(str, " Color");
	}
    else if(o_dev[i].devcolors==2)
		strcat(str, "Monochrome");
	else strcat(str, "Gray Scale");
    }


MouseInfo(i, str)
int i;
char *str;
    {
    strcpy(str, i_dev[i].devdesc);
    }
/*---------------------------------------------------------------------- 
 *	tabsgen()
 *
 *	xai[],yai[] and cost[] table generator. Uses the sint[] table.
 *	angle between 0 and 255, sin and cos tables, x and y angle increments,
 *	Wall map, x and y location, corridor Height. Grid size is 256.		
 *---------------------------------------------------------------------- 
 */
tabsgen()
{
#if !defined(IBM_tabsgen)
int i;

for(i=0 ; i<256 ; i++)
  	{
	if(i < 192) cost[i] = sint[i + 64];
	else		cost[i] = sint[i - 192];
	xai[i] = cost[i] >> 4;
	yai[i] = sint[i] >> 4;
	}
SetRect(&Clip, 0, 0, Width, Height);
Clip.left = screenR.left;
Clip.right = screenR.right;
Clip.top = screenR.top;
Clip.bottom = screenR.bottom;
/*  ClipRect(&Clip);  */
#endif
}
/*----------------------------------------------------------------------*/
char *story[]={
			"Mankind has left the",
			"cradle of earth and",
			"is beginning to eye",
			"the galaxy. He has",
			"begun to colonize",
			"distant planets but has",
			"yet to meet any alien",
			"life forms.",
			"****",
			"Until now...",
			"****",
			"Press any key to begin",
			"the Adventure..."};
#define STORYLENGTH 13
int ocolor[]={0x00,0x01,0x02,0x03,0x04,0x05,0x14,0x07,
			0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f};
int ScrollInfo()
{
#if !defined(IBM_ScrollInfo)
int mx,my,mbt;
int i,width,centerx,centery,inc;
int qt = FALSE;
int color=0;
int pcolor;
int count=0;
int scolor[STORYLENGTH];
Rect m;

SetPort(scrport);
HideCursor();
if(colornum==16)
	{
	for(i=0;i<STORYLENGTH;i++)scolor[i]=0x39;
	scolor[0]=0x04;
	}
PenColor(realcolor[vINTWHITE]);
BackColor(realcolor[vBLACK]);

ClipRect(&sR);
EraseRect(&sR);
centerx=(sR.right-sR.left)>>1;
centery=(sR.bottom-sR.top)>>1;
centery-=(STORYLENGTH*15)>>1;
centery+=5;
TextAlign(1,2);
TextMode(zREPz);
if(colornum==16)
	LoadPalette(1,STORYLENGTH,scolor);
for(i=0;i<STORYLENGTH;i++)
	{
	if(colornum==16)PenColor(i+1);
	MoveTo( centerx, centery+15*i);
	DrawString(story[i]);
	}
qt=KeyPress(1);
if(!qt)DoBeammeSound();
mbt=0;
while(!mbt)
	{
	if(colornum==16)
		{
		scolor[color]=0x39;
		color++;
		if(color==STORYLENGTH)color=0;
		scolor[color]=0x04;
		LoadPalette(1,15,scolor);
		count=0;
		}
	mbt=KeyPress(0);
	}
if(colornum==16)
	{
	scolor[color]=0x39;
	LoadPalette(1,15,scolor);
	}
ClipRect(&sR);
for(i=0;i<sR.bottom;i+=8)
	{
	ScrollRect(&sR,0,-8);
	qt=KeyPress(1);
	}
if(colornum==16)
	LoadPalette(0,15,ocolor);
KillSound();
PenPattern(1);		    /* bits on */
ClipRect(&sR);
return(qt);
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
extern int oX;
extern int oY;
extern Rect DClip;
extern imageHeader* backImage;
extern unsigned int *xlateCGA;
extern BitMap *offBitMap;

InitDejaVu()
{
Rect r;
unsigned int s;
unsigned int i,j,k,bit;

SetPort(scrport);
HeapGreedy();
/*If CGA build xlate image table*/
if (scrport->portBMap->pixBits == 2 || scrport->portBMap->pixPlanes == 2)
	{
	xlateCGA=malloc(sizeof(int)*256);
	for(i=0;i<256;i++)
		{
		xlateCGA[i]=0;
		for(j=0,k=0; j<8; j++,k+=2)
			{
			bit=(1<<k)&(i<<j);
			xlateCGA[i] |= bit|(bit<<1);
			}
		swab(&xlateCGA[i],&xlateCGA[i],2);
		}
	}
SetRect(&DClip,0,0,415,263);
r.left=((sR.right-sR.left)-416)/2;
r.left=r.left/8;
oX=r.left=r.left*8;
r.right=r.left+415;
oY=r.top=((sR.bottom-sR.top)-264)/2;
r.bottom=r.top+263;
/*if 16 color EGA build 1 bit/pixel offscreen image/bitmap*/
if(is_EGAtype)
	{
	int pxWidth,pxHeight;
	
	pxWidth=1+DClip.right - DClip.left;
	pxHeight=1+DClip.bottom - DClip.top;
	if(NULL==(offBitMap = (BitMap *)malloc( sizeof(BitMap))))
		MemoryErr();
	(*offBitMap) = *(scrport->portBMap);
	offBitMap->devClass    = scrport->portBMap->devClass;
	offBitMap->devType     =0;     /* scrport->portBMap->devType;  */
	offBitMap->pixWidth    =pxWidth;
	offBitMap->pixHeight   =pxHeight;
	offBitMap->pixResX     =scrport->portBMap->pixResX;
	offBitMap->pixResY     =scrport->portBMap->pixResY;
	offBitMap->pixBits     =1;
	offBitMap->pixPlanes   =1;
	offBitMap->rowBytes    =(pxWidth*offBitMap->pixBits+7 )/8 ;
	if(NULL==(offBitMap->mapTable[0] =
		(rlmap *)malloc((sizeof(char *))*offBitMap->pixHeight))) 
			MemoryErr();
	if(NULL==(backImage=
	(imageHeader *)malloc(sizeof(imageHeader)+offBitMap->rowBytes*pxHeight)))
				MemoryErr();
	backImage->imWidth=pxWidth;
	backImage->imHeight=pxHeight;
	backImage->imAlign=0;
	backImage->imRowBytes=offBitMap->rowBytes;
	backImage->imBits=1;
	backImage->imPlanes=1;
	offBitMap->mapTable[0]->rowTable[0] =(char *)(backImage+1);
	InitRowTable(offBitMap, 0, 0, 0);     /*  */
	}
else
	if(0==(backImage=(imageHeader *)NewPtr(ImageSize(&DClip))))MemoryErr();
}
/*---------------------------------------------------------------------
 * initBitMap()
 * Set up the offscreen bit map for use in drawing the pictures.
 *---------------------------------------------------------------------
 */
BitMap *NewBitMap();
initBitMap()
{
#if !defined(IBM_initBitMap)
Rect r;
BitMap *offScreen;

if((metaPnt=(GrafPort *)malloc(sizeof(GrafPort)))==NULL)MemoryErr();
if ((offScreen=NewBitMap(&sR))==NULL)MemoryErr();
InitPort(metaPnt);
SetPort(metaPnt);
PortBitmap(offScreen);
SetOrigin(0,0);
r.top=0;
r.left=0;
r.right=sR.right-sR.left;
r.bottom=sR.bottom-sR.top;
FillRect(&r, 0);

SetPort(scrport);

return 0;
#endif
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
BitMap *EGA_BitMap(Rect *cr)
{
int i, j;
BitMap far *EGAScreen;
Rect brect;
long Off_Set;

brect=*cr;

brect.left-=cr->left;
brect.right-=cr->left;
brect.top-=cr->top;
brect.bottom-=cr->top;

EGAScreen = (bitmap far *)_fmalloc( sizeof(bitmap) );
if ( EGAScreen == NULL )
    { fputs("memory allocation error1\n", stderr); return (Ptr)NULL; }

EGAScreen->devClass    =scrport->portBMap->devClass;
EGAScreen->devType     =scrport->portBMap->devType;
/* EGAScreen->devMode	  =0; */
/* EGAScreen->devRsvd	  =0; */
EGAScreen->pixWidth    =brect.right+1;
EGAScreen->pixHeight   =brect.bottom+1;
EGAScreen->pixResX     =scrport->portBMap->pixResX;
EGAScreen->pixResY     =scrport->portBMap->pixResY;
EGAScreen->pixBits     =scrport->portBMap->pixBits;
EGAScreen->pixPlanes   =scrport->portBMap->pixPlanes;
EGAScreen->rowBytes    =( EGAScreen->pixWidth*EGAScreen->pixBits+7 )/8;

for (i=0; i<EGAScreen->pixPlanes; i++)
    {
    EGAScreen->mapTable[i] =
	(rlmap far *)_fmalloc((sizeof(char far *))*EGAScreen->pixHeight);
    if ( EGAScreen->mapTable[i] == NULL )
	{ fputs("memory allocation error2\n", stderr); return NULL; }

    for (j=0; j<EGAScreen->pixHeight; j++)
	EGAScreen->mapTable[i]->rowTable[j]=
	    scrport->portBMap->mapTable[i]->rowTable[j+cr->top]+cr->left/8;
    }
return(EGAScreen);
}



/*---------------------------------------------------------------------
 * initEGA_BitMap()
 * Set up the EGA bit maps for use in drawing the sensor.
 *---------------------------------------------------------------------
 */
initEGA_BitMap()
{
Rect r;
r.top=0;
r.left=0;
r.right=sR.right-sR.left;
r.bottom=sR.bottom-sR.top;


SetDisplay(GrafPg0);
SetBitmap (GrafPg0);
GetPort(&scrport);
if (	  (   EGA_board0=EGA_BitMap(&sR)   )	    ==NULL	 )
    return -1;
SetDisplay(GrafPg1);
SetBitmap (GrafPg1);
GetPort(&scrport);
if (	  (   EGA_board1=EGA_BitMap(&sR)   )	    ==NULL	 )
    return -1;


if(  NIL==(metaPnt=(GrafPort *)malloc( sizeof(GrafPort) ))  )
    return -1;

SetDisplay(GrafPg0);
SetBitmap (GrafPg0);
GetPort(&scrport);

InitPort(metaPnt);
SetPort(metaPnt);
PortBitmap(EGA_board1);
SetOrigin(0,0);
FillRect(&r, 0);

SetPort(scrport);

return 0;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
LimitJMouse(xMin,yMin,xMax,yMax,xCenter,yCenter)
int xMin, yMin, xMax, yMax;
int xCenter, yCenter;
	{
	union REGS regs;

	regs.x.ax = 35;
	regs.x.si = (xMin - xCenter) * 16 + MouseScaleX-1;
	regs.x.si = (int)regs.x.si / MouseScaleX;
	regs.x.di = (xMax - xCenter) * 16 + MouseScaleX-1;
	regs.x.di = (int)regs.x.di / MouseScaleX;
	regs.x.cx = (yMin - yCenter) * 16 + MouseScaleY-1;
	regs.x.cx = (int)regs.x.cx / MouseScaleY;
	regs.x.dx = (yMax - yCenter) * 16 + MouseScaleY-1;
	regs.x.dx = (int)regs.x.dx / MouseScaleY;
	int86(0x33, &regs, &regs);
	}
