#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer.h"


void Automat() {
	enum LedState{WAITING, LEFT, RIGHT};
	static enum LedState eLedState = WAITING;

	switch(eLedState) {
		case WAITING:
			if(eKeyBoardRead() == BUTTON_0) {
				eLedState = LEFT;
			} else if(eKeyBoardRead() == BUTTON_2) {
				eLedState = RIGHT;
			} else {
				eLedState = WAITING;
			}
			break;
		case LEFT:
			if(eKeyBoardRead() == BUTTON_1) {
					eLedState = WAITING;
			} else {
				eLedState = LEFT;
			}
			LedStepLeft();
			break;
		case RIGHT:
			if(eKeyBoardRead() == BUTTON_1) {
					eLedState = WAITING;
			} else {
				eLedState = RIGHT;
			}
			LedStepRight();
			break;
	}
}// gittest

int main (){
	unsigned int iMainLoopCtr;
	Timer0Interrupts_Init(250000, &Automat);
	KeyboardInit();
	LedInit();

	while(1){
	 	iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
	}
}