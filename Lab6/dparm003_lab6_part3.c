/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 6  Exercise 3
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code is my own original work.
 *
 *  Demo Link: https://youtu.be/OaAnIY2eDLU
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "../header/timer.h"

enum SM_STATES {SM_Start, SM_Wait, SM_Inc, SM_Dec, SM_Res, SM_Wait1, SM_Wait2} SM_STATE;
int i = 0;
unsigned char Tick_Toggle(unsigned char tmpA0, unsigned char tmpA1, unsigned char tmpB) {
   switch(SM_STATE) { 
      case SM_Start:
	SM_STATE = SM_Wait;
	tmpB = 0x07;
	i = 0;
	break;
      case SM_Wait:
 	 if (!tmpA1 && !tmpA0) {
            SM_STATE = SM_Wait;
         }
         else if (!tmpA0 && tmpA1) {
            SM_STATE = SM_Dec;
         }
	 else if (tmpA0 && !tmpA1){
		SM_STATE = SM_Inc;
	 }
	 else {
		SM_STATE = SM_Res;		
	 }
         break;
      case SM_Dec:
         if (tmpA0 && tmpA1) {
            SM_STATE = SM_Res;
         }
         else if(!tmpA0 && tmpA1) {
            SM_STATE = SM_Wait1;
	 }
	 else if(!tmpA0 && !tmpA1){	
	    SM_STATE = SM_Wait;
	 }
         break;
      case SM_Wait1:
	 if(!tmpA0 && tmpA1){
	 	if(i<10){
		++i;
		SM_STATE = SM_Wait1;
		}
		else{
		SM_STATE = SM_Dec;
		i = 0;
		}
	 }
	 else{
	 	SM_STATE  = SM_Wait;
	 }
	 break;
      case SM_Inc:
         if (tmpA0 && tmpA1) {
            SM_STATE = SM_Res;
         }
         else if(tmpA0 && !tmpA1){
            SM_STATE = SM_Wait2;
         }
	 else if(!tmpA0 && !tmpA1) {
	    SM_STATE = SM_Wait;
	 } 
         break;
      case SM_Wait2:
	 if(tmpA0 && !tmpA1){
	 	if(i<10){
		++i;
		SM_STATE = SM_Wait2;
		}
		else {
		SM_STATE = SM_Inc;
		i = 0;
		}
	 }
	 else{
	 	SM_STATE = SM_Wait;
	 }
	 break;
      case SM_Res:
            SM_STATE = SM_Wait;
         break;
      default:
         SM_STATE = SM_Wait;
         break;
   }
   switch(SM_STATE) {
      case SM_Start:
	 break;	   
      case SM_Wait:
         break;
      case SM_Wait1:
	 break;
      case SM_Wait2:
	 break;
      case SM_Dec:
         if(tmpB > 0)tmpB = tmpB - 1;
         break;
      case SM_Inc:
         if(tmpB < 9)tmpB = tmpB + 1;
         break;
      case SM_Res:
         tmpB = 0x00;
         break;
   }
return tmpB;
}

int main(void) {
   
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char tmpA0 = 0x00;
	unsigned char tmpA1 = 0x00;
	unsigned char tmpB = 0x00;

	TimerSet(100);
	TimerOn();
	
	SM_STATE = SM_Start;

	while (1) {
	tmpA0 = ~PINA & 0x01;
	tmpA1 = ~PINA & 0x02;
	tmpB = Tick_Toggle(tmpA0, tmpA1, tmpB);
	PORTB = tmpB;
	while(!TimerFlag){}
	TimerFlag = 0;
    }

    return 1;
}
