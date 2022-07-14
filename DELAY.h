#ifndef DELAY
#define DELAY



//Interrupt handler functions 
void SysTick_Handler(void);
void TIM2_IRQHandler(void);

//Initialisation the clock for the delays 
void initMilliDelay(void);
void initMicroDelay(void);

//The functions execute delays
//delayMS for milliseconds delay
//delayUs for microseconds delay

void delayMs(int time_delay);
void delayUs(int time_delay);
#endif
