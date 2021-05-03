/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 7  Exercise 3
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code is my own original work.
 *
 *  Demo Link: 
 */

// MAX = 254
// MIN = 62

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

unsigned short MAX = 254;

int main(void) {
   
	//DDRD = 0xFF; PORTD = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;

	//unsigned char tmpD = 0x00;
	unsigned char tmpB = 0x00;
	unsigned short tmpA = 0x00;
  	unsigned short myADC = 0x00;
	
	ADC_init();
	
	while (1) {
	tmpA = PINA & 0xFF;
	myADC = ADC;
	//tmpB = (char)myADC;  
	//tmpD = (char)(myADC >> 8); 
	
	if(myADC >= (MAX/2)){
		tmpB = 0x01;
	}
	else{
		tmpB = 0x00;
	}
	//PORTD = tmpD;
	PORTB = tmpB;
    }

    return 1;
}
