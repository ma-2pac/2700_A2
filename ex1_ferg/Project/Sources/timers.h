#ifndef TIMERS_HEADER
#define TIMERS_HEADER

extern volatile long overFlows;

// function to initialise the timer
void Init_TCNT (void);

void resetOF (void);

void Stop_TCNT (void);

// Timer interrupt definition
__interrupt void TOF_ISR(void);


#endif
