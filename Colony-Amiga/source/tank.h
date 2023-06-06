Prism Tank[7];
Prism Entrance[2];
Prism Shuttle[7];
Prism Project;

extern int dAbdomen[6][3];
extern int dAbdomen2[6][3];
extern unsigned char dAbdomenv[8];
extern unsigned char dAbdomensurface[8][SURFSIZE];
extern int lPincer[4][3];
extern int lPincer2[4][3];
extern unsigned char lPincerv[4];
extern unsigned char lPincersurface[4][SURFSIZE];
extern int rPincer[4][3];
extern int rPincer2[4][3];
extern unsigned char rPincerv[4];
extern unsigned char rPincersurface[4][SURFSIZE];
extern int llPincer[4][3];
extern int rrPincer[4][3];
extern int leye[3][3];
extern int leye2[3][3];
extern unsigned char leyev[2];
extern unsigned char leyesurface[2][SURFSIZE];
extern int reye[3][3];
extern int reye2[3][3];
extern unsigned char reyev[2];
extern unsigned char reyesurface[2][SURFSIZE];


Prism Rock;
#define BSIZE 75
int Rck[5][3]={	{-BSIZE, BSIZE, 0},
					{ BSIZE, BSIZE, 0},
					{ BSIZE,-BSIZE, 0},
					{-BSIZE,-BSIZE, 0},
					{   0,   0,200}};
int Rck2[5][3];
unsigned char  Rckv[4];
unsigned char  Rcksurface[4][SURFSIZE]={	{LTGRAY,3,1,0,4,1},
							{LTGRAY,3,2,1,4,2},
							{LTGRAY,3,3,2,4,3},
							{LTGRAY,3,0,3,4,0}};

#define LSIZE 300
#define HSIZE 250
int Ent[8][3]={		{-LSIZE, LSIZE, 0},
					{ LSIZE, LSIZE, 0},
					{ LSIZE,-LSIZE, 0},
					{-LSIZE,-LSIZE, 0},
					{-HSIZE, HSIZE,600},
					{ HSIZE, HSIZE,600},
					{ HSIZE,-HSIZE,600},
					{-HSIZE,-HSIZE,600}};
int Ent2[8][3];
unsigned char  Entv[4];
unsigned char  Entsurface[4][SURFSIZE]={	{LTGRAY,4,1,0,4,5,1},
						{LTGRAY,4,0,3,7,4,0},
						{LTGRAY,4,3,2,6,7,3},
						{LTGRAY,4,2,1,5,6,2}};
						
int EDoor[4][3]={	{-60,LSIZE,0},
					{60,LSIZE,0},
					{50,(LSIZE+HSIZE)/2,200},
					{-50,(LSIZE+HSIZE)/2,200}};
int EDoor2[4][3];
unsigned char  EDoorv[1];
unsigned char  EDoorsurface[1][SURFSIZE]={{LTGRAY,4,0,3,2,1,0}};
#define SSIZE 150
int SBody[12][3]={	{ 500, 250, 0},
					{ 500, 350, 200},
					{ 500, 150, 400},
					{ 500,-150, 400},
					{ 500,-350, 200},
					{ 500,-250, 0},
					{-500, 250, 0},
					{-500, 350, 200},
					{-500, 150, 400},
					{-500,-150, 400},
					{-500,-350, 200},
					{-500,-250, 0}};
int SBody2[12][3];
unsigned char  SBodyv[4];
unsigned char  SBodysurface[4][SURFSIZE]={	{LTGRAY,4,0,6,7,1,0},
							{LTGRAY,4,1,7,8,2,1},
							{LTGRAY,4,3,9,10,4,3},
							{LTGRAY,4,4,10,11,5,4}};

int SFront[7][3]={	{ 500, 250, 0},
					{ 500, 350, 200},
					{ 500, 150, 400},
					{ 500,-150, 400},
					{ 500,-350, 200},
					{ 500,-250, 0},
					{ 900,   0, 50}};

int SFront2[7][3];
unsigned char  SFrontv[6];
unsigned char  SFrontsurface[6][SURFSIZE]={	{LTGRAY,3,0,1,6,0},
							{LTGRAY,3,1,2,6,1},
							{LTGRAY,3,2,3,6,2},
							{LTGRAY,3,3,4,6,3},
							{LTGRAY,3,4,5,6,4},
							{LTGRAY,3,5,0,6,5}};

int SBack[7][3]={	{-500, 250, 0},
					{-500, 350, 200},
					{-500, 150, 400},
					{-500,-150, 400},
					{-500,-350, 200},
					{-500,-250, 0},
					{-900,   0,400}};

int SBack2[7][3];
unsigned char  SBackv[5];
unsigned char  SBacksurface[5][SURFSIZE]={	{LTGRAY,3,0,6,1,0},
							{LTGRAY,3,1,6,2,1},
							{LTGRAY,3,3,6,4,3},
							{LTGRAY,3,4,6,5,4},
							{LTGRAY,3,5,6,0,5}};

int FTop[4][3]={	{-500,   0, 400},
					{-900,   0, 400},
					{-1000,   0, 800},
					{-700,   0, 800}};

int FTop2[4][3];
unsigned char  FTopv[1];
unsigned char  FTopsurface[1][SURFSIZE]={	{LTGRAY,4,0,1,2,3,0}};

int FLeft[4][3]={	{-100, -350, 200},
					{-700, -350, 200},
					{-900,-750, 200},
					{-500, -750, 200}};

int FLeft2[4][3];
unsigned char  FLeftv[1];
unsigned char  FLeftsurface[1][SURFSIZE]={	{LTGRAY,4,0,1,2,3,0}};

int FRight[4][3]={	{-100, 350, 200},
					{-700, 350, 200},
					{-900,750, 200},
					{-500, 750, 200}};

int FRight2[4][3];
unsigned char  FRightv[1];
unsigned char  FRightsurface[1][SURFSIZE]={	{LTGRAY,4,0,1,2,3,0}};

int SDoor[4][3]={	{-50, 262,25},
					{ 50, 262,25},
					{ 60, 325,150},
					{-60, 325,150}};
int SDoor2[4][3];
unsigned char  SDoorv[1];
unsigned char  SDoorsurface[1][SURFSIZE]={	{LTGRAY,4,0,3,2,1,0}};


int proj[5][3]={
				{80,0,80},
				{-80,20,80},
				{-80,0,100},
				{-80,-20,80},
				{-80,0,60}};
int proj2[5][3];
unsigned char  projv[5];
unsigned char  projsurface[5][SURFSIZE]={
				{BLACK,4,1,4,3,2,1},
				{LTGRAY,3,0,1,2,0},
				{LTGRAY,3,0,2,3,0},
				{LTGRAY,3,0,3,4,0},
				{LTGRAY,3,0,4,1,0}};
