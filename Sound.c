/*******************************************************************
 * Sound.c
 * Instructor: Devinder Kaur
 * Runs on TM4C123
 * Use the SysTick timer to request interrupts at a particular period.
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: Nicholas Nassar
 * Section: 002
 * Date:    11/20/2020
 *
 * This module calls the 4-bit DAC
 *******************************************************************/

#include "Sound.h"
#include "DAC.h"
#include "..//inc//tm4c123gh6pm.h"

int32_t count; // our current count
uint32_t up = 1; // are we counting up or down?
uint32_t pitch = 0;

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
  DAC_Init();
	
	NVIC_ST_CTRL_R = 0; // disable SysTick during setup
	NVIC_ST_RELOAD_R = 5000; // reload value
	NVIC_ST_CURRENT_R = 0; // any write to current clears it
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000; // priority 2
	NVIC_ST_CTRL_R = 0x07; // enable SysTick with core clock and interrupts
	
	pitch = 0;
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// This routine sets the RELOAD and starts SysTick
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
	if (period == 0) {
		Sound_Off();
	} else {
		GPIO_PORTB_DEN_R |= 0x3F; // enable PB6-0 digitally
	}
}


// **************Sound_Off*********************
// Stop outputing to DAC
// This routine stops the sound output
// Output: none
void Sound_Off(void){
	GPIO_PORTB_DATA_R &= ~0x3F; // clear PB6-0
	GPIO_PORTB_DEN_R &= ~0x3F; // disable PB6-0 digitally
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
	GPIO_PORTB_DATA_R |= 0x40; // start debug monitor

	GPIO_PORTF_DATA_R ^= 0x04; // flip the heartbeat
	
	pitch = (pitch + 1) % GPIO_PORTE_DATA_R;
	
	if (pitch == 0) {
		if (count == 16) {
			DAC_Out(15);
		} else if (count == -1) {
			DAC_Out(0);
		} else {
			DAC_Out(count);
		}

		if (count == 16) {
			up = 0;
		} else if (count == -1) {
			up = 1;
		}
		
		if (up) {
			count++;
		} else {
			count--;
		}
	}
	
	GPIO_PORTB_DATA_R &= ~0x40; // end debug monitor
}
