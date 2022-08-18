#ifndef ADC
#define ADC
#include <stdint.h>
//******************************************************************************
//************ ADC Library        																**************
//************ Author: Cid Gilani																	**************
//************ Revision:1.0 																			**************
//************ This library contains functions to read continous  **************
//************ ADC readings	using DMA															**************
//******************************************************************************
extern volatile uint32_t adcread;
extern volatile uint16_t sample[2];

void ADC1_2_IRQHandler(void);
void initADC(void);
void calibrateADC(void);
#endif
