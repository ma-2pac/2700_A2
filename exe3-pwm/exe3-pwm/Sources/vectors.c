


extern void near oc5ISR(void);
#pragma CODE_SEG __NEAR_SEG NON_BANKED
#pragma CODE_SEG DEFAULT              // Change code section to DEFAULT.
typedef void (*near tIsrFunc)(void);
const tIsrFunc _vect[] @0xFFE4 5 {
oc5ISR
};

