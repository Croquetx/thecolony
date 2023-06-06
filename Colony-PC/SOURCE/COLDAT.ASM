    PAGE 60,132
    NAME COLONY
;****************************************************************************
; VSP-88 version 2.00
; Virtual Sound Processor for the IBM PC personal computer
; --------------------------------------------------------
; By: Jack Thornton for SofTalent
;
; DATA (VSP 'PROGRAM') FOR: COLONY
;
;
; 35 sound effects for the Mindscape game Colony for the IBM PC
;    programmed by Eric Wanger of Cornerstone Information Systems, Inc
;         September, 1988.
;****************************************************************************

            INCLUDE TCHEADL.ASM  ; This declares the C language macros
                                 ; and sets up the segments.
            INCLUDE vspmacro.ibm

SoundEffect MACRO   lbl
            PUBLIC  _&lbl
_&lbl       EQU     THIS BYTE
            ENDM

			CODESTART
			PUBLIC _SoundCount  
_SoundCount	DW	0

_SoundOff	PROC	FAR
			DEC		CS:_SoundCount
			RET
_SoundOff	ENDP
			CODEEND


            DATASTART
;--------------------------------------------
SoundEffect Explode2
            LOAD    VOL,8
            LOAD USER,48
            LOAD FREQ, 1280
            EOP
Explodeloop EQU THIS BYTE
            RAMP    FREQ,-2
            RAMP    USER,-1
            EOP
            CMPREG  USER,0
            JPNE    Explodeloop

            LOAD FREQ, 36864
            LOAD USER, 80
            EOP
Explosion   EQU THIS BYTE
            RAMP USER,-1
            EOP
            CMPREG USER,0
            JPNE Explosion
			FAR_SUBROUTINE	_SoundOff					
            RELEASE

;--------------------------------------------
SoundEffect Chime
            LOAD    FREQ,4649
            LOAD    VOL,8
            DURATION 7
            EOP
            LOAD    FREQ,3690
            DURATION 7
            EOP
            LOAD    FREQ,3103
            DURATION 7
            EOP
			FAR_SUBROUTINE	_SoundOff
            RELEASE

;--------------------------------------------
SoundEffect Them
            LOAD USER,10
            LOAD    FREQ,8000		;12288
            DURATION 10
            EOP
Themloop    EQU THIS BYTE
            LOAD    VOL,8
            EOP
            LOAD VOL,0
            EOP
            RAMP USER,-1
            CMPREG USER,0
            JPNE Themloop
			FAR_SUBROUTINE	_SoundOff
            RELEASE

;--------------------------------------------
SoundEffect TTorps
            LOAD    VOL,8
            DURATION 7
            LOAD  USER,2
TTorploop   EQU THIS BYTE
            LOAD  FREQ,200
OneTTorp    EQU THIS BYTE
            RAMP    FREQ,30
            EOP
            CMPREG  FREQ,600
            JPLE    OneTTorp
            RAMP USER,-1
            CMPREG USER,0
            JPNE TTorploop
			FAR_SUBROUTINE	_SoundOff
            RELEASE

;--------------------------------------------
SoundEffect Eat
            LOAD    VOL,8
            DURATION 2
            LOAD    FREQ,8888h
            EOP
            LOAD    FREQ,7777h
            EOP
            LOAD    FREQ,6666h
            EOP
            LOAD    FREQ,5555h
            EOP
            LOAD    FREQ,4444h
            EOP
            LOAD    FREQ,3333h
            EOP
            LOAD    FREQ,2222h
            EOP
            LOAD    FREQ,1111h
            EOP
            LOAD    FREQ,0600
            EOP

			FAR_SUBROUTINE	_SoundOff
            RELEASE

;--------------------------------------------
SoundEffect Dit
            LOAD    VOL,8
            LOAD    FREQ,210
            DURATION 3
            EOP
            LOAD    FREQ,9210
            DURATION 2
            EOP
            LOAD    FREQ,3000
            DURATION 3
            EOP
            LOAD    FREQ,1000
            DURATION 2
            EOP
            LOAD    FREQ,40000
            DURATION 3
            EOP
			FAR_SUBROUTINE	_SoundOff
            RELEASE

;--------------------------------------------
SoundEffect Ouch
            LOAD    FREQ,4649
            LOAD    VOL,8
            DURATION 3
            EOP
			FAR_SUBROUTINE	_SoundOff
            RELEASE

;--------------------------------------------
SoundEffect PlanetShot
            LOAD    FREQ,10000
            LOAD    VOL,8
            DURATION 2
            EOP
PlanLoop    EQU THIS BYTE
            RAMP    FREQ,-100
            DURATION 2
            EOP
            CMPREG  FREQ,5000
            JPGT    PlanLoop

            LOAD    FREQ,500
            LOAD    VOL,8
            DURATION 7
            EOP
Planetloop  EQU THIS BYTE
            RAMP  FREQ, 16
            EOP
            CMPREG  FREQ,4096
            JPLE Planetloop
			FAR_SUBROUTINE	_SoundOff
            RELEASE

;--------------------------------------------
SoundEffect Test
            LOAD    VOL,8
            NOTE_POINTER TestC
            DEFAULT_DURS 1, 2, 3, 4
;                        E, Q, H ,W
            BASE_OCTAVE 2
            LOAD USER,5
Testit      EQU THIS BYTE
            RAMP USER,-1
            Jsub TestLoop
            CMPREG USER,0
            JPNE Testit
			FAR_SUBROUTINE	_SoundOff
            RELEASE

TestLoop    EQU THIS BYTE
            PLAY_NOTE
            EOP
            JUMP TestLoop

;           PLAY Sample and Hold

TestC       DB BNT+E+O2
            DB GNT+E+O4
            DB CNT+E+O1
            DB ANT+E+O3
            DB DNT+E+O2
            DB BNT+E+O2
            DB EFL+E+O1
            DB DNT+E+O4
            DB ENT+E+O3
            DB GNT+E+O3
            DB CNT+E+O2
            DB CNT+E+O1
            DB FNT+E+O4
            DB DNT+E+O3

            DB NEND
			RELEASE

;--------------------------------------------
SoundEffect Xporter2
Xport       EQU THIS BYTE
			LOAD    VOL,8
			LOAD    USER,40
			LOAD    FREQ,65535
Xportloop   EQU THIS BYTE
			RAMP    FREQ,-20
			DURATION 1
			RAMP     USER,-1
			EOP
			CMPREG  USER,0
			JPGT    Xportloop
            LOAD    FREQ,65531
            LOAD    USER,40
Xportloop1  EQU THIS BYTE
            RAMP    FREQ,-20
            DURATION 1
            RAMP     USER,-1
            EOP
            CMPREG  USER,0
            JPGT    Xportloop1
            LOAD    FREQ,65535
            LOAD    USER,200
Xportloop2  EQU THIS BYTE
            RAMP    FREQ,-20
            DURATION 1
            RAMP     USER,-1
            EOP
            CMPREG  USER,0
            JPGT    Xportloop2
			FAR_SUBROUTINE	_SoundOff
            RELEASE


;--------------------------------------------
SoundEffect Stars1
            LOAD  VOL,8
            NOTE_POINTER Stars1C
            DEFAULT_DURS 1, 2, 3, 4
;                        E, Q, H ,W
            BASE_OCTAVE 1
            LOAD USER,60
Stars1it      EQU THIS BYTE
            NOTE_POINTER Stars1C
            RAMP USER,-1
            Jsub Stars1Loop
            CMPREG USER,0
            JPNE Stars1it
            RELEASE

Stars1Loop    EQU THIS BYTE
            PLAY_NOTE
            EOP
            JUMP Stars1Loop

;           PLAY Sample and Hold

Stars1C       DB BNT+H+O2
            DB REST+H+O4
            DB REST+H+O1
            DB REST+H+O3
            DB DNT+H+O2
            DB REST+H+O2
            DB REST+H+O1
            DB REST+H+O4
            DB ENT+H+O3
            DB REST+H+O3
            DB REST+H+O2
            DB REST+H+O1
            DB FNT+H+O4
            DB REST+H+O3

            DB NEND

            RELEASE


;--------------------------------------------
SoundEffect Stars2
            LOAD  VOL,8
            NOTE_POINTER Stars2C
            DEFAULT_DURS 1, 2, 3, 4
;                        E, Q, H ,W
            BASE_OCTAVE 1
            LOAD USER,60
Stars2it      EQU THIS BYTE
            NOTE_POINTER Stars2C
            RAMP USER,-1
            Jsub Stars2Loop
            CMPREG USER,0
            JPNE Stars2it
            RELEASE

Stars2Loop    EQU THIS BYTE
            PLAY_NOTE
            EOP
            JUMP Stars2Loop

;           PLAY Sample and Hold


Stars2C     DB BNT+H+O2
            DB REST+H+O4
            DB REST+H+O1
            DB ANT+H+O3
            DB DNT+H+O2
            DB REST+H+O2
            DB REST+H+O1
            DB DNT+H+O4
            DB ENT+H+O3
            DB REST+H+O3
            DB REST+H+O2
            DB CNT+H+O1
            DB FNT+H+O4
            DB REST+H+O3

            DB NEND

            RELEASE




;--------------------------------------------
SoundEffect Stars3
            LOAD  VOL,8
            NOTE_POINTER Stars3C
            DEFAULT_DURS 1, 2, 3, 4
;                        E, Q, H ,W
            BASE_OCTAVE 1
            LOAD USER,60
Stars3it      EQU THIS BYTE
            NOTE_POINTER Stars3C
            RAMP USER,-1
            Jsub Stars3Loop
            CMPREG USER,0
            JPNE Stars3it
            RELEASE

Stars3Loop    EQU THIS BYTE
            PLAY_NOTE
            EOP
            JUMP Stars1Loop

;           PLAY Sample and Hold

Stars3C     DB BNT+H+O2
            DB REST+H+O4
            DB CNT+H+O1
            DB ANT+H+O3
            DB DNT+H+O2
            DB REST+H+O2
            DB EFL+H+O1
            DB DNT+H+O4
            DB ENT+H+O3
            DB REST+H+O3
            DB CNT+H+O2
            DB CNT+H+O1
            DB FNT+H+O4
            DB REST+H+O3

            DB NEND

            RELEASE


;--------------------------------------------
SoundEffect Stars4
            LOAD  VOL,8
            NOTE_POINTER Stars4C
            DEFAULT_DURS 1, 2, 3, 4
;                        E, Q, H ,W
            BASE_OCTAVE 1
            LOAD USER,60
Stars4it      EQU THIS BYTE
            NOTE_POINTER Stars4C
            RAMP USER,-1
            Jsub Stars4Loop
            CMPREG USER,0
            JPNE Stars4it
            RELEASE

Stars4Loop    EQU THIS BYTE
            PLAY_NOTE
            EOP
            JUMP Stars4Loop

;           PLAY Sample and Hold

Stars4C     DB BNT+H+O2
            DB GNT+H+O4
            DB CNT+H+O1
            DB ANT+H+O3
            DB DNT+H+O2
            DB BNT+H+O2
            DB EFL+H+O1
            DB DNT+H+O4
            DB ENT+H+O3
            DB GNT+H+O3
            DB CNT+H+O2
            DB CNT+H+O1
            DB FNT+H+O4
            DB DNT+H+O3

            DB NEND

            RELEASE

;--------------------------------------------
SoundEffect Airlock
            LOAD    VOL,8
            LOAD    FREQ,57344
            DURATION 150
            EOP
            LOAD    FREQ,512
            DURATION 2
            EOP
            LOAD    FREQ,1024
            DURATION 1
            EOP
			FAR_SUBROUTINE	_SoundOff
            RELEASE

;--------------------------------------------
SoundEffect Ugh
            LOAD    FREQ,400
            LOAD    VOL,8
            LOAD    USER,30
            EOP
UghLoop     EQU THIS BYTE
            RAMP    FREQ, 134
            RAMP    USER,-1
            EOP
            CMPREG  USER,0
            JPNE    UghLoop
			FAR_SUBROUTINE	_SoundOff
            Release

;--------------------------------------------
SoundEffect Floor
            LOAD USER,10
FloorLoop   EQU THIS BYTE
            LOAD    FREQ,60000
            LOAD    VOL,8
            EOP

            RAMP    USER,-1
            LOAD VOL,0
            DURATION 1
            EOP
            LOAD VOL,8
            DURATION 1
            CMPREG  USER,0
            JPNE    FloorLoop
			FAR_SUBROUTINE	_SoundOff
            Release


;--------------------------------------------
SoundEffect Toilet2
            LOAD    VOL,8
            NOTE_POINTER ToiletC
            DEFAULT_DURS 7,15,31,63
;                        E, Q, H ,W
            BASE_OCTAVE 2
ToiletLoop  EQU THIS BYTE
            PLAY_NOTE
            EOP
            JUMP ToiletLoop

;           PLAY The sailor's hornpipe

ToiletC     DB GNT+Q+O2
            DB GNT+E+O1
            DB REST+E+O1
            DB GNT+E+O1
            DB REST+E+O1
            DB DNT+E+O2
            DB CNT+E+O2

            DB BNT+E+O2
            DB DNT+E+O2
            DB GNT+E+O2
            DB REST+E+O2
            DB GNT+H+O2

            DB NEND

;--------------------------------------------
SoundEffect Bath
            LOAD    VOL,8
            NOTE_POINTER BathC
            DEFAULT_DURS 7,11,20,39
;                        E, Q, H ,W
            BASE_OCTAVE 2
BathLoop    EQU THIS BYTE
            PLAY_NOTE
            EOP
            JUMP BathLoop

;           PLAY RUBBER DUCKY

BathC       DB GNT+Q+O1
            DB REST+Q+O1
            DB ANT+Q+O2
            DB REST+Q+O1
            DB BNT+Q+O2
            DB REST+Q+O1

            DB CNT+H+O2
            DB ENT+E+O2
            DB ENT+E+O2
            DB EFL+E+O2
            DB ENT+Q+O2
            DB GNT+Q+O2
            DB GNT+H+O2

            DB FNT+H+O2
            DB CNT+Q+O3
            DB BNT+Q+O3
            DB BNT+W+O3

            DB NEND


;--------------------------------------------
SoundEffect Teleport
            LOAD    FREQ,400
            LOAD    VOL,8
            LOAD    USER,100
            EOP
Teleport    EQU THIS BYTE
            RAMP    FREQ, 134
            RAMP    USER,-1
            EOP
            CMPREG  USER,0
            JPNE    Teleport
			FAR_SUBROUTINE	_SoundOff
            Release

SoundEffect Door1
            LOAD    FREQ,1000
            LOAD    VOL,8
            DURATION 7
            EOP
            LOAD    FREQ,2000
            DURATION 3
            EOP
			FAR_SUBROUTINE	_SoundOff
            RELEASE

;--------------------------------------------
SoundEffect Elevator
            LOAD    VOL,8
            LOAD  USER,8
Elevloop    EQU THIS BYTE
            LOAD    FREQ,512
            DURATION 2
            EOP
            LOAD    FREQ,1024
            DURATION 75
            EOP
            RAMP USER,-1
            CMPREG USER,0
            JPNE Elevloop
			FAR_SUBROUTINE	_SoundOff
            RELEASE


;--------------------------------------------
SoundEffect Slug2

            LOAD USER,5
SlugLoop    EQU THIS BYTE
            LOAD    FREQ,200
            LOAD    VOL,8
            EOP
SlugLoop1   EQU THIS BYTE
            RAMP    FREQ, -2
            EOP
            CMPREG  FREQ,100
            JPLT SlugLoop1

            RAMP    USER,-1
            EOP
            CMPREG  USER,0
            JPNE    SlugLoop
			FAR_SUBROUTINE	_SoundOff
            Release



;--------------------------------------------
SoundEffect Lift
            LOAD    FREQ,4649
            LOAD    VOL,8
            DURATION 1
            EOP
LiftLoop    EQU THIS BYTE
            RAMP    FREQ,-8
            DURATION 1
            EOP
            CMPREG  FREQ,3103
            JPGT    LiftLoop
			FAR_SUBROUTINE	_SoundOff
            RELEASE

;--------------------------------------------
SoundEffect Drop
            LOAD    FREQ,3103
            LOAD    VOL,8
            DURATION 1
            EOP
DropLoop    EQU THIS BYTE
            RAMP    FREQ,8
            DURATION 1
            EOP
            CMPREG  FREQ,4649
            JPLT    DropLoop
			FAR_SUBROUTINE	_SoundOff
            RELEASE


;--------------------------------------------
SoundEffect Clatter
            Jsub _Dit
            Jsub _Them
            Jsub _Swish
			FAR_SUBROUTINE	_SoundOff
            RELEASE
;--------------------------------------------
SoundEffect Sink2
SinkLoop    EQU THIS BYTE
            LOAD    FREQ,200
            LOAD    VOL,8
            EOP
SinkLoop1   EQU THIS BYTE
            RAMP    FREQ, 200
            EOP
            CMPREG  FREQ,1600
            JPLT SinkLoop1
 			FAR_SUBROUTINE	_SoundOff
           Release

;--------------------------------------------
SoundEffect Wallx
            LOAD USER,1
WallLoop    EQU THIS BYTE
            LOAD    FREQ,60000
            LOAD    VOL,8
            EOP
WallLoop1   EQU THIS BYTE
            RAMP    FREQ, -1000
            EOP
            CMPREG  FREQ,50000
            JPLT WallLoop1
            RAMP    USER,-1
            LOAD VOL,0
            DURATION 10
            EOP
            LOAD VOL,8
            DURATION 1
            CMPREG  USER,0
            JPNE    WallLoop
 			FAR_SUBROUTINE	_SoundOff
            Release
;--------------------------------------------
SoundEffect Glass
            LOAD USER,20
GlassLoop   EQU THIS BYTE
            LOAD    FREQ,60000
            LOAD    VOL,8
            EOP
GlassLoop1  EQU THIS BYTE
            RAMP    FREQ, -1000
            EOP
            CMPREG  FREQ,50000
            JPLT GlassLoop1

            RAMP    USER,-1
            LOAD VOL,0
            DURATION 10
            EOP
            LOAD VOL,8
            DURATION 1
            CMPREG  USER,0
            JPNE    GlassLoop
 			FAR_SUBROUTINE	_SoundOff
            Release
 ;--------------------------------------------
SoundEffect Tunnel2
            LOAD    VOL,8
            LOAD  USER,8
Tunn2loop   EQU THIS BYTE
            LOAD    FREQ,1000
            DURATION 2
            EOP
            LOAD    FREQ,30000
            DURATION 75
            EOP
            RAMP USER,-1
            CMPREG USER,0
            JPNE Tunn2loop
 			FAR_SUBROUTINE	_SoundOff
            RELEASE
;--------------------------------------------
SoundEffect Klaxon
            LOAD    VOL,8
            LOAD    USER,4
KlaxonLoop  EQU THIS BYTE
            LOAD    FREQ,4649
            DURATION 1
            EOP
IncKlaxon   EQU THIS BYTE
            RAMP    FREQ,-64
            DURATION 1
            EOP
            CMPREG  FREQ,4000
            JPGT    IncKlaxon
            RAMP    USER,-1
            CMPREG  USER,0
            JPNE    KlaxonLoop
 			FAR_SUBROUTINE	_SoundOff
            RELEASE
;--------------------------------------------
SoundEffect Fullstop
            LOAD    FREQ,512
            LOAD    VOL,8
            DURATION 10
            Jsub  Fullloop
            DURATION 12
            Jsub  Fullloop
            DURATION 14
            Jsub  Fullloop
            DURATION 16
            Jsub  Fullloop
            DURATION 18
            Jsub  Fullloop
            DURATION 20
            Jsub  Fullloop
            DURATION 22
            Jsub  Fullloop
            DURATION 24
            Jsub  Fullloop
            DURATION 26
            Jsub  Fullloop
            DURATION 28
            Jsub  Fullloop
            DURATION 30
            Jsub  Fullloop
            DURATION 32
            Jsub  Fullloop
            DURATION 34
            Jsub  Fullloop
            DURATION 36
            Jsub  Fullloop
            DURATION 38
            Jsub  Fullloop
            Jsub _Swish
            Jsub _Floor
 			FAR_SUBROUTINE	_SoundOff
            RELEASE
Fullloop    EQU THIS BYTE
            RAMP FREQ, 150
            EOP
            RELEASE
;--------------------------------------------
SoundEffect Swish
            LOAD    FREQ,50240
            LOAD    VOL,8
            DURATION 50
            EOP
 			FAR_SUBROUTINE	_SoundOff
            RELEASE
;--------------------------------------------
	DATAEND
	END