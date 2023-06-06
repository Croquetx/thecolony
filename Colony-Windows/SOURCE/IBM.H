#define NOT_MAC 	/*    */


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>


/*  metawindows stuff  */

#include <GRconst.h>
#include <GRports.h>
/* #include <GRfonts.h> */
#include <GRextrn.h>
EXT int GrafixCard, CommPort;


/* MAC to IBM stuff  */

typedef  char far *Ptr;        /*  I-81    */
typedef  Ptr far *Handle;
typedef  long Size;

/*
typedef unsigned char STRING[255];
typedef STRING Str255;
typedef Str255 *StringPtr;
typedef StringPtr *StringHandle;
*/
typedef struct
    {
    int h;
    int v;
    }Point;

typedef struct {
    int left;
    int top;
    int right;
    int bottom;}Rect;

typedef Rect WindowRecord;
typedef Rect *WindowPtr;


/*
typedef WindowRecord *WindowPeek;

typedef struct {
    Rect	    scr_rect;
    int 	    scr_orig_x;
    int 	    scr_orig_y;
    int 	    type;
} WindowRecord;
*/

#define MAX_NUM_WINDOWS 10
Rect *WindowList[MAX_NUM_WINDOWS];

#define NewPtr(x) malloc((unsigned int)(x))
#define DisposPtr free
#define Random() (rand()>16000?rand():-rand())

typedef patRcd Pattern;
typedef event EventRecord;

typedef metaPort GrafPort;
typedef GrafPort far *GrafPtr;	    /*	I-148  */

typedef bitmap BitMap;
typedef map rlmap;
#define map ibm_map		/* David used map as a name */


/*  #define patXor  2  */


/* Randy's stuff  */
#define do_nothing()
EXT mapArray far in_cur_map;
EXT mapArray far out_cur_map;
EXT Rect sR;
EXT float aspect;
EXT int pix_per_Qinch_x, pix_per_Qinch_y;
EXT Rect info_Rect, move_Rect, the_Rect;
EXT int open_mem_error;


#undef max
#undef min

EXT GrafPtr scrport;				 /*   far Pointer  */
EXT GrafPtr metaPnt;			      /*   far Pointer	*/
EXT BitMap  far *EGA_board0, far *EGA_board1;
EXT my_graf_page;


EXT unsigned char HardwareType;

EXT unsigned char vlight, vdark;
EXT unsigned char vwall_Light, vwall_noLight;

EXT unsigned char MonoCrome, WhiteBackGround, is_EGAtype;
EXT unsigned int color_cursor, color_wall;
EXT int far *randnum;

EXT int isMouse, QuitPlease;

EXT Rect nearClipRect;

#define MONOCHROME	0
#define LINEFILLCOLOR 	1
#define FILLCOLOR	2
#define BACKCOLOR	3
#define LINECOLOR	4
#define PATTERN		5

#define MAXROB_COLOR  100	/*  should be in gamedefs with robot constants */
extern char lsColor[MAXROB_COLOR][6];

typedef struct{
	Rect Rect;
	unsigned char *strInside;
	unsigned char *strOutside;
	unsigned char strColor;
	unsigned char buttColor;
	char buttType;
	}buttonStruct;

#define patCopy zREPz
#define srcCopy zREPz
#define patOr	zORz
#define srcOr	zORz
#define patXor	zXORz
#define srcXor	zXORz
#define patBic	zNANDz
#define srcBic	zNANDz

int my_write(int fd, unsigned char *buffer, long length);
int my_read(int fd, unsigned char *buffer, long length);
int my_read_loc(int fd, unsigned char *buffer, long length, long mark);
