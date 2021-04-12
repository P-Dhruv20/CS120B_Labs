/*	Author: dparm003
 * 	Partner(s) Name: None 
 *	Lab Section: 22
 *	Assignment: Lab 3  Exercise 5
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
   
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xF1; PORTB = 0x01;

	unsigned char tmpD = 0x00;
	unsigned char tmpBIn = 0x00;
	unsigned char tmpBOut = 0x00;
  	unsigned short total = 0x00;
	while (1) {
	tmpD = PIND & 0xFF;
	tmpBIn  = PINB & 0x01;
	tmpBOut = 0x00;
	
	total = tmpD;
	total =  (total << 1);
	total = total | tmpBIn;

	if(total >= 0x46)tmpBOut = 0x02;
	else if(total > 0x05 && tmpD < 0x46) tmpBOut = 0x04;
	else if (total <= 0x05) tmpBOut = 0x00;
	
	PORTB = tmpBOut;
    }

    return 1;
}
