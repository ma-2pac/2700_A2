#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "timers.h"

void main(void) {
  // Aim: Allowing a message to be sent via serial and interrupts
  
  // set the ports for so the information can be put in and sent out
  DDRB= 0xFF;   /* Port B output */
  DDRJ= 0xFF;   // Port J to Output
  PTJ = 0x00;   // enable LEDs
 
  PORTB=0x0F;     // debugging info
  
  // set functions to read from serial and transmit messages from serial
  InputSerial = sdfs;
  OutputSerial = hfbmnds;
  
  ; export symbols
            XDEF Entry, _Startup            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point



  ; Include derivative-specific definitions
  		INCLUDE 'derivative.inc'

  ROMStart    EQU  $4000  ; absolute address to place my code/constant data

  ; variable/data section

              ORG RAMStart
  ; String and ASCII definitions
  STRING_IN   DS.B  100
  NL_A        FCB    10
  CR_A        FCB    13

  ; Constants
  ASCII_NL    EQU    10
  ASCII_CR    EQU    13

  BAUD_RATE   EQU    $9C
  CR_1        EQU    $00
  CR_2        EQU    $0C



  ; code section
              ORG   ROMStart



  Entry:
  _Startup:
              LDS   #RAMEnd+1       ; initialize the stack pointer

              CLI                   ; enable interrupts
    
  config:   LDD   #BAUD_RATE      ; Set baud rate to 9600bps
            STD   SCI1BD
            LDAA  #CR_1           ; Set Control Registers to enable reading and transmission
            STAA  SCI1CR1
            LDAA  #CR_2
            STAA  SCI1CR2
            
  configStrR: LDX   #STRING_IN      ; Load a string

  readLoop:   LDAA  SCI1SR1         ; Attempt to read from serial
              ANDA  #mSCI1SR1_RDRF
              BEQ   readLoop
              LDAA  SCI1DRL         ; Store byte read from serial
              STAA  0, X
              CMPA  #ASCII_CR       ; If we are at end of string start transmitting
              BEQ   configStrT
              INX                   ; Otherwise keep reading
              BRA   readLoop
              
  configStrT: LDX   #STRING_IN      ; Load the string to send

  transmLoop: LDAA  SCI1SR1         ; Wait till we can send the byte
              ANDA  #mSCI1SR1_TDRE
              BEQ   transmLoop
              LDAA  0, X            ; Send the byte
              STAA  SCI1DRL
              CMPA  #ASCII_CR       ; If we are at end of string start reading
              BEQ   configStrR
              INX                   ; Otherwise keep transmitting
              BRA   transmLoop
   
  // call the initise timer function
  Init_TC7();
 
  // enable the interrupts
	// calls asm("CLI");
	EnableInterrupts;
  
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
