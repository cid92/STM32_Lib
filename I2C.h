#ifndef I2C
#define I2C
#include <stdint.h>

extern uint8_t i2cOutput[32];

typedef enum {
i2c1,i2c2} i2c_no;

//Initialise the I2C peripheral
void initI2C (void);

//Write single data to single register address  
void i2cWriteSingle(uint8_t device_addr, uint8_t reg_addr,uint8_t data);

//Write to register address to change the pointer address of I2C slave for reading data
void i2cWriteReg(uint8_t device_addr,uint8_t reg_addr);

//Read a single byte at the specified register adress
uint8_t i2cReadAByte(uint8_t device_addr, uint8_t reg_addr);

//Read multiple bytes starting from the speciffied register address
void i2cReadBytes(uint8_t device_addr, uint8_t reg_addr,uint8_t dataSize);

#endif

