Prism Screen[1];

int vscreen[8][3]={	{-16, 64,  0},
					{ 16, 64,  0},
					{ 16,-64,  0},
					{-16,-64,  0},
					{-16, 64,288},
					{ 16, 64,288},
					{ 16,-64,288},
					{-16,-64,288}};

unsigned char  vscreensurface[4][SURFSIZE]={
							{c_monolith,4,0,3,7,4},
							{c_monolith,4,3,2,6,7},
							{c_monolith,4,1,0,4,5},
							{c_monolith,4,2,1,5,6}};


int vscreen2[8][3];
unsigned char  vscreenv[4];
