/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 9  Exercise 1
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code is my own original work.
 *
 *  Demo Link: https://youtu.be/RBnwZ6Qfwd0
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "../header/timer.h"

enum ThreeLEDsSM_States { SM1_Start, SM1_PB0, SM1_PB1, SM1_PB2 } SM1_State;
unsigned char ThreeLEDs = 0;
void tick_ThreeLEDs() {
   switch ( SM1_State ) {
      case SM1_Start:
         SM1_State = SM1_PB0; 
         break;
	  case SM1_PB0:
		 SM1_State = SM1_PB1;
		 break;
	  case SM1_PB1:
		 SM1_State = SM1_PB2;
		 break;
	  case SM1_PB2:
		 SM1_State = SM1_PB0;
		 break;
      default:
         SM1_State = SM1_Start;
         break;
   }
   switch ( SM1_State ) {
      case SM1_Start:
         break;
	  case SM1_PB0:
		 ThreeLEDs = 0x01;
		 break;
	  case SM1_PB1:
		 ThreeLEDs = 0x02;
		 break;
	  case SM1_PB2:
		 ThreeLEDs = 0x04;
		 break;
      default:
         break;
   }
}

enum BlinkingLEDSM_States { SM2_Start, SM2_On, SM2_Off} SM2_State;
unsigned char BlinkingLED = 0;
void tick_BlickingLED() {
	switch(SM2_State){
		case SM2_Start:
			SM2_State = SM2_On;
			break;
		case SM2_On:
			SM2_State = SM2_Off;
			break;
		case SM2_Off:
			SM2_State = SM2_On;
			break;
		default:
			SM2_State = SM2_On;
			break;
	}
		switch(SM2_State){
		case SM2_Start:
			break;
		case SM2_On:
			BlinkingLED = 0x01;
			break;
		case SM2_Off:
			BlinkingLED = 0x00;
			break;
	}
}

enum CombineLEDsSM_States { SM3_Start, SM3_Combine} SM3_State;
unsigned char CombineLEDs = 0;
void tick_CombineLEDs(){
	switch(SM3_State){
		case SM3_Start:
			SM3_State = SM3_Combine;
			break;
		case SM3_Combine:
			break;
		default:
			SM3_State = SM3_Combine;
			break;
	}
	switch(SM3_State){
		case SM3_Start:
			break;
		case SM3_Combine:
			CombineLEDs = (ThreeLEDs & 0x07) | ((BlinkingLED & 0x01) << 3);
			PORTB = CombineLEDs;
			break;
	}
}
int main(void) {
	
	DDRB = 0xFF; PORTB = 0x00;
	
	int ThreeLEDs_Elapsedtime = 1000;
	int BlinkingLED_Elapsedtime = 1000;
	int CombineLEDs_Elapsedtime = 1000;
	int period = 1;

	TimerSet(period);
	TimerOn(); 
	SM1_State = SM1_Start;
	SM2_State = SM2_Start;
	SM3_State = SM3_Start;
	while (1) {
		if(ThreeLEDs_Elapsedtime >= 1000){
			tick_ThreeLEDs();
			ThreeLEDs_Elapsedtime = 0;
		}
		ThreeLEDs_Elapsedtime += 1;
		if(BlinkingLED_Elapsedtime >= 1000){
			tick_BlickingLED();
			BlinkingLED_Elapsedtime = 0;
		}
		BlinkingLED_Elapsedtime += 1;
		if(CombineLEDs_Elapsedtime >= 1000){
			tick_CombineLEDs();
			CombineLEDs_Elapsedtime = 0;
		}
		CombineLEDs_Elapsedtime += 1;
      while (!TimerFlag){} 
      TimerFlag = 0;     
	}
}
