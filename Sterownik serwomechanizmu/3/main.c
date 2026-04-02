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

enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo {
enum ServoState eState; 
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};

struct Servo sServo;

void Automat(){

	enum ServoState eState = CALLIB;
	
	switch(eState){
		
		case CALLIB:
		sServo.uiCurrentPosition =0;
		sServo.uiDesiredPosition =0;
		if(eReadDetector() == INACTIVE){
			LedStepLeft();
		}
		else{
			eState = IDLE;
		}
		break;
		
		case IDLE:
		if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
				eState = IN_PROGRESS;
		}
		else{
				eState = IDLE;
		}
		break;
		
		case IN_PROGRESS:
		if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
			LedStepRight();
			eState = IN_PROGRESS;
			sServo.uiCurrentPosition = sServo.uiCurrentPosition +1;
		}
		else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
			LedStepLeft();
			eState = IN_PROGRESS;
			sServo.uiCurrentPosition = sServo.uiCurrentPosition -1;
		}
		else{
			eState = IDLE;
		}
		break;
	}
}

int main (){
	unsigned int iMainLoopCtr;
	DetectorInit();
	LedInit();
	Timer0Interrupts_Init(2000,&Automat);
	
	while(1){
	 	iMainLoopCtr++;
		
		switch(eKeyboardRead()){
		
		case BUTTON_0:
			sServo.eState = CALLIB;
			break;
		case BUTTON_1:
			sServo.uiDesiredPosition = 12;
			break;
		case BUTTON_2:
			sServo.uiDesiredPosition = 24;
			break;
		case BUTTON_3:
			sServo.uiDesiredPosition = 36;
			break;
		default: {}
				
		}
	}
}
