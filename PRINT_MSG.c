#include "PRINT_MSG.h"


void echoPrintMsg(void)
{
		if (USART1->SR & USART_SR_RXNE){
		char temp = USART1->DR;
		USART1->DR = temp;
			while (!(USART1->SR & USART_SR_TC));
			
		}
}
void printMsg(char *msg , ...)
{
	va_list args;
	va_start(args,msg);
	char buff[BUFFSIZE];
	uint8_t txLen = vsprintf(buff, msg, args);
	sendBytes(buff,txLen);
	
}

/*
void printMsg(char *msg , ...)
{
	char buff[80];
	va_list args;
	va_start(args,msg);
	vsprintf(buff, msg, args);
	
	for (unsigned int i = 0; i < strlen(buff) ; i++)
	{
		while (!( USART1->SR & USART_SR_TXE));
		USART1->DR = buff[i];
	}
}
*/
