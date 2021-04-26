#include "pwm.h"
#include <stdio.h>

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */
volatile long int Period;
volatile int frequency;
char HiorLo;
char re[100];
volatile int re_place;
volatile int test;
unsigned char SCIString[12];
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
volatile int i = 0;


//need to creae an over flow time of one hz 

/*

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
  
  SCI1BDH = 0x00;             // Set the baud rate at 9600
  SCI1BDL = 156; 
  SCI1CR2 = 0x2c; //re te and rtede
  //SCI1CR2 = 0x8c; //re te and rtde
  
  re_place = 0;
  SCI1CR2 |= 0x20; //enable to rdte intterupt  
}

*/

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

#pragma CODE_SEG __NEAR_SEG NON_BANKED  /*Interrupt section for this module. Placement will be in NON_BANKED area.*/ 
__interrupt void TC1_ISR(void){
   output_PWM(TC1);

}

#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TC5_ISR(void) { 
  //need to add an interrupt section in here that counts and resets      
   output_PWM(TC5);
}

long int Duty_Hi_Calculator(void){

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


//module to run PWM for any output
void output_PWM(unsigned int portName){
  
  Hi_count = Duty_Hi_Calculator();
  Lo_count= Period - Hi_count;
  
  if(HiorLo){
   //delay??
   portName = portName + Hi_count;    //portName is chosen interrupt pin
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