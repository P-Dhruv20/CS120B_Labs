/*	Author: dparm003
 *  Partner(s) Name: none
 *	Lab Section: 22
 *	Assignment: Lab 2  Exercise 1
 *	Exercise Description: Garage Open
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A

    /* Insert your solution below */
    while (1) {
	// 1) Read input
	tmpA = PINA & 0x03;
	// 2) Perform computation
	// // if PA0 is 1, set PB1PB0 = 01, else = 10
  	if (tmpA == 0x01){
		tmpB = (tmpB & 0xFE) | 0x01; // Sets tmpB to bbbbbbb1
						// (clear rightmost 1 bit, then set to 1 )
	} else {
			tmpB = (tmpB & 0xFE) | 0x00; // sets tmpB to bbbbbbb0
						// (clear rightmost 1 bit, then set to 0)
	}
	// 3) Write ouput
	PORTB = tmpB;
}
return 0;
}

