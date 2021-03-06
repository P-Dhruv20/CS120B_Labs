/*	Author: dparm003
 *  Partner(s) Name: None
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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
	DDRB = 0x00; PORTB = 0xFF; 
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00; 
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char tmpD = 0x00;
	unsigned char total = 0x00;

    while (1) {
	tmpA = PINA;
	tmpB = PINB;
	tmpC = PINC;
	total = tmpA + tmpB + tmpC;
	tmpD = (total >> 2);
	if(total > 140) tmpD = tmpD | 0x01;
	else tmpD = tmpD & 0xFE;
	if(((tmpA - tmpC) > 0x50) || ((tmpC - tmpA) > 0x50)) tmpD = tmpD | 0x02;
	else tmpD = tmpD & 0xFD;
	PORTD = tmpD;
	PORTD = tmpD;
    }
    return 0;
}
