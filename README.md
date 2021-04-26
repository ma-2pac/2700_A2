# 2700_A2

# Documentation Overview
There are two major sections which are the program overview and the testing procedures.  Each section is then divided into subsections, which correspond to the three exercises in order. 

# Members and roles

**Fergus Charles** - 
- Lead developer for exercise 2
- Assisted in the creation of exercise 3 and its testing
- General debugging of overall system

**Marco Tupaz** - 

**Darragh McMullen** - 

**Hilton Nguyen** - 


# Program Overview

## Exercise 1
input here

## Exercise 2
input here

## Exercise 3
input here

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

### Integration Testing
- Start program with other modules
- Check if the LEDs are on with all switches down
- Toggle switches and observe if brightness changes with different iterations

