#ifndef SERIAL_HEADER
#define SERIAL_HEADER

//defining a structure for the serial, what has to be defined
//here: 

/*
typedef struct serialParams {
  unsigned int SCI_BD;
  unsigned char SCI_CR2;
  unsigned char SCI_SR1;
  unsigned char 



} serialParam;
*/


//function to initialise serial
void Init_sci(void);

//serial interrupt definiton
__interrupt void RE_ISR(void);

#endif