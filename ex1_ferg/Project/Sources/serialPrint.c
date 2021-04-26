#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include <string.h>
#include "serialPrint.h"
volatile int table_transmit = 1;
volatile int i;
volatile int end_string =0;
char re[100];
volatile int re_place;
unsigned char SCIString[500];
unsigned char table[100];



void Init_sci(char* start, char* add, char* mult,char* div,char* sqrt,char* sin,char* cos){

  SCI1BDH = 0x00;             // Set the baud rate at 9600
  SCI1BDL = 156; 
  SCI1CR2 = 0x2c; //re te and rtede 
  re_place = 0;
  //SCI1CR2 |= 0x20; //enable to rdte intterupt
  //
  sprintf(SCIString, "%s%s%s%s%s%s%s", start, add, mult, div,sqrt,sin,cos);
  SCI1CR2 |= 0x80;
  //initialise
  //joined together string 


  
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
        table_transmit = 0; 
        SCI1CR2 |= 0x80; //enable tranmit interupt
      }
   }
  
  if (SCI1SR1 & 0x80 && SCI1CR2 & 0x80 && table_transmit == 0){ /*If transmission flag is set*/
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
  
  if (SCI1SR1 & 0x80 && SCI1CR2 & 0x80 && table_transmit == 1){ /*If transmission flag is set*/
    SCI1SR1;
    
    if(SCIString[re_place] != '!'){
      SCI1DRL = SCIString[re_place];
      re_place = re_place +1;
    }
    else{
    SCI1DRL = 13;
    re_place = 0;
    SCI1CR2 &= 0x7F; /*Disable TDRE interrupt*/
    //SCI1CR2 |= 0x10;
    }
  //
  }
  
   
  return;
}








