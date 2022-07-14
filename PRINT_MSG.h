#ifndef PRINT_MSG
#define PRINT_MSG
#include "stm32f10x.h"
#include "PRINT_MSG.h"
#include "UART.h"
//This library is use for debugging purpose. Messages are printed via UART1. 


void echoPrintMsg(void);
void printMsg(char *msg , ...);
#endif
