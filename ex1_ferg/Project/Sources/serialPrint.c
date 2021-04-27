#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include <string.h>
#include "serialPrint.h"
volatile int table_transmit = 1; //used to first transmit serial results
volatile int i;
volatile int end_string =0;
unsigned char table[100];



//initialise the serial
void Init_sci(char* start, char* add, char* mult,char* div,char* sqrt,char* sin,char* cos, char* bar){

  SCI1BDH = 0x00;  // Set the baud rate at 9600
  SCI1BDL = 156; 
  SCI1CR2 = 0x2c; //re te enabled 
  SCI1CR2 |= 0x20; //enable to rdte intterupt
  re_place = 0; // place holder for recieving/transmitting sci string
  
  //Initialise serial ex1 string as string to be printed
  sprintf(SCIString, "%s%s%s%s%s%s%s", start,add, mult, div,sqrt,sin,cos);
  SCI1CR2 |= 0x80;
}


//serial interrupt vector
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void RE_ISR(void) {

    //if the receiving flag and re enabled - then receive
    if(SCI1SR1 & 0x20 && SCI1CR2 & 0x20){ 
    SCI1SR1;
      if(SCI1DRL != 13){ //if not at the end of the string
        SCIString[re_place] = SCI1DRL;
        re_place = re_place +1;
      }
      else{ //at end of string
        SCIString[re_place] = 10; //print new line
        re_place = re_place +1;
        SCIString[re_place] = 13; //print carrage return
        re_place = 0;
        table_transmit = 0; //make sure that the initial table cant be printing
        SCI1CR2 |= 0x80; //enable transmit interupt
      }
   }
  
  //after having received characters then transmit is enabled - following is for printing to serial:
  if (SCI1SR1 & 0x80 && SCI1CR2 & 0x80 && table_transmit == 0){ /*If transmission flag is set*/
    SCI1SR1;
    
    if(SCIString[re_place] != 13 ){ //if not at the end of the string
      SCI1DRL = SCIString[re_place]; //send to data out register
      re_place = re_place +1;
    }
    else{ //at end of the string
    SCI1DRL = 13; //transmit a carrage return
    re_place = 0;
    SCI1CR2 &= 0x7F; /*Disable TDRE interrupt*/
    }
  } 
  
  //when starting the table_transmit flag will be 1, this is to send out the table
  if (SCI1SR1 & 0x80 && SCI1CR2 & 0x80 && table_transmit == 1){ /*If transmission flag is set*/
    SCI1SR1;
    
    if(SCIString[re_place] != '!'){ // special character used to denote end of table
      SCI1DRL = SCIString[re_place];
      re_place = re_place +1;
    }
    else{
    SCI1DRL = 13;
    re_place = 0;
    SCI1CR2 &= 0x7F; /*Disable TDRE interrupt*/
    }
  }   
  return;
}






