#ifndef SERIALPRINT_HEADER
#define SERIALPRINT_HEADER


//function to initialise serial
void Init_sci(char*, char*, char*, char*, char*, char*, char*);

__interrupt void RE_ISR(void);

#endif
