#include "DELAY.h"
#include "stm32f10x.h"

static volatile int	msTicks;
static volatile int usTicks;

void SysTick_Handler(void) {
	msTicks++;
}
void TIM2_IRQHandler(void){
	TIM2->SR &= ~(TIM_SR_UIF); //clear the timer interrupt flag 
	usTicks++;
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
void delayMs(int time_delay){
	msTicks = 0;
	while (msTicks <time_delay);
}
void delayUs(int time_delay){
	TIM2->CR1 |= TIM_CR1_CEN; //enable the the timer 
	usTicks = 0;
	while (usTicks <time_delay);
	
	TIM2->CR1 &= ~(TIM_CR1_CEN); //disable the timer
}