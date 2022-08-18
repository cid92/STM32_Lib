#ifndef PRINT_MSG
#define PRINT_MSG
#include "stm32f10x.h"
#include "Uart.h"
#include <stdint.h>
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
//This library is use for debugging purpose. Messages are printed via UART1. 


void echoPrintMsg(void);
void printMsg(char *msg , ...);
#endif

