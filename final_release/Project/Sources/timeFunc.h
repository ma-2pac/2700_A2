#ifndef TIMEFUNC_HEADER
#define TIMEFUNC_HEADER

extern volatile long overFlows;

//function that takes in data type and the desired operation and returns the time
/* Takes inputs for function to run and datatype to use
  funcs:     0 = add, 1 = mult, 2 = divide, 3 = sqrt,  4 = sin, 5 = cos
  datatypes: 0 = int, 1 = long, 2 = float,  3 = double
  returns number of clock cycles elapsed (accounting for timer overflow interrupt routine overhead)
  */
long timeFunc(int,int);

#endif
