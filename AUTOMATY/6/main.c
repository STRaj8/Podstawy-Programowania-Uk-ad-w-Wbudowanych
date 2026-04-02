#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iDelayInMs){
	int iLoopCounter;
	iDelayInMs = iDelayInMs*12000;
	for(iLoopCounter=0; iLoopCounter<iDelayInMs; iLoopCounter++){
	}
}

int main(){
	enum LedState {LED_LEFT ,LED_RIGHT, STOP};
	enum LedState eLedState = STOP ;
	LedInit();
	KeyboardInit();
	while(1){
		Delay(100);
		switch(eLedState){
			case STOP:
				if(eKeyBoardRead()==BUTTON_0){
					eLedState=LED_LEFT;
					LedStepLeft();
					break;
				}
				else if(eKeyBoardRead()==BUTTON_2){
					eLedState=LED_RIGHT;
					LedStepRight();
					break;
				}
				else{
					break;
				}
			case LED_LEFT:
				if(eKeyBoardRead()==BUTTON_1){
					eLedState=STOP;
					break;
				}
				else{
					LedStepLeft();
					break;
				}
			case LED_RIGHT:
				if(eKeyBoardRead()==BUTTON_1){
					eLedState=STOP;
					break;
				}
				else{
					LedStepRight();
					break;
				}
		}
	}
}
