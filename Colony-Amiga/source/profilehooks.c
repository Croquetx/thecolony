/*
 
  Profile and tracing package for LightspeedC.
  
  (C) Copyright 1986 THINK Technologies, Inc.  All rights reserved.

*/

extern void __profile();
extern void __profile_exit();

/*
;
; Entry point for profiler.  Add another parameter to the stack which is
; a pointer to the return address of the caller of this function.
;
*/
_profile_()
{

	asm
	{
		move.l	(a7)+,d0			; get current return address
		pea		4(a6)				; push pointer to return address
		move.l	d0,-(a7)			; push back the return address
		jsr		__profile			; call the C profiler
		move.l	(a7)+,d0			; get return address
		move.l	d0,(a7)				; write on top of stack and return
	}
}

/*
;
; Exit point for profiler.  This calls the end of function timing routine
; and returns to the user.
;
*/

_profile_exit_()
{
	asm
	{
		move.l	d0, -(a7)			; save old function result
		jsr		__profile_exit		; call end of routine timer
		move.l	d0, a0				; save return address in A0
		move.l	(a7)+, d0			; retrieve old function result
		jmp		(a0)				; then return
	}
}
