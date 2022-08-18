#ifndef DELAY
#define DELAY
#include "stm32f10x.h"




/*** Interrupt handler functions ***/ 
void SysTick_Handler(void);	
void TIM2_IRQHandler(void); 

/*** Initialisation the clock for the delays ***/ 
void initMilliDelay(void);
void initMicroDelay(void);

/*** Return timestamp ***/
uint32_t millis(void) ;
uint32_t micros(void) ;


/*** The functions execute delays ***/
 
// Delay for milliseconds delay
void delayMs(uint32_t time_delay);
// Delay for microseconds delay
void delayUs(uint32_t time_delay);
#endif
