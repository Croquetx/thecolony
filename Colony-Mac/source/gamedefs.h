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
 * gamedefs.h
 * this file contains the gloabal variable definitions. The prefix EXT
 * is declared as an extern in all files except Gmain.c where it is
 * declared null. This has the effect of having the globals defined only in
 * foobar and extern everywhere else.
 *----------------------------------------------------------------------
 */
#define VARIABLE
#define max(x,y) ((x>y)?x:y)
#define min(x,y) ((x<y)?x:y)
#define abs(x) (((x)>0)?(x):-(x))
#define nabs(x) (((x)>0)?-(x):(x))

#define NIL 0L
#define TRUE 1
#define FALSE 0
/*menu ID's*/
#define LASTMENU 4
#define APPLEMENU 1
#define FILEMENU 256
#define EDITMENU 257
#define OPTIONS 258

#define SURFSIZE 8
typedef int	Point3D[3];
typedef int Surf3D[SURFSIZE];	
EXT Handle fl_icon[5];
EXT Rect fl_rect;
typedef struct{
	int points;		/*number of points					*/
	Point3D *pnt;	/*[0]x,y,z [1]x,y,z ...				*/
	Point3D *copy;	/*[0]x,y,z,flag [1]x,y,z,flag...	*/
	int surfaces;	/*number of surfaces				*/
	Surf3D *surface;/*[0][0]number of points			*/
					/*[0][1]point 1						*/
					/*[0][2]point 2						*/
					/*.....								*/
					/*[1][0]number of points			*/
					/*.....								*/
	int *vsurface;	/*array of visible surface flags	*/
	int visible;
	int fill;
	}Prism;

EXT Prism *Robot[50];
EXT int *drX[32];
EXT int *drY[32];
EXT unsigned char *dirXY[32];
EXT unsigned char *Wall[32];
EXT unsigned char *robotarray[32];
EXT unsigned char *foodarray[32];
EXT unsigned int count;/*just a cycle counter for use by the game*/
EXT union{
	char (*data)[31][31][5][5];
	char *buffer;
	}map;
EXT int *rtable;/*a perspective lookup table*/
EXT char *buffer;/*the map buffer used for unpacking maps*/
EXT int notDone; /*flag indicates we are still playing*/
EXT int flip;	/*flag indictates if the floor is on the ceiling*/
EXT int change; /*indicates a need to recalculate the walls*/
EXT int speed;  /*keyboard control speed (1-5)*/
EXT int speedshift;/*keyboard control*/
EXT int level; /*map number*/
/*----menu array*/
EXT MenuHandle myMenus[LASTMENU];
EXT GrafPtr theWindow,infoWindow,moveWindow;
EXT WindowRecord infowRecord,movewRecord,wRecord;
EXT EventRecord key;
EXT Rect Clip;
EXT Rect rClip;
EXT int cellx,celly;
EXT CursHandle Curs;
EXT Point myPt;

/*xindex,yindex are the current locations in the Wall grid.		*/
EXT int  xindex,yindex;
EXT int  rox,roy;
extern int sint[];
EXT int *cost;
EXT int *xai, *yai;
EXT int tsin,tcos;
EXT int ow;
typedef struct {
	unsigned char ang;
	unsigned char look;
	int lookx;
	int delta;
	int xloc;
	int yloc;
	int xindex;
	int yindex;
	int xmx,xmn;
	int zmx,zmn;
	long power[3];
	int type;
	int dx,dy;
	int dist;
	} Locate;

EXT Locate Me;
EXT int epower[3];

EXT int robotnum;
EXT int crosshair;
EXT int lights;
EXT int insight;
EXT int soundon;
EXT int Mac512;
EXT int polyfill;
EXT int cshoot;/*cursor shooting flag*/
EXT int fadein;
EXT int Mac2;
EXT int gametest;
typedef struct{
	int type;
	int visible;
	int alive;
	Rect clip;
	int count;
	Locate where;
	int opcode;
	int counter;
	int time;
	int grow;
	void (*make)();
	void (*think)();
	}Thing;
	
#define WHITE 	0
#define LTGRAY 	1
#define GRAY 	2
#define DKGRAY 	3
#define BLACK 	4
#define CLEAR 	5

#define NORTH 	0
#define EAST 	1
#define WEST 	2
#define SOUTH 	3
#define CENTER	4

#define DOOR 		2
#define WINDOW 		3
#define SHELVES		4
#define UPSTAIRS 	5
#define DNSTAIRS 	6
#define CHAR		7
#define GLYPH		8
#define ELEVATOR	9
#define TUNNEL		10
#define AIRLOCK		11
#define COLOR		12

#define SMHOLEFLR	1
#define LGHOLEFLR	2
#define SMHOLECEIL 	3
#define LGHOLECEIL	4
#define HOTFOOT		5

EXT int direction;

EXT int maxrob;
EXT int maxobjects;
EXT int allgrow;


#define EYE 		1
#define PYRAMID 	2
#define CUBE 		3
#define UPYRAMID	4

#define F_EYE 		5
#define F_PYRAMID 	6
#define F_CUBE 		7
#define F_UPYRAMID	8

#define S_EYE 		9
#define S_PYRAMID 	10
#define S_CUBE 		11
#define S_UPYRAMID	12

#define M_EYE 		13
#define M_PYRAMID 	14
#define M_CUBE 		15
#define M_UPYRAMID	16

#define QUEEN		17
#define DRONE		18
#define SOLDIER		19
#define SNOOP		20

#define BASEOBJECT	20

#define DESK		21
#define PLANT		22
#define CCHAIR 		23
#define BED			24
#define TABLE		25
#define COUCH		26
#define CHAIR		27
#define TV			28
#define SCREEN		29
#define CONSOLE		30
#define POWERSUIT	31
#define FORKLIFT	32
#define CRYO		33
#define BOX1		34
#define BOX2		35
#define TELEPORT	36
#define DRAWER		37
#define TUB			38
#define	SINK		39
#define TOILET		40
#define BENCH		41
#define BBED		42
#define PTOILET		43
#define CBENCH		44
#define PROJECTOR	45
#define REACTOR		46
#define	FWALL		48
#define CWALL		49
#define MAXROB 		48
#define MENUM 		101
EXT int game;

#define BATTLE		1
#define COLONY		2
#define SPACEWAR	3

#define MAXQUAD 15
EXT Locate (*pwhere)[4][4][MAXQUAD];
EXT union{
	Locate (*data)[4][4][MAXQUAD];
	char *buffer;
	}pbattle;
EXT int mountains[256];
EXT Rect screenR;
EXT Rect rScreen;
#define Floor 160

#ifdef VARIABLE
EXT int Width;
EXT int Height;
EXT int centerX;
EXT int centerY;
EXT int cx;
EXT int cy;
#else
#define Width 416
#define Height 306
#define centerX 208
#define centerY 153
#endif

EXT int doorsound;

EXT int xmas;

/*----------------------------------------------------------------------*/
/*save these variables to save the game:								*/
/*----------------------------------------------------------------------*/
EXT struct leveldata{
	unsigned char visit;/*have we been here before? If yes use the data below, else make it up*/
	unsigned char queen;/*is the queen alive?*/
	unsigned char object[BASEOBJECT+1];/*how many of each object is there?*/
	unsigned char count;
	unsigned char size;/*number of changes in each map*/
	char location[10][3]; /*which wall is changed?*/
	char  data[10][5];	/*the saved data*/
	}leveldata[8];
EXT Thing *Object;
EXT struct patchstrct
	{
	struct {
		unsigned char level;
		unsigned char xindex;
		unsigned char yindex;
		}from;
	struct {
		unsigned char level;
		unsigned char xindex;
		unsigned char yindex;
		int xloc;
		int yloc;
		unsigned char ang;
		}to;
	unsigned char type;
	char mapdata[5];
	} *patch;
EXT int patchnum;
struct passpatch
	{
	unsigned char level;
	unsigned char xindex;
	unsigned char yindex;
	int xloc;
	int yloc;
	unsigned char ang;
	};	
EXT char decode1[4];
EXT char decode2[4];
EXT char decode3[4];
EXT int unlocked;
EXT struct passpatch carrypatch[2];
EXT int carrytype;
EXT int armor;
EXT int weapons;
EXT int armor2;
EXT int weapons2;
EXT int fl;
EXT int corestate[2];
EXT int coreheight[2];
EXT int corepower[3];
EXT int coreindex;
EXT int orbit;
/*battle zone*/
EXT Locate bfight[16];
EXT Locate Enter,Ship,Proj;
EXT int projon;/*switch to turn the projectile on*/
EXT int pcount;
