/*******************************************************************
 * piano.c
 * Instructor: Devinder Kaur
 * Runs on TM4C123
 * There are four keys in the piano
 * Authors: Daniel Valvano,
 * 					Thomas Royko
 * Student: Nicholas Nassar
 * Section: 002
 * Date:    11/20/2020
 *
 * Port E bits 3-0 have 4 piano keys
 *******************************************************************/

#include "Piano.h"
#include "..//inc//tm4c123gh6pm.h"


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x10; // turn Port E clock on
	delay = SYSCTL_RCGC2_R; // delay
	GPIO_PORTE_AMSEL_R &= ~0x0F; // disable analog function
	GPIO_PORTE_PCTL_R &= ~0xFFFF; // we want regular GPIO
	GPIO_PORTE_DIR_R &= ~0x0F; // PE3-PE0 are inputs
	GPIO_PORTE_AFSEL_R &= ~0x0F; // no alternate function
	GPIO_PORTE_PUR_R &= ~0x0F; // no pullup resistors
	GPIO_PORTE_DEN_R |= 0x0F; // enable digital pins for PE3-PE0
}

// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
	return GPIO_PORTE_DATA_R;
}
