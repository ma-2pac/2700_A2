#ifndef TIMERS_HEADER
#define TIMERS_HEADER


//struct to define a pwm signal
typedef struct{
  char port[5];     //defines what port the pwm will be outputted to
  int signalTotal;  //defines the constant that the duty cycle will be multiplied by
  float Duty_High;  //defines the duration for when PWM signal is high
  float Duty_Low;   //defines the duration for when PWM signal is low
  
}PWM_Output;


// function to initialise the timer
void Init_TC5 (int);

//function to initialise serial
void Init_sci(void);

// Timer interrupt definition
__interrupt void TC5_ISR(void);


__interrupt void RE_ISR(void);
//calculate the duty cycle and return the number of timer cycles for Hi and Lo
int Duty_Hi_Calculator(void);


//module to run PWM for any output
int run_PWM(int Hi_count, char enable_port[5], char output_port[5]);


#endif