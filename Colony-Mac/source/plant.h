Prism Plantparts[8];

int pot[12][3]={	{ 10, 17,40},
					{ 20,  0,40},
					{ 10,-17,40},
					{-10,-17,40},
					{-20,  0,40},
					{-10, 17,40},
					
					{  8, 12, 0},
					{ 15,  0, 0},
					{  8,-12, 0},
					{ -8,-12, 0},
					{-15,  0, 0},
					{ -8, 12, 0}};
int pot2[12][3];
unsigned char  potv[6];
unsigned char  potsurface[6][SURFSIZE]={{c_pot,4,0,1,7,6},
						{c_pot,4,1,2,8,7},
						{c_pot,4,2,3,9,8},
						{c_pot,4,3,4,10,9},
						{c_pot,4,4,5,11,10},
						{c_pot,4,5,0,6,11}};

int toppot[6][3]={	{ 10, 17,40},
					{ 20,  0,40},
					{ 10,-17,40},
					{-10,-17,40},
					{-20,  0,40},
					{-10, 17,40}};
int toppot2[6][3];
unsigned char  toppotv[1];
unsigned char  toppotsurface[1][SURFSIZE]={{c_soil,6,5,4,3,2,1,0}};

int leaf0[3][3]={	{0,0,0},
					{20,20,150},
					{70,70,100}};
int leaf02[3][3];
unsigned char  leaf0v[2];
unsigned char  leaf0surface[2][SURFSIZE]={{c_plant,3,0,1,2},
						{c_plant,3,2,1,0}};

int leaf1[3][3]={	{0,0,0},
					{-20,30,100},
					{-60,50,50}};
int leaf12[3][3];
unsigned char  leaf1v[2];
unsigned char  leaf1surface[2][SURFSIZE]={{c_plant,3,0,1,2},
						{c_plant,3,2,1,0}};

int leaf2[3][3]={	{0,0,0},
					{-20,-10,70},
					{-90,-70,50}};
int leaf22[3][3];
unsigned char  leaf2v[2];
unsigned char  leaf2surface[2][SURFSIZE]={{c_plant,3,0,1,2},
						{c_plant,3,2,1,0}};

int leaf3[3][3]={	{0,0,0},
					{20,-10,50},
					{90,-70,70}};
int leaf32[3][3];
unsigned char  leaf3v[2];
unsigned char  leaf3surface[2][SURFSIZE]={{c_plant,3,0,1,2},
						{c_plant,3,2,1,0}};

int leaf4[3][3]={	{0,0,0},
					{20,-30,190},
					{40,-60,150}};
int leaf42[3][3];
unsigned char  leaf4v[2];
unsigned char  leaf4surface[2][SURFSIZE]={{c_plant,3,0,1,2},
						{c_plant,3,2,1,0}};

int leaf5[3][3]={	{0,0,0},
					{20,-10,130},
					{50,-80,200}};
int leaf52[3][3];
unsigned char  leaf5v[2];
unsigned char  leaf5surface[2][SURFSIZE]={{c_plant,3,0,1,2},
						{c_plant,3,2,1,0}};
