#include "I2C.h"
#include "stm32f10x.h"

uint8_t i2cOutput[32];

//Initialise the I2C peripheral 
void initI2C (void){
		//Initialise I2C1 
		I2C1->CR1 = 0UL;
		I2C1->CR2 = 0UL;
		I2C1->CR2 |= 36; // Set freq of APB1 buss to 36
		I2C1->CCR &= ~(I2C_CCR_FS); // Set to Sm mode I2C
		I2C1->CCR |= 180;
		I2C1->TRISE |= 37;
		I2C1->CR1 |= I2C_CR1_ACK;
		//Initialise I2C1 pins
		GPIOB->CRL |= GPIO_CRL_MODE6|GPIO_CRL_CNF6|GPIO_CRL_MODE7|GPIO_CRL_CNF7;
		//GPIOB->ODR |= ((1<<6) | (1<<7)); //Pin6/Pin7 : SCL/SDA 
		I2C1->CR1 |= I2C_CR1_PE;
}

	
//Write single data to single register address  
void i2cWriteSingle(uint8_t device_addr, uint8_t reg_addr,uint8_t data)
{

		uint32_t clear_addr; //read SR2 to clear ADDR status 
		I2C1->CR1 |= I2C_CR1_START; // generate start condition 
		while (!(I2C1->SR1 & I2C_SR1_SB)){}
		I2C1->DR = device_addr; //device address to communicate with
		while (!(I2C1->SR1 & I2C_SR1_ADDR)){} //send address
		clear_addr = I2C1->SR2;
		I2C1->DR = reg_addr; // indicate the address to send to
		while (!(I2C1->SR1 & I2C_SR1_TXE)){}
		I2C1->DR = data;
		while (!(I2C1->SR1 & I2C_SR1_TXE)){}
	
	
}

void i2cWriteReg(uint8_t device_addr,uint8_t reg_addr)
{
	uint32_t clear_addr;
	I2C1->CR1 |= I2C_CR1_START; // generate start condition 
	while (!(I2C1->SR1 & I2C_SR1_SB)){}
	I2C1->DR = device_addr; //device address to communicate with
	while (!(I2C1->SR1 & I2C_SR1_ADDR)){} //send address
	clear_addr = I2C1->SR2;
	I2C1->DR = reg_addr; // indicate the address to send to
	while (!(I2C1->SR1 & I2C_SR1_TXE)){}
}

uint8_t i2cReadAByte(uint8_t device_addr, uint8_t reg_addr)
{
	uint32_t clear_addr;
	i2cWriteReg(device_addr,reg_addr);
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));
	I2C1->DR  = device_addr+1;
	while (!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C1->CR1 &= ~I2C_CR1_ACK;
	clear_addr = I2C1->SR2;
	I2C1->CR1 |= I2C_CR1_STOP;
	while (!(I2C1->SR1 & I2C_SR1_RXNE)); 
	uint8_t aByte = (uint8_t)I2C1->DR;
	I2C1->CR1 |= I2C_CR1_ACK;
	return aByte;
}


void i2cReadBytes(uint8_t device_addr, uint8_t reg_addr,uint8_t dataSize)
{
	uint32_t clear_addr;
	i2cWriteReg(device_addr,(reg_addr|0x80));
	//DMA Setting for I2C	  
	DMA1_Channel7->CPAR =	 (uint32_t)&(I2C1->DR);
	DMA1_Channel7->CMAR = (uint32_t)&(i2cOutput);
	DMA1_Channel7->CNDTR = dataSize;
	DMA1_Channel7->CCR |= DMA_CCR7_TCIE|DMA_CCR7_MINC|DMA_CCR7_EN;
	
	I2C1->CR2 |= I2C_CR2_DMAEN;
	I2C1->CR2 |= I2C_CR2_LAST;
	I2C1->CR1 |= I2C_CR1_ACK;
		
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));
	I2C1->DR  = device_addr+1;
	while (!(I2C1->SR1 & I2C_SR1_ADDR));
	clear_addr = I2C1->SR2;
	
	while((DMA1->ISR & DMA_ISR_TCIF7) == 0);
	DMA1->IFCR |= DMA_IFCR_CTCIF7;      // Clear the DMA transfer complete flag
	DMA1_Channel7->CCR &= ~(DMA_CCR7_EN);  // Disable DMA channel 7
	I2C1->CR1 |= I2C_CR1_STOP;

}

		
