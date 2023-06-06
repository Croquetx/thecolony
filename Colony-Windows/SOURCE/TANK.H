Prism Tank[7];
Prism Entrance[2];
Prism Shuttle[7];
Prism Project;

extern int dAbdomen[6][3];
extern int dAbdomen2[6][3];
extern int dAbdomenv[8];
extern int dAbdomensurface[8][SURFSIZE];
extern int lPincer[4][3];
extern int lPincer2[4][3];
extern int lPincerv[4];
extern int lPincersurface[4][SURFSIZE];
extern int rPincer[4][3];
extern int rPincer2[4][3];
extern int rPincerv[4];
extern int rPincersurface[4][SURFSIZE];
extern int llPincer[4][3];
extern int rrPincer[4][3];
extern int leye[3][3];
extern int leye2[3][3];
extern int leyev[2];
extern int leyesurface[2][SURFSIZE];
extern int reye[3][3];
extern int reye2[3][3];
extern int reyev[2];
extern int reyesurface[2][SURFSIZE];


Prism Rock;
#define BSIZE 75
int Rck[5][3]={	{-BSIZE, BSIZE, 0},
		{ BSIZE, BSIZE, 0},
		{ BSIZE,-BSIZE, 0},
		{-BSIZE,-BSIZE, 0},
		{   0,   0,200}};
int Rck2[5][3];
int Rckv[4];
int Rcksurface[4][SURFSIZE]={	{cROCK,3,1,0,4,1},
				{cROCK,3,2,1,4,2},
				{cROCK,3,3,2,4,3},
				{cROCK,3,0,3,4,0}};

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
int Entv[4];
int Entsurface[4][SURFSIZE]={	{cCOLONY,4,1,0,4,5,1},
				{cCOLONY,4,0,3,7,4,0},
				{cCOLONY,4,3,2,6,7,3},
				{cCOLONY,4,2,1,5,6,2}};
						
int EDoor[4][3]={	{-60,LSIZE,0},
			{60,LSIZE,0},
			{50,(LSIZE+HSIZE)/2,200},
			{-50,(LSIZE+HSIZE)/2,200}};
int EDoor2[4][3];
int EDoorv[1];
int EDoorsurface[1][SURFSIZE]={{cCDOOR,4,0,3,2,1,0}};
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
int SBodyv[4];
int SBodysurface[4][SURFSIZE]={	{cSHIP,4,0,6,7,1,0},
				{cSHIP,4,1,7,8,2,1},
				{cSHIP,4,3,9,10,4,3},
				{cSHIP,4,4,10,11,5,4}};

int SFront[7][3]={	{ 500, 250, 0},
			{ 500, 350, 200},
			{ 500, 150, 400},
			{ 500,-150, 400},
			{ 500,-350, 200},
			{ 500,-250, 0},
			{ 900,   0, 50}};

int SFront2[7][3];
int SFrontv[6];
int SFrontsurface[6][SURFSIZE]={{cSHIP,3,0,1,6,0},
				{cSHIP,3,1,2,6,1},
				{cSHIP,3,2,3,6,2},
				{cSHIP,3,3,4,6,3},
				{cSHIP,3,4,5,6,4},
				{cSHIP,3,5,0,6,5}};

int SBack[7][3]={	{-500, 250, 0},
			{-500, 350, 200},
			{-500, 150, 400},
			{-500,-150, 400},
			{-500,-350, 200},
			{-500,-250, 0},
			{-900,   0,400}};

int SBack2[7][3];
int SBackv[5];
int SBacksurface[5][SURFSIZE]={	{cSHIP,3,0,6,1,0},
				{cSHIP,3,1,6,2,1},
				{cSHIP,3,3,6,4,3},
				{cSHIP,3,4,6,5,4},
				{cSHIP,3,5,6,0,5}};

int FTop[4][3]={	{-500,   0, 400},
			{-900,   0, 400},
			{-1000,   0, 800},
			{-700,   0, 800}};

int FTop2[4][3];
int FTopv[1];
int FTopsurface[1][SURFSIZE]={	{cSHIP,4,0,1,2,3,0}};

int FLeft[4][3]={	{-100, -350, 200},
			{-700, -350, 200},
			{-900,-750, 200},
			{-500, -750, 200}};

int FLeft2[4][3];
int FLeftv[1];
int FLeftsurface[1][SURFSIZE]={	{cSHIP,4,0,1,2,3,0}};

int FRight[4][3]={	{-100, 350, 200},
			{-700, 350, 200},
			{-900,750, 200},
			{-500, 750, 200}};

int FRight2[4][3];
int FRightv[1];
int FRightsurface[1][SURFSIZE]={{cSHIP,4,0,1,2,3,0}};

int SDoor[4][3]={	{-50, 262,25},
			{ 50, 262,25},
			{ 60, 325,150},
			{-60, 325,150}};
int SDoor2[4][3];
int SDoorv[1];
int SDoorsurface[1][SURFSIZE]={	{cSHIP,4,0,3,2,1,0}};


int proj[5][3]={{80,0,80},
		{-80,20,80},
		{-80,0,100},
		{-80,-20,80},
		{-80,0,60}};
int proj2[5][3];
int projv[5];
int projsurface[5][SURFSIZE]={
				{cBLACK,4,1,4,3,2,1},
				{cPROJ,3,0,1,2,0},
				{cPROJ,3,0,2,3,0},
				{cPROJ,3,0,3,4,0},
				{cPROJ,3,0,4,1,0}};
