/*  #define IBM_MakeFWall  */
/*  #define IBM_MakeCWall  */
/*                       */
/*----------------------------------*
 * The Colony
 * Copyright 1988 by David A. Smith
 * All Rights Reserved
 * David A. Smith
 * 111 Gold Meadow Dr.
 * Cary, NC 27513
 * (919) 469-8485
 *----------------------------------*/
#define EXT extern 
#include "gamedefs.h"
/*---------------------------------------------------------------------
 * MakeFWall()
 *---------------------------------------------------------------------
 */
void MakeFWall(num)
{
#if !defined(IBM_MakeFWall)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[FWALL][0],&Object[num].where,0);
if(Robot[FWALL][0].visible)DrawPrism(&Robot[FWALL][0],1);
Object[num].visible=FALSE;
#endif
}

/*---------------------------------------------------------------------
 * MakeCWall()
 *---------------------------------------------------------------------
 */
void MakeCWall(num)
{
#if !defined(IBM_MakeCWall)

nearClipRect= Object[num].clip;
ClipRect(&nearClipRect);

/*  ClipRect(&Object[num].clip);  */
MakePrism(&Robot[CWALL][0],&Object[num].where,0);
if(Robot[CWALL][0].visible)DrawPrism(&Robot[CWALL][0],1);
Object[num].visible=FALSE;
#endif
}
