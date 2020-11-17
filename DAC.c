/*******************************************************************
 * DAC.c
 * Instructor: Devinder Kaur
 * Runs on TM4C123
 * Implementation of the 4-bit digital to analog converter
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: Nicholas Nassar
 * Section: 002
 * Date:    11/20/2020
 *
 * Port B bits 3-0 have the 4-bit DAC
 *******************************************************************/

#include "DAC.h"
#include "..//inc//tm4c123gh6pm.h"

// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
	// Init Port B
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x02;	// turn port B clock on
	delay = SYSCTL_RCGC2_R; // delay
	GPIO_PORTB_AMSEL_R &= ~0x7F; // disable analog function on PB6-0
	GPIO_PORTB_PCTL_R &= ~0x0FFFFFFF; // we want regular GPIO
	GPIO_PORTB_DIR_R |= 0x7F; // PB6-0 is output
	GPIO_PORTB_DR8R_R |= 0x7F; //PB6-0 DR8R
	GPIO_PORTB_AFSEL_R &= ~0x7F; // no alternate function for PB6-0
	GPIO_PORTB_PUR_R &= ~0x7F; // no pullup resistors for PB6-0
	GPIO_PORTB_DEN_R |= 0x7F; // enable digital pins for PB6-0
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
	GPIO_PORTB_DATA_R = data; // set Port B's data to our data
}
