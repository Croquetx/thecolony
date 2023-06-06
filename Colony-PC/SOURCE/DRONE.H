
Prism Droneparts[7];
int dAbdomen[6][3]={	{	  0,   0,  170},
			{ 	120,   0,  130},
			{	  0, 100,  130},
			{  -130,   0,  130},
			{	  0,-100,  130},
			{ 	  0,   0,  100}};
int dAbdomen2[6][3];
int dAbdomenv[8];
int dAbdomensurface[8][SURFSIZE]={{cDRONE,3,0,1,2,0},
				{cDRONE,3,0,2,3,0},
				{cDRONE,3,0,3,4,0},
				{cDRONE,3,0,4,1,0},
				{cDRONE,3,5,2,1,5},
				{cDRONE,3,5,3,2,5},
				{cDRONE,3,5,4,3,5},
				{cDRONE,3,5,1,4,5}};
int lPincer[4][3];
int lPincer2[4][3];
int lPincerv[4];
int lPincersurface[4][SURFSIZE]={{cCLAW1,3,0,2,1,0},
				   {cCLAW1,3,0,1,3,0},
				   {cCLAW2,3,0,3,2,0},
				   {cCLAW2,3,1,2,3,1}};
int rPincer[4][3];
int rPincer2[4][3];
int rPincerv[4];
int rPincersurface[4][SURFSIZE]={{cCLAW1,3,0,1,2,0},
				   {cCLAW1,3,0,3,1,0},
				   {cCLAW2,3,0,2,3,0},
				   {cCLAW2,3,1,3,2,1}};
int llPincer[4][3]={
		{0,0,130},
		{50,-2,130},
		{35,-20,140},
		{35,-20,120}};
int rrPincer[4][3]={
		{0,0,130},
		{50,2,130},
		{35,20,140},
		{35,20,120}};
					
int leye[3][3]={	{	 60,   0,  150},
			{ 	 60,  50,  130},
			{	 60,  25,  150}};
int leye2[3][3];
int leyev[2];
int leyesurface[2][SURFSIZE]={{cEYES,3,0,1,2,0},
				{cEYES,3,0,2,1,0}};
int reye[3][3]={	{	 60,   0,  150},
			{ 	 60, -50,  130},
			{	 60, -25,  150}};
int reye2[3][3];
int reyev[2];
int reyesurface[2][SURFSIZE]={{cEYES,3,0,1,2,0},
			{cEYES,3,0,2,1,0}};

