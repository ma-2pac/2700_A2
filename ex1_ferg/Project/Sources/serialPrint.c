#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include "serialPrint.h"
int i;
char re[100];
volatile int re_place;
unsigned char SCIString[12];
unsigned char table[100];



void Init_sci(char *start, char* add, char* mult,char* div,char* sqrt,char* sin,char* cos){

  SCI1BDH = 0x00;             // Set the baud rate at 9600
  SCI1BDL = 156; 
  SCI1CR2 = 0x2c; //re te and rtede 
  re_place = 0;
  SCI1CR2 |= 0x20; //enable to rdte intterupt
  SCI1CR2 |= 0x80;
  
  //initialise
  for(i=0; i<strlen(start); i++){ 
    if(start[i] != 10 ){
      SCI1DRL = start[i];
      i = i +1;
    }
    else{
     SCI1DRL = 13;
    }
  }
  //add
  for(i=0; i<strlen(add); i++){ 
    if(add[i] != 10 ){
      SCI1DRL = add[i];
      i = i +1;
    }
    else{
     SCI1DRL = 13;
    }
  }
  
  for(i=0; i<strlen(mult); i++){ 
    if(mult[i] != 10 ){
      SCI1DRL = mult[i];
      i = i +1;
    }
    else{
     SCI1DRL = 13;
    }
  }
  
  for(i=0; i<strlen(div); i++){ 
    if(div[i] != 10 ){
      SCI1DRL = div[i];
      i = i +1;
    }
    else{
     SCI1DRL = 13;
    }
  }
  
  
  for(i=0; i<strlen(sqrt); i++){ 
    if(sqrt[i] != 10 ){
      SCI1DRL = sqrt[i];
      i = i +1;
    }
    else{
     SCI1DRL = 13;
    }
  }
  
  for(i=0; i<strlen(sin); i++){ 
    if(sin[i] != 10 ){
      SCI1DRL = sin[i];
      i = i +1;
    }
    else{
     SCI1DRL = 13;
    }
  }
  
  for(i=0; i<strlen(cos); i++){ 
    if(cos[i] != 10 ){
      SCI1DRL = cos[i];
      i = i +1;
    }
    else{
     SCI1DRL = 13;
    }
  }
  
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








