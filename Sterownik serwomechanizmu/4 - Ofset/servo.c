#include <LPC21xx.H>
#include "servo.h"
#include "timer_interrupts.h"
#include "led.h"

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

enum ServoState {CALLIB, IDLE, IN_PROGRESS, OFFSET};

struct Servo {
enum ServoState eState; 
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};

struct Servo sServo;

void ServoCallib() {
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition) {
	sServo.eState=IN_PROGRESS;
	sServo.uiDesiredPosition = uiPosition;
	// ---> rozwiazanie while(sServo.eState == IN_PROGRESS){}
}

void Automat(){
	
	switch(sServo.eState) {
			
		case CALLIB:
				if(eReadDetector() == ACTIVE) {
					sServo.uiCurrentPosition = 0;
					sServo.eState = OFFSET;
				}
				else {
					LedStepRight();
					sServo.eState = CALLIB;
				}
				break;
			case IDLE:
				if(sServo.uiCurrentPosition != sServo.uiDesiredPosition) {
					sServo.eState = IN_PROGRESS;
				}
				else {
					sServo.eState = IDLE;
				}
				break;
			case IN_PROGRESS:
				if(sServo.uiCurrentPosition < sServo.uiDesiredPosition) {
					sServo.uiCurrentPosition = sServo.uiCurrentPosition+1;
					LedStepRight();
				}
				else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition) {
					sServo.uiCurrentPosition = sServo.uiCurrentPosition-1;
					LedStepLeft();
				}
				else if (sServo.uiCurrentPosition == sServo.uiDesiredPosition) {
					sServo.eState = IDLE;
				}
				break;
			case OFFSET:	
				if(sServo.uiCurrentPosition == 12) {
					sServo.uiCurrentPosition = 0;
					sServo.uiDesiredPosition = 0;
					sServo.eState = IDLE;
				}
				else {
					LedStepRight();
					sServo.uiCurrentPosition = sServo.uiCurrentPosition+1;
				}
				break;
	}
}

void ServoInit(unsigned int uiServoFrequency) {
	Timer0Interrupts_Init(1000000/uiServoFrequency,&Automat);
	LedInit();
	DetectorInit();
}
