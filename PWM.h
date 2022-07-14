#ifndef PWM
#define PWM
#include <stdint.h>

//******************************************************************************
//************ PWM Library        																**************
//************ Author: Cid Gilani																	**************
//************ Revision:1.0 																			**************
//************ This library contains functions to generate PWM    **************
//************ at desired frequency and duty cycle							  **************
//******************************************************************************


enum Timer {
TIMER1,TIMER2,TIMER3,TIMER4,TIMER5,TIMER6,TIMER7,TIMER8
};

enum Channel {
CHANNEL1,CHANNEL2,CHANNEL3,CHANNEL4
};

void initPWM(uint8_t timer, uint8_t channel, uint16_t freq);
void setPwmDuty(uint8_t timer, uint8_t channel, uint16_t dutyCycle);

#endif
