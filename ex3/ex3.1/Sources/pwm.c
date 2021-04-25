#include "pwm.h"
#include <stdio.h>

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */
volatile int Period = 1886;
char HiorLo;
char re[100];
volatile int re_place;
volatile int test;
unsigned char SCIString[12];
volatile int Hi_count=1500;
volatile int Lo_count=200;

volatile int dip_switch;
unsigned char P1[2];
unsigned char P2[1];
volatile float Percent;
volatile int Duty_Hi;

volatile int Int_Percent;;
volatile float Percent_SCI;
volatile float Period_SCI;
volatile int i = 0;





const int Hi = 1500;
const int Lo = 200;

//need to creae an over flow time of one hz 

void Init_TC5 (int param) {

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
   TC5 = TC5 + Lo_count;
   HiorLo = 0;
   PTJ = 0x00;
   PORTB = 0x00;
  }
  else{
   TC5 = TC5 + Hi_count;
   HiorLo = 1;
   PTJ = 0x00;
   PORTB = 0xFF;  
  }
}

int Duty_Hi_Calculator(void){

   dip_switch = PTH;
   Period = 1886;
   
   switch(dip_switch){
    case 0:
      Duty_Hi = 1;
      return Duty_Hi;
      break;
    case 128:
      Percent = 0.1;
      break;
    case 192:
      Percent = 0.2;
      break;
    case 224:
      Percent = 0.3;
      break;
    case 240:
      Percent = 0.4;
      break;
    case 248:
      Percent = 0.5;
      break;
    case 252:
      Percent = 0.6;
      break; 
    case 254:
      Percent = 0.7;
      break;
    case 255:
      Percent = 0.8;
      break;
    
    case 127:
      if (strlen(SCIString)>0 && SCIString[0] == '!'){
        i = 0;
        while (SCIString[i] != 10){
          P1[i] = SCIString[i+1];
          i++;
        }
      }
      //Int_Percent = boost::lexical_cast<int>(P1)
      sscanf(P1, "%d", &Int_Percent);
      Percent = Int_Percent/100.00;
      Period = 1886;
      
      break;
      
      default:
      Percent = ((float) dip_switch)/255.00;
      break;
  } 
   
   Duty_Hi = Period*Percent;
   return Duty_Hi;
}

//module to run PWM for any output
int run_PWM(int Hi_count, char enable_port[5], char output_port[5]){
  
  int Lo_count;
  
  Lo_count= Period - Hi_count;
  
  if(HiorLo){
   //delay??
   TC5 = TC5 + Hi_count;    //TC5 is chosen interrupt pin
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
  
}


//might be best to use ch7

// how to set break points in an interrupt routine?
//how they tested 
//how did they demo it 
// 3.662109375
//1886
// float round to int later from input 