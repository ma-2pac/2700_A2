#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

int i;

void serialPrint(char* string){ 
 
  /****************************************************************
  * SCI Setup
  *****************************************************************/
  SCI1BDL = 156; /* Set BAUD rate to 9,600 */
  SCI1BDH = 0;
  SCI1CR1 = 0x00; /* 0 0 0 0 0 0 0 0
   | | | | | | | |
   | | | | | | | \__ Even Parity
   | | | | | | \____ Parity Disabled
   | | | | | \______ Short IDLE line mode (not used)
   | | | | \________ Wakeup by IDLE line rec (not used)
   | | | \__________ 8 data bits
   | | \____________ Not used (loopback disabled)
   | \______________ SCI1 enabled in wait mode
   \________________ Normal (not loopback) mode
  */
  SCI1CR2 = 0x08; /* 0 0 0 0 1 0 0 0
   | | | | | | | |
   | | | | | | | \__ No Break
   | | | | | | \____ Not in wakeup mode (always awake)
   | | | | | \______ Receiver disabled
   | | | | \________ Transmitter enabled
   | | | \__________ No IDLE Interrupt
   | | \____________ No Receiver Interrupt
   | \______________ No Transmit Complete Interrupt
   \________________ No Transmit Ready Interrupt
  */
  /****************************************************************
  * End of SCI Setup
  *****************************************************************/
  
  // loop over elements in string
  for(i = 0; i < 512; i++){
    SCI1DRL = string[i]; /* Send first byte */
    while ((SCI1SR1 & 0x80) == 0) ; /* Wait for TDRE flag */
      
  }
  
}






