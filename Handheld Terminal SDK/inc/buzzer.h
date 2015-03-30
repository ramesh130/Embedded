
#ifndef __BUZZER
#define __BUZZER

#ifdef  __BUZZER_C
#define BUZZER_SCOPE
#else
#define BUZZER_SCOPE extern
#endif

//------------------------------------------------------------------------
//	BEEP TYPES.
//------------------------------------------------------------------------
#define NORM 		0
#define LONG 		1
#define SHRT 		2
#define OKKK 		3
#define ERRR 		4

BUZZER_SCOPE void Beep(unsigned char typ);

#endif
