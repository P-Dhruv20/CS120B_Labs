/*	Author: dparm003
 *  Partner(s) Name: None 
 *	Lab Section: 22
 *	Assignment: Lab 3  Exercise 3
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
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	unsigned char tmpA = 0x00;
	unsigned char tmpA1 = 0x00;
	unsigned char tmpC = 0x00;
    while (1) {
	tmpA = PINA & 0x0F;
	tmpA1 = PINA & 0x70;
	tmpC = 0x00;
/*	if(tmpA == 0) tmpC = tmpC | 0x40;
	else if(tmpA == 1 || tmpA == 2) tmpC = tmpC | 0x60;
	else if(tmpA == 3 || tmpA == 4) tmpC = tmpC | 0x70;
	else if(tmpA == 5 || tmpA == 6) tmpC = tmpC | 0x38;
	else if(tmpA > 6 && tmpA < 10) tmpC = tmpC | 0x3C;
	else if(tmpA > 9 && tmpA < 13) tmpC = tmpC | 0x3E;
	else if(tmpA > 12 && tmpA < 16) tmpC = tmpC | 0x3F;
*/	
	
	tmpC = 0x00;
	if(tmpA == 0x00) tmpC = tmpC | 0x40;
	else if(tmpA < 0x03) tmpC = tmpC | 0x60;
	else if(tmpA < 0x05) tmpC = tmpC | 0x70;
	else if(tmpA < 0x07) tmpC = tmpC | 0x38;
	else if(tmpA < 0x0A) tmpC = tmpC | 0x3C;
	else if(tmpA < 0x0D) tmpC = tmpC | 0x3E;
	else if(tmpA <= 0x0F) tmpC = tmpC | 0x3F;
	if(tmpA1 == 0x30) tmpC = tmpC | 0x80;
	else tmpC = tmpC | 0x00;
	PORTC = tmpC;
    }

    return 1;
}
