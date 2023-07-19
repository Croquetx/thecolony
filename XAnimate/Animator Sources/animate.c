/*--------------------------------- * The Animator * Copyright 1988 by David A. Smith * All Rights Reserved * 111 Gold Meadow Dr. * Cary, NC 27513 *---------------------------------*/#define EXT extern #include "adefs.h"WindowRecord aRecord;int abnum;#define ANIMATE		 8#define ERASE		 9#define UPONE		10#define DOWNONE		11#define UPTOP		12#define DOWNBOTTOM	13#define INFORMATION	14#define max(x,y) ((x<y) ? (y):(x))/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */InitAnimate(){Rect r;int i;DClip.top=size.top;DClip.bottom=size.bottom-BTOP;DClip.left=size.left;DClip.right=size.right;rBounds.bottom=HEIGHT-BTOP+4;rBounds.left=4;rBounds.right=WIDTH-4;rBounds.top=0;anum= -1;SetRect(&r, 90, 60, 507, 354);animWindow = NewWindow( &aRecord , &r, "\pObject Animator",	1, 0, -1L, 0, 0L);SetPort(animWindow);PenMode(8);SetOrigin(0,0);MakeGrafPort(&size,&meta1);SetPort(&meta1);ClipRect(&size);FillRect(&size,white);MoveTo(0,HEIGHT-BTOP);LineTo(WIDTH,HEIGHT-BTOP);TextFont(0);DrawAButtons();DrawBackGround(&meta1);DrawAnim();/*draw in the foreground*/SetPort( animWindow );AnimCopy();}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */DrawAButtons(){PicHandle Butt;Rect buttR;int xSize,ySize;Butt=GetPicture(1005);SizeRect(&xSize,&ySize,&(**Butt).picFrame);SetRect(&buttR,4,HEIGHT+4-BTOP,4+xSize,HEIGHT+4+ySize-BTOP);DrawPicture(Butt,&buttR);}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */animUpdate(){GrafPtr	savePort;GetPort( &savePort );SetPort(animWindow);BeginUpdate(animWindow);AnimCopy();DrawInfo();EndUpdate(animWindow);SetPort( savePort );}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */DrawInfo(){char str[255];int i=0;Rect r;if(maxSprite)	{	r.left=360; r.right=460;	r.top=HEIGHT+5-BTOP;r.bottom=HEIGHT+5;	FillRect(&r,white);	sprintf(str," %d/%d     ",anum+1,maxSprite);	while(str[i])i++;str[0]=i;	MoveTo(360,HEIGHT+20-BTOP);	DrawString(str);	InvertRect(&dbutton[lSprite[anum].acurrent]);	}}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */AnimCopy(){GrafPtr	savePort;GetPort( &savePort );SetPort(animWindow);CopyBits(&meta1.portBits,&animWindow->portBits,	&size,&size,srcCopy,NIL);SetPort( savePort );}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */AnimDCopy(){GrafPtr	savePort;GetPort( &savePort );SetPort(animWindow);CopyBits(&meta1.portBits,&animWindow->portBits,	&DClip,&DClip,srcCopy,NIL);SetPort( savePort );}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */DrawAnim(){GrafPtr	savePort;int cnum;Rect locate;GetPort( &savePort );SetPort(&meta1);if(anum!=-1)	{	cnum=FindASprite(anum,&locate);	ClipRect(&DClip);	CopyBits(cSprite[cnum].mask,		&meta1.portBits,		&cSprite[cnum].clip,&locate,		srcBic,NIL);	CopyBits(cSprite[cnum].fg,		&meta1.portBits,		&cSprite[cnum].clip,&locate,		srcOr,NIL);	ClipRect(&size);	}SetPort(savePort);}/*----------------------------------------------------------------------*//*----------------------------------------------------------------------*/int FindASprite(snum,pr)int snum;Rect *pr;{int cnum,xloc,yloc;cnum=lSprite[snum].acurrent;xloc=lSprite[snum].axloc + lSprite[snum].object[cnum].xloc;yloc=lSprite[snum].ayloc + lSprite[snum].object[cnum].yloc;cnum=lSprite[snum].object[cnum].spritenum;pr->top=cSprite[cnum].clip.top+yloc;pr->left=cSprite[cnum].clip.left+xloc;pr->bottom=cSprite[cnum].clip.bottom+yloc;pr->right=cSprite[cnum].clip.right+xloc;return(cnum);/*return the sprite number*/}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */DoAnimate(){Point p;int i;Rect r,dummy;if(maxSprite==0)return;SetPort(animWindow);if(Button())	{	GetMouse(&p);	if(p.v>HEIGHT-BTOP)AnimButton();	else MoveAObject(&p);	}}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */AnimButton(){int i,j,onoff;Point p;GrafPtr	savePort;int ch=0;int redraw=FALSE;GetPort( &savePort );SetPort(animWindow);onoff=FALSE;GetMouse(&p);for(i=0;i<lSprite[anum].size;i++)	{	if(p.h>dbutton[i].left &&		p.h<dbutton[i].right &&		p.v>dbutton[i].top &&		p.v<dbutton[i].bottom)		{		if(maxSprite)DrawInfo();		InvertRect(&dbutton[i]);		lSprite[anum].acurrent=i;		DrawBackGround(&meta1);		DrawAnim();/*draw in the foreground*/		SetPort( animWindow );		AnimDCopy();		FlushEvents(mDownMask|mUpMask|keyDownMask|keyUpMask|autoKeyMask,0);		SetPort(savePort);		return;		}	}for(i=8;i<15;i++)	{	if(p.h>dbutton[i].left &&		p.h<dbutton[i].right &&		p.v>dbutton[i].top &&		p.v<dbutton[i].bottom)		{		InvertRect(&dbutton[i]);		switch(i)			{			case ANIMATE:				doMovie();				break;			case ERASE:				KillAObject();				changed=TRUE;				redraw=TRUE;				break;			case UPONE:				AUpOne();				changed=TRUE;				redraw=TRUE;				break;			case DOWNONE:				ADownOne();				changed=TRUE;				redraw=TRUE;				break;			case UPTOP:				AUpTop();				changed=TRUE;				redraw=TRUE;				break;			case DOWNBOTTOM:				ADownBottom();				changed=TRUE;				redraw=TRUE;				break;			case INFORMATION:				SetExtend();				break;			}		InvertRect(&dbutton[i]);		if(redraw)			{			DrawBackGround(&meta0);			DrawPlane();/*draw in the foreground*/			DejaDCopy();			}		}	}}/*----------------------------------------------------------------------*/extern BitMap* MakeBitMap();SpriteAPaste(loc)Rect *loc;{Point p;int i;int current;Rect r;SetPort(animWindow);p.v=loc->top;p.h=loc->left;GlobalToLocal(&p);lSprite[anum].size++;current=lSprite[anum].acurrent+1;for(i=lSprite[anum].size-1;i>=current;i--)	{	lSprite[anum].object[i].spritenum=lSprite[anum].object[i-1].spritenum;	lSprite[anum].object[i].xloc=lSprite[anum].object[i-1].xloc;	lSprite[anum].object[i].yloc=lSprite[anum].object[i-1].yloc;	}lSprite[anum].object[current].yloc=p.v-lSprite[anum].ayloc;lSprite[anum].object[current].xloc=p.h-lSprite[anum].axloc;lSprite[anum].object[current].spritenum=locSprite;lSprite[anum].acurrent++;cSprite[locSprite].used++;r.left=r.top=0;r.bottom=max(cSprite[locSprite].clip.bottom,lSprite[anum].bg->bounds.bottom);r.right=max(cSprite[locSprite].clip.right,lSprite[anum].bg->bounds.right);KillBitMap(lSprite[anum].bg);lSprite[anum].bg=MakeBitMap(&r);DrawBackGround(&meta0);DrawPlane();/*draw in the foreground*/DejaDCopy();DrawBackGround(&meta1);DrawAnim();AnimCopy();if(maxSprite)DrawInfo();DrawSprite();changed=TRUE;}/*----------------------------------------------------------------------*/doMovie(){int i;int current=lSprite[anum].acurrent;if(maxSprite)DrawInfo();for(i=0;i<lSprite[anum].size;i++)	{	lSprite[anum].acurrent=i;	if(maxSprite)DrawInfo();	DrawBackGround(&meta1);	DrawAnim();	AnimDCopy();	if(maxSprite)DrawInfo();	}lSprite[anum].acurrent=current;DrawBackGround(&meta1);DrawAnim();AnimDCopy();if(maxSprite)DrawInfo();}/*----------------------------------------------------------------------*/KillAObject(){int i;if(lSprite[anum].size<=1)return;if(maxSprite)DrawInfo();if(lSprite[anum].acurrent==lSprite[anum].size-1)	{	lSprite[anum].acurrent--;	}else	{	for(i=lSprite[anum].acurrent;i<lSprite[anum].size-1;i++)		{		lSprite[anum].object[i].xloc=lSprite[anum].object[i+1].xloc;		lSprite[anum].object[i].yloc=lSprite[anum].object[i+1].yloc;		lSprite[anum].object[i].spritenum=			lSprite[anum].object[i+1].spritenum;		}	}lSprite[anum].size--;DrawBackGround(&meta1);DrawAnim();AnimDCopy();if(maxSprite)DrawInfo();}/*----------------------------------------------------------------------*/AUpOne(){int i;int xloc,yloc,spritenum,current;if(lSprite[anum].acurrent==lSprite[anum].size-1)return;current=lSprite[anum].acurrent;if(maxSprite)InvertRect(&dbutton[current]);xloc=lSprite[anum].object[current+1].xloc;yloc=lSprite[anum].object[current+1].yloc;spritenum=lSprite[anum].object[current+1].spritenum;lSprite[anum].object[current+1].xloc=lSprite[anum].object[current].xloc;lSprite[anum].object[current+1].yloc=lSprite[anum].object[current].yloc;lSprite[anum].object[current+1].spritenum=	lSprite[anum].object[current].spritenum;lSprite[anum].object[current].xloc=xloc;lSprite[anum].object[current].yloc=yloc;lSprite[anum].object[current].spritenum=spritenum;lSprite[anum].acurrent++;if(maxSprite)DrawInfo();}/*----------------------------------------------------------------------*/ADownOne(){int i;int xloc,yloc,spritenum,current;if(lSprite[anum].acurrent==0)return;current=lSprite[anum].acurrent;if(maxSprite)InvertRect(&dbutton[current]);xloc=lSprite[anum].object[current-1].xloc;yloc=lSprite[anum].object[current-1].yloc;spritenum=lSprite[anum].object[current-1].spritenum;lSprite[anum].object[current-1].xloc=lSprite[anum].object[current].xloc;lSprite[anum].object[current-1].yloc=lSprite[anum].object[current].yloc;lSprite[anum].object[current-1].spritenum=	lSprite[anum].object[current].spritenum;lSprite[anum].object[current].xloc=xloc;lSprite[anum].object[current].yloc=yloc;lSprite[anum].object[current].spritenum=spritenum;lSprite[anum].acurrent--;if(maxSprite)DrawInfo();}/*----------------------------------------------------------------------*/AUpTop(){int i;int xloc,yloc,spritenum,current;if(lSprite[anum].acurrent==lSprite[anum].size-1)return;current=lSprite[anum].acurrent;if(maxSprite)InvertRect(&dbutton[current]);xloc=lSprite[anum].object[current].xloc;yloc=lSprite[anum].object[current].yloc;spritenum=lSprite[anum].object[current].spritenum;for(i=current;i<lSprite[anum].size-2;i++)	{	lSprite[anum].object[i].xloc=lSprite[anum].object[i+1].xloc;	lSprite[anum].object[i].yloc=lSprite[anum].object[i+1].yloc;	lSprite[anum].object[i].spritenum=		lSprite[anum].object[i+1].spritenum;	}lSprite[anum].object[lSprite[anum].size-1].xloc=xloc;lSprite[anum].object[lSprite[anum].size-1].yloc=yloc;lSprite[anum].object[lSprite[anum].size-1].spritenum=spritenum;lSprite[anum].acurrent=lSprite[anum].size-1;if(maxSprite)DrawInfo();}/*----------------------------------------------------------------------*/ADownBottom(){int i;int xloc,yloc,spritenum,current;if(lSprite[anum].acurrent==0)return;current=lSprite[anum].acurrent;if(maxSprite)InvertRect(&dbutton[current]);xloc=lSprite[anum].object[current].xloc;yloc=lSprite[anum].object[current].yloc;spritenum=lSprite[anum].object[current].spritenum;for(i=current;i>1;i--)	{	lSprite[anum].object[i].xloc=lSprite[anum].object[i-1].xloc;	lSprite[anum].object[i].yloc=lSprite[anum].object[i-1].yloc;	lSprite[anum].object[i].spritenum=		lSprite[anum].object[i-1].spritenum;	}lSprite[anum].object[0].xloc=xloc;lSprite[anum].object[0].yloc=yloc;lSprite[anum].object[0].spritenum=spritenum;lSprite[anum].acurrent=0;if(maxSprite)DrawInfo();}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */MoveASprite(p)Point *p;{Point new,old;int current=lSprite[anum].acurrent;old.v=p->v;old.h=p->h;while(Button())	{	GetMouse(&new);	if(new.v>0&&new.v<(HEIGHT-BTOP)&&new.h>0&&new.h<WIDTH)	if(new.v!=old.v || new.h!=old.h)		{		if(current==0)			{			lSprite[anum].axloc+=new.h-old.h;			lSprite[anum].ayloc+=new.v-old.v;			}		else			{			lSprite[anum].object[current].xloc+=new.h-old.h;			lSprite[anum].object[current].yloc+=new.v-old.v;			}		DrawBackGround(&meta1);		DrawAnim();		AnimDCopy();		old.h=new.h;		old.v=new.v; 		}	}}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */int WhichASprite(p)Point *p;{GrafPtr temp;GrafPtr	savePort;Rect r;int cnum;int found=FALSE;GetPort( &savePort );temp=(GrafPtr)NewPtr((long)sizeof(GrafPort));OpenPort(temp);cnum=FindASprite(anum,&r);if( p->h>=r.left &&	p->h<=r.right &&	p->v>=r.top &&	p->v<=r.bottom)	{	SetPortBits(cSprite[cnum].mask);	if(GetPixel(p->h-r.left,p->v-r.top))found=TRUE;	}ClosePort(temp);DisposPtr(temp);SetPort(savePort);return(found);}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */MoveAObject(p)Point *p;{int num,loc;if(WhichASprite(p))MoveASprite(p);}/*--------------------------------------------------------------------- *--------------------------------------------------------------------- */SetExtend(){Rect r;DialogPtr thedialog;int not_end=TRUE;int itemhit=0;int type;Handle item[12];int i;char str[255];thedialog=GetNewDialog(19640,NIL,(WindowPtr)-1);for(i=0;i<13;i++)GetDItem(thedialog,i,&type,&item[i],&r);SetCtlValue(item[3],0);SetCtlValue(item[4],0);SetCtlValue(item[5],0);type=lSprite[anum].type;switch(type)	{	case 0:		SetCtlValue(item[3],1);		break;	case 1:		SetCtlValue(item[4],1);		break;	case 2:		SetCtlValue(item[5],1);		break;	}if(lSprite[anum].frozen)SetCtlValue(item[6],1);else SetCtlValue(item[6],0);if(lSprite[anum].locked)SetCtlValue(item[7],1);else SetCtlValue(item[7],0);sprintf(str," %d",lSprite[anum].link); i=0; while(str[i])i++;str[0]=i;SetIText(item[8],str);sprintf(str," %d",lSprite[anum].key); i=0; while(str[i])i++;str[0]=i;SetIText(item[9],str);sprintf(str," %d",lSprite[anum].lock); i=0; while(str[i])i++;str[0]=i;SetIText(item[10],str);while(not_end)	{	ModalDialog(NIL,&itemhit);	switch(itemhit)		{		case 1:/*OK*/			lSprite[anum].type=type;			lSprite[anum].frozen=GetCtlValue(item[6]);			lSprite[anum].locked=GetCtlValue(item[7]);			GetIText(item[8],&str);			sscanf(&str[1],"%d",&lSprite[anum].link);			GetIText(item[9],&str);			sscanf(&str[1],"%d",&lSprite[anum].key);			GetIText(item[10],&str);			sscanf(&str[1],"%d",&lSprite[anum].lock);			changed=TRUE;			not_end=0;			break;		case 2:			not_end=0;			break;		case 3:			type=0;			SetCtlValue(item[3],1);			SetCtlValue(item[4],0);			SetCtlValue(item[5],0);			break;		case 4:/*Key*/			type=1;			SetCtlValue(item[3],0);			SetCtlValue(item[4],1);			SetCtlValue(item[5],0);			break;		case 5:/*Object*/			type=2;			SetCtlValue(item[3],0);			SetCtlValue(item[4],0);			SetCtlValue(item[5],1);			break;		case 6:/*Frozen check box*/			SetCtlValue(item[6],!GetCtlValue(item[6]));						break;		case 7:/*Locked check box*/			SetCtlValue(item[7],!GetCtlValue(item[7]));						break;		case 8:/*link to object*/			break;		case 9:/*key number*/			break;		case 10: /*lock number*/			break;		}	}DisposDialog(thedialog);}