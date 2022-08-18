#include "DELAY.h"


static volatile uint32_t	msTicks;
static volatile uint32_t usTicks;


void SysTick_Handler(void) {
	msTicks++;

}
void TIM2_IRQHandler(void){
	TIM2->SR &= ~(TIM_SR_UIF); //clear the timer interrupt flag 
	usTicks++;

}

uint32_t millis(void) {
	return msTicks;
}


void initMilliDelay(void)
{
	// Initialise SysTick timer
	SysTick_Config(SystemCoreClock/ 1000);
}

void initMicroDelay(void)
{
		// Intialise TIM2 timer
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 0; // Set prescaler 
	TIM2->ARR = 71; // Set the auto reload counter (after 71, count starts back from zero) 
	TIM2->CR1 |= TIM_CR1_URS; // Set update interrupt to occur every counter reload
	TIM2->DIER |= TIM_DIER_UIE; // enable update interrupt
	TIM2->EGR |= TIM_EGR_UG;
	NVIC_EnableIRQ(TIM2_IRQn); 
}

void delayMs(uint32_t time_delay){
	uint32_t prevTicks = msTicks;
	while (msTicks-prevTicks <time_delay);
	
}

void delayUs(uint32_t time_delay){
	TIM2->CR1 |= TIM_CR1_CEN; //enable the the timer 
	usTicks = 0;
	while (usTicks <time_delay);
	TIM2->CR1 &= ~(TIM_CR1_CEN); //disable the timer
}
