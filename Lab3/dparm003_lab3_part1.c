/*	Author: dparm003
 *  Partner(s) Name: None 
 *	Lab Section:
 *	Assignment: Lab 3  Exercise 1
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
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF; 
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char count = 0x00;
	unsigned char i;
	unsigned char currBit;
    while (1) {
	tmpA = PINA;
	tmpB = PINB;
	count = 0;
  	for (i = 0; i < 8; ++i) {
     	currBit = ((tmpA >> i) & 0x01) + ((tmpB >> i) & 0x01);
     	count = count + currBit;
  	}
  	tmpC = count;
	PORTC = tmpC;
    }

    return 1;
}
