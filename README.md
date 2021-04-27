# 2700_A2

# Documentation Overview
There are two major sections which are the program overview and the testing procedures.  Each section is then divided into subsections, which correspond to the three exercises in order. 

# Members and roles

**Fergus Charles** 
- Assisted in the creation of exercise 3, serial ext and its testing
- Developed core for exercise 2
- Serial and table output for ex1
- Building integration and General debugging of overall system

**Marco Tupaz** 
- Assisted in the creation of exercise 3 and its testing
- General debugging of exercise 1 and 2

**Darragh McMullen** 
- Lead developer for exercise 1

**Hilton Nguyen**  
- Assisted in creation of exercise 2

# Program Overview

## Exercise 1
The aim of this program was to record the time taken to perform different arithmetic functions on the HCS12 using different data types (int, float, long, double). The code would run through for loops for each data type performing the following operations, addition, multiplication, division, square root, sin and cos. The time taken for each operation would be measured and then stored in a designated location in an array. Upon running all loops, the results of these tests would be outputted to serial in a table format, built through a seperate module, which stores this result in an external a string. A flag set upon serial start up ensures that this table goes out first upon the SCI_ISR vector being run.  

## Exercise 2
This program aimed to use interrupts in C to receive and transmit messages. The HCS12 would be constantly ready to receive information sent to it via the serial port from the computer. Firstly serial port 1 is configured to send/recieve and receive interrupts enabled. Each character typed into the terminal from the computer would trigger an interrupt, if the receiving flag on the status register is set then this sending then this character is stored. Characters are stored untill a carriage return, then transmitting interrupts are enbables. Upon receiving a carriage return character, it would trigger the transfer interrupt that sends the data stored on the board back to the computer terminal via serial. 

## Exercise 3
This program toogles an output pin high/low depending on receiving interrupts, which durations are altered by a duty cycle specified by the configuration of the DIP switches on the HCS12 board and outputs a PWM signal to the onboard LEDs. Each switch is associated with a set duty cycle, such as pin 1 enabled is 10% duty, pin 1 and 2 is 20% duty. The user can also enter their own duty cycles and frequency (see user instructions). This duty cycle is a percentage of the total period in represents the number of timer clicks the signal should be high. If the signal is high then upon an interrupt the leds are set to low and a corresponding time is added to the TCx interrupt.

# Instructions for User
- For serial input and output, ensure a wire is connected to Serial Port 1 (right side of the HCS12)
- For power and debugging, connect a wire to Serial Port 0 (left side of HCS12)
- If Windows user, use the PUTTY software to have a Serial terminal to send and receive messages from the HCS12
- Setting up Putty
  - Choose ‘Serial’ as Connection type in Session tab
  - Set baud rate to 9600
  - Set Serial line to whatever port the HCS12 is connected to on your computer
  - In Terminal tab, tick box for Implicit LF in every CR
  - In Serial tab under Connection, set Flow Control to be None
- In main set "port" to be either 1,2,3,4,5 which represents the output port for the pwm 
- Set the dip switches to be the desired duty cycle. Pin 1 high all else zero is 10% , pin 1 and 2 high all else 0 is 20%  duty high ect. 
- To use serial type your message into putty 
- To use serial to control frequency and duty cycle, type "@xxx" (must be 3 digits) to control the frequency. This must be first set. Then you can set the duty cycle by "!xx" must be 2 digits. This can be changed as required by the user. 


# Testing Procedures

## Exercise 1
### Modular Testing
- Start program with board connected
- Set breakpoint at end of first FOR loop. Check entries in Data for timeInt array that time entries have been entered.
- Set breakpoint at end of second FOR loop. Check entries in Data for timeLong array that time entires have been entered.
- Set breakpoint at end of third FOR loop. Check entries in Data for timeFloat array that time entires have been entered.
- Set breakpoint at end of fourth FOR loop. Check entries in Data for timeDouble array that time entires have been entered.
- Run code without breakpoints. Check that values from array are displayed in table sent over serial output.
- if no:
- Check the values for the add, mult, div ect strings in the asciitable function, do they have correct newline and carraige return? do they look as expected?
- Is the SCIString variable being set with these new new strings correctly?
- Is the new SCIString accessable in the printSerial function? 
- set SCIString as a fixed string with a '!' at the end and check that it is being printed properly, if no, go to serial section. 

## Exercise 2
Successful demonstration of the code can be shown qualitatively through the board terminal.

### Modular Testing
- Start the program with the board connected, open putty.
- Type a string of characters from the keyboard. 
- Press the enter key. The string that is stored is now displayed onto the terminal.
- If no, open Init_SCI function in debugger and check that SCI1BDH = 0x00, SCI1BDL = 156, SCI1CR2 = 0x2c, SCI1CR2 |= 0x20
- Ceck that code stops at the ex1 serial printing section in the ISR function, if not check that SCI1SR1 & 0x80 && SCI1CR2 & 0x80 && table_transmit == 1, if not, find why.
- If code keep printing, check that transmit interrupt is disbaled.
- Once serial table from ex 1 is printing, check that table_transmit is now = 0 and that only the receive interrupt is enabled SCI1CR2 |= 0x20
- Set break points at the recieving section and step through 
- Check transmit is being enabled correctly at the end of the receiving section 
- Then step through transmitting section.


## Exercise 3: Module for the major project - PWM output

Successful demonstration of the code can be shown qualitatively through the output of the LEDs being brighter for higher duty cycles and dimmer for lower duty cycles. 

### Modular Testing
- Start program with no switches UP. LEDs should be very dim as this is a duty_high of 1 count.
- If Led's are not in this state:
- Go through the init functions for the enabled ports, step through and check that the gereric timer register settings and output channel specific settings are being set as desired.
- Check that the timer interrupt is occuring by setting a breakpoint at the TCx_ISR vector of interest. 
- Check that the leds are toggling and hence the PWM is toggling. 
- If toggling but timings wrong, check duty high calculator: 
- Toggle switch 1 to UP. The LEDs should be on and dull
- To observe duty cycle changes in code, set breakpoint at "switch(dip_switch){" in the Duty_Hi_Calculator() function and check that the value of dip_switch is as desired. Then check that its case is working and percentage is being set correctly. Then check duty high is being set as expected. Then check it is caused hi_count and lo_count to be set correctly, if these values are being set correctly and output channel is toggling then the pwm signal should be working. 

### Integration Testing
- Start program with other modules.
- Check if the LEDs are dim with all switches down.
- Check the first outputted result from serial is the ascii table. 
- Check pwm changes with dip switch.
- Check serial is working and can be typed to. 
- Check serial can change duty cycle settings.


