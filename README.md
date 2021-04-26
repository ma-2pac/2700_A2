# 2700_A2

# Documentation Overview
There are two major sections which are the program overview and the testing procedures.  Each section is then divided into subsections, which correspond to the three exercises in order. 

# Members and roles

**Fergus Charles** - 
- Lead developer for exercise 2
- Assisted in the creation of exercise 3 and its testing
- General debugging of overall system

**Marco Tupaz** -
- Assisted in the creation of exercise 3 and its testing
- General debugging of exercise 1 and 2


**Darragh McMullen** - 

**Hilton Nguyen** - 


# Program Overview

## Exercise 1
The aim of this program was to record the time taken to perform different arithmetic functions on the HCS12 using different data types (int, float, long, double). The code would run through for loops for each data type performing the following operations, addition, multiplication, division, square root, sin and cos. The time taken for each operation would be measured and then stored in a designated location in an array. Upon running all loops, the results of these tests would be outputted to serial in a table format. 

## Exercise 2
This program aimed to use interrupts in C to receive and transmit messages. The HCS12 would be constantly ready to receive information sent to it via the serial port from the computer. Each character typed into the terminal from the computer would trigger a receive interrupt, sending the information to the board. Upon receiving a carriage return character, it would trigger the transfer interrupt that sends the data stored on the board back to the computer terminal via serial. 

## Exercise 3
This program takes a duty cycle specified by the configuration of the DIP switches on the HCS12 board and outputs a PWM signal to the onboard LEDs. Each switch is associated with a set duty cycle, such as (insert set duty cycle). The timer taken for the signal to be high is then calculated and sent to the outputting timer port. 

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


# Testing Procedures

## Exercise 1
input here

## Exercise 2
input here

## Exercise 3: Module for the major project - PWM output

Successful demonstration of the code can be shown qualitatively through the output of the LEDs being brighter for higher duty cycles and dimmer for lower duty cycles. 

### Modular Testing
- Start program with no switches UP. LEDs should be off or close to off
- Toggle switch 1 to UP. The LEDs should be on and bright
- Toggle switch 1 to DOWN and toggle switch 2 to UP. The LEDs should be on but slightly dimmer
- Repeat for all other switches, observing brightness decreasing with each switch
- To observe duty cycle changes in code, set breakpoint at "switch(dip_switch){" in the Duty_Hi_Calculator() function and check that the value of dip_switch is as desired. 

### Integration Testing
- Start program with other modules
- Check if the LEDs are on with all switches down
- Toggle switches and observe if brightness changes with different iterations similar to modular testing

