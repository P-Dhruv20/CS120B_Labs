/*	Author: dparm003
 *  Partner(s) Name: None
 *	Lab Section: 22
 *	Assignment: Lab 5  Exercise 1
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
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;

    while (1) {
	tmpA = ~PINA & 0x0F;
	tmpC = 0x00;
	
	if(tmpA == 0x00) tmpC = tmpC | 0x40;
	else if(tmpA < 0x03) tmpC = tmpC | 0x60;
	else if(tmpA < 0x05) tmpC = tmpC | 0x70;
	else if(tmpA < 0x07) tmpC = tmpC | 0x38;
	else if(tmpA < 0x0A) tmpC = tmpC | 0x3C;
	else if(tmpA < 0x0D) tmpC = tmpC | 0x3E;
	else if(tmpA <= 0x0F) tmpC = tmpC | 0x3F;
	PORTC = tmpC;
    }

    return 1;
}
