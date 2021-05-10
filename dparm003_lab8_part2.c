/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 8  Exercise 2
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

#include "../header/timer.h"

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

double notes[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

enum SM1_STATES {SM1_Start, SM1_Wait, SM1_Dec, SM1_DecWait, SM1_Inc, SM1_IncWait} SM1_STATE;
int i = 0;

void ScaleUpDown(unsigned char tmpA1, unsigned char tmpA2) {
   switch(SM1_STATE) { 
      case SM1_Start:
		SM1_STATE = SM1_Wait;
		break;
      case SM1_Wait:
		if (tmpA1) {
            SM1_STATE = SM1_Inc;
         }
        else if (tmpA2) {
            SM1_STATE = SM1_Dec;
         }
		else {
			SM1_STATE = SM1_Wait;		
		}
        break;
      case SM1_Inc:
            SM1_STATE = SM1_IncWait;
        break;
      case SM1_IncWait:
        if (tmpA1) {
            SM1_STATE = SM1_IncWait;
        }
        else {
            SM1_STATE = SM1_Wait;
		}
        break;
      case SM1_Dec:
            SM1_STATE = SM1_DecWait;
        break;
	  case SM1_DecWait:
			if(tmpA2){
				SM1_STATE = SM1_DecWait;
			}
			else {
				SM1_STATE = SM1_Wait;
			}
      default:
         SM1_STATE = SM1_Wait;
         break;
   }
   switch(SM1_STATE) {
      case SM1_Start:
		break;	   
      case SM1_Wait:
        break;
      case SM1_Inc:
        if(i<7) {
		i = i + 1;
		}
        break;
      case SM1_IncWait:
        break;
      case SM1_Dec:
		if(i>0){
		i = i - 1;
		}
        break;
	  case SM1_DecWait:
		break;
   }
}

enum SM2_STATES {SM2_Start, SM2_On, SM2_Off} SM2_STATE;

void SystemOnOff(unsigned char tmpA0) {
   switch(SM2_STATE) { 
      case SM2_Start:
		SM2_STATE = SM2_On;
		break;
      case SM2_On:
		if (tmpA0) {
            SM2_STATE = SM2_Off;
         }
        break;
      case SM2_Off:
		if(tmpA0){
            SM2_STATE = SM2_On;
		}
        break;
      default:
         SM2_STATE = SM2_On;
         break;
   }
   switch(SM2_STATE) {
      case SM2_Start:
		break;
      case SM2_On:
		set_PWM(notes[i]);
        break;
      case SM2_Off:
		set_PWM(0);
        break;
   }
}

int main(void) {
   
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char tmpA0 = 0x00;
	unsigned char tmpA1 = 0x00;
	unsigned char tmpA2 = 0x00;
	
	TimerSet(130);
	TimerOn();
	PWM_on();
	
	SM1_STATE = SM1_Start;
	SM2_STATE = SM2_Start;

	while (1) {
	tmpA0 = ~PINA & 0x01;
	tmpA1 = ~PINA & 0x02;
	tmpA2 = ~PINA & 0x04;
	SystemOnOff(tmpA0);
	ScaleUpDown(tmpA1,tmpA2);
	while(!TimerFlag){}
	TimerFlag = 0;
	}
    return 1;
}
