/* Author: dparm003
 * Lab Section: 22
 * Assignment: Lab 10  Exercise 1
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

enum SM_States { SMStart, Input};

unsigned char x;

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
   switch (nextState ) { 
  case Input:
  		x = GetKeypadKey();
		switch(x){
			case '\0': PORTB = 0x1F; break;
			case '1': PORTB = 0x81; break;
			case '2': PORTB = 0x82; break;
			case '3': PORTB = 0x83; break;
			case '4': PORTB = 0x84; break;
			case '5': PORTB = 0x85; break;
			case '6': PORTB = 0x86; break;
			case '7': PORTB = 0x87; break;
			case '8': PORTB = 0x88; break;
			case '9': PORTB = 0x89; break;
			case 'A': PORTB = 0x8A; break;
			case 'B': PORTB = 0x8B; break;
			case 'C': PORTB = 0x8C; break;
			case 'D': PORTB = 0x8D; break;
			case '*': PORTB = 0x8E; break;
			case '0': PORTB = 0x80; break;
			case '#': PORTB = 0x8F; break;
			default: PORTB = 0x1B; break;
		}
      break;
  default:
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

task tasks[1];

int main() {
  
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	
   int i;
   
   tasks[0].state = 0;
   tasks[0].TickFct = &keypadInput;
   tasks[0].period = 1;
   tasks[0].elapsedTime = tasks[0].period;
   unsigned long timerPeriod = tasks[0].period;
   TimerSet(timerPeriod);
   TimerOn();
   
   while (1) {  
 
  for (i = 0; i < 1; ++i) {
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
