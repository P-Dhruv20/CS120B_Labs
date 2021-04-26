/*	Author: dparm003
 *	 *  Partner(s) Name: None
 *	  *	Lab Section: 22
 *	   *	Assignment: Lab 4  Exercise 2
 *	    *	Exercise Description: [optional - include for your own benefit]
 *	     *
 *	      *	I acknowledge all content contained herein, excluding template or example
 *	       *	code, is my own original work.
 *	        */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_STATES {SM_Start, SM_Wait, SM_Inc, SM_IncWait, SM_Dec, SM_DecWait, SM_Res} SM_STATE;
unsigned char Tick_Toggle(unsigned char tmpA0, unsigned char tmpA1, unsigned char tmpC) {
   switch(SM_STATE) { 
      case SM_Start:
	 SM_STATE = SM_Wait;
	 tmpC = 0x07;
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
	 else	{
	    SM_STATE = SM_Res;
	 }
         break;
      case SM_Dec:
         if (tmpA0 && tmpA1) {
            SM_STATE = SM_Res;
         }
         else {
            SM_STATE = SM_DecWait;
         }
         break;
      case SM_Inc:
         if (tmpA0 && tmpA1) {
            SM_STATE = SM_Res;
         }
         else {
            SM_STATE = SM_IncWait;
         }
         break;
	  case SM_DecWait:
		 if (!tmpA0 && tmpA1){
			SM_STATE = SM_DecWait;
		 }
		 else if (tmpA0 && tmpA1){
			SM_STATE = SM_Res;
		 }
		 else if (!tmpA0 && !tmpA1){
			SM_STATE = SM_Wait;
		 }
		 break;
	  case SM_IncWait:
		 if (tmpA0 && !tmpA1){
			SM_STATE = SM_IncWait;
		 }
		 else if (tmpA0 && tmpA1){
			SM_STATE = SM_Res;
		 }
		 else if (!tmpA0 && !tmpA1){
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
	  case SM_DecWait:
		 break;
	  case SM_IncWait:
		 break;	   
      case SM_Wait:
         break;
      case SM_Dec:
         if(tmpC > 0)tmpC = tmpC - 1;
         break;
      case SM_Inc:
         if(tmpC < 9)tmpC = tmpC + 1;
         break;
      case SM_Res:
         tmpC = 0x00;
         break;
   }
return tmpC;
}

int main(void) {
   
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char tmpA0 = 0x00;
	unsigned char tmpA1 = 0x00;
	unsigned char tmpC = 0x00;

	SM_STATE = SM_Start;

	while (1) {
	tmpA0 = ~PINA & 0x01;
	tmpA1 = ~PINA & 0x02;
	tmpC = Tick_Toggle(tmpA0, tmpA1, tmpC);
	PORTC = tmpC;
    }

    return 1;
}

