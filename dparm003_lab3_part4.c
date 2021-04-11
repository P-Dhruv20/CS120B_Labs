/*	Author: dparm003
 * 	Partner(s) Name: None 
 *	Lab Section: 22
 *	Assignment: Lab 3  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
   
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	unsigned char tmpALo = 0x00;
	unsigned char tmpAHi = 0x00;
	unsigned char tmpB = 0x00;
   
	while (1) {
	tmpALo = PINA & 0x0F;
	tmpAHi = PINA & 0xF0;
	tmpB = 0x00;
	tmpALo = (tmpALo << 4);
	tmpAHi = (tmpAHi >> 4);
	tmpB = tmpALo | tmpAHi;

	PORTB = tmpB;
    }

    return 1;
}
