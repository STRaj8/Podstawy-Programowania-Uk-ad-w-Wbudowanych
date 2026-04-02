#include <LPC21xx.H>
#include "timer.h"

#define mCounter_Enable (1<<0)
#define mCounter_Reset (1<<1)

void InitTimer0(void){
	T0TCR = mCounter_Enable; 
}
void WaitOnTimer0(unsigned int uiTime){
	T0TCR = T0TCR|mCounter_Reset;
	T0TCR = T0TCR&(~mCounter_Reset);
	while(T0TC<((uiTime)*15)){
	}
}
