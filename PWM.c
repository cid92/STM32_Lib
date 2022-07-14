#include "PWM.h"
#include "stdint.h"
#include "stm32f10x.h"




void initPWM(uint8_t Timer, uint8_t channel, uint16_t freq){
	switch (Timer)
	{
		case TIMER1:
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			TIM1->BDTR|= TIM_BDTR_MOE;	
			TIM1->CR1 |= TIM_CR1_ARPE;
			if (channel == CHANNEL1) {
					TIM1->CCER|= TIM_CCER_CC1E;
					TIM1->CCMR1 |= TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1PE;
			}
			else if (channel == CHANNEL2){ //Pin Shared with UART1
					TIM1->CCER|= TIM_CCER_CC2E;
					TIM1->CCMR1 |= TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2M_1|TIM_CCMR1_OC2PE;
			}
			else if (channel == CHANNEL3){
					TIM1->CCER|= TIM_CCER_CC3E;
					TIM1->CCMR2 |= TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3PE;
			}
			else if (channel == CHANNEL4){
					TIM1->CCER|= TIM_CCER_CC4E;
					TIM1->CCMR2 |= TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4PE;
			}
			TIM1->PSC = 35; //Set the prescale
			TIM1->ARR = freq-1;		//Set max counter value
			TIM1->EGR |= TIM_EGR_UG;
			TIM1->CR1 |= TIM_CR1_CEN;
			break;
			// TODO for other timers 
	}
}

void setPwmDuty(uint8_t timer, uint8_t channel, uint16_t dutyCycle){
	switch (timer)
	{
		case TIMER1:
			if (channel == CHANNEL1){
					TIM1->CCR1 = dutyCycle; // Set duty cycle
			}
			else if (channel == CHANNEL2){
					TIM1->CCR2 = dutyCycle; // Set duty cycle
			}
			else if (channel == CHANNEL3){
					TIM1->CCR3 = dutyCycle; // Set duty cycle
			}
			else if (channel == CHANNEL4){
					TIM1->CCR4 = dutyCycle; // Set duty cycle
			}
			break;
			// TODO for other timers 
	}
}
