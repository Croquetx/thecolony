Prism CChair[5];
int Cseat[4][3]={	{-40,40,60},
					{ 40,40,60},
					{ 40,-40,60},
					{-40,-40,60}};
int Cseat2[4][3];
unsigned char  Cseatv[1];
unsigned char  Cseatsurface[1][SURFSIZE]={{c_cchair,4,3,2,1,0}};

int Carmleft[4][3]={{-50,40,90},
					{-40, 40, 60},
					{-40,-40, 60},
					{-50,-40, 90}};
int Carmleft2[4][3];
unsigned char  Carmleftv[1];
unsigned char  Carmleftsurface[1][SURFSIZE]={{c_cchair,4,3,2,1,0}};

int Carmrite[4][3]={{50,40,90},
					{40, 40,60},
					{40,-40,60},
					{50,-40,90}};
int Carmrite2[4][3];
unsigned char  Carmritev[1];
unsigned char  Carmritesurface[1][SURFSIZE]={	{c_cchair,4,3,2,1,0}};

int Cback[4][3]={	{-20,60,150},
					{ 20,60,150},
					{ 40,40, 60},
					{-40,40, 60}};
int Cback2[4][3];
unsigned char  Cbackv[2];
unsigned char  Cbacksurface[2][SURFSIZE]={{c_cchair,4,3,2,1,0},
						{c_cchair,4,0,1,2,3}};

int Cbase[8][3]={	{-5, 5,   0},
					{ 5, 5,   0},
					{ 5,-5,   0},
					{-5,-5,   0},
					{-5, 5,60},
					{ 5, 5,60},
					{ 5,-5,60},
					{-5,-5,60}};

int Cbase2[8][3];
unsigned char  Cbasev[4];
unsigned char  Cbasesurface[4][SURFSIZE]={{c_cchairbase,4,0,3,7,4},
							{c_cchairbase,4,3,2,6,7},
							{c_cchairbase,4,1,0,4,5},
							{c_cchairbase,4,2,1,5,6}};
