Prism Cubeparts[4];
int Cube[6][3]={	{	  0,   0,  200},
					{ 	100,   0,  100},
					{	  0, 100,  100},
					{  -100,   0,  100},
					{	  0,-100,  100},
					{ 	  0,   0,	  0}};
int Cube2[6][3];
unsigned char  Cubev[8];
unsigned char  Cubesurface[8][SURFSIZE]={	{c_diamond,3,0,1,2,0},
							{c_diamond,3,0,2,3,0},
							{c_diamond,3,0,3,4,0},
							{c_diamond,3,0,4,1,0},
							{c_diamond,3,5,2,1,5},
							{c_diamond,3,5,3,2,5},
							{c_diamond,3,5,4,3,5},
							{c_diamond,3,5,1,4,5},
							};

Prism fCubeparts[1];
int fCube[6][3]={	{	  0,   0,  150},
					{ 	 75,   0,   75},
					{	  0,  75,   75},
					{   -75,   0,   75},
					{	  0, -75,   75},
					{ 	  0,   0,	  0}};

Prism sCubeparts[1];
int sCube[6][3]={	{	  0,   0,  100},
					{ 	 50,   0,   50},
					{	  0,  50,   50},
					{   -50,   0,   50},
					{	  0, -50,   50},
					{ 	  0,   0,	  0}};
Prism mCubeparts[1];
int mCube[6][3]={	{	  0,   0,  50},
					{ 	25,   0,  25},
					{	  0, 25,  25},
					{  -25,   0,  25},
					{	  0,-25,  25},
					{ 	  0,   0,	  0}};
