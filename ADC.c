#include "ADC.h"
#include "stm32f10x.h"


volatile uint32_t adcread;
volatile uint16_t sample[2];

void ADC1_2_IRQHandler(void){
	if (ADC1->SR & ADC_SR_EOC)
	{
		adcread = ADC1->DR;
	}
}	
	
void initADC(void){	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN|RCC_APB2ENR_AFIOEN;
		//Initialise the clock for DMA1
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	//Set ADC prescaler clock to be less than 14Mhz
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	//Initialise ADC pin
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN| RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
	//configure pin as analog input
	//Pin A5
	GPIOA->CRL &= ~(GPIO_CRL_CNF5_1);
	GPIOA->CRL &= ~(GPIO_CRL_CNF5_0);
	//Pin A4
	GPIOA->CRL &= ~(GPIO_CRL_CNF4_1);
	GPIOA->CRL &= ~(GPIO_CRL_CNF4_0);
	
	/* //Interrupt not require with scan mode
	//Enable ADC interrupt 
	ADC1->CR1 |= ADC_CR1_EOCIE;
	//enable the interrupt in the NVIC
	NVIC_EnableIRQ(ADC1_2_IRQn);
	*/
	
	//Set sampling rate 
	ADC1->SMPR2 |= ADC_SMPR2_SMP5_2 | ADC_SMPR2_SMP5_0|ADC_SMPR2_SMP5_1;
	ADC1->SMPR2 |= ADC_SMPR2_SMP4_2 | ADC_SMPR2_SMP4_0|ADC_SMPR2_SMP4_1;
	
	//Set the number of conversion
	ADC1->SQR1 |= ADC_SQR1_L_0; //length of two sequences 
	
	//Set the channel to convert in the sequence register
	ADC1->SQR3 |= ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_2;
	ADC1->SQR3 |= ADC_SQR3_SQ2_2;
	
	// Enable scan mode
	ADC1->CR1 |= ADC_CR1_SCAN;	
	// Enable DMA for ADC
	ADC1->CR2 |= ADC_CR2_DMA;
	
	// DMA settings
	DMA1_Channel1->CPAR = (uint32_t)(&(ADC1->DR));
	DMA1_Channel1->CMAR = (uint32_t)sample;
	DMA1_Channel1->CNDTR = 2;
	DMA1_Channel1->CCR |= DMA_CCR1_CIRC|DMA_CCR1_MINC|DMA_CCR1_PSIZE_0|DMA_CCR1_MSIZE_0;
	DMA1_Channel1->CCR |= DMA_CCR1_EN;
	
	//Enable ADC for the first time to wake up and set continous mode 
	ADC1->CR2 |= ADC_CR2_CONT|ADC_CR2_ADON;
	
	//Ideally delay t_stab
	delayMs(100);
	
	//Enable ADC again to turn ADC on;
	ADC1->CR2 |= ADC_CR2_ADON;
	delayMs(100);
}
void calibrateADC(){
	//Calibrate the ADC
	ADC1->CR2 |= ADC_CR2_CAL;
	delayMs(500);
	while ((ADC1->CR2&ADC_CR2_RSTCAL) == ADC_CR2_CAL){
	}
}
