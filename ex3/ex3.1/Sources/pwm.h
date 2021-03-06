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
//void Init_TC5 (int);

//function to initialise serial
void Init_sci(void);

//function to output a pwm signal to a given port
void output_PWM(unsigned int portName);

// Timer interrupt definition

__interrupt void TC1_ISR(void);

__interrupt void TC5_ISR(void);


__interrupt void RE_ISR(void);
//calculate the duty cycle and return the number of timer cycles for Hi and Lo
long int Duty_Hi_Calculator(void);



#endif