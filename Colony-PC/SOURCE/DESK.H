Prism Deskparts[10];

int desktop[4][3]={	{-150, 110,100},
			{ 150, 110,100},
			{ 150,-110,100},
			{-150,-110,100}};
int desktop2[4][3];
int desktopv[1];
int desktopsurface[1][SURFSIZE]={{cDESKTOP,4,3,2,1,0}};


int deskleft[8][3]={{-135, 95,   0},
		{ -55, 95,   0},
		{ -55,-95,   0},
		{-135,-95,   0},
		{-135, 95,100},
		{ -55, 95,100},
		{ -55,-95,100},
		{-135,-95,100}};

int deskleft2[8][3];
int deskleftv[4];
int desksurface[4][SURFSIZE]={{cDESK,4,0,3,7,4},
				{cDESK,4,3,2,6,7},
				{cDESK,4,1,0,4,5},
				{cDESK,4,2,1,5,6}};
int deskrite[8][3]={{  55, 95,   0},
		{ 135, 95,   0},
		{ 135,-95,   0},
		{  55,-95,   0},
		{  55, 95,100},
		{ 135, 95,100},
		{ 135,-95,100},
		{  55,-95,100}};

int deskrite2[8][3];
int deskritev[4];

int seat[4][3]={	{-40,210,60},
			{ 40,210,60},
			{ 40,115,60},
			{-40,115,60}};
int seat2[4][3];
int seatv[1];
int seatsurface[1][SURFSIZE]={{cDESKCHAIR,4,3,2,1,0}};

int armleft[4][3]={ {-40,210,90},
		{-40,210,  0},
		{-40,115,  0},
		{-40,115,90}};
int armleft2[4][3];
int armleftv[2];
int armleftsurface[2][SURFSIZE]={{cCLEAR,4,3,2,1,0},
				{cCLEAR,4,0,1,2,3}};

int armrite[4][3]={ {40,210,90},
		{40,210,  0},
		{40,115,  0},
		{40,115,90}};
int armrite2[4][3];
int armritev[2];
int armritesurface[2][SURFSIZE]={	{cCLEAR,4,3,2,1,0},
					{cCLEAR,4,0,1,2,3}};

int back[4][3]={	{-40,210,130},
			{ 40,210,130},
			{ 40,210, 70},
			{-40,210, 70}};
int back2[4][3];
int backv[2];
int backsurface[2][SURFSIZE]={{cDESKCHAIR,4,3,2,1,0},
			{cDESKCHAIR,4,0,1,2,3}};


int monitor[8][3]={{  75, 20,120},
		{ 115, 20,120},
		{ 115,-20,120},
		{  75,-20,120},
		{  75, 20,155},
		{ 115, 20,155},
		{ 115,-20,145},
		{  75,-20,145}};
int monitor2[8][3];
int monitorv[5];

int computer[8][3]=
	{   {  70, 25,100},
		{ 120, 25,100},
		{ 120,-25,100},
		{  70,-25,100},
		{  70, 25,120},
		{ 120, 25,120},
		{ 120,-25,120},
		{  70,-25,120}};

int computer2[8][3];
int computerv[5];
int computersurface[5][SURFSIZE]={
			{cMAC,4,7,6,5,4},
			{cMAC,4,0,3,7,4},
			{cMAC,4,3,2,6,7},
			{cMAC,4,1,0,4,5},
			{cMAC,4,2,1,5,6}};


int screen[4][3]={	{80,20,125},
			{110,20,125},
			{110,20,150},
			{80,20,150}};
int screen2[4][3];
int screenv[1];
int screensurface[1][SURFSIZE]={{cMACSCREEN,4,3,2,1,0}};
