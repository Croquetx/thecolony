Prism Bed[3];

int BPost[4][3]={	{-82,128,100},
					{ 82,128,100},
					{ 82,128,  0},
					{-82,128,  0}};
int BPost2[4][3];
unsigned char  BPostv[1];
unsigned char  BPostsurface[1][SURFSIZE]={{c_bedhead,4,3,2,1,0}};

int Blanket[8][3]={	{-80, 70,   0},
					{ 80, 70,   0},
					{ 80,-175,   0},
					{-80,-175,   0},
					
					{-80, 70,60},
					{ 80, 70,60},
					{ 80,-175,60},
					{-80,-175,60}};

int Blanket2[8][3];
unsigned char  Blanketv[4];
unsigned char  Blanketsurface[4][SURFSIZE]={{c_bedblnkt,4,0,3,7,4},
							{c_bedblnkt,4,3,2,6,7},
							/*{LTGRAY,4,1,0,4,5},*/
							{c_bedblnkt,4,2,1,5,6},
							{c_bedblnkt,4,7,6,5,4}};

int Sheet[8][3]={	{-80,128, 30},
					{ 80,128, 30},
					{ 80, 70, 30},
					{-80, 70, 30},
					
					{-80,128,60},
					{ 80,128,60},
					{ 80, 70,60},
					{-80, 70,60}};

int Sheet2[8][3];
unsigned char  Sheetv[3];
unsigned char  Sheetsurface[3][SURFSIZE]={{c_bedsheet,4,0,3,7,4},
							/*{WHITE,4,3,2,6,7},front*/
							/*{WHITE,4,1,0,4,5},back*/
							{c_bedsheet,4,2,1,5,6},
							{c_bedsheet,4,7,6,5,4}};/*top*/

Prism BBed[3];

int BBPost[4][3]={	{-130,128,100},
					{ 130,128,100},
					{ 130,128,  0},
					{-130,128,  0}};
int BBPost2[4][3];
unsigned char  BBPostv[1];
unsigned char  BBPostsurface[1][SURFSIZE]={{c_bedhead,4,3,2,1,0}};

int BBlanket[8][3]={{-128, 70,   0},
					{ 128, 70,   0},
					{ 128,-175,   0},
					{-128,-175,   0},
					
					{-128, 70,60},
					{ 128, 70,60},
					{ 128,-175,60},
					{-128,-175,60}};

int BBlanket2[8][3];
unsigned char  BBlanketv[4];

int BSheet[8][3]={	{-128,128, 30},
					{ 128,128, 30},
					{ 128, 70, 30},
					{-128, 70, 30},
					
					{-128,128,60},
					{ 128,128,60},
					{ 128, 70,60},
					{-128, 70,60}};

int BSheet2[8][3];
unsigned char  BSheetv[3];
