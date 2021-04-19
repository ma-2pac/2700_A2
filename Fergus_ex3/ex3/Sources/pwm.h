#ifndef TIMERS_HEADER
#define TIMERS_HEADER





// function to initialise the timer
void Init_TC5 (void);

// Timer interrupt definition
__interrupt void TC5_ISR(void);
#endif

//calculate the duty cycle and return the number of timer cycles for Hi and Lo
int Duty_Hi_Calculator(void);