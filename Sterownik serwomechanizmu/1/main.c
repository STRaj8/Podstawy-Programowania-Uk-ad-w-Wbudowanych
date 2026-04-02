#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#include <LPC21xx.H>

#define DETECTOR_bm (1<<10) 

void DetectorInit(){
 IO1DIR = IO1DIR & (~DETECTOR_bm);
}

enum DetectorState{ACTIVE,INACTIVE};
enum DetectorState eReadDetector() {

if ((IO0PIN & DETECTOR_bm) == 0){
			return ACTIVE;
			}
else{
			return INACTIVE;
			}
}

void Automat(){

enum LedState {LED_RIGHT,LED_LEFT,LED_STOP,CALLIB};
enum LedState eLedState = CALLIB;

		switch(eLedState){
			
			case LED_RIGHT:
				if(eKeyboardRead() == BUTTON_1){
					eLedState = LED_STOP;}
				else {
					LedStepRight();
					eLedState = LED_RIGHT;
				}
				break;
			
				case LED_STOP:
				if(eKeyboardRead() == BUTTON_0){
					eLedState = LED_LEFT;}
				else if(eKeyboardRead() == BUTTON_2){
					eLedState = LED_RIGHT;}
				else {
					eLedState = LED_STOP;
				}
				break;
			
				case LED_LEFT:
				if(eKeyboardRead() == BUTTON_1){
					eLedState = LED_STOP;}
				else {
					LedStepLeft();
					eLedState = LED_LEFT;
				}
				break;
				
				case CALLIB:
				if(eReadDetector() == INACTIVE){
					eLedState = LED_LEFT;}
				else {
						eLedState = LED_STOP;}
				break;
				}
			}

int main (){
	unsigned int iMainLoopCtr;
	DetectorInit();
	KeyboardInit();
	LedInit();
	Timer0Interrupts_Init(2000,&Automat);

	while(1){
	iMainLoopCtr++;
	}
}
