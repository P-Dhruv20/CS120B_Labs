/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 6  Exercise 2
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

enum SM_States { SM_Start, SM_PB0, SM_02PB1, SM_20PB1, SM_PB2 } SM_State;

unsigned char ToggleLights(unsigned char A0) {
unsigned char tmpB;
   switch ( SM_State ) {
      case SM_Start:
         SM_State = SM_PB0; 
         break;
	  case SM_PB0:
	 	if(A0){
			SM_State = SM_PB0;
		}
		else{
		 	SM_State = SM_02PB1;
		}
		 break;
	  case SM_02PB1:
		 if(A0){
			 SM_State = SM_02PB1;
		 }
		 else{
		 	SM_State = SM_PB2;
		 }
		 break;
	  case SM_20PB1:
		 if(A0){
		 	SM_State = SM_20PB1;
		 }
		 else{
		 	SM_State = SM_PB0;
		 }
		 break;
	  case SM_PB2:
		 if(A0){
		 	SM_State = SM_PB2;
		 }
		 else{
			SM_State = SM_20PB0;
		 }
		 break;
      default:
         SM_State = SM_Start;
         break;
   }

   switch ( SM_State ) {
      case SM_Start:
         break;
	  case SM_PB0:
		 tmpB = 0x01;
		 break;
	  case SM_02PB1:
		 tmpB = 0x02;
		 break;
	  case SM_20PB1:
		 tmpB = 0x02;
		 break;
	  case SM_PB2:
		 tmpB = 0x04;
		 break;
      default:
         break;
   }
	return tmpB;
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;	
	DDRB = 0xFF; PORTB = 0x00;
	unsigned char A0 = 0x00;
	unsigned char tmpB = 0x00;

   TimerSet(300);
   TimerOn(); 
   SM_State = SM_Start;
   while (1) {
      A0 = ~PINA & 0x01;
      tmpB = ToggleLights(A0);
      PORTB = tmpB;
      while (!TimerFlag){} 
      TimerFlag = 0;     
   }
   return 1;
}
