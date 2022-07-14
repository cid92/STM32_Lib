#ifndef UART
#define UART
#include "stm32f10x.h"
#define BUFFSIZE 80

extern volatile char buffTx[BUFFSIZE]; // Store the message to be transmitted  
extern volatile char buffRx[BUFFSIZE]; // Store the received message  

//Circular buffer initialisation 
typedef struct{
	volatile uint8_t head; //index where data is written in the buffer
	volatile uint8_t tail; //index where data is read in the buffer
	uint8_t index; //current index of the buffer
	uint8_t space; //space available in the buffer
	uint8_t buff[BUFFSIZE]; //intialise circular buffer
}BUFF;

typedef enum baud{
	BD_9600 = 0x1D4C,
	BD_19200 = 0xEA6
}BAUD;


//This libarary handles the data transmission and reception via UART
void USART1_IRQHandler(void);
extern void sendBytes(char txData[], uint8_t txLength);
void initUsart1(BAUD baudrate);
#endif