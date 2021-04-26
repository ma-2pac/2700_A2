#include "pwm.h"
#include <stdio.h>
#include "serialPrint.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */

volatile long int Period;
volatile int frequency;
char HiorLo;


volatile int test;
volatile long int Hi_count;;
volatile long int Lo_count;

volatile int dip_switch;
unsigned char Duty_Array[2];
unsigned char Period_Array[6];
unsigned char Frequency_Array[3];
volatile float Percent;
volatile float Frequency;
volatile long int Duty_Hi;

volatile int Int_Percent;


//need to creae an over flow time of one hz 

void Init_TC5 (void) {

//mainsection from book
   TSCR1 = 0x90; // enable TCNT and fast timer flag clear
   TSCR2 = 0x07; // disable TCNT interrupt, set prescaler to 128
   

   //configure 05c
   TIOS = 0x20; // enable OC5 function
   TCTL1 = 0x04; //change pin action to toggle
   TFLG1 = 0xFF; // clear all cl flag
   TIE = 0x20; //enable interrupt of channel 5
   
   TC5 = TCNT + 100;
   while(TFLG1 & TFLG1_C5F); // wait until OC0 pin go high after counting 2100   //debug
   TCTL1 = 0x04; // set OC5 pin action to toggle
   HiorLo = 0;
}
 

// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TC5_ISR(void) { 
  //need to add an interrupt section in here that counts and resets
   //int Hi_count = read_analog();
   Hi_count = Duty_Hi_Calculator();
   Lo_count = Period - Hi_count; 
  if(HiorLo){
   //delay??
   //TC5 = TC5 + Lo;
   TC5 = TC5 + Lo_count;
   HiorLo = 0;
   PTJ = 0x00;
   PORTB = 0x00;
  }
  else{
   //TC5 = TC5 + Hi;
   TC5 = TC5 + Hi_count;
   HiorLo = 1;
   PTJ = 0x00;
   PORTB = 0xFF;  
  }
}

long int Duty_Hi_Calculator(void){
   volatile int i = 0;
   char re[100];
   volatile int re_place;
   dip_switch = PTH;
   
   
   switch(dip_switch){
    case 0:
      Duty_Hi = 1;
      return Duty_Hi;
      Period = 1875;
      break;
    case 128:
      Percent = 0.1;
      Period = 1875;
      break;
    case 192:
      Percent = 0.2;
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
    case 255:
      Percent = 0.8;
      Period = 1875;
      break;
    
    case 127:

        if (strlen(SCIString)>0 && SCIString[0] == '!'){
        i = 0;
        while (SCIString[i] != 10){
          Duty_Array[i] = SCIString[i+1];
          i++;
        }
        sscanf(Duty_Array, "%d", &Int_Percent);
        Percent = Int_Percent/100.00;
      }
      
      if (strlen(SCIString)>0 && SCIString[0] == '@'){
        i = 0;
        while (SCIString[i] != 10){
          Frequency_Array[i] = SCIString[i+1];
          i++;
        }
        sscanf(Frequency_Array, "%f", &Frequency);
        Period = Frequency/(10000*0.00000533);   //frquency is 
      } 
      
      break;
      
    default:
      Percent = ((float) dip_switch)/255.00;
      Period = 1870;
      break;
   }
   
   Duty_Hi = Period*Percent;
   return Duty_Hi;
}

