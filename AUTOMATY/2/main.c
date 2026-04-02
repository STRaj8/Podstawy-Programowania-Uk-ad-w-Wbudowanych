#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"



void Delay (int iDelayInMs){
	int iLoopCounter;
	iDelayInMs=iDelayInMs*12000;
	for(iLoopCounter=0; iLoopCounter<iDelayInMs; iLoopCounter++)
	{	
	}
}

int main(){
	enum LedState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
	enum LedState eLedState = STATE0;
	KeyboardInit();
 	LedInit();
	while(1){
		Delay(250);
		switch(eLedState){
			case STATE0:
				LedStepLeft();
				eLedState = STATE1;
				break;
			case STATE1:
				LedStepLeft();
				eLedState = STATE2;
				break;
			case STATE2:
				LedStepLeft();
				eLedState = STATE3;
				break;
			case STATE3:
				LedStepRight();
				eLedState = STATE4;
				break;
			case STATE4:
				LedStepRight();
				eLedState = STATE5;
				break;
			case STATE5:
				LedStepRight();
				eLedState = STATE0;
				break;
		}		
	}
}

