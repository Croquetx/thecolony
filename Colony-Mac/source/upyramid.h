Prism UPyramidparts[2];
#define UPSIZE 75
#define UPSSIZE 25
int UPyramid[5][3]={{-UPSIZE, UPSIZE, 190},
					{ UPSIZE, UPSIZE, 190},
					{ UPSIZE,-UPSIZE, 190},
					{-UPSIZE,-UPSIZE, 190},
					{   0,   0, 30}};
int UPyramid2[5][3];
unsigned char  UPyramidv[5];
unsigned char  UPyramidsurface[5][SURFSIZE]={
							{c_upyramid,3,0,1,4,0},
							{c_upyramid,3,1,2,4,1},
							{c_upyramid,3,2,3,4,2},
							{c_upyramid,3,3,0,4,3},
							{c_upyramid,4,3,2,1,0,3}};

int UPshadow[4][3]={{-UPSSIZE, UPSSIZE, 0},
					{ UPSSIZE, UPSSIZE, 0},
					{ UPSSIZE,-UPSSIZE, 0},
					{-UPSSIZE,-UPSSIZE, 0}};
					
int UPshadow2[4][3];
unsigned char  UPshadowv[1];
unsigned char  UPshadowsurface[1][SURFSIZE]={{BLACK,4,3,2,1,0,3}};

Prism fUPyramidparts[1];
int fUPyramid[5][3]={	{-UPSIZE, UPSIZE, 170},
					{ UPSIZE, UPSIZE, 170},
					{ UPSIZE,-UPSIZE, 170},
					{-UPSIZE,-UPSIZE, 170},
					{   0,   0,  0}};

Prism sUPyramidparts[1];
#define sUPSIZE 40
int sUPyramid[5][3]={{-sUPSIZE, sUPSIZE, 100},
					{ sUPSIZE, sUPSIZE, 100},
					{ sUPSIZE,-sUPSIZE, 100},
					{-sUPSIZE,-sUPSIZE, 100},
					{   0,   0,  0}};

Prism mUPyramidparts[1];
#define mUPSIZE 20
int mUPyramid[5][3]={{-mUPSIZE, mUPSIZE, 50},
					{ mUPSIZE, mUPSIZE, 50},
					{ mUPSIZE,-mUPSIZE, 50},
					{-mUPSIZE,-mUPSIZE, 50},
					{   0,   0,0}};
