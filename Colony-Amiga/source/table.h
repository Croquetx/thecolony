Prism Tableparts[2];

int tabletop[4][3]={{-128, 128,100},
					{ 128, 128,100},
					{ 128,-128,100},
					{-128,-128,100}};
int tabletop2[4][3];
int tabletopv[1];
int tabletopsurface[1][SURFSIZE]={{LTGRAY,4,3,2,1,0}};

int tablebase[8][3]={{-5, 5,   0},
					{ 5, 5,   0},
					{ 5,-5,   0},
					{-5,-5,   0},
					{-5, 5,100},
					{ 5, 5,100},
					{ 5,-5,100},
					{-5,-5,100}};

int tablebase2[8][3];
int tablebasev[4];
int tablebasesurface[4][SURFSIZE]={{LTGRAY,4,0,3,7,4},
							{LTGRAY,4,3,2,6,7},
							{LTGRAY,4,1,0,4,5},
							{LTGRAY,4,2,1,5,6}};
