Prism Deskparts[9];

int desktop[4][3]={	{-150, 110,100},
					{ 150, 110,100},
					{ 150,-110,100},
					{-150,-110,100}};
int desktop2[4][3];
unsigned char  desktopv[1];
unsigned char  desktopsurface[1][SURFSIZE]={{c_desktop,4,3,2,1,0}};


int deskleft[8][3]={{-135, 95,   0},
					{ -55, 95,   0},
					{ -55,-95,   0},
					{-135,-95,   0},
					{-135, 95,100},
					{ -55, 95,100},
					{ -55,-95,100},
					{-135,-95,100}};

int deskleft2[8][3];
unsigned char  deskleftv[4];
unsigned char  deskleftsurface[4][SURFSIZE]={
							{c_desk,4,0,3,7,4},
							{c_desk,4,3,2,6,7},
							{c_desk,4,1,0,4,5},
							{c_desk,4,2,1,5,6}};

int deskrite[8][3]={{  55, 95,   0},
					{ 135, 95,   0},
					{ 135,-95,   0},
					{  55,-95,   0},
					{  55, 95,100},
					{ 135, 95,100},
					{ 135,-95,100},
					{  55,-95,100}};

int deskrite2[8][3];
unsigned char  deskritev[4];
unsigned char  deskritesurface[4][SURFSIZE]={
						{c_desk,4,0,3,7,4},
						{c_desk,4,3,2,6,7},
						{c_desk,4,1,0,4,5},
						{c_desk,4,2,1,5,6}};


int seat[4][3]={	{-40,210,60},
					{ 40,210,60},
					{ 40,115,60},
					{-40,115,60}};
int seat2[4][3];
unsigned char  seatv[1];
unsigned char  seatsurface[1][SURFSIZE]={{c_deskchair,4,3,2,1,0}};

int armleft[4][3]={ {-40,210,90},
					{-40,210,  0},
					{-40,115,  0},
					{-40,115,90}};
int armleft2[4][3];
unsigned char  armleftv[2];
unsigned char  armleftsurface[2][SURFSIZE]={
						{CLEAR,4,3,2,1,0},
						{CLEAR,4,0,1,2,3}};

int armrite[4][3]={ {40,210,90},
					{40,210,  0},
					{40,115,  0},
					{40,115,90}};
int armrite2[4][3];
unsigned char  armritev[2];
unsigned char  armritesurface[2][SURFSIZE]={
							{CLEAR,4,3,2,1,0},
							{CLEAR,4,0,1,2,3}};

int back[4][3]={	{-40,210,130},
					{ 40,210,130},
					{ 40,210, 70},
					{-40,210, 70}};
int back2[4][3];
unsigned char  backv[2];
unsigned char  backsurface[2][SURFSIZE]={
						{c_deskchair,4,3,2,1,0},
						{c_deskchair,4,0,1,2,3}};


int computer[8][3]={{  75, 20,100},
					{ 115, 20,100},
					{ 115,-20,100},
					{  75,-20,100},
					{  75, 20,150},
					{ 115, 20,150},
					{ 115,-20,150},
					{  75,-20,150}};

int computer2[8][3];
unsigned char  computerv[5];
unsigned char  computersurface[5][SURFSIZE]={
						{c_computer,4,7,6,5,4},
						{c_computer,4,0,3,7,4},
						{c_computer,4,3,2,6,7},
						{c_computer,4,1,0,4,5},
						{c_computer,4,2,1,5,6}};


int screen[4][3]={	{80,20,120},
					{110,20,120},
					{110,20,145},
					{80,20,145}};
int screen2[4][3];
unsigned char  screenv[1];
unsigned char  screensurface[1][SURFSIZE]={
					{c_screen,4,3,2,1,0}};