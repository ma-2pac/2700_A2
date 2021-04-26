#ifndef SERIAL_HEADER
#define SERIAL_HEADER

//defining a structure for the serial, what has to be defined
//here: 

/*
typedef struct serialParams 
{
  
  unsigned int SCI_BD;       // Baud rate register for any serial port
  unsigned char SCI_CR2;     // Control register 2 for any serial port
  unsigned char SCI_SR1;     // Status register 1 for any serial port
  unsigned char SCI_DRL;     // Data resgister low for any serial port
  volatile int portNumber;   // determine which port is used to receive and transmit signals

}serialParam;
*/


//function to initialise serial
void Init_sci(void);

//serial interrupt definiton
__interrupt void RE_ISR(void);

#endif