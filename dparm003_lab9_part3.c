/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 9  Exercise 3
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

enum SpeakerSound_States { SM4_Start, SM4_Wait, SM4_Play } SM4_State;
unsigned char SpeakerSound = 0;
void tick_SpeakerSound(unsigned char tmpA){
	switch(SM4_State){
		case SM4_Start:
			SM4_State = SM4_Wait;
			break;
		case SM4_Wait:
			if(tmpA){
				SM4_State = SM4_Play;
			}
			else {
				SM4_State = SM4_Wait;
			}
			break;
		case SM4_Play:
			SM4_State = SM4_Wait;
			break;
		default:
			SM4_State = SM4_Wait;
			break;
	}
	switch(SM4_State){
		case SM4_Start:
			break;
		case SM4_Wait:
			SpeakerSound = 0x00;
			break;
		case SM4_Play:
			SpeakerSound = 0x01;
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
			CombineLEDs = (ThreeLEDs & 0x07) | ((BlinkingLED & 0x01) << 3) | ((SpeakerSound & 0x01) << 4);
			PORTB = CombineLEDs;
			break;
	}
}
int main(void) {
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	int ThreeLEDs_Elapsedtime = 300;
	int BlinkingLED_Elapsedtime = 1000;
	int SpeakerSound_Elapsedtime = 2;
	int CombineLEDs_Elapsedtime = 1;
	int period = 1;
	
	unsigned char tmpA = 0x00;

	TimerSet(period);
	TimerOn(); 
	SM1_State = SM1_Start;
	SM2_State = SM2_Start;
	SM3_State = SM3_Start;
	while (1) {
		tmpA = ~PINA & 0x04;
		
		if(ThreeLEDs_Elapsedtime >= 300){
			tick_ThreeLEDs();
			ThreeLEDs_Elapsedtime = 0;
		}
		ThreeLEDs_Elapsedtime += 1;
		if(BlinkingLED_Elapsedtime >= 1000){
			tick_BlickingLED();
			BlinkingLED_Elapsedtime = 0;
		}
		BlinkingLED_Elapsedtime += 1;
		if(SpeakerSound_Elapsedtime >= 2){
			tick_SpeakerSound(tmpA);
			SpeakerSound_Elapsedtime = 0;
		}
		SpeakerSound_Elapsedtime += 1;
		if(CombineLEDs_Elapsedtime >= 1){
			tick_CombineLEDs();
			CombineLEDs_Elapsedtime = 0;
		}
		CombineLEDs_Elapsedtime += 1;
      while (!TimerFlag){} 
      TimerFlag = 0;     
	}
}
