
Prism Droneparts[7];
int dAbdomen[6][3]={	{	  0,   0,  170},
					{ 	120,   0,  130},
					{	  0, 100,  130},
					{  -130,   0,  130},
					{	  0,-100,  130},
					{ 	  0,   0,  100}};
int dAbdomen2[6][3];
unsigned char  dAbdomenv[8];
unsigned char  dAbdomensurface[8][SURFSIZE]={{c_drone,3,0,1,2,0},
							{c_drone,3,0,2,3,0},
							{c_drone,3,0,3,4,0},
							{c_drone,3,0,4,1,0},
							{c_drone,3,5,2,1,5},
							{c_drone,3,5,3,2,5},
							{c_drone,3,5,4,3,5},
							{c_drone,3,5,1,4,5}
							};
int lPincer[4][3];
int lPincer2[4][3];
unsigned char  lPincerv[4];
unsigned char  lPincersurface[4][SURFSIZE]={
							{c_jaws1,3,0,2,1,0},
							{c_jaws1,3,0,1,3,0},
							{c_jaws2,3,0,3,2,0},
							{c_jaws2,3,1,2,3,1}};
int rPincer[4][3];
int rPincer2[4][3];
unsigned char  rPincerv[4];
unsigned char  rPincersurface[4][SURFSIZE]={
							{c_jaws1,3,0,1,2,0},
							{c_jaws1,3,0,3,1,0},
							{c_jaws2,3,0,2,3,0},
							{c_jaws2,3,1,3,2,1}};
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
unsigned char  leyev[2];
unsigned char  leyesurface[2][SURFSIZE]={
						{c_edrone,3,0,1,2,0},
						{c_edrone,3,0,2,1,0}};
int reye[3][3]={	{	 60,   0,  150},
					{ 	 60, -50,  130},
					{	 60, -25,  150}};
int reye2[3][3];
unsigned char  reyev[2];
unsigned char  reyesurface[2][SURFSIZE]={
						{c_edrone,3,0,1,2,0},
						{c_edrone,3,0,2,1,0}};

