
Prism Queenparts[7];

int qball[2][3]={	{0,   0, 130},
			{0,   0, 155}};
int qball2[2][3];
int qballv[1];
int qballsurface[1][SURFSIZE]={{cEYE,20}};

int qiris[4][3]={	{15,	  0,	 140},
			{15,	 15,	 155},
			{15,	  0,	 170},
			{15,	-15,	 155}};
int qiris2[4][3];
int qirisv[1];
int qirissurface[1][SURFSIZE]={{cIRIS,4,0,1,2,3,0}};

int qpupil[4][3]={
		{16,	  0,	 148},
		{16,	  6,	 155},
		{16,	  0,	 161},
		{16,	- 6,	 155}};
			
int qpupil2[4][3];
int qpupilv[1];
int qpupilsurface[1][SURFSIZE]={{cPUPIL,4,0,1,2,3,0}};

int qAbdomen[9][3]=	{{ 	120,   0,  130},
			{	 30,   0,  160},
			{ 	 30,   0,  100},
			{	 30,  50,  130},
			{	 30, -50,  130},
			{ 	  0,   0,  150},
			{     0,   0,  110},
			{     0,  25,  130},
			{     0, -25,  130}};
int qAbdomen2[9][3];
int qAbdomenv[9];
int qAbdomensurface[9][SURFSIZE]={{cQUEEN,3,0,3,1,0},
				{cQUEEN,3,0,1,4,0},
				{cQUEEN,3,0,2,3,0},
				{cQUEEN,3,0,4,2,0},
				{cQUEEN,4,1,5,8,4,1},
				{cQUEEN,4,1,3,7,5,1},
				{cQUEEN,4,2,4,8,6,2},
				{cQUEEN,4,2,6,7,3,2},
				{cCLEAR,4,5,7,6,8,5}};
int qThorax[9][3]=	{{ 	-120,   0,  130},
			{	 -50,   0,  170},
			{ 	 -50,   0,	90},
			{	 -50,  60,  130},
			{	 -50, -60,  130},
			{ 	  0,   0,  150},
			{     0,   0,  110},
			{     0,  25,  130},
			{     0, -25,  130}};
int qThorax2[9][3];
int qThoraxv[8];
int qThoraxsurface[8][SURFSIZE]={ {cQUEEN,3,0,1,3,0},
				{cQUEEN,3,0,4,1,0},
				{cQUEEN,3,0,3,2,0},
				{cQUEEN,3,0,2,4,0},
				{cQUEEN,4,1,4,8,5,1},
				{cQUEEN,4,1,5,7,3,1},
				{cQUEEN,4,2,6,8,4,2},
				{cQUEEN,4,2,3,7,6,2}};
							
int lwing[4][3]={	{80,	0,	140},
			{-40, 	10,	200},
			{-120,	60,	170},
			{-40,	120,	140}};
int lwing2[4][3];
int lwingv[1];
int lwingsurface[1][SURFSIZE]={{cCLEAR,4,0,1,2,3}};

int rwing[4][3]={	{80,	0,	140},
			{-40, 	-10,	200},
			{-120,	-60,	170},
			{-40,	-120,	140}};
int rwing2[4][3];
int rwingv[1];
int rwingsurface[1][SURFSIZE]={{cCLEAR,4,0,1,2,3}};