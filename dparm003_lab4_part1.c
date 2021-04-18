/*	Author: dparm003
 *  Partner(s) Name: None
 *	Lab Section: 22
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_STATES {SM_PB0Wait, SM_PB1, SM_PB1Wait, SM_PB0} SM_STATE;
unsigned char Tick_Toggle(unsigned char tmpA) {
	unsigned char tmpB; 
   switch(SM_STATE) { 
      case SM_PB0Wait:
         if (!tmpA) {
            SM_STATE = SM_PB0Wait;
         }
         else {
            SM_STATE = SM_PB1;
         }
         break;
      case SM_PB1:
         if (tmpA) {
            SM_STATE = SM_PB1;
         }
         else {
            SM_STATE = SM_PB1Wait;
         }
         break;
      case SM_PB1Wait:
         if (!tmpA) {
            SM_STATE = SM_PB1Wait;
         }
         else {
            SM_STATE = SM_PB0;
         }
         break;
      case SM_PB0:
         if (!tmpA) {
            SM_STATE = SM_PB0Wait;
         }
         else {
            SM_STATE = SM_PB0;
         }
         break;
      default:
         SM_STATE = SM_PB0Wait;
         break;
   }
   switch(SM_STATE) { 
      case SM_PB0Wait:
        tmpB = 0x01;
         break;
      case SM_PB1:
         tmpB = 0x02;
         break;
      case SM_PB1Wait:
         tmpB = 0x02;
         break;
      case SM_PB0:
         tmpB = 0x01;
         break;
   }
return tmpB;
}

int main(void) {
   
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char tmpA = 0x00;
	unsigned char tmpB;

	SM_STATE = SM_PB0Wait;

	while (1) {
	tmpA = PINA & 0x01;
	tmpB = 0x00;
	tmpB = Tick_Toggle(tmpA);
	PORTB = tmpB;
    }

    return 1;
}
