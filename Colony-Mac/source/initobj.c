/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
#define EXT extern 
#include "cgamedefs.h"
#include "colordef.h"
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
Prism Tubparts[2];
Prism Toiletparts[5];
Prism Sinkparts[3];
Prism Reactorparts[3];
int tub[8][3]={		{-128, 128,  0},
					{   0, 128,  0},
					{   0,-128,  0},
					{-128,-128,  0},
					{-128, 128, 70},
					{   0, 128, 70},
					{   0,-128, 70},
					{-128,-128, 70}};

int tub2[8][3];
unsigned char  tubv[5];

unsigned char tubsurface[5][SURFSIZE]={{c_tub,4,0,3,7,4},
							 {c_tub,4,3,2,6,7},
							 {c_tub,4,1,0,4,5},
							 {c_tub,4,2,1,5,6},
							 {c_tub,4,7,6,5,4}};

int dtub[6][3]={	{ -16, 112,70},
					{  -8,   0,70},
					{ -16,-112,70},
					{-112,-112,70},
					{-120,   0,70},
					{-112, 112,70}};
int dtub2[6][3];
unsigned char  dtubv[1];
unsigned char  dtubsurface[1][SURFSIZE]={{c_water,6,5,4,3,2,1,0}};

int atoilet[8][3]={	{-128, 45, 30},
					{-100, 45, 30},
					{-100,-45, 30},
					{-128,-45, 30},
					{-128, 45,100},
					{-100, 45,100},
					{-100,-45,100},
					{-128,-45,100}};

int atoilet2[8][3];
unsigned char  atoiletv[5];

int btoilet[12][3]={ {-100, 20,50},
					 { -60, 40,50},
					 { -20, 20,50},
					 { -20,-20,50},
					 { -60,-40,50},
					 {-100,-20,50},
					 
					 { -80, 10, 0},
					 { -60, 20, 0},
					 { -40, 10, 0},
					 { -40,-10, 0},
					 { -60,-20, 0},
					 { -80,-10, 0}};

int btoilet2[12][3];
unsigned char  btoiletv[7];
unsigned char  btoiletsurface[7][SURFSIZE]={ 	
									{c_toilet,4,0,1,7,6},
									{c_toilet,4,1,2,8,7},
									{c_toilet,4,2,3,9,8},
									{c_toilet,4,3,4,10,9},
									{c_toilet,4,4,5,11,10},
									{c_toilet,4,5,0,6,11},
									{c_toilet,6,5,4,3,2,1}};

int ctoilet[6][3]={ {-95, 15,50},
					 { -60, 35,50},
					 { -25, 15,50},
					 { -25,-15,50},
					 { -60,-35,50},
					 {-95,-15,50}};

int ctoilet2[6][3];
unsigned char  ctoiletv[1];

int dtoilet[6][3]={ {-100, 20,50},
					 {-100, 40,90},
					 {-100, 20,130},
					 {-100,-20,130},
					 {-100,-40,90},
					 {-100,-20,50}};
int dtoilet2[6][3];
unsigned char  dtoiletsurface[1][SURFSIZE]={{c_toiletseat,6,5,4,3,2,1,0}};
unsigned char  dtoiletv[1];

int etoilet[4][3]={ {-128,-128,20},
					{-128,-128,200},
					{ 128,-128,200},
					{ 128,-128,20}};
int etoilet2[4][3];
unsigned char  etoiletv[1];
unsigned char etoiletsurface[1][SURFSIZE]={{c_barrier,4,0,1,2,3}};

int sink[8][3]={	{-128, 50, 70},
					{ -50, 50, 90},
					{ -50,-50, 90},
					{-128,-50, 70},
					{-128, 50,110},
					{ -50, 50,110},
					{ -50,-50,110},
					{-128,-50,110}};

int sink2[8][3];
unsigned char  sinkv[5];

int dsink[6][3]={	{ -55,   0,110},
					{ -60, -45,110},
					{-118, -45,110},
					{-123,   0,110},
					{-118,  45,110},
					{ -60,  45,110}};
int dsink2[6][3];
unsigned char  dsinkv[1];

int sinkmirror[4][3]={  {-128, 65, 130},
					{-128,-65,130},
					{-128, 65,250},
					{-128,-65,250}};

int sinkmirror2[4][3];
unsigned char  sinkmirrorv[1];
unsigned char  sinkmirrorsurface[1][SURFSIZE]={{c_mirror,4,1,0,2,3}};
					 
int core[12][3]={ 
					 { -40, 20,288},
					 {   0, 40,288},
					 {  40, 20,288},
					 {  40,-20,288},
					 {   0,-40,288},
					 { -40,-20,288},
					 
					 { -40, 20, 32},
					 {   0, 40, 32},
					 {  40, 20, 32},
					 {  40,-20, 32},
					 {   0,-40, 32},
					 { -40,-20, 32}};

int core2[12][3];
unsigned char  coresurface[7][SURFSIZE]={ 	
									{c_ccore,4,0,1,7,6},
									{c_ccore,4,1,2,8,7},
									{c_ccore,4,2,3,9,8},
									{c_ccore,4,3,4,10,9},
									{c_ccore,4,4,5,11,10},
									{c_ccore,4,5,0,6,11},
									{c_ccore,6,5,4,3,2,1}};
unsigned char  corev[7];
int areactor[8][3]={	{-128, 128,  0},
					{ 128, 128,  0},
					{ 128,-128,  0},
					{-128,-128,  0},
					{-128, 128, 32},
					{ 128, 128, 32},
					{ 128,-128, 32},
					{-128,-128, 32}};

int areactor2[8][3];
unsigned char  areactorv[6];

int breactor[8][3]={{-128, 128,288},
					{ 128, 128,288},
					{ 128,-128,288},
					{-128,-128,288},
					{-128, 128,320},
					{ 128, 128,320},
					{ 128,-128,320},
					{-128,-128,320}};

int breactor2[8][3];
unsigned char  breactorv[6];
unsigned char  breactorsurface[6][SURFSIZE]={
							{c_reactor,4,0,3,7,4},
							{c_reactor,4,3,2,6,7},
							{c_reactor,4,1,0,4,5},
							{c_reactor,4,2,1,5,6},
							{c_reactor,4,7,6,5,4},
							{c_reactor,4,0,1,2,3}};
							

int trunk[12][3]={   { -20, 10,32},
					 {   0, 20,32},
					 {  20, 10,32},
					 {  20,-10,32},
					 {   0,-20,32},
					 { -20,-10,32},
					 
					 { -20, 10, 0},
					 {   0, 20, 0},
					 {  20, 10, 0},
					 {  20,-10, 0},
					 {   0,-20, 0},
					 { -20,-10, 0}};

int tree[7][3]={ 
					 {   0,  0,288},					 
					 { -60, 30, 32},
					 {   0, 60, 32},
					 {  60, 30, 32},
					 {  60,-30, 32},
					 {   0,-60, 32},
					 { -60,-30, 32}};
int tree2[7][3];
unsigned char  treesurface[6][SURFSIZE]=
					{{c_xmas,3,0,2,1},
					 {c_xmas,3,0,3,2},
					 {c_xmas,3,0,4,3},
					 {c_xmas,3,0,5,4},
					 {c_xmas,3,0,6,5},
					 {c_xmas,3,0,1,6}};
unsigned char  treev[6];
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
InitBathroom(RobotSize)
int RobotSize[];
{
Robot[TUB] = Tubparts;
Robot[TUB][0].points=8;
Robot[TUB][0].pnt=tub;
Robot[TUB][0].copy=tub2;
Robot[TUB][0].surfaces=5;
Robot[TUB][0].vsurface=tubv;
Robot[TUB][0].surface=tubsurface;

Robot[TUB][1].points=6;
Robot[TUB][1].pnt=dtub;
Robot[TUB][1].copy=dtub2;
Robot[TUB][1].surfaces=1;
Robot[TUB][1].vsurface=dtubv;
Robot[TUB][1].surface=dtubsurface;

RobotSize[TUB]=2;

Robot[TOILET] = Toiletparts;
Robot[TOILET][0].points=8;
Robot[TOILET][0].pnt=atoilet;
Robot[TOILET][0].copy=atoilet2;
Robot[TOILET][0].surfaces=5;
Robot[TOILET][0].vsurface=atoiletv;
Robot[TOILET][0].surface=tubsurface;

Robot[TOILET][1].points=12;
Robot[TOILET][1].pnt=btoilet;
Robot[TOILET][1].copy=btoilet2;
Robot[TOILET][1].surfaces=7;
Robot[TOILET][1].vsurface=btoiletv;
Robot[TOILET][1].surface=btoiletsurface;

Robot[TOILET][2].points=6;
Robot[TOILET][2].pnt=ctoilet;
Robot[TOILET][2].copy=ctoilet2;
Robot[TOILET][2].surfaces=1;
Robot[TOILET][2].vsurface=ctoiletv;
Robot[TOILET][2].surface=dtubsurface;

Robot[TOILET][3].points=6;
Robot[TOILET][3].pnt=dtoilet;
Robot[TOILET][3].copy=dtoilet2;
Robot[TOILET][3].surfaces=1;
Robot[TOILET][3].vsurface=dtoiletv;
Robot[TOILET][3].surface=dtoiletsurface;

Robot[TOILET][4].points=4;
Robot[TOILET][4].pnt=etoilet;
Robot[TOILET][4].copy=etoilet2;
Robot[TOILET][4].surfaces=1;
Robot[TOILET][4].vsurface=etoiletv;
Robot[TOILET][4].surface=etoiletsurface;
RobotSize[TOILET]=5;

Robot[SINK] = Sinkparts;
Robot[SINK][0].points=8;
Robot[SINK][0].pnt=sink;
Robot[SINK][0].copy=sink2;
Robot[SINK][0].surfaces=5;
Robot[SINK][0].vsurface=sinkv;
Robot[SINK][0].surface=tubsurface;

Robot[SINK][1].points=6;
Robot[SINK][1].pnt=dsink;
Robot[SINK][1].copy=dsink2;
Robot[SINK][1].surfaces=1;
Robot[SINK][1].vsurface=dsinkv;
Robot[SINK][1].surface=dtubsurface;

Robot[SINK][2].points=4;
Robot[SINK][2].pnt=sinkmirror;
Robot[SINK][2].copy=sinkmirror2;
Robot[SINK][2].surfaces=1;
Robot[SINK][2].vsurface=sinkmirrorv;
Robot[SINK][2].surface=sinkmirrorsurface;
RobotSize[SINK]=3;

Robot[REACTOR]=Reactorparts;
Robot[REACTOR][0].points=12;
Robot[REACTOR][0].pnt=core;
Robot[REACTOR][0].copy=core2;
Robot[REACTOR][0].surfaces=7;
Robot[REACTOR][0].vsurface=corev;
Robot[REACTOR][0].surface=coresurface;

Robot[REACTOR][1].points=8;
Robot[REACTOR][1].pnt=areactor;
Robot[REACTOR][1].copy=areactor2;
Robot[REACTOR][1].surfaces=6;
Robot[REACTOR][1].vsurface=areactorv;
Robot[REACTOR][1].surface=breactorsurface;

Robot[REACTOR][2].points=8;
Robot[REACTOR][2].pnt=breactor;
Robot[REACTOR][2].copy=breactor2;
Robot[REACTOR][2].surfaces=6;
Robot[REACTOR][2].vsurface=breactorv;
Robot[REACTOR][2].surface=breactorsurface;
RobotSize[REACTOR]=3;
}

/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "bed.h"
InitBed(RobotSize)
int RobotSize[];
{
Robot[BED] = Bed;
Robot[BED][0].points=4;
Robot[BED][0].pnt=BPost;
Robot[BED][0].copy=BPost2;
Robot[BED][0].surfaces=1;
Robot[BED][0].surface=BPostsurface;
Robot[BED][0].vsurface=BPostv;

Robot[BED][1].points=8;
Robot[BED][1].pnt=Blanket;
Robot[BED][1].copy=Blanket2;
Robot[BED][1].surfaces=4;
Robot[BED][1].surface=Blanketsurface;
Robot[BED][1].vsurface=Blanketv;

Robot[BED][2].points=8;
Robot[BED][2].pnt=Sheet;
Robot[BED][2].copy=Sheet2;
Robot[BED][2].surfaces=3;
Robot[BED][2].surface=Sheetsurface;
Robot[BED][2].vsurface=Sheetv;
RobotSize[BED]=3;

Robot[BBED] = BBed;
Robot[BBED][0].points=4;
Robot[BBED][0].pnt=BBPost;
Robot[BBED][0].copy=BBPost2;
Robot[BBED][0].surfaces=1;
Robot[BBED][0].surface=BPostsurface;
Robot[BBED][0].vsurface=BBPostv;

Robot[BBED][1].points=8;
Robot[BBED][1].pnt=BBlanket;
Robot[BBED][1].copy=BBlanket2;
Robot[BBED][1].surfaces=4;
Robot[BBED][1].surface=Blanketsurface;
Robot[BBED][1].vsurface=BBlanketv;

Robot[BBED][2].points=8;
Robot[BBED][2].pnt=BSheet;
Robot[BBED][2].copy=BSheet2;
Robot[BBED][2].surfaces=3;
Robot[BBED][2].surface=Sheetsurface;
Robot[BBED][2].vsurface=BSheetv;
RobotSize[BBED]=3;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */

Prism Box1parts[1];
Prism Box2parts[2];
int box1[8][3]={	{-50, 50,  0},
					{ 50, 50,  0},
					{ 50,-50,  0},
					{-50,-50,  0},
					{-50, 50,100},
					{ 50, 50,100},
					{ 50,-50,100},
					{-50,-50,100}};

int box12[8][3];
unsigned char  box1v[5];
unsigned char box1surface[5][SURFSIZE]={{c_box1,4,0,3,7,4},
							{c_box1,4,3,2,6,7},
							{c_box1,4,1,0,4,5},
							{c_box1,4,2,1,5,6},
							{c_box1,4,7,6,5,4}};
int box2[8][3]={	{-50, 50,100},
					{ 50, 50,100},
					{ 50,-50,100},
					{-50,-50,100},
					{-50, 50,200},
					{ 50, 50,200},
					{ 50,-50,200},
					{-50,-50,200}};

int box22[8][3];
unsigned char  box2v[4];
unsigned char  box2surface[4][SURFSIZE]={{c_box2,4,0,3,7,4},
							{c_box2,4,3,2,6,7},
							{c_box2,4,1,0,4,5},
							{c_box2,4,2,1,5,6}};

Prism Benchparts[1];
int bench[8][3]={	{-60, 128,  0},
					{ 60, 128,  0},
					{ 60,-128,  0},
					{-60,-128,  0},
					{-60, 128,120},
					{ 60, 128,120},
					{ 60,-128,120},
					{-60,-128,120}};

int bench2[8][3];
unsigned char  benchv[5];

Prism cBenchparts[2];
int cbench[8][3]={	{-60, 60,  0},
					{ 60, -60,  0},
					{ 60,-128,  0},
					{-60,-128,  0},
					{-60, 60,120},
					{ 60, -60,120},
					{ 60,-128,120},
					{-60,-128,120}};

int cbench2[8][3];
unsigned char  cbenchv[5];

int dbench[8][3]={	{- 60, 60,  0},
					{ 128, 60,  0},
					{ 128,-60,  0},
					{  60,-60,  0},
					{- 60, 60,120},
					{ 128, 60,120},
					{ 128,-60,120},
					{  60,-60,120}};

int dbench2[8][3];
unsigned char  dbenchv[5];
unsigned char benchsurface[5][SURFSIZE]={{c_bench,4,0,3,7,4},
							{c_bench,4,3,2,6,7},
							{c_bench,4,1,0,4,5},
							{c_bench,4,2,1,5,6},
							{c_benchtop,4,7,6,5,4}};

/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
InitBox(RobotSize)
int RobotSize[];
{
Robot[BOX1] = Box1parts;
Robot[BOX1][0].points=8;
Robot[BOX1][0].pnt=box1;
Robot[BOX1][0].copy=box12;
Robot[BOX1][0].surfaces=5;
Robot[BOX1][0].surface=box1surface;
Robot[BOX1][0].vsurface=box1v;
RobotSize[BOX1]=1;

Robot[BOX2] = Box2parts;
Robot[BOX2][1].points=8;
Robot[BOX2][1].pnt=box1;
Robot[BOX2][1].copy=box12;
Robot[BOX2][1].surfaces=5;
Robot[BOX2][1].surface=box1surface;
Robot[BOX2][1].vsurface=box1v;

Robot[BOX2][0].points=8;
Robot[BOX2][0].pnt=box2;
Robot[BOX2][0].copy=box22;
Robot[BOX2][0].surfaces=4;
Robot[BOX2][0].surface=box2surface;
Robot[BOX2][0].vsurface=box1v;
RobotSize[BOX2]=1;

Robot[BENCH] = Benchparts;
Robot[BENCH][0].points=8;
Robot[BENCH][0].pnt=bench;
Robot[BENCH][0].copy=bench2;
Robot[BENCH][0].surfaces=5;
Robot[BENCH][0].surface=benchsurface;
Robot[BENCH][0].vsurface=benchv;
RobotSize[BENCH]=1;

Robot[CBENCH] = cBenchparts;
Robot[CBENCH][0].points=8;
Robot[CBENCH][0].pnt=cbench;
Robot[CBENCH][0].copy=cbench2;
Robot[CBENCH][0].surfaces=5;
Robot[CBENCH][0].surface=benchsurface;
Robot[CBENCH][0].vsurface=cbenchv;

Robot[CBENCH][1].points=8;
Robot[CBENCH][1].pnt=dbench;
Robot[CBENCH][1].copy=dbench2;
Robot[CBENCH][1].surfaces=5;
Robot[CBENCH][1].surface=benchsurface;
Robot[CBENCH][1].vsurface=dbenchv;

RobotSize[CBENCH]=2;

}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "CChair.h"
InitCChair(RobotSize)
int RobotSize[];
{
Robot[CCHAIR] = CChair;
Robot[CCHAIR][0].points=4;
Robot[CCHAIR][0].pnt=Cseat;
Robot[CCHAIR][0].copy=Cseat2;
Robot[CCHAIR][0].surfaces=1;
Robot[CCHAIR][0].surface=Cseatsurface;
Robot[CCHAIR][0].vsurface=Cseatv;

Robot[CCHAIR][1].points=4;
Robot[CCHAIR][1].pnt=Carmleft;
Robot[CCHAIR][1].copy=Carmleft2;
Robot[CCHAIR][1].surfaces=1;
Robot[CCHAIR][1].surface=Carmleftsurface;
Robot[CCHAIR][1].vsurface=Carmleftv;

Robot[CCHAIR][2].points=4;
Robot[CCHAIR][2].pnt=Carmrite;
Robot[CCHAIR][2].copy=Carmrite2;
Robot[CCHAIR][2].surfaces=1;
Robot[CCHAIR][2].surface=Carmritesurface;
Robot[CCHAIR][2].vsurface=Carmritev;

Robot[CCHAIR][3].points=4;
Robot[CCHAIR][3].pnt=Cback;
Robot[CCHAIR][3].copy=Cback2;
Robot[CCHAIR][3].surfaces=1;
Robot[CCHAIR][3].surface=Cbacksurface;
Robot[CCHAIR][3].vsurface=Cbackv;

Robot[CCHAIR][4].points=8;
Robot[CCHAIR][4].pnt=Cbase;
Robot[CCHAIR][4].copy=Cbase2;
Robot[CCHAIR][4].surfaces=4;
Robot[CCHAIR][4].surface=Cbasesurface;
Robot[CCHAIR][4].vsurface=Cbasev;
RobotSize[CCHAIR]=5;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */

Prism Console[1];

int Cons[8][3]={	{-5, 5,   0},
					{ 5, 5,   0},
					{ 5,-5,   0},
					{-5,-5,   0},
					{-100, 70,100},
					{-35, 70,140},
					{-35,-70,140},
					{-100,-70,100}};

int Cons2[8][3];
unsigned char  Consv[5];
unsigned char  Conssurface[5][SURFSIZE]={{c_console,4,4,0,3,7},
						{c_console,4,7,3,2,6},
						{c_console,4,5,1,0,4},
						{c_console,4,6,2,1,5},
						{c_consoletop,4,7,6,5,4}};

/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
InitConsole(RobotSize)
int RobotSize[];
{
Robot[CONSOLE] = Console;
Robot[CONSOLE][0].points=8;
Robot[CONSOLE][0].pnt=Cons;
Robot[CONSOLE][0].copy=Cons2;
Robot[CONSOLE][0].surfaces=5;
Robot[CONSOLE][0].surface=Conssurface;
Robot[CONSOLE][0].vsurface=Consv;
RobotSize[CONSOLE]=1;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
Prism Couchparts[4];
Prism Chairparts[4];
int acouch[8][3]={	{-50, 150,  0},
					{ 50, 150,  0},
					{ 50,-150,  0},
					{-50,-150,  0},
					{-50, 150,50},
					{ 50, 150,50},
					{ 50,-150,50},
					{-50,-150,50}};

int acouch2[8][3];
unsigned char  acouchv[5];

int bcouch[8][3]={	{-80, 150,  0},
					{-45, 150,  0},
					{-45,-150,  0},
					{-80,-150,  0},
					{-80, 150,120},
					{-55, 150,120},
					{-55,-150,120},
					{-80,-150,120}};

int bcouch2[8][3];
unsigned char  bcouchv[5];

int ccouch[8][3]={	{-70, 170,  0},
					{ 50, 170,  0},
					{ 50, 150,  0},
					{-70, 150,  0},
					{-70, 170,80},
					{ 50, 170,80},
					{ 50, 150,80},
					{-70, 150,80}};

int ccouch2[8][3];
unsigned char  ccouchv[5];

int dcouch[8][3]={	{-70,-150,  0},
					{ 50,-150,  0},
					{ 50,-170,  0},
					{-70,-170,  0},
					{-70,-150,80},
					{ 50,-150,80},
					{ 50,-170,80},
					{-70,-170,80}};

int dcouch2[8][3];
unsigned char  dcouchv[5];

int achair[8][3]={	{-50, 50,  0},
					{ 50, 50,  0},
					{ 50,-50,  0},
					{-50,-50,  0},
					{-50, 50,50},
					{ 50, 50,50},
					{ 50,-50,50},
					{-50,-50,50}};

int achair2[8][3];
unsigned char  achairv[5];

int bchair[8][3]={	{-80, 50,  0},
					{-45, 50,  0},
					{-45,-50,  0},
					{-80,-50,  0},
					{-80, 50,120},
					{-55, 50,120},
					{-55,-50,120},
					{-80,-50,120}};

int bchair2[8][3];
unsigned char  bchairv[5];

int cchair[8][3]={	{-70, 70,  0},
					{ 50, 70,  0},
					{ 50, 50,  0},
					{-70, 50,  0},
					{-70, 70,80},
					{ 50, 70,80},
					{ 50, 50,80},
					{-70, 50,80}};

int cchair2[8][3];
unsigned char  cchairv[5];

int dchair[8][3]={	{-70,-50,  0},
					{ 50,-50,  0},
					{ 50,-70,  0},
					{-70,-70,  0},
					{-70,-50,80},
					{ 50,-50,80},
					{ 50,-70,80},
					{-70,-70,80}};

int dchair2[8][3];
unsigned char  dchairv[5];

unsigned char  couchsurface[5][SURFSIZE]={{c_couch,4,0,3,7,4},
							{c_couch,4,3,2,6,7},
							{c_couch,4,1,0,4,5},
							{c_couch,4,2,1,5,6},
							{c_couch,4,7,6,5,4}};
							
unsigned char  chairsurface[5][SURFSIZE]={{c_chair,4,0,3,7,4},
							{c_chair,4,3,2,6,7},
							{c_chair,4,1,0,4,5},
							{c_chair,4,2,1,5,6},
							{c_chair,4,7,6,5,4}};

unsigned char  tvsurface[5][SURFSIZE]={{c_tv,4,0,3,7,4},
							{c_tv,4,3,2,6,7},
							{c_tv,4,1,0,4,5},
							{c_tv,4,2,1,5,6},
							{c_tv,4,7,6,5,4}};

unsigned char  drawersurface[5][SURFSIZE]={{c_vanity,4,0,3,7,4},
							{c_vanity,4,3,2,6,7},
							{c_vanity,4,1,0,4,5},
							{c_vanity,4,2,1,5,6},
							{c_vanity,4,7,6,5,4}};

Prism TVparts[2];
int tv[8][3]={		{-30, 60,  0},
					{ 30, 60,  0},
					{ 30,-60,  0},
					{-30,-60,  0},
					{-30, 60,120},
					{ 30, 60,120},
					{ 30,-60,120},
					{-30,-60,120}};

int tv2[8][3];
unsigned char  tvv[5];

int tvscreen[4][3]={{ 30, 50, 10},
					{ 30,-50, 10},
					{ 30, 50,110},
					{ 30,-50,110}};

int tvscreen2[4][3];
unsigned char  tvscreenv[1];
unsigned char  tvscreensurface[1][SURFSIZE]={{c_tvscreen,4,1,0,2,3}};

Prism Drawerparts[2];
int drawer[8][3]={	{-80, 70,  0},
					{  0, 70,  0},
					{  0,-70,  0},
					{-80,-70,  0},
					{-80, 70,100},
					{  0, 70,100},
					{  0,-70,100},
					{-80,-70,100}};

int drawer2[8][3];
unsigned char  drawerv[5];

int mirror[4][3]={  {-80, 65, 100},
					{-80,-65,100},
					{-80, 65,210},
					{-80,-65,210}};

int mirror2[4][3];
unsigned char  mirrorv[1];
unsigned char  mirrorsurface[1][SURFSIZE]={{c_mirror,4,1,0,2,3}};
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
InitCouch(RobotSize)
int RobotSize[];
{
Robot[COUCH] = Couchparts;
Robot[COUCH][0].points=8;
Robot[COUCH][0].pnt=acouch;
Robot[COUCH][0].copy=acouch2;
Robot[COUCH][0].surfaces=5;
Robot[COUCH][0].vsurface=acouchv;
Robot[COUCH][0].surface=couchsurface;

Robot[COUCH][1].points=8;
Robot[COUCH][1].pnt=bcouch;
Robot[COUCH][1].copy=bcouch2;
Robot[COUCH][1].surfaces=5;
Robot[COUCH][1].vsurface=bcouchv;
Robot[COUCH][1].surface=couchsurface;

Robot[COUCH][2].points=8;
Robot[COUCH][2].pnt=ccouch;
Robot[COUCH][2].copy=ccouch2;
Robot[COUCH][2].surfaces=5;
Robot[COUCH][2].vsurface=ccouchv;
Robot[COUCH][2].surface=couchsurface;

Robot[COUCH][3].points=8;
Robot[COUCH][3].pnt=dcouch;
Robot[COUCH][3].copy=dcouch2;
Robot[COUCH][3].surfaces=5;
Robot[COUCH][3].vsurface=dcouchv;
Robot[COUCH][3].surface=couchsurface;

RobotSize[COUCH]=4;

Robot[CHAIR] = Chairparts;
Robot[CHAIR][0].points=8;
Robot[CHAIR][0].pnt=achair;
Robot[CHAIR][0].copy=achair2;
Robot[CHAIR][0].surfaces=5;
Robot[CHAIR][0].vsurface=achairv;
Robot[CHAIR][0].surface=chairsurface;

Robot[CHAIR][1].points=8;
Robot[CHAIR][1].pnt=bchair;
Robot[CHAIR][1].copy=bchair2;
Robot[CHAIR][1].surfaces=5;
Robot[CHAIR][1].vsurface=bchairv;
Robot[CHAIR][1].surface=chairsurface;

Robot[CHAIR][2].points=8;
Robot[CHAIR][2].pnt=cchair;
Robot[CHAIR][2].copy=cchair2;
Robot[CHAIR][2].surfaces=5;
Robot[CHAIR][2].vsurface=cchairv;
Robot[CHAIR][2].surface=chairsurface;

Robot[CHAIR][3].points=8;
Robot[CHAIR][3].pnt=dchair;
Robot[CHAIR][3].copy=dchair2;
Robot[CHAIR][3].surfaces=5;
Robot[CHAIR][3].vsurface=dchairv;
Robot[CHAIR][3].surface=chairsurface;

RobotSize[CHAIR]=4;

Robot[TV] = TVparts;
Robot[TV][0].points=8;
Robot[TV][0].pnt=tv;
Robot[TV][0].copy=tv2;
Robot[TV][0].surfaces=5;
Robot[TV][0].vsurface=tvv;
Robot[TV][0].surface=tvsurface;

Robot[TV][1].points=4;
Robot[TV][1].pnt=tvscreen;
Robot[TV][1].copy=tvscreen2;
Robot[TV][1].surfaces=1;
Robot[TV][1].vsurface=tvscreenv;
Robot[TV][1].surface=tvscreensurface;

RobotSize[TV]=2;

Robot[DRAWER] = Drawerparts;
Robot[DRAWER][0].points=8;
Robot[DRAWER][0].pnt=drawer;
Robot[DRAWER][0].copy=drawer2;
Robot[DRAWER][0].surfaces=5;
Robot[DRAWER][0].vsurface=drawerv;
Robot[DRAWER][0].surface=drawersurface;

Robot[DRAWER][1].points=4;
Robot[DRAWER][1].pnt=mirror;
Robot[DRAWER][1].copy=mirror2;
Robot[DRAWER][1].surfaces=1;
Robot[DRAWER][1].vsurface=mirrorv;
Robot[DRAWER][1].surface=mirrorsurface;

RobotSize[DRAWER]=2;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */

Prism Cryoparts[2];

int cryotop[16][3]={ {-130,  50, 80},
					{ 130,  50, 80},
					{ 130,- 50, 80},
					{-130,- 50, 80},
					
					{-130,  50,140},
					{ 130,  50,140},
					{ 130,- 50,140},
					{-130,- 50,140},
					{0,50,140},
					{0,-50,140},
					{-140,  70,110},
					{ 140,  70,110},
					{ 140,- 70,110},
					{-140,- 70,110},
					{0,70,110},
					{0,-70,110}};
int cryotop2[16][3];
unsigned char  cryotopv[12];
unsigned char  cryotopsurface[12][SURFSIZE]={{c_cryo,4,7,9,8,4},
						 	{c_cryoglass,4,9,6,5,8},
						 	{c_cryo,4,0,10,11,1},
						 	{c_cryo,4,1,11,12,2},
						 	{c_cryo,4,2,12,13,3},
						 	{c_cryo,4,3,13,10,0},
						 	
						 	{c_cryo,4,7,13,15,9},
						 	{c_cryo,4,4,10,13,7},
						 	{c_cryo,4,14,10,4,8},
						 	{c_cryoglass,4,5,11,14,8},
						 	{c_cryoglass,4,6,12,11,5},
						 	{c_cryoglass,4,9,15,12,6}};

int cryobase[8][3]={{-130,  50,   0},
					 { 130,  50,   0},
					 { 130,- 50,   0},
					 {-130,- 50,   0},
					 {-130,  50, 80},
					 { 130,  50, 80},
					 { 130,- 50, 80},
					 {-130,- 50, 80}};

int cryobase2[8][3];
unsigned char  cryobasev[5];
unsigned char  cryobasesurface[5][SURFSIZE]={{c_cryostand,4,0,3,7,4},
							{c_cryostand,4,3,2,6,7},
							{c_cryostand,4,1,0,4,5},
							{c_cryostand,4,2,1,5,6},
							{c_cryostand,4,7,6,5,4}};
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
InitCryo(RobotSize)
int RobotSize[];
{
Robot[CRYO] = Cryoparts;
Robot[CRYO][0].points=16;
Robot[CRYO][0].pnt=cryotop;
Robot[CRYO][0].copy=cryotop2;
Robot[CRYO][0].surfaces=12;
Robot[CRYO][0].surface=cryotopsurface;
Robot[CRYO][0].vsurface=cryotopv;

Robot[CRYO][1].points=8;
Robot[CRYO][1].pnt=cryobase;
Robot[CRYO][1].copy=cryobase2;
Robot[CRYO][1].surfaces=5;
Robot[CRYO][1].surface=cryobasesurface;
Robot[CRYO][1].vsurface=cryobasev;
RobotSize[CRYO]=2;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "cube.h"

InitCube(RobotSize)
int RobotSize[];
{
Robot[CUBE] = Cubeparts;

Robot[CUBE][0].points=6;
Robot[CUBE][0].pnt=Cube;
Robot[CUBE][0].copy=Cube2;
Robot[CUBE][0].surfaces=8;
Robot[CUBE][0].surface=Cubesurface;
Robot[CUBE][0].vsurface=Cubev;
RobotSize[CUBE]=1;
/*-F_Cube-------------------*/
Robot[F_CUBE] = fCubeparts;

Robot[F_CUBE][0].points=6;
Robot[F_CUBE][0].pnt=fCube;
Robot[F_CUBE][0].copy=Cube2;
Robot[F_CUBE][0].surfaces=8;
Robot[F_CUBE][0].surface=Cubesurface;
Robot[F_CUBE][0].vsurface=Cubev;
RobotSize[F_CUBE]=1;
/*-S_Cube-------------------*/
Robot[S_CUBE] = sCubeparts;

Robot[S_CUBE][0].points=6;
Robot[S_CUBE][0].pnt=sCube;
Robot[S_CUBE][0].copy=Cube2;
Robot[S_CUBE][0].surfaces=8;
Robot[S_CUBE][0].surface=Cubesurface;
Robot[S_CUBE][0].vsurface=Cubev;
RobotSize[S_CUBE]=1;
/*-M_Cube-------------------*/
Robot[M_CUBE] = mCubeparts;

Robot[M_CUBE][0].points=6;
Robot[M_CUBE][0].pnt=mCube;
Robot[M_CUBE][0].copy=Cube2;
Robot[M_CUBE][0].surfaces=8;
Robot[M_CUBE][0].surface=Cubesurface;
Robot[M_CUBE][0].vsurface=Cubev;
RobotSize[M_CUBE]=1;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "desk.h"
InitDesk(RobotSize)
int RobotSize[];
{
Robot[DESK] = Deskparts;
Robot[DESK][0].points=4;
Robot[DESK][0].pnt=desktop;
Robot[DESK][0].copy=desktop2;
Robot[DESK][0].surfaces=1;
Robot[DESK][0].surface=desktopsurface;
Robot[DESK][0].vsurface=desktopv;

Robot[DESK][1].points=8;
Robot[DESK][1].pnt=deskleft;
Robot[DESK][1].copy=deskleft2;
Robot[DESK][1].surfaces=4;
Robot[DESK][1].surface=deskleftsurface;
Robot[DESK][1].vsurface=deskleftv;

Robot[DESK][2].points=8;
Robot[DESK][2].pnt=deskrite;
Robot[DESK][2].copy=deskrite2;
Robot[DESK][2].surfaces=4;
Robot[DESK][2].surface=deskritesurface;
Robot[DESK][2].vsurface=deskritev;

Robot[DESK][3].points=4;
Robot[DESK][3].pnt=seat;
Robot[DESK][3].copy=seat2;
Robot[DESK][3].surfaces=1;
Robot[DESK][3].surface=seatsurface;
Robot[DESK][3].vsurface=seatv;

Robot[DESK][4].points=4;
Robot[DESK][4].pnt=armleft;
Robot[DESK][4].copy=armleft2;
Robot[DESK][4].surfaces=2;
Robot[DESK][4].surface=armleftsurface;
Robot[DESK][4].vsurface=armleftv;

Robot[DESK][5].points=4;
Robot[DESK][5].pnt=armrite;
Robot[DESK][5].copy=armrite2;
Robot[DESK][5].surfaces=2;
Robot[DESK][5].surface=armritesurface;
Robot[DESK][5].vsurface=armritev;

Robot[DESK][6].points=4;
Robot[DESK][6].pnt=back;
Robot[DESK][6].copy=back2;
Robot[DESK][6].surfaces=2;
Robot[DESK][6].surface=backsurface;
Robot[DESK][6].vsurface=backv;

Robot[DESK][7].points=8;
Robot[DESK][7].pnt=computer;
Robot[DESK][7].copy=computer2;
Robot[DESK][7].surfaces=5;
Robot[DESK][7].surface=computersurface;
Robot[DESK][7].vsurface=computerv;

Robot[DESK][8].points=4;
Robot[DESK][8].pnt=screen;
Robot[DESK][8].copy=screen2;
Robot[DESK][8].surfaces=1;
Robot[DESK][8].surface=screensurface;
Robot[DESK][8].vsurface=screenv;
RobotSize[DESK]=9;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "drone.h"
InitDrone(RobotSize)
int RobotSize[];
{
Robot[DRONE] = Droneparts;
Robot[DRONE][0].points=6;
Robot[DRONE][0].pnt=dAbdomen;
Robot[DRONE][0].copy=dAbdomen2;
Robot[DRONE][0].surfaces=8;
Robot[DRONE][0].surface=dAbdomensurface;
Robot[DRONE][0].vsurface=dAbdomenv;

Robot[DRONE][1].points=4;
Robot[DRONE][1].pnt=lPincer;
Robot[DRONE][1].copy=lPincer2;
Robot[DRONE][1].surfaces=4;
Robot[DRONE][1].surface=lPincersurface;
Robot[DRONE][1].vsurface=lPincerv;

Robot[DRONE][2].points=4;
Robot[DRONE][2].pnt=rPincer;
Robot[DRONE][2].copy=rPincer2;
Robot[DRONE][2].surfaces=4;
Robot[DRONE][2].surface=rPincersurface;
Robot[DRONE][2].vsurface=rPincerv;

Robot[DRONE][3].points=4;
Robot[DRONE][3].pnt=llPincer;

Robot[DRONE][4].points=4;
Robot[DRONE][4].pnt=rrPincer;
Robot[DRONE][5].points=3;
Robot[DRONE][5].pnt=leye;
Robot[DRONE][6].points=3;
Robot[DRONE][6].pnt=reye;
RobotSize[DRONE]=7;
/*-Soldier-----------------*/
Robot[SOLDIER] = Droneparts;
RobotSize[SOLDIER]=0;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "eye.h"
InitEye(RobotSize)
int RobotSize[];
{
Robot[EYE] = Eyeparts;
Robot[EYE][0].points=2;
Robot[EYE][0].pnt=ball;
Robot[EYE][0].copy=ball2;
Robot[EYE][0].surfaces=1;
Robot[EYE][0].surface=ballsurface;
Robot[EYE][0].vsurface=ballv;
	
Robot[EYE][1].points=4;
Robot[EYE][1].pnt=iris;
Robot[EYE][1].copy=iris2;
Robot[EYE][1].surfaces=1;
Robot[EYE][1].surface=irissurface;
Robot[EYE][1].vsurface=irisv;

Robot[EYE][2].points=4;
Robot[EYE][2].pnt=pupil;
Robot[EYE][2].copy=pupil2;
Robot[EYE][2].surfaces=1;
Robot[EYE][2].surface=pupilsurface;
Robot[EYE][2].vsurface=pupilv;
RobotSize[EYE]=3;
/*-M_Eye-------------------*/
Robot[M_EYE] = mEyeparts;
Robot[M_EYE][0].points=2;
Robot[M_EYE][0].pnt=mball;
Robot[M_EYE][0].copy=ball2;
Robot[M_EYE][0].surfaces=1;
Robot[M_EYE][0].surface=ballsurface;
Robot[M_EYE][0].vsurface=ballv;
	
Robot[M_EYE][1].points=4;
Robot[M_EYE][1].pnt=miris;
Robot[M_EYE][1].copy=iris2;
Robot[M_EYE][1].surfaces=1;
Robot[M_EYE][1].surface=irissurface;
Robot[M_EYE][1].vsurface=irisv;

Robot[M_EYE][2].points=4;
Robot[M_EYE][2].pnt=mpupil;
Robot[M_EYE][2].copy=pupil2;
Robot[M_EYE][2].surfaces=1;
Robot[M_EYE][2].surface=pupilsurface;
Robot[M_EYE][2].vsurface=pupilv;
RobotSize[M_EYE]=3;
/*-F_Eye-------------------*/
Robot[F_EYE] = fEyeparts;
Robot[F_EYE][0].points=2;
Robot[F_EYE][0].pnt=fball;
Robot[F_EYE][0].copy=ball2;
Robot[F_EYE][0].surfaces=1;
Robot[F_EYE][0].surface=ballsurface;
Robot[F_EYE][0].vsurface=ballv;
	
Robot[F_EYE][1].points=4;
Robot[F_EYE][1].pnt=firis;
Robot[F_EYE][1].copy=iris2;
Robot[F_EYE][1].surfaces=1;
Robot[F_EYE][1].surface=irissurface;
Robot[F_EYE][1].vsurface=irisv;

Robot[F_EYE][2].points=4;
Robot[F_EYE][2].pnt=fpupil;
Robot[F_EYE][2].copy=pupil2;
Robot[F_EYE][2].surfaces=1;
Robot[F_EYE][2].surface=pupilsurface;
Robot[F_EYE][2].vsurface=pupilv;
RobotSize[F_EYE]=3;
/*-S_Eye-------------------*/
Robot[S_EYE] = sEyeparts;
Robot[S_EYE][0].points=2;
Robot[S_EYE][0].pnt=sball;
Robot[S_EYE][0].copy=ball2;
Robot[S_EYE][0].surfaces=1;
Robot[S_EYE][0].surface=ballsurface;
Robot[S_EYE][0].vsurface=ballv;
	
Robot[S_EYE][1].points=4;
Robot[S_EYE][1].pnt=siris;
Robot[S_EYE][1].copy=iris2;
Robot[S_EYE][1].surfaces=1;
Robot[S_EYE][1].surface=irissurface;
Robot[S_EYE][1].vsurface=irisv;

Robot[S_EYE][2].points=4;
Robot[S_EYE][2].pnt=spupil;
Robot[S_EYE][2].copy=pupil2;
Robot[S_EYE][2].surfaces=1;
Robot[S_EYE][2].surface=pupilsurface;
Robot[S_EYE][2].vsurface=pupilv;
RobotSize[S_EYE]=3;
}

/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
Prism ForkLiftparts[6];

int FLCab[14][3]={	{-35, 60,  40},
					{ 35, 60,  40},
					{ 35,-60,  40},
					{-35,-60,  40},
					
					{-15, 60, 260},
					{ 15, 60, 260},
					{ 15,-60, 260},
					{-15,-60, 260},
					
					{ 25, 60, 140},
					{ 25,-60, 140},
					{ 70, 35, 120},
					{ 70,-35, 120},
					{-70, 40, 80},
					{-70,-40, 80}
					};

int FLCab2[14][3];
unsigned char  FLCabv[12];
unsigned char  FLCabsurface[12][SURFSIZE]={	{c_forklift,4,0,3,13,12},
							{c_forklift,4,12,13,7,4},
							{c_forklift,3,0,12,4},
							{c_forklift,3,3,7,13},
							{c_forklift,4,3,2,6,7},
							{c_forklift,4,1,0,4,5},
							{c_forklift,3,1,8,10},
							{c_forklift,3,2,11,9},
							{c_forklift,4,1,10,11,2},
							{c_flglass,3,8,5,10},
							{c_flglass,3,11,6,9},
							{c_flglass,4,10,5,6,11}};

int FLTread[12][3]={ {-60, 60, 20},
					{ 60, 60, 20},
					{ 60,-60, 20},
					{-60,-60, 20},
					{-35, 60, 40},
					{ 35, 60, 40},
					{ 35,-60, 40},
					{-35,-60, 40},
					{-35, 60,  0},
					{ 35, 60,  0},
					{ 35,-60,  0},
					{-35,-60,  0}
					};

int FLTread2[12][3];
unsigned char  FLTreadv[6];
unsigned char  FLTreadsurface[6][SURFSIZE]={{c_fltreadtop,4,0,3,7,4},
							{c_fltreadside,6,3,11,10,2,6,7},
							{c_fltreadside,6,0,4,5,1,9,8},
							{c_fltreadtop,4,2,1,5,6},
							{c_fltreadtop,4,0,8,11,3},
							{c_fltreadtop,4,10,9,1,2}};

int FLUL[8][3]={	{-15,70,120},
					{ 15,70,120},
					{ 15,60,120},
					{-15,60,120},
					{-25,70,230},
					{ 25,70,230},
					{ 25,60,230},
					{-25,60,230}};
int FLUL2[8][3];
unsigned char  FLULv[4];
unsigned char  FLULsurface[4][SURFSIZE]={	{c_forklift,4,0,3,7,4},
							{c_forklift,4,3,2,6,7},
							{c_forklift,4,1,0,4,5},
							{c_forklift,4,2,1,5,6}};

int FLLL[8][3]={	{ -15,80,120},
					{ 100,80,125},
					{ 100,70,125},
					{ -15,70,120},
					{ -15,80,150},
					{ 100,80,140},
					{ 100,70,140},
					{ -15,70,150}};
int FLLL2[8][3];
unsigned char  FLLLv[6];
unsigned char  FLLLsurface[6][SURFSIZE]={	{c_forklift,4,0,3,7,4},
							{c_forklift,4,3,2,6,7},
							{c_forklift,4,1,0,4,5},
							{BLACK,4,2,1,5,6},
							{c_forklift,4,7,6,5,4},
							{c_forklift,4,0,1,2,3}};

int FLUR[8][3]={	{-15,-60,120},
					{ 15,-60,120},
					{ 15,-70,120},
					{-15,-70,120},
					{-25,-60,230},
					{ 25,-60,230},
					{ 25,-70,230},
					{-25,-70,230}};
int FLUR2[8][3];
unsigned char  FLURv[4];
unsigned char  FLURsurface[4][SURFSIZE]={	{c_forklift,4,0,3,7,4},
							{c_forklift,4,3,2,6,7},
							{c_forklift,4,1,0,4,5},
							{c_forklift,4,2,1,5,6}};

int FLLR[8][3]={	{ -15,-70,120},
					{ 100,-70,125},
					{ 100,-80,125},
					{ -15,-80,120},
					{ -15,-70,150},
					{ 100,-70,140},
					{ 100,-80,140},
					{ -15,-80,150}};
int FLLR2[8][3];
unsigned char  FLLRv[6];
unsigned char  FLLRsurface[6][SURFSIZE]={	{c_forklift,4,0,3,7,4},
							{c_forklift,4,3,2,6,7},
							{c_forklift,4,1,0,4,5},
							{BLACK,4,2,1,5,6},
							{c_forklift,4,7,6,5,4},
							{c_forklift,4,0,1,2,3}};
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
InitForkLift(RobotSize)
int RobotSize[];
{
Robot[FORKLIFT] = ForkLiftparts;
Robot[FORKLIFT][0].points=14;
Robot[FORKLIFT][0].pnt=FLCab;
Robot[FORKLIFT][0].copy=FLCab2;
Robot[FORKLIFT][0].surfaces=12;
Robot[FORKLIFT][0].surface=FLCabsurface;
Robot[FORKLIFT][0].vsurface=FLCabv;

Robot[FORKLIFT][1].points=12;
Robot[FORKLIFT][1].pnt=FLTread;
Robot[FORKLIFT][1].copy=FLTread2;
Robot[FORKLIFT][1].surfaces=6;
Robot[FORKLIFT][1].surface=FLTreadsurface;
Robot[FORKLIFT][1].vsurface=FLTreadv;

Robot[FORKLIFT][2].points=8;
Robot[FORKLIFT][2].pnt=FLUL;
Robot[FORKLIFT][2].copy=FLUL2;
Robot[FORKLIFT][2].surfaces=4;
Robot[FORKLIFT][2].surface=FLULsurface;
Robot[FORKLIFT][2].vsurface=FLULv;

Robot[FORKLIFT][3].points=8;
Robot[FORKLIFT][3].pnt=FLLL;
Robot[FORKLIFT][3].copy=FLLL2;
Robot[FORKLIFT][3].surfaces=6;
Robot[FORKLIFT][3].surface=FLLLsurface;
Robot[FORKLIFT][3].vsurface=FLLLv;


Robot[FORKLIFT][4].points=8;
Robot[FORKLIFT][4].pnt=FLUR;
Robot[FORKLIFT][4].copy=FLUR2;
Robot[FORKLIFT][4].surfaces=4;
Robot[FORKLIFT][4].surface=FLURsurface;
Robot[FORKLIFT][4].vsurface=FLURv;

Robot[FORKLIFT][5].points=8;
Robot[FORKLIFT][5].pnt=FLLR;
Robot[FORKLIFT][5].copy=FLLR2;
Robot[FORKLIFT][5].surfaces=6;
Robot[FORKLIFT][5].surface=FLLRsurface;
Robot[FORKLIFT][5].vsurface=FLLRv;
RobotSize[FORKLIFT]=6;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "plant.h"
InitPlant(RobotSize)
int RobotSize[];
{
if(xmas)
	{
	Robot[PLANT] = Plantparts;

	Robot[PLANT][0].points=12;
	Robot[PLANT][0].pnt=trunk;
	Robot[PLANT][0].copy=pot2;
	Robot[PLANT][0].surfaces=6;
	Robot[PLANT][0].surface=potsurface;
	Robot[PLANT][0].vsurface=potv;

	Robot[PLANT][1].points=7;
	Robot[PLANT][1].pnt=tree;
	Robot[PLANT][1].copy=tree2;
	Robot[PLANT][1].surfaces=6;
	Robot[PLANT][1].surface=treesurface;
	Robot[PLANT][1].vsurface=treev;
	RobotSize[PLANT]=2;
	}
else
	{
	Robot[PLANT] = Plantparts;

	Robot[PLANT][0].points=12;
	Robot[PLANT][0].pnt=pot;
	Robot[PLANT][0].copy=pot2;
	Robot[PLANT][0].surfaces=6;
	Robot[PLANT][0].surface=potsurface;
	Robot[PLANT][0].vsurface=potv;

	Robot[PLANT][1].points=6;
	Robot[PLANT][1].pnt=toppot;
	Robot[PLANT][1].copy=toppot2;
	Robot[PLANT][1].surfaces=1;
	Robot[PLANT][1].surface=toppotsurface;
	Robot[PLANT][1].vsurface=toppotv;

	Robot[PLANT][2].points=3;
	Robot[PLANT][2].pnt=leaf0;
	Robot[PLANT][2].copy=leaf02;
	Robot[PLANT][2].surfaces=2;
	Robot[PLANT][2].surface=leaf0surface;
	Robot[PLANT][2].vsurface=leaf0v;

	Robot[PLANT][3].points=3;
	Robot[PLANT][3].pnt=leaf1;
	Robot[PLANT][3].copy=leaf12;
	Robot[PLANT][3].surfaces=2;
	Robot[PLANT][3].surface=leaf1surface;
	Robot[PLANT][3].vsurface=leaf1v;

	Robot[PLANT][4].points=3;
	Robot[PLANT][4].pnt=leaf2;
	Robot[PLANT][4].copy=leaf22;
	Robot[PLANT][4].surfaces=2;
	Robot[PLANT][4].surface=leaf2surface;
	Robot[PLANT][4].vsurface=leaf2v;

	Robot[PLANT][5].points=3;
	Robot[PLANT][5].pnt=leaf3;
	Robot[PLANT][5].copy=leaf32;
	Robot[PLANT][5].surfaces=2;
	Robot[PLANT][5].surface=leaf3surface;
	Robot[PLANT][5].vsurface=leaf3v;

	Robot[PLANT][6].points=3;
	Robot[PLANT][6].pnt=leaf4;
	Robot[PLANT][6].copy=leaf42;
	Robot[PLANT][6].surfaces=2;
	Robot[PLANT][6].surface=leaf4surface;
	Robot[PLANT][6].vsurface=leaf4v;

	Robot[PLANT][7].points=3;
	Robot[PLANT][7].pnt=leaf5;
	Robot[PLANT][7].copy=leaf52;
	Robot[PLANT][7].surfaces=2;
	Robot[PLANT][7].surface=leaf5surface;
	Robot[PLANT][7].vsurface=leaf5v;
	RobotSize[PLANT]=8;
	}
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */

Prism Powerparts[5];

int powertop[3][3]={{-150, 120,2*Floor},
					{ 150, 120,2*Floor},
					{   0,-150,2*Floor}};
int powertop2[3][3];
unsigned char  powertopv[1];
unsigned char  powertopsurface[1][SURFSIZE]={{c_powerbase,3,0,1,2}};

int powerbottom[3][3]={{-150, 120,0},
					{ 150, 120,0},
					{   0,-150,0}};
int powerbottom2[3][3];
unsigned char  powerbottomv[1];
unsigned char powerbottomsurface[1][SURFSIZE]={{c_powerbase,3,2,1,0}};

int powerbase[8][3]={{-5,100,   0},
					{ 5, 100,   0},
					{ 5, 90,   0},
					{-5, 90,   0},
					{-5, 100,100},
					{ 5, 100,100},
					{ 5, 90,100},
					{-5, 90,100}};

int powerbase2[8][3];
unsigned char powerbasev[4];
unsigned char  powerbasesurface[4][SURFSIZE]={{c_powerbase,4,0,3,7,4},
							{c_powerbase,4,3,2,6,7},
							{c_powerbase,4,1,0,4,5},
							{c_powerbase,4,2,1,5,6}};

int powertable[4][3]={{-50, 135,100},
					{ 50,135,100},
					{ 50, 55,100},
					{-50, 55,100}};
int powertable2[4][3];
unsigned char  powertablev[1];
unsigned char  powertablesurface[1][SURFSIZE]={{c_powertable,4,3,2,1,0}};

int powersource[12][3]={ {-75,0,2*Floor-30},
						{-35,60,2*Floor-30},
						{35,60,2*Floor-30},
						{75,0,2*Floor-30},
						{35,-60,2*Floor-30},
						{-35,-60,2*Floor-30},
						 {-75,0,2*Floor},
						{-35,60,2*Floor},
						{35,60,2*Floor},
						{75,0,2*Floor},
						{35,-60,2*Floor},
						{-35,-60,2*Floor}};
int powersource2[12][3];
unsigned char  powersourcev[7];
unsigned char  powersourcesurface[7][SURFSIZE]={{BLACK,6,0,1,2,3,4,5},
								{c_powersource,4,0,6,7,1},
								{c_powersource,4,1,7,8,2},
								{c_powersource,4,2,8,9,3},
								{c_powersource,4,3,9,10,4},
								{c_powersource,4,4,10,11,5},
								{c_powersource,4,5,11,6,0}};
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
InitPowerSuit(RobotSize)
int RobotSize[];
{
Robot[POWERSUIT] = Powerparts;
Robot[POWERSUIT][0].points=3;
Robot[POWERSUIT][0].pnt=powertop;
Robot[POWERSUIT][0].copy=powertop2;
Robot[POWERSUIT][0].surfaces=1;
Robot[POWERSUIT][0].surface=powertopsurface;
Robot[POWERSUIT][0].vsurface=powertopv;

Robot[POWERSUIT][1].points=3;
Robot[POWERSUIT][1].pnt=powerbottom;
Robot[POWERSUIT][1].copy=powerbottom2;
Robot[POWERSUIT][1].surfaces=1;
Robot[POWERSUIT][1].surface=powerbottomsurface;
Robot[POWERSUIT][1].vsurface=powerbottomv;

Robot[POWERSUIT][2].points=8;
Robot[POWERSUIT][2].pnt=powerbase;
Robot[POWERSUIT][2].copy=powerbase2;
Robot[POWERSUIT][2].surfaces=4;
Robot[POWERSUIT][2].surface=powerbasesurface;
Robot[POWERSUIT][2].vsurface=powerbasev;

Robot[POWERSUIT][3].points=4;
Robot[POWERSUIT][3].pnt=powertable;
Robot[POWERSUIT][3].copy=powertable2;
Robot[POWERSUIT][3].surfaces=1;
Robot[POWERSUIT][3].surface=powertablesurface;
Robot[POWERSUIT][3].vsurface=powertablev;

Robot[POWERSUIT][4].points=12;
Robot[POWERSUIT][4].pnt=powersource;
Robot[POWERSUIT][4].copy=powersource2;
Robot[POWERSUIT][4].surfaces=7;
Robot[POWERSUIT][4].surface=powersourcesurface;
Robot[POWERSUIT][4].vsurface=powersourcev;

RobotSize[POWERSUIT]=5;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "pyramid.h"
InitPyramid(RobotSize)
int RobotSize[];
{
/*-Pyramid-------------------*/
Robot[PYRAMID] = Pyramidparts;
Robot[PYRAMID][0].points=5;
Robot[PYRAMID][0].pnt=Pyramid;
Robot[PYRAMID][0].copy=Pyramid2;
Robot[PYRAMID][0].surfaces=4;
Robot[PYRAMID][0].surface=Pyramidsurface;
Robot[PYRAMID][0].vsurface=Pyramidv;

Robot[PYRAMID][1].points=4;
Robot[PYRAMID][1].pnt=Pshadow;
Robot[PYRAMID][1].copy=Pshadow2;
Robot[PYRAMID][1].surfaces=1;
Robot[PYRAMID][1].surface=Pshadowsurface;
Robot[PYRAMID][1].vsurface=Pshadowv;

Robot[PYRAMID][2].points=2;
Robot[PYRAMID][2].pnt=pball;
Robot[PYRAMID][2].copy=pball2;
Robot[PYRAMID][2].surfaces=1;
Robot[PYRAMID][2].surface=pballsurface;
Robot[PYRAMID][2].vsurface=pballv;
	
Robot[PYRAMID][3].points=4;
Robot[PYRAMID][3].pnt=piris;
Robot[PYRAMID][3].copy=piris2;
Robot[PYRAMID][3].surfaces=1;
Robot[PYRAMID][3].surface=pirissurface;
Robot[PYRAMID][3].vsurface=pirisv;

Robot[PYRAMID][4].points=4;
Robot[PYRAMID][4].pnt=ppupil;
Robot[PYRAMID][4].copy=ppupil2;
Robot[PYRAMID][4].surfaces=1;
Robot[PYRAMID][4].surface=ppupilsurface;
Robot[PYRAMID][4].vsurface=ppupilv;
RobotSize[PYRAMID]=5;
/*-fPyramid-------------------*/
Robot[F_PYRAMID] = fPyramidparts;
Robot[F_PYRAMID][0].points=5;
Robot[F_PYRAMID][0].pnt=fPyramid;
Robot[F_PYRAMID][0].copy=Pyramid2;
Robot[F_PYRAMID][0].surfaces=4;
Robot[F_PYRAMID][0].surface=Pyramidsurface;
Robot[F_PYRAMID][0].vsurface=Pyramidv;
RobotSize[F_PYRAMID]=1;
/*-sPyramid-------------------*/
Robot[S_PYRAMID] = sPyramidparts;
Robot[S_PYRAMID][0].points=5;
Robot[S_PYRAMID][0].pnt=sPyramid;
Robot[S_PYRAMID][0].copy=Pyramid2;
Robot[S_PYRAMID][0].surfaces=4;
Robot[S_PYRAMID][0].surface=Pyramidsurface;
Robot[S_PYRAMID][0].vsurface=Pyramidv;
RobotSize[S_PYRAMID]=1;
/*-mPyramid-------------------*/
Robot[M_PYRAMID] = mPyramidparts;
Robot[M_PYRAMID][0].points=5;
Robot[M_PYRAMID][0].pnt=mPyramid;
Robot[M_PYRAMID][0].copy=Pyramid2;
Robot[M_PYRAMID][0].surfaces=4;
Robot[M_PYRAMID][0].surface=Pyramidsurface;
Robot[M_PYRAMID][0].vsurface=Pyramidv;
RobotSize[M_PYRAMID]=1;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "queen.h"
InitQueen(RobotSize)
int RobotSize[];
{
Robot[QUEEN] = Queenparts;
Robot[QUEEN][0].points=2;
Robot[QUEEN][0].pnt=qball;
Robot[QUEEN][0].copy=qball2;
Robot[QUEEN][0].surfaces=1;
Robot[QUEEN][0].surface=qballsurface;
Robot[QUEEN][0].vsurface=qballv;
	
Robot[QUEEN][1].points=4;
Robot[QUEEN][1].pnt=qiris;
Robot[QUEEN][1].copy=qiris2;
Robot[QUEEN][1].surfaces=1;
Robot[QUEEN][1].surface=qirissurface;
Robot[QUEEN][1].vsurface=qirisv;

Robot[QUEEN][2].points=4;
Robot[QUEEN][2].pnt=qpupil;
Robot[QUEEN][2].copy=qpupil2;
Robot[QUEEN][2].surfaces=1;
Robot[QUEEN][2].surface=qpupilsurface;
Robot[QUEEN][2].vsurface=qpupilv;

Robot[QUEEN][3].points=9;
Robot[QUEEN][3].pnt=qAbdomen;
Robot[QUEEN][3].copy=qAbdomen2;
Robot[QUEEN][3].surfaces=9;
Robot[QUEEN][3].surface=qAbdomensurface;
Robot[QUEEN][3].vsurface=qAbdomenv;

Robot[QUEEN][4].points=9;
Robot[QUEEN][4].pnt=qThorax;
Robot[QUEEN][4].copy=qThorax2;
Robot[QUEEN][4].surfaces=8;
Robot[QUEEN][4].surface=qThoraxsurface;
Robot[QUEEN][4].vsurface=qThoraxv;

Robot[QUEEN][5].points=4;
Robot[QUEEN][5].pnt=lwing;
Robot[QUEEN][5].copy=lwing2;
Robot[QUEEN][5].surfaces=1;
Robot[QUEEN][5].surface=lwingsurface;
Robot[QUEEN][5].vsurface=lwingv;

Robot[QUEEN][6].points=4;
Robot[QUEEN][6].pnt=rwing;
Robot[QUEEN][6].copy=rwing2;
Robot[QUEEN][6].surfaces=1;
Robot[QUEEN][6].surface=rwingsurface;
Robot[QUEEN][6].vsurface=rwingv;
RobotSize[QUEEN]=7;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "screen.h"
InitScreen(RobotSize)
int RobotSize[];
{
Robot[SCREEN] = Screen;
Robot[SCREEN][0].points=8;
Robot[SCREEN][0].pnt=vscreen;
Robot[SCREEN][0].copy=vscreen2;
Robot[SCREEN][0].surfaces=4;
Robot[SCREEN][0].surface=vscreensurface;
Robot[SCREEN][0].vsurface=vscreenv;
RobotSize[SCREEN]=1;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "snoop.h"
InitSnoop(RobotSize)
int RobotSize[];
{
Robot[SNOOP] = Snoopparts;
Robot[SNOOP][0].points=4;
Robot[SNOOP][0].pnt=sAbdomen;
Robot[SNOOP][0].copy=sAbdomen2;
Robot[SNOOP][0].surfaces=2;
Robot[SNOOP][0].surface=sAbdomensurface;
Robot[SNOOP][0].vsurface=sAbdomenv;

Robot[SNOOP][1].points=4;
Robot[SNOOP][1].pnt=sHead;
Robot[SNOOP][1].copy=sHead2;
Robot[SNOOP][1].surfaces=3;
Robot[SNOOP][1].surface=sHeadsurface;
Robot[SNOOP][1].vsurface=sHeadv;

RobotSize[SNOOP]=2;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
Prism Tableparts[2];

int tabletop[4][3]={{-128, 128,100},
					{ 128, 128,100},
					{ 128,-128,100},
					{-128,-128,100}};
int tabletop2[4][3];
unsigned char  tabletopv[1];
unsigned char  tabletopsurface[1][SURFSIZE]={{c_table,4,3,2,1,0}};

int tablebase[8][3]={{-5, 5,   0},
					{ 5, 5,   0},
					{ 5,-5,   0},
					{-5,-5,   0},
					{-5, 5,100},
					{ 5, 5,100},
					{ 5,-5,100},
					{-5,-5,100}};

int tablebase2[8][3];
unsigned char  tablebasev[4];
unsigned char  tablebasesurface[4][SURFSIZE]={{c_table,4,0,3,7,4},
							{c_table,4,3,2,6,7},
							{c_table,4,1,0,4,5},
							{c_table,4,2,1,5,6}};

int projector[8][3]={{-30, 30,140},
					{ 30, 30,140},
					{ 30,-30,140},
					{-30,-30,140},
					{-20, 30,160},
					{ 30, 30,160},
					{ 30,-30,160},
					{-20,-30,160}};

int projector2[8][3];
unsigned char  projectorv[5];

int pstand[4][3]={{-25,50,100},
				  {0,10,140},
				  {0,-10,140},
				  {-25,-50,100}};
int pstand2[4][3];
unsigned char  pstandv[1];
unsigned char  pstandsurface[1][SURFSIZE]={{c_proj,4,0,1,2,3}};

int plens[12][3]={{30,  8,154},
				  {30,  0,158},
				  {30, -8,154},
				  {30, -8,146},
				  {30,  0,142},
				  {30,  8,146},
				  
				  {55, 10,155},
				  {55,  0,160},
				  {55,-10,155},
				  {55,-10,145},
				  {55,  0,140},
				  {55, 10,145}};
int plens2[12][3];
unsigned char  plensv[7];
unsigned char  plenssurface[7][SURFSIZE]={ {c_projlens,4,0,1,7,6},
								{c_projlens,4,1,2,8,7},
								{c_projlens,4,2,3,9,8},
								{c_projlens,4,3,4,10,9},
								{c_projlens,4,4,5,11,10},
								{c_projlens,4,5,0,6,11},
								{BLACK,6,6,7,8,9,10,11}};
Prism Projectorparts[3];

unsigned char projectorsurface[5][SURFSIZE]={{c_proj,4,0,3,7,4},
							{c_proj,4,3,2,6,7},
							{c_proj,4,1,0,4,5},
							{c_proj,4,2,1,5,6},
							{c_proj,4,7,6,5,4}};
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
InitTable(RobotSize)
int RobotSize[];
{
Robot[TABLE] = Tableparts;
Robot[TABLE][0].points=4;
Robot[TABLE][0].pnt=tabletop;
Robot[TABLE][0].copy=tabletop2;
Robot[TABLE][0].surfaces=1;
Robot[TABLE][0].surface=tabletopsurface;
Robot[TABLE][0].vsurface=tabletopv;

Robot[TABLE][1].points=8;
Robot[TABLE][1].pnt=tablebase;
Robot[TABLE][1].copy=tablebase2;
Robot[TABLE][1].surfaces=4;
Robot[TABLE][1].surface=tablebasesurface;
Robot[TABLE][1].vsurface=tablebasev;
RobotSize[TABLE]=2;

Robot[PROJECTOR] = Projectorparts;
Robot[PROJECTOR][0].points=8;
Robot[PROJECTOR][0].pnt=projector;
Robot[PROJECTOR][0].copy=projector2;
Robot[PROJECTOR][0].surfaces=5;
Robot[PROJECTOR][0].surface=projectorsurface;
Robot[PROJECTOR][0].vsurface=projectorv;

Robot[PROJECTOR][1].points=4;
Robot[PROJECTOR][1].pnt=pstand;
Robot[PROJECTOR][1].copy=pstand2;
Robot[PROJECTOR][1].surfaces=1;
Robot[PROJECTOR][1].surface=pstandsurface;
Robot[PROJECTOR][1].vsurface=pstandv;

Robot[PROJECTOR][2].points=12;
Robot[PROJECTOR][2].pnt=plens;
Robot[PROJECTOR][2].copy=plens2;
Robot[PROJECTOR][2].surfaces=7;
Robot[PROJECTOR][2].surface=plenssurface;
Robot[PROJECTOR][2].vsurface=plensv;

RobotSize[PROJECTOR]=3;

}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
Prism Teleparts[1];

int tele[24][3]={	{   0, 175,140},
					{ 125, 125,140},
					{ 175,   0,140},
					{ 125,-125,140},
					{   0,-175,140},
					{-125,-125,140},
					{-175,   0,140},
					{-125, 125,140},
					
					{  0, 80,0},
					{ 65, 65,0},
					{ 80,  0,0},
					{ 65,-65,0},
					{  0,-80,0},
					{-65,-65,0},
					{-80,  0,0},
					{-65, 65,0},
					
					{  0, 80,280},
					{ 65, 65,280},
					{ 80,  0,280},
					{ 65,-65,280},
					{  0,-80,280},
					{-65,-65,280},
					{-80,  0,280},
					{-65, 65,280}};
int tele2[24][3];
unsigned char  telev[16];
unsigned char  telesurface[16][SURFSIZE]={
						{c_teledoor,4,0,1,9,8},
						{c_teleport,4,1,2,10,9},
						{c_teleport,4,2,3,11,10},
						{c_teleport,4,3,4,12,11},
						{c_teleport,4,4,5,13,12},
						{c_teleport,4,5,6,14,13},
						{c_teleport,4,6,7,15,14},
						{c_teleport,4,7,0,8,15},
						
						{c_teleglass,4,1,0,16,17},
						{c_teleport,4,2,1,17,18},
						{c_teleport,4,3,2,18,19},
						{c_teleport,4,4,3,19,20},
						{c_teleport,4,5,4,20,21},
						{c_teleport,4,6,5,21,22},
						{c_teleport,4,7,6,22,23},
						{c_teleport,4,0,7,23,16}};
InitTele(RobotSize)
int RobotSize[];
{
Robot[TELEPORT] = Teleparts;

Robot[TELEPORT][0].points=24;
Robot[TELEPORT][0].pnt=tele;
Robot[TELEPORT][0].copy=tele2;
Robot[TELEPORT][0].surfaces=16;
Robot[TELEPORT][0].surface=telesurface;
Robot[TELEPORT][0].vsurface=telev;

RobotSize[TELEPORT]=1;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
#include "upyramid.h"

InitUPyramid(RobotSize)
int RobotSize[];
{
Robot[UPYRAMID] = UPyramidparts;
Robot[UPYRAMID][0].points=5;
Robot[UPYRAMID][0].pnt=UPyramid;
Robot[UPYRAMID][0].copy=UPyramid2;
Robot[UPYRAMID][0].surfaces=4;
Robot[UPYRAMID][0].surface=UPyramidsurface;
Robot[UPYRAMID][0].vsurface=UPyramidv;

Robot[UPYRAMID][1].points=4;
Robot[UPYRAMID][1].pnt=UPshadow;
Robot[UPYRAMID][1].copy=UPshadow2;
Robot[UPYRAMID][1].surfaces=1;
Robot[UPYRAMID][1].surface=UPshadowsurface;
Robot[UPYRAMID][1].vsurface=UPshadowv;
RobotSize[UPYRAMID]=2;
/*-F_Upside Down Pyramid-------------------*/
Robot[F_UPYRAMID] = fUPyramidparts;
Robot[F_UPYRAMID][0].points=5;
Robot[F_UPYRAMID][0].pnt=fUPyramid;
Robot[F_UPYRAMID][0].copy=UPyramid2;
Robot[F_UPYRAMID][0].surfaces=5;
Robot[F_UPYRAMID][0].surface=UPyramidsurface;
Robot[F_UPYRAMID][0].vsurface=UPyramidv;
RobotSize[F_UPYRAMID]=1;
/*-S_Upside Down Pyramid-------------------*/
Robot[S_UPYRAMID] = sUPyramidparts;
Robot[S_UPYRAMID][0].points=5;
Robot[S_UPYRAMID][0].pnt=sUPyramid;
Robot[S_UPYRAMID][0].copy=UPyramid2;
Robot[S_UPYRAMID][0].surfaces=5;
Robot[S_UPYRAMID][0].surface=UPyramidsurface;
Robot[S_UPYRAMID][0].vsurface=UPyramidv;
RobotSize[S_UPYRAMID]=1;
/*-M_Upside Down Pyramid-------------------*/
Robot[M_UPYRAMID] = mUPyramidparts;
Robot[M_UPYRAMID][0].points=5;
Robot[M_UPYRAMID][0].pnt=mUPyramid;
Robot[M_UPYRAMID][0].copy=UPyramid2;
Robot[M_UPYRAMID][0].surfaces=5;
Robot[M_UPYRAMID][0].surface=UPyramidsurface;
Robot[M_UPYRAMID][0].vsurface=UPyramidv;
RobotSize[M_UPYRAMID]=1;
}
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */

Prism FWallparts[1];
Prism CWallparts[1];

int fwall[4][3]={   {-128, 128,-Floor},
					{ 128,-128,-Floor},
					{-128, 128, Floor},
					{ 128,-128, Floor}};

int fwall2[4][3];
unsigned char  fwallv[1];
unsigned char  fwallsurface[1][SURFSIZE]={{c_dwall,4,2,3,1,0}};/*top*/

int cwall[8][3]={   {  -128,   128,-Floor},
					{     0,128-16,-Floor},
					{128-16,     0,-Floor},
					{   128,  -128,-Floor},
					{  -128,   128, Floor},
					{     0,128-16, Floor},
					{128-16,     0, Floor},
					{   128,  -128, Floor}};

int cwall2[8][3];
unsigned char  cwallv[3];
unsigned char  cwallsurface[3][SURFSIZE]={{c_dwall,4,1,0,4,5},
							   {c_dwall,4,2,1,5,6},
							   {c_dwall,4,3,2,6,7}};/*top*/
/*---------------------------------------------------------------------
 *---------------------------------------------------------------------
 */
InitWall(RobotSize)
int RobotSize[];
{
Robot[FWALL] = FWallparts;
Robot[FWALL][0].points=4;
Robot[FWALL][0].pnt=fwall;
Robot[FWALL][0].copy=fwall2;
Robot[FWALL][0].surfaces=1;
Robot[FWALL][0].vsurface=fwallv;
Robot[FWALL][0].surface=fwallsurface;

Robot[CWALL] = CWallparts;
Robot[CWALL][0].points=8;
Robot[CWALL][0].pnt=cwall;
Robot[CWALL][0].copy=cwall2;
Robot[CWALL][0].surfaces=3;
Robot[CWALL][0].surface=cwallsurface;
Robot[CWALL][0].vsurface=cwallv;
}
/*---------------------------------------------------------------------- 
 *---------------------------------------------------------------------- 
 */
#include "tank.h"
extern int battledx;
BattleInit()
{
int i,j,k;
int temp[257];
Enter.xloc=16000;
Enter.yloc=16000;
Enter.look=Enter.ang=32;
Ship.xloc=0;
Ship.yloc=0;
Ship.look=Ship.ang=32;

battledx=Width/59;
for(i=0;i<257;i++)
	temp[i]=10+(0x01F&Random());
for(i=0;i<256;i++)
	mountains[i]=((temp[i]+temp[i+1])>>1);
/*-Rock-------------------*/
Rock.points=5;
Rock.pnt=Rck;
Rock.copy=Rck2;
Rock.surfaces=4;
Rock.surface=Rcksurface;
Rock.vsurface=Rckv;
for(i=0;i<5;i++)
	Rock.pnt[i][2]-=Floor;
/*-Rock-------------------*/
Project.points=5;
Project.pnt=proj;
Project.copy=proj2;
Project.surfaces=4;
Project.surface=projsurface;
Project.vsurface=projv;
for(i=0;i<5;i++)
	Project.pnt[i][2]-=Floor;
/*-Entrance-------------------*/
Entrance[0].points=8;
Entrance[0].pnt=Ent;
Entrance[0].copy=Ent2;
Entrance[0].surfaces=4;
Entrance[0].surface=Entsurface;
Entrance[0].vsurface=Entv;
for(i=0;i<8;i++)
	Entrance[0].pnt[i][2]-=Floor;

Entrance[1].points=4;
Entrance[1].pnt=EDoor;
Entrance[1].copy=EDoor2;
Entrance[1].surfaces=1;
Entrance[1].surface=EDoorsurface;
Entrance[1].vsurface=EDoorv;
for(i=0;i<4;i++)
	Entrance[1].pnt[i][2]-=Floor;
/*-Tank-------------------*/
Tank[0].points=6;
Tank[0].pnt=dAbdomen;
Tank[0].copy=dAbdomen2;
Tank[0].surfaces=8;
Tank[0].surface=dAbdomensurface;
Tank[0].vsurface=dAbdomenv;

Tank[1].points=4;
Tank[1].pnt=lPincer;
Tank[1].copy=lPincer2;
Tank[1].surfaces=4;
Tank[1].surface=lPincersurface;
Tank[1].vsurface=lPincerv;

Tank[2].points=4;
Tank[2].pnt=rPincer;
Tank[2].copy=rPincer2;
Tank[2].surfaces=4;
Tank[2].surface=rPincersurface;
Tank[2].vsurface=rPincerv;

Tank[3].pnt=llPincer;

Tank[4].pnt=rrPincer;

Tank[5].points=3;
Tank[5].pnt=leye;
Tank[5].copy=leye2;
Tank[5].surfaces=2;
Tank[5].surface=leyesurface;
Tank[5].vsurface=leyev;

Tank[6].points=3;
Tank[6].pnt=reye;
Tank[6].copy=reye2;
Tank[6].surfaces=2;
Tank[6].surface=reyesurface;
Tank[6].vsurface=reyev;
/*-Shuttle-------------------*/
Shuttle[0].points=12;
Shuttle[0].pnt=SBody;
Shuttle[0].copy=SBody2;
Shuttle[0].surfaces=4;
Shuttle[0].surface=SBodysurface;
Shuttle[0].vsurface=SBodyv;
for(i=0;i<12;i++)
	Shuttle[0].pnt[i][2]-=Floor;

Shuttle[1].points=7;
Shuttle[1].pnt=SFront;
Shuttle[1].copy=SFront2;
Shuttle[1].surfaces=6;
Shuttle[1].surface=SFrontsurface;
Shuttle[1].vsurface=SFrontv;
for(i=0;i<7;i++)
	Shuttle[1].pnt[i][2]-=Floor;

Shuttle[2].points=7;
Shuttle[2].pnt=SBack;
Shuttle[2].copy=SBack2;
Shuttle[2].surfaces=5;
Shuttle[2].surface=SBacksurface;
Shuttle[2].vsurface=SBackv;
for(i=0;i<7;i++)
	Shuttle[2].pnt[i][2]-=Floor;

Shuttle[3].points=4;
Shuttle[3].pnt=FTop;
Shuttle[3].copy=FTop2;
Shuttle[3].surfaces=1;
Shuttle[3].surface=FTopsurface;
Shuttle[3].vsurface=FTopv;
for(i=0;i<4;i++)
	Shuttle[3].pnt[i][2]-=Floor;

Shuttle[4].points=4;
Shuttle[4].pnt=FLeft;
Shuttle[4].copy=FLeft2;
Shuttle[4].surfaces=1;
Shuttle[4].surface=FLeftsurface;
Shuttle[4].vsurface=FLeftv;
for(i=0;i<4;i++)
	Shuttle[4].pnt[i][2]-=Floor;

Shuttle[5].points=4;
Shuttle[5].pnt=FRight;
Shuttle[5].copy=FRight2;
Shuttle[5].surfaces=1;
Shuttle[5].surface=FRightsurface;
Shuttle[5].vsurface=FRightv;
for(i=0;i<4;i++)
	Shuttle[5].pnt[i][2]-=Floor;

Shuttle[6].points=4;
Shuttle[6].pnt=SDoor;
Shuttle[6].copy=SDoor2;
Shuttle[6].surfaces=1;
Shuttle[6].surface=SDoorsurface;
Shuttle[6].vsurface=SDoorv;
for(i=0;i<4;i++)
	Shuttle[6].pnt[i][2]-=Floor;
}	

