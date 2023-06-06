Prism Pyramidparts[5];
#define PSIZE 75
int Pyramid[5][3]={	{-PSIZE, PSIZE, 30},
					{ PSIZE, PSIZE, 30},
					{ PSIZE,-PSIZE, 30},
					{-PSIZE,-PSIZE, 30},
					{   0,   0,200}};
int Pyramid2[5][3];
unsigned char  Pyramidv[4];
unsigned char  Pyramidsurface[4][SURFSIZE]={	
							{c_pyramid,3,1,0,4,1},
							{c_pyramid,3,2,1,4,2},
							{c_pyramid,3,3,2,4,3},
							{c_pyramid,3,0,3,4,0}};
						
int Pshadow[4][3]={	{-PSIZE, PSIZE, 0},
					{ PSIZE, PSIZE, 0},
					{ PSIZE,-PSIZE, 0},
					{-PSIZE,-PSIZE, 0}};
					
int Pshadow2[4][3];
unsigned char  Pshadowv[1];
unsigned char  Pshadowsurface[4][SURFSIZE]={{BLACK,4,3,2,1,0,3}};


Prism fPyramidparts[1];
int fPyramid[5][3]={	{-PSIZE, PSIZE, 0},
					{ PSIZE, PSIZE, 0},
					{ PSIZE,-PSIZE, 0},
					{-PSIZE,-PSIZE, 0},
					{   0,   0,170}};

Prism sPyramidparts[1];
#define sPSIZE 40
int sPyramid[5][3]={	{-sPSIZE, sPSIZE, 0},
					{ sPSIZE, sPSIZE, 0},
					{ sPSIZE,-sPSIZE, 0},
					{-sPSIZE,-sPSIZE, 0},
					{   0,   0,100}};
						
Prism mPyramidparts[1];
#define mPSIZE 20
int mPyramid[5][3]={	{-mPSIZE, mPSIZE, 0},
					{ mPSIZE, mPSIZE, 0},
					{ mPSIZE,-mPSIZE, 0},
					{-mPSIZE,-mPSIZE, 0},
					{   0,   0,50}};

int pball[2][3]={	{0,   0, 175},
					{0,   0, 200}};
int pball2[2][3];
unsigned char  pballv[1];
unsigned char  pballsurface[1][SURFSIZE]={{c_eyeball,20}};

int piris[4][3]={	{15,	  0,	 185},
					{15,	 15,	 200},
					{15,	  0,	 215},
					{15,	-15,	 200}};
int piris2[4][3];
unsigned char  pirisv[1];
unsigned char  pirissurface[1][SURFSIZE]={{c_iris,4,0,1,2,3,0}};

int ppupil[4][3]={
				{16,	  0,	 194},
				{16,	  6,	 200},
				{16,	  0,	 206},
				{16,	- 6,	 200}};
			
int ppupil2[4][3];
unsigned char  ppupilv[1];
unsigned char  ppupilsurface[1][SURFSIZE]={{c_pupil,4,0,1,2,3,0}};
