/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 8  Exercise 1
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code is my own original work.
 *
 *  Demo Link: 
 */
 
 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


 void set_PWM(double frequency){
	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency){ TCCR3B &= 0x08; }
		else { TCCR3B |= 0x03; }
		if(frequency < 0.954) { OCR3A = 0xFFFF; }
		else if (frequency > 31250) { OCR3A = 0x0000; }
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

double C4 = 261.63;
double D4 = 293.66;
double E4 = 329.63;
double F4 = 349.23;
double G4 = 392.00;
double A4 = 440.00;
double B4 = 493.88;
double C5 = 523.25;

enum SM_STATES {SM_Start, SM_Wait, SM_C4, SM_D4, SM_E4} SM_STATE;

void Tick_Toggle(unsigned char tmpA) {
   switch(SM_STATE) { 
      case SM_Start:
		SM_STATE = SM_Wait;
		break;
      case SM_Wait:
		if (tmpA == 0x01) {
            SM_STATE = SM_C4;
         }
        else if (tmpA == 0x02) {
            SM_STATE = SM_D4;
         }
		else if (tmpA == 0x04){
			SM_STATE = SM_E4;
		}	
		else {
			SM_STATE = SM_Wait;		
		}
        break;
      case SM_C4:
        if (tmpA == 0x01) {
            SM_STATE = SM_C4;
        }
        else {
            SM_STATE = SM_Wait;
		}
        break;
      case SM_D4:
        if (tmpA == 0x02) {
            SM_STATE = SM_D4;
        }
        else {
            SM_STATE = SM_Wait;
		}
        break;
      case SM_E4:
        if (tmpA == 0x04) {
            SM_STATE = SM_E4;
        }
        else {
            SM_STATE = SM_Wait;
		}
        break;
      default:
         SM_STATE = SM_Wait;
         break;
   }
   switch(SM_STATE) {
      case SM_Start:
		break;	   
      case SM_Wait:
		set_PWM(0);
        break;
      case SM_C4:
		set_PWM(C4);
        break;
      case SM_D4:
		set_PWM(D4);
		break;
	  case SM_E4:
		set_PWM(E4);
        break;
   }
}

int main(void) {
   
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char tmpA = 0x00;
	
	SM_STATE = SM_Start;
	PWM_on();

	while (1) {
	tmpA = ~PINA & 0x07;
	Tick_Toggle(tmpA);
	}
    return 1;
} 
