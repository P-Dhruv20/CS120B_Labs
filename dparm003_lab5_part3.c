/*	Author: dparm003
 *  Partner(s) Name: None
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_STATES {SM_Start, SM_Off, SM_ASC_B0, SM_ASC_B1, SM_ASC_B2, SM_ASC_B3, SM_ASC_B4, SM_ASC_B5, SM_DES_B5, SM_DES_B4, SM_DES_B3, SM_DES_B2, SM_DES_B1, SM_DES_B0, SM_Blink1, SM_Blink2, SM_AllOn} SM_STATE;


void Wait(){
	unsigned int count = 0;
	while(count< 15000) {
		++count;
	}
}

unsigned char Light_Toggle(unsigned char tmpA) {
	unsigned char tmpB;
   switch(SM_STATE) {
      case SM_Start:
	 SM_STATE = SM_Off;
	 break;
      case SM_Off:
         if (tmpA) {
            SM_STATE = SM_ASC_B0;
         }
		 else	{
	    SM_STATE = SM_Off;
		 }
		 Wait();
        break;
      case SM_ASC_B0:
            SM_STATE = SM_ASC_B1;
			Wait();
        break;
	  case SM_ASC_B1:
            SM_STATE = SM_ASC_B2;
			Wait();
        break;
	  case SM_ASC_B2:
            SM_STATE = SM_ASC_B3;
			Wait();
        break;
	  case SM_ASC_B3:
            SM_STATE = SM_ASC_B4;
			Wait();
        break;
	  case SM_ASC_B4:
            SM_STATE = SM_ASC_B5;
			Wait();
        break;
	  case SM_ASC_B5:
            if(tmpA){
				SM_STATE = SM_DES_B5;
			}
			else{
				SM_STATE = SM_ASC_B0;
			}
			Wait();
        break;
	  case SM_DES_B5:
            SM_STATE = SM_DES_B4;
			Wait();
        break;
	  case SM_DES_B4:
            SM_STATE = SM_DES_B3;
			Wait();
        break;
	  case SM_DES_B3:
            SM_STATE = SM_DES_B2;
			Wait();
        break;
	  case SM_DES_B2:
            SM_STATE = SM_DES_B1;
			Wait();
        break;
	  case SM_DES_B1:
            SM_STATE = SM_DES_B0;
			Wait();
        break;
	  case SM_DES_B0:
            if(tmpA){
				SM_STATE = SM_Blink1;
			}
			else{
				SM_STATE = SM_DES_B5;
			}
			Wait();
        break;
	  case SM_Blink1:
            SM_STATE = SM_Blink2;
        break;
      case SM_Blink2:
         if (tmpA) {
            SM_STATE = SM_AllOn;
         }
         else {
            SM_STATE = SM_Blink1;
         }
		 Wait();
         break;
	  case SM_AllOn:
			if(tmpA){
				SM_STATE = SM_Off;
			}
			else{
				SM_STATE = SM_AllOn;
			}
			Wait();
		break;
      default:
         SM_STATE = SM_Off;
         break;
   }
   switch(SM_STATE) {
      case SM_Start:
		tmpB = 0x00;
	 Wait();
	 break;
      case SM_Off:
         tmpB = 0x00;
        Wait();
	 break;
      case SM_ASC_B0:
            tmpB = 0x01;
	    Wait();
        break;
	  case SM_ASC_B1:
            tmpB = 0x03;
	    Wait();
        break;
	  case SM_ASC_B2:
            tmpB = 0x07;
	    Wait();
        break;
	  case SM_ASC_B3:
            tmpB = 0x0F;
	    Wait();
        break;
	  case SM_ASC_B4:
            tmpB = 0x1F;
	    Wait();
        break;
	  case SM_ASC_B5:
            tmpB = 0x3F;
	    Wait();
	 break;
	  case SM_DES_B5:
            tmpB = 0x20;
	    Wait();
        break;
	  case SM_DES_B4:
            tmpB = 0x30;
	    Wait();
        break;
	  case SM_DES_B3:
            tmpB = 0x38;
	    Wait();
        break;
	  case SM_DES_B2:
            tmpB = 0x3C;
	    Wait();
        break;
	  case SM_DES_B1:
            tmpB = 0x3E;
	    Wait();
        break;
	  case SM_DES_B0:
            tmpB = 0x3F;
	    Wait();
        break;
	  case SM_Blink1:
            tmpB = 0x3F;
	    Wait();
        break;
      case SM_Blink2:
            tmpB = 0x00;
	    Wait();
         break;
	  case SM_AllOn:
            tmpB = 0x3F;
	    Wait();
		break;
   }
return tmpB;
}

int main(void) {

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;

	SM_STATE = SM_Start;

	while (1) {
	tmpA = ~PINA & 0x01;
	Wait();
	tmpB = Light_Toggle(tmpA);
	PORTB = tmpB;
	Wait();
    }

    return 1;
}