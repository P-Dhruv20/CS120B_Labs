/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 8  Exercise 3
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code is my own original work.
 *
 *  Demo Link: https://youtu.be/Gtno9L3G7QU
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

int size = 34;
double notes[] = {261.63, 261.63, 293.66, 293.66, 329.63, 329.63, 349.23, 349.23, 392.00, 392.00, 440.00, 440.00, 493.88, 493.88, 523.25, 523.25, 0.0,
				  523.25, 523.25, 493.88, 493.88, 440.00, 440.00, 392.00, 392.00, 349.23, 349.23, 329.63, 329.63, 293.66, 293.66, 261.63, 261.63, 0.0};

enum SM1_STATES {SM1_Start, SM1_Wait, SM1_Inc, SM1_IncWait} SM1_STATE;
int i = 0;

void PlayMelody(unsigned char tmpA) {
   switch(SM1_STATE) { 
      case SM1_Start:
		SM1_STATE = SM1_Wait;
		break;
      case SM1_Wait:
		if (tmpA) {
            SM1_STATE = SM1_Inc;
         }
		else {
			SM1_STATE = SM1_Wait;		
		}
        break;
      case SM1_Inc:
			if(i == size){
            SM1_STATE = SM1_IncWait;
			}
        break;
      case SM1_IncWait:
        if (tmpA) {
            SM1_STATE = SM1_IncWait;
        }
        else {
            SM1_STATE = SM1_Wait;
		}
        break;
      default:
         SM1_STATE = SM1_Wait;
         break;
   }
   switch(SM1_STATE) {
      case SM1_Start:
		break;	   
      case SM1_Wait:
		i = 0;
        break;
      case SM1_Inc:
		set_PWM(notes[i]);
		if(i < size){
			i = i + 1;
		}
        break;
	  case SM1_IncWait:
		break;
   }
}

int main(void) {
   
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char tmpA = 0x00;

	TimerSet(300);
	TimerOn();
	PWM_on();
	
	SM1_STATE = SM1_Start;

	while (1) {
	tmpA = ~PINA & 0x01;
	PlayMelody(tmpA);
	while(!TimerFlag){}
	TimerFlag = 0;
	}
    return 1;
} 
