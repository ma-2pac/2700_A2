#ifndef TIMERS_HEADER
#define TIMERS_HEADER

extern volatile long overFlows;

// function to initialise the timer
void Init_TCNT (void);

//reset timer counter
void resetOF (void);

//stop the timer
void Stop_TCNT (void);

// Timer interrupt definition
__interrupt void TOF_ISR(void);


#endif
