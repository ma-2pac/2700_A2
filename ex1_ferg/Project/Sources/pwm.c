#include "pwm.h"
#include <stdio.h>
#include "serialPrint.h"
#include "pwm_ports.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */

volatile long int Period; //amount of timer ticks per period
volatile int frequency;
volatile float Frequency;

//volatile int test;
volatile long int Hi_count; //used to control how long the signal is high
volatile long int Lo_count; //used to control how long the signal is low

volatile int dip_switch;   //stores port h
unsigned char Duty_Array[2]; //used for serial duty cycle
unsigned char Period_Array[6]; //used for the period when using serial
unsigned char Frequency_Array[3]; //used for the ferquencey when using serial
volatile float Percent; //% of duty high
volatile int Int_Percent; //intermediate calculation
volatile long int Duty_Hi; //the count of the high ticks


//interrupt routine for timer 1
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TC1_ISR(void) { 
   Hi_count = Duty_Hi_Calculator(); //count high
   Lo_count = Period - Hi_count; //count low
  if(HiorLo){
   TC1 = TC1 + Lo_count; //add low count to be the next interrupt.
   HiorLo = 0;
   PTJ = 0x00; //disable leds.
   PORTB = 0x00; //disable leds.
  }
  else{
   TC1 = TC1 + Hi_count; //add high count to be the next interrupt.
   HiorLo = 1; //toggle hiorlo
   PTJ = 0x00;
   PORTB = 0xFF; //enable leds. 
  }
}


//#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
//__interrupt void TC2_ISR(void) { 
  //need to add an interrupt section in here that counts and resets
//   Hi_count = Duty_Hi_Calculator();
//   Lo_count = Period - Hi_count; 
//  if(HiorLo){
//   TC5 = TC5 + Lo_count;
//   HiorLo = 0;
//   PTJ = 0x00;
//   PORTB = 0x00;
//  }
//  else{
//   TC5 = TC5 + Hi_count;
//   HiorLo = 1;
//   PTJ = 0x00;
//   PORTB = 0xFF;  
//  }
//}



// interrupt routine for output channel 5
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TC5_ISR(void) { 
   Hi_count = Duty_Hi_Calculator(); //count high
   Lo_count = Period - Hi_count; //count low
  if(HiorLo){
   TC5 = TC5 + Lo_count; //add low count to be the next interrupt.
   HiorLo = 0;
   PTJ = 0x00; //disable leds.
   PORTB = 0x00; //disable leds.
  }
  else{
   TC5 = TC5 + Hi_count; //add high count to be the next interrupt.
   HiorLo = 1; //toggle hiorlo
   PTJ = 0x00;
   PORTB = 0xFF; //enable leds. 
  }
}

//calculating the desired duty high 
long int Duty_Hi_Calculator(void){
   volatile int i = 0;
   char re[100]; //set variables for use in serial case 127
   volatile int re_place; // ""
   dip_switch = PTH; //load dip switch
   
   //each number on the dip switch corresponds to a % duty high, starting with PH7
   // with the number 1, increasing these from the left, with all others 0 with show a % high.
   //With all high but switch 1, serial can be used to set these values. 
      
   switch(dip_switch){
    case 0: //no pins enables
      Duty_Hi = 1;   
      return Duty_Hi;
      Period = 1875;
      break;
    case 128: //ph7 or pin 1 enabled, 10% duty
      Percent = 0.1;
      Period = 1875;
      break;
    case 192:
      Percent = 0.2; //pin 1 and 2 enabled, 20% duty
      Period = 1875;
      break;
    case 224:
      Percent = 0.3;
      Period = 1875;
      break;
    case 240:
      Percent = 0.4;
      Period = 1875;
      break;
    case 248:
      Percent = 0.5;
      Period = 1875;
      break;
    case 252:
      Percent = 0.6;
      Period = 1875;
      break; 
    case 254:
      Percent = 0.7;
      Period = 1875;
      break;
    case 255: //all pins enabled 80% duty
      Percent = 0.8;
      Period = 1875;
      break;
    
    case 127: // all enabled but pin 1, uses serial
      //type ! followed by 2 digits for a duty cycle
      if (strlen(SCIString)>0 && SCIString[0] == '!'){
        i = 0;
        while (SCIString[i] != 10){
          Duty_Array[i] = SCIString[i+1];
          i++;
        }
        sscanf(Duty_Array, "%d", &Int_Percent); //scan into variable
        Percent = Int_Percent/100.00; //convert to float
      }  
      //tpye @ followed by 3 digits for a change in frequency
      if (strlen(SCIString)>0 && SCIString[0] == '@'){
        i = 0;
        while (SCIString[i] != 10){
          Frequency_Array[i] = SCIString[i+1];
          i++;
        }
        sscanf(Frequency_Array, "%f", &Frequency); //scan into frequency variable
        Period = Frequency/(10000*0.00000533);   //frquency calculation based on prescaler of 128
      }  
      break;
      
    default: //dip switch true value used in calculations
      Percent = ((float) dip_switch)/255.00;
      Period = 1870;
      break;
   }
   //return the duty high
   Duty_Hi = Period*Percent;
   return Duty_Hi;
}

