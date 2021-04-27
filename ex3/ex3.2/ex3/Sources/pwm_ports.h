#ifndef TIMER_PORT_HEADER
#define TIMER_PORT_HEADER

extern char HiorLo;

// choose which ports to enable
void enable_ports(void);

//initialises port 1 of timer for output
void Init_TC1 (void);

//initialises port 2 of timer for output
void Init_TC2 (void);

//initialises port 3 of timer for output
void Init_TC3 (void);

//initialises port 4 of timer for output
void Init_TC4 (void);

//initialises port 5 of timer for output
void Init_TC5 (void);


#endif