#include "pwm.h"
#include "pwm_ports.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */


const int Period = 1886;
#define START_CYCLE 1
#define WAIT_CYCLE 0
#define Hi 1200
#define Lo 50
int HiorLo = 0;


char re[100];
volatile int re_place;
volatile int test;
//unsigned char SCIString[12]={'F','R','E','E','S','C','A','L','E',0xa,0xd,'\0'};
unsigned char SCIString[12];


//need to creae an over flow time of one hz 

/*
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
   TC5 = TC5 + 900;
}
*/


void Init_sci(void){
  
  test = 1;
  SCI1BDH = 0x00;             // Set the baud rate at 9600
  SCI1BDL = 156; 
  SCI1CR2 = 0x2c; //re te and rtede
  //SCI1CR2 = 0x8c; //re te and rtde
  
  re_place = 0;
  ///SCI1CR2 |= 0x80; //enable to tdre intterupt
  SCI1CR2 |= 0x20; //enable to rdte intterupt
  //SCI1CR2 = 0x0c;    // te and re
  //SCI1CR2 |= 0x10; //enable receive
  //SCI1DRL = SCIString[re_place]; 
  //re_place = re_place+1;  
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void RE_ISR(void) {

  
    if(SCI1SR1 & 0x20 && SCI1CR2 & 0x20){ /*If reception flag is set*/
    SCI1SR1;
      if(SCI1DRL != 13){
        SCIString[re_place] = SCI1DRL;
       re_place = re_place +1;
      }
      else{
        SCIString[re_place] = 10;
        re_place = re_place +1;
        SCIString[re_place] = 13;
        re_place = 0; 
        SCI1CR2 |= 0x80; //enable tranmit interupt
      }
   }
  
  if (SCI1SR1 & 0x80 && SCI1CR2 & 0x80 ){ /*If transmission flag is set*/
    SCI1SR1;
    
    if(SCIString[re_place] != 13 ){
      SCI1DRL = SCIString[re_place];
      re_place = re_place +1;
    }
    else{
    SCI1DRL = 13;
    re_place = 0;
    SCI1CR2 &= 0x7F; /*Disable TDRE interrupt*/
    //SCI1CR2 |= 0x10;
    }
  } 
  

  return;
}
 
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TC1_ISR(void) {

  output_PWM(TC1);
  
}

// look at the isr_vectors.c for where this function is 
//  added to the ISR vector table
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TC5_ISR(void) {

  output_PWM(TC5);

/* 
  //need to add an interrupt section in here that counts and resets
   int Hi_count;
   int Lo_count;
   //int Hi_count = read_analog();
   Hi_count = Duty_Hi_Calculator();
   Lo_count = Period - Hi_count; 
  if(HiorLo){
   //delay??
   TC5 = TC5 + Hi_count;
   HiorLo = 0;
   PTJ = 0x00;
   PORTB = 0x00;
  }
  else{
   TC5 = TC5 + Lo_count;
   HiorLo = 1;
   PTJ = 0x00;
   PORTB = 0xFF;  
  }
  
  */
}


int Duty_Hi_Calculator(void){
   volatile int dip_switch;
   volatile float Percent;
   volatile int Duty_Hi;
   dip_switch = PTH; 
   Percent = dip_switch/128;
   Duty_Hi = Period*Percent;
   return Duty_Hi;
}

void output_PWM(Word portName){

  //need to add an interrupt section in here that counts and resets
   int Hi_count;
   int Lo_count;
   //int Hi_count = read_analog();
   Hi_count = Duty_Hi_Calculator();
   Lo_count = Period - Hi_count; 
  if(HiorLo){
   //delay??
   portName = portName + Hi_count;
   HiorLo = 0;
   PTJ = 0x00;
   PORTB = 0x00;
  }
  else{
   portName = portName + Lo_count;
   HiorLo = 1;
   PTJ = 0x00;
   PORTB = 0xFF;  
  }


}


//might be best to use ch7

// how to set break points in an interrupt routine?
//how they tested 
//how did they demo it 
// 3.662109375
//1886
// float round to int later from input 