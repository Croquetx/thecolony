/*
 
  Profile and tracing package for LightspeedC.
  
  (C) Copyright 1986 THINK Technologies, Inc.  All rights reserved.
 
 */
#define NULL 0
 
typedef unsigned char   Bool;                   /* for size                  */
enum{false,true};
 
typedef void (*address)();						/* address type			 	 */
typedef unsigned char   byte;
typedef unsigned long   time;
 
typedef struct{
        char         	*name;                  /* function name             */
        time            average;                /* average time              */
        time            maximum;                /* largest time              */
        time            minimum;                /* smallest time             */
        time            total;                  /* total time                */
        unsigned int    entries;                /* times entered             */
        } PROFILE;
 
typedef struct {
        address         user;                   /* user return address       */
        int             function;               /* index into profiles       */
        time            correction;             /* nested call time          */
        time            start;                  /* entry time                */
        } STACK;
 
#define LOCAL           static                  /* local to profiler         */
#define MAX_PROFILES       200L                  /* routines to follow        */
#define MAX_STACK          200L                  /* max nested calls          */
#define MAX_TIME        500000L                 /* max time                  */
 
 
/*
 
        Select execution/compilation options.
 
        SINGLE                  - each routine contains only its time
        TESTING                 - test profile package without LightspeedC PROFILE option
 
 */
 
#define SINGLE                                  /* single routine only       */
/* #define TESTING                              standalone testing   */
 
 
#ifdef  TESTING
#undef  LOCAL                                   /* make items visible        */
#define LOCAL
#endif
 
 
LOCAL int 				progo					=  0;
LOCAL int               depth                   = -1;
LOCAL PROFILE           *profiles;
LOCAL int               profile_count           =  0;
LOCAL STACK             *stack;
LOCAL int               stack_pointer           = -1;
LOCAL time              start_time;
 
int                     _profile                =  1;
int                     _trace                  =  0;
 
void	DumpProfile();
extern	_profile_exit_();
extern  char *CtoPstr();
extern  char *PtoCstr();

#define _VIATIMER_	/* if this symbol is defined, the VIA timer now is used
						instead of TickCount -- it provides faster ticks,
						however there is a false precision to the numbers
						and there is a range of + or - 500 ticks since
						the VIAtimer is so fast that interrupts and such
						play a more significant time role.
						
						NOTE THAT THIS PROFILE OPTION CANNOT BE USED WITH
						ANY PROGRAM THAT MANIPULATES THE #1 VIA timer */
						

#ifdef	_VIATIMER_

/* TickCount() - redefine TickCount trap to be a procedure for determining
				 the timing according to the VIA timer */

#define	VIAbase	(*((unsigned char**)0x01D4))
#define	VIAt1lo	(*(VIAbase+512*4))
#define	VIAt1hi	(*(VIAbase+512*5))
#define	VIAmaxtime	~0

time TickCount()
{
static time timer=0;

	if (timer > 0)
	{
		/* Use VIA timer #1 (sound driver) and to implement a fine
			resolution counter */
		
		/* Find delta of VIA #1 */
		
		timer += VIAmaxtime - (((unsigned short)VIAt1hi<<8)+VIAt1lo);
	}
	else
		timer = 1;
	
	/* Reset VIA counter */
	
	VIAt1hi = VIAmaxtime;
	VIAt1lo = VIAmaxtime;
	
	return (timer);
}

#endif _VIATIMER_

InitProfile()
{
int i;

progo=0;
profiles=(PROFILE *)NewPtr(MAX_PROFILES * sizeof(PROFILE));
stack=(STACK *)NewPtr(MAX_STACK * sizeof(STACK));
for(i=0;i<MAX_PROFILES;i++)
	{
    profiles[i].average=0;                /* average time              */
    profiles[i].maximum=0;                /* largest time              */
    profiles[i].minimum=0;                /* smallest time             */
    profiles[i].total=0;                  /* total time                */
    profiles[i].entries=0;                /* times entered             */
    }
for(i=0;i<MAX_STACK;i++)
	{
    stack[i].user=0;                   /* user return address       */
    stack[i].function=0;               /* index into profiles       */
    stack[i].correction=0;             /* nested call time          */
    stack[i].start=0;                  /* entry time                */
    }
progo=1;
}


/*
 
  Compare two Pascal strings for equality.
 
 */

LOCAL Bool pstreq( s1, s2 )
register unsigned char	*s1, *s2;
{
  register int			n = *s1;
  
  if ((n = *s1++) != *s2++)
    return( false );
  while (n-- > 0)
    if (*s1++ != *s2++)
      return( false );
  return( true );
}


/*
 
  Return the time difference caused by the overhead of function entry and
  timer call.
 
 */
 
LOCAL time delta( original )
time            original;
{
	return( (time) TickCount() - original );
}
 
 
/*
 
  Lookup a name in the active profile table.  For this system, "names" are
  the address of the routine.  If the name is found in the table, then the
  index to the table entry is returned.  If the name is not found and the
  insert flag is on, then the item is inserted, and the new table index
  is returned (if insert is false, then -1 is returned).  If the profile
  table is full, then -1 is returned.
 
 */
 
LOCAL int lookup( name, insert )
char         	*name;
Bool            insert;
{
  register int  i;
 
  for (i = 0; i < profile_count; i++)
    if (pstreq( profiles[i].name, name ))
      return( i );
  if ( insert && profile_count < MAX_PROFILES)
    { /* place in table  - i points to correct entry */
    if (++profile_count == 1)
      { /* first time in */
      start_time = (time) TickCount();
      }
    profiles[i].name            = name;
    profiles[i].minimum         = MAX_TIME;
    profiles[i].maximum         =
    profiles[i].total           = NULL;
    profiles[i].entries         = 0;
    return( i );
    }
  return( -1 );
}
 
 
/*
 
  Print the profile table on demand.  Output is written to stdout and may
  be redirected with the Unix '>' mechanism to a file.  The user should
  call this routine whenever a report is desired.  Each time the routine is
  called, the program opens the map file which corresponds to the program
  running.  The name of the map file is built by appending ".map" to the name
  of the running program.  If the map file cannot be found then the routine
  returns.
 
 */
char *eol="\r ";
writenum(x,field,space)
long x;
int field,space;
{
char str[255];

NumToString((long)x,str); 
if(field>str[0])
	{
	my_write("                                 ",(long)field-str[0]);
	my_write(&str[1],(long)str[0]); 
	}
else	my_write("*****************************",(long)field);
my_write("                                 ",(long)space);
}
void DumpProfile()
{
  int           j, k;                           /* generic loop variables    */
  register int  i;                              /* primary loop variable     */
  register time duration        = 0L;           /* time in test regions      */
  unsigned char str[255];
  _profile = 0;                                 /* turn off profiling here   */
 
  for (i = 0; i < profile_count; i++)
    duration += profiles[i].total;              /* compute total time        */
 
  if (duration <= 0.0)
    duration++;
  my_write("duration = ",11L);
  writenum((long)duration,10,0);
  my_write(eol,1L);
  my_write(eol,1L);
  my_write("profile_count = ",16L);
  writenum((long)profile_count,10,0);
  my_write(eol,1L);
  my_write(eol,1L);
  my_write( "Function            Minimum   Maximum   Average    %x100    Entries   \r",71L );
  my_write( "--------            -------   -------   -------   -------   -------   \r",71L);
  for (i = 0; i < profile_count; i++)
    { /* for all entries in the profile table */
    if (profiles[i].minimum == MAX_TIME)
      continue;                                 /* routine entry, no exit    */
    my_write(&profiles[i].name[1],(long)profiles[i].name[0]);
    my_write("                                 ",20L-profiles[i].name[0]);
    writenum((long)profiles[i].minimum,7,3);
    writenum((long)profiles[i].maximum,7,3);
    writenum((long)profiles[i].average,7,3);
    writenum((long)(((float) profiles[i].total * 10000.0) / (float) duration + 0.05),7,3);
    writenum((long)profiles[i].entries,7,3);
    my_write(eol,1L);
    }
 
  _profile = 1;                                 /* re-enable profiling       */
}
 
 
/*
 
  Called by assembler exit routine.  Compute usage statistics for routine on
  top of profiling stack.
 
 */
 
address __profile_exit()
{
  int           i;
  time          exit_time       = (time) TickCount();
  
  if(!progo)return(0);
  depth--;
  /* end timing for a function */
 
  i = stack[stack_pointer].function;
#ifdef  SINGLE
    exit_time = exit_time - delta( exit_time ) -
                stack[stack_pointer].start - stack[stack_pointer--].correction;
    if (exit_time > 0x7FFFFFFF)
      exit_time = 0L;     						/* handle clock rollover     */
    profiles[i].total += exit_time;
    if (stack_pointer >= 0)
      stack[stack_pointer].correction += exit_time + stack[stack_pointer + 1].correction;
#else
    exit_time = exit_time - delta( exit_time ) - stack[stack_pointer--].start;
    if (exit_time > 0x7FFFFFFF)
      exit_time = 0L;							/* handle clock rollover     */
    profiles[i].total += exit_time;
#endif
  if (exit_time > profiles[i].maximum)
    profiles[i].maximum         = exit_time;
  if (exit_time < profiles[i].minimum)
    profiles[i].minimum         = exit_time;
  if (profiles[i].entries)
    profiles[i].average         = profiles[i].total / profiles[i].entries;
  return( stack[stack_pointer + 1].user );
}
 
 
/*
 
 Handle the routine entry profiling.  Setup a stack frame and a profile 
 table entry if needed.
 
 */
 
void __profile( unused, ret, name )
unsigned long	*ret;
address			unused;
char        	*name;
{
  register int  function,                       /* index of routine          */
                i;
  register time entry_time = (time) TickCount();
 
  if(!progo)return;
  depth++;
  if (++stack_pointer < MAX_STACK)
    { /* setup for return to PROFILE_EXIT on user exit */
    stack[stack_pointer].user           = (address) *ret;
    *ret								= (unsigned long) _profile_exit_;
    stack[stack_pointer].correction     = NULL;
    }
  else
    {
    depth--;
    return;
    }
 
  if ((function = lookup( name, true )) >= 0)
    { /* process function entry */
    profiles[function].entries++;
    stack[stack_pointer].function     = function;
    entry_time                        = TickCount();
    stack[stack_pointer].start        = entry_time - delta( entry_time );
    }
  else
    { /* remove entry from stack */
    *ret								= (unsigned long) stack[stack_pointer--].user;
    depth--;
    }
}
