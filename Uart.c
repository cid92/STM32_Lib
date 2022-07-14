#include "Uart.h"
#include <stdint.h>
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"


static BUFF Tx; //circular buffer for Tranmission
static BUFF Rx; //circular buffer for Reception


void USART1_IRQHandler(void)
{
		if (USART1->SR & USART_SR_RXNE){
			//
			Rx.buff[Rx.head] = USART1->DR;
			Rx.head++;
			if (Rx.head==BUFFSIZE){ //reset the read index
					Rx.head = 0;
					}  
		//	while (!(USART1->SR & USART_SR_TC));
		}
		if (USART1->SR & USART_SR_TXE){
			//Do TX tranmission 
			if (Tx.tail == Tx.head){ //tranmission completed
				USART1->SR &= ~(USART_SR_TC); //disable TX interrupt
				USART1->CR1 &= ~(USART_CR1_TXEIE); //clear TX interrupt
			}
			else {
				USART1->DR = Tx.buff[Tx.tail];
				Tx.tail++;
				if (Tx.tail==BUFFSIZE){ //reset the read index
					Tx.tail = 0;
					}  
			}
		}
}

void readBytes(uint8_t numByte, char dataRx[])
{
	if (Rx.tail != Rx.head) //new data available to be read 
	{
		for (int i=0;i<numByte;i++)
		{
			dataRx[i] = Rx.buff[Rx.tail];
			Rx.tail++;
			if (Rx.tail == BUFFSIZE){
				Rx.tail = 0;
			}
		}
		dataRx[numByte] = '\0'; 
	}
	else{ //No new data to read 
	}
}

void sendBytes(char txData[], uint8_t txLength)
{	
	Tx.space = 0;
	Tx.index = 0;
	if (Tx.tail == Tx.head){ //buffer is empty 
		Tx.index = Tx.head;
	}
	else {
		Tx.index = Tx.head+1; //buffer not empty
	}
	if (Tx.tail < Tx.head){ //the read index and the write index are in the same lap
		Tx.space= (Tx.tail) + (BUFFSIZE-Tx.head);
	}
	else { //the write index is one lap ahead of the read index 
		Tx.space = (BUFFSIZE-Tx.tail)+Tx.head; 
	}
	if (txLength<=Tx.space){ //check if the buffer is full 
		for (int i =0 ;i <txLength;i++)
		{
					if (Tx.index>=BUFFSIZE){
							Tx.index = 0;
					}  
				 // printf("%d\n",i_cir);
				Tx.buff[Tx.index] = txData[i];
				Tx.index++;
		}
		Tx.head += txLength;//update the index where last data is written in the buffer
		if (Tx.head >= BUFFSIZE){ //reset the write index
			Tx.head = 0; //update the write index 
		}
		USART1->CR1 |= USART_CR1_TXEIE; //enable TX interrupt to start sending data
	}
	else { //Buffer is full 
			//printf("Insufficient buffer\n");
	}
}


void initUsart1(BAUD baudrate){
	//Initiaise UART Clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN|RCC_APB2ENR_AFIOEN|RCC_APB2ENR_USART1EN;
	//Initiaise UART Pins
	GPIOA->CRH |=  GPIO_CRH_CNF9_1|GPIO_CRH_MODE9_0|GPIO_CRH_MODE9_1;
	GPIOA->CRH &= ~(GPIO_CRH_CNF9_0);
	GPIOA->CRH |=  GPIO_CRH_CNF10_1;
	GPIOA->CRH &= ~(GPIO_CRH_CNF10_0|GPIO_CRH_MODE10_0|GPIO_CRH_MODE10_1);
	USART1->BRR = baudrate; //clkPer /  (baudR x 16) = 72MHz/(9600 x 16) 
	// 468.75
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
	USART1->CR1 |= USART_CR1_UE;
	USART1->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART1_IRQn);
}
