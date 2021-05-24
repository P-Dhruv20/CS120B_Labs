/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 10  Exercise 2
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
#include "../header/keypad.h"

unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a % b;
		if( c == 0 ) { return b; }
		a = b;
		b = c;
	}
	return 0;
}

enum SM1_States { SMStart, Input};

unsigned char x;
unsigned char key;

int keypadInput(int state) {
   int nextState;
   switch ( state ) { 
  case SMStart:
      nextState = Input;
      break;
  case Input:
      break;
  default:
      nextState = SMStart;
      break;
   }
   switch (nextState) { 
  case Input:
  		x = GetKeypadKey();
		switch(x){
			case '\0': key = 0x1F; break;
			case '1': key = 0x01; break;
			case '2': key = 0x02; break;
			case '3': key = 0x03; break;
			case '4': key = 0x04; break;
			case '5': key = 0x05; break;
			case '6': key = 0x06; break;
			case '7': key = 0x07; break;
			case '8': key = 0x08; break;
			case '9': key = 0x09; break;
			case 'A': key = 0x0A; break;
			case 'B': key = 0x0B; break;
			case 'C': key = 0x0C; break;
			case 'D': key = 0x0D; break;
			case '*': key = 0x0E; break;
			case '0': key = 0x00; break;
			case '#': key = 0x0F; break;
			default: key = 0x1B; break;
		}
		if(key) { PORTB = 0x02;
		}
      break;
  default:
      break;
   }
   return nextState;
}

unsigned char lockSignal;
unsigned char unlockSequence[5] = {0x01,0x02,0x03,0x04,0x05};
unsigned int count = 0;

enum SM2_STATES {SM_Start, Wait, sequence, sq1, sq2, sq3, sq4, sq0, unlock, lock};
int LockMechanism(int state) {
   int nextState;
	switch(state) { 
      case SM_Start:
		nextState = Wait;
		break;
      case Wait:
         if (lockSignal) {
            nextState = lock;
         }
         else if (key == 0x0F) {
            nextState = sequence;
         }
		 else {
			nextState = Wait;
		 }
         break;
      case sequence:
         if (key == 0x1F){
			nextState = sequence; 
		 }
		 else if(key == unlockSequence[0] && count == 0){
			nextState = sq0;
			++count;
		 }
		 else if(key == unlockSequence[1] && count == 1){
			nextState = sq1;
			++count;
		 }
		 else if(key == unlockSequence[2] && count == 2){
			nextState = sq2;
			++count;
		 }
		 else if(key == unlockSequence[3] && count == 3){
			nextState = sq3;
			++count;
		 }
		 else if(key == unlockSequence[4] && count == 4){
			nextState = sq4;
			++count;
		 }
		 else if(count == 5){
			 nextState = unlock;
			 count = 0;
		 }
		 else {
			 nextState = Wait;
		 }
         break;
	  case sq0:
		if(key == 0x1F){
			nextState = sequence;
		}
		break;
	  case sq1:
	  	if(key == 0x1F){
			nextState = sequence;
		}
		break;
	  case sq2:
		if(key == 0x1F){
			nextState = sequence;
		}
		break;	  
	  case sq3:	
		if(key == 0x1F){
			nextState = sequence;
		}
		break;	  
	  case sq4:
		if(key == 0x1F){
			nextState = sequence;
		}
		break;
      case lock:
		nextState = Wait;
         break;
      case unlock:
		nextState = Wait;
         break;
      default:
         nextState = SM_Start;
         break;
   }
   switch(nextState) {
	  case SM_Start:
		 PORTB = 0x01;
		  break;
      case Wait:
         break;
      case sequence:
         break;
	  case sq0:
		break;
	  case sq1:
		break;
	  case sq2:
		break;	  
	  case sq3:	
		break;	  
	  case sq4:
		break;
      case unlock:
		 PORTB = 0x01;
         break;
	  case lock:
		 PORTB = 0x00;
		 break;
   }
return nextState;
}

typedef struct task {
  int state; // Current state of the task
  int (*TickFct)(int); // Function to call for task's tick
  unsigned long period; // Rate at which the task should tick
  unsigned long elapsedTime; // Time since task's previous tick
} task;

task tasks[2];

int main() {
  
	DDRB = 0x7F; PORTB = 0x80;
	DDRC = 0xF0; PORTC = 0x0F;
	
	lockSignal = ~PINB && 0x80;
   int i;
   
   tasks[0].state = 0;
   tasks[0].TickFct = &keypadInput;
   tasks[0].period = 1;
   tasks[0].elapsedTime = tasks[0].period;
   
   tasks[1].state = 0;
   tasks[1].TickFct = &LockMechanism;
   tasks[1].period = 1;
   tasks[1].elapsedTime = tasks[1].period;
   
   unsigned long timerPeriod = findGCD(tasks[0].period, tasks[1].period);
   
   TimerSet(timerPeriod);
   TimerOn();
   
   while (1) {   
  for (i = 0; i < 2; ++i) {
      if (tasks[i].elapsedTime >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = 0;
      }
      tasks[i].elapsedTime += timerPeriod;
  }

  while (!TimerFlag){}
  TimerFlag = 0;
   }
return 1;
}
