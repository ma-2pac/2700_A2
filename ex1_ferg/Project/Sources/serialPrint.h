#ifndef SERIALPRINT_HEADER
#define SERIALPRINT_HEADER

extern unsigned char SCIString[500];
extern char re[100];
extern volatile int re_place;

//function to initialise serial
void Init_sci(char*, char*, char*, char*, char*, char*, char*, char*);

//serial isr vector
__interrupt void RE_ISR(void);


// Timer interrupt definition
__interrupt void TC1_ISR(void);

// Timer interrupt definition
__interrupt void TC2_ISR(void);

// Timer interrupt definition
__interrupt void TC3_ISR(void);

// Timer interrupt definition
__interrupt void TC4_ISR(void);

// Timer interrupt definition
__interrupt void TC5_ISR(void);


#endif
