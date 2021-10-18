/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 7  Exercise 4
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code is my own original work.
 *
 *  Demo Link: https://youtu.be/YqQ_XCpy7js
 */

// MAX = 254
// MIN = 62
// Interval = (254-62)/8 = 24
// lights range [1:8] = 62,86,110,134,158,182,206,230,254

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

unsigned short MAX = 254;
unsigned short MIN = 62;
unsigned short Interval = 24; 

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

	if(myADC <= 254 && myADC > 230) {
		tmpB = 0xFF;
	}
	else if(myADC <= 230 && myADC > 206){
		tmpB = 0x7F;
	}
	else if(myADC <= 206 && myADC > 182){
		tmpB = 0x3F;
	}
	else if(myADC <= 182 && myADC > 158){
		tmpB = 0x1F;
	}
	else if(myADC <= 158 && myADC > 134){
		tmpB = 0x0F;
	}
	else if(myADC <= 134 && myADC > 110){
		tmpB = 0x07;
	}
	else if(myADC <= 110 && myADC > 86){
		tmpB = 0x03;
	}
	else if(myADC <= 86 && myADC >= 62){
		tmpB = 0x01;
	}

	PORTB = tmpB;
    }

    return 1;
}
