#ifndef AN4602
#define AN4602

#include <stdint.h>
#include <stdbool.h>
#include "Uart.h"
#include "I2C.h"
#include "IMU_DEFINITION.h"
#define COMPASS_ADDR 0x3C

/* All extern global variables*/
extern uint8_t i2cOutput[32];

extern imu magno;

/*	Registers	*/
#define WHO_AM_I 0x0F
#define CTRL_REG1	0x20
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define TEMP_OUT_L 0x2E

/*** CTRL_REG1 Setting ***/
#define ST_EN 0x01
#define TEMP_EN 0x80

// X and Y Operating Mode
#define XY_LOW_POWER 0x00 // ODR 1000 Hz when FODR is set
#define XY_MED_PERF 0x20 // ODR 560 Hz when FODR is set
#define XY_HIGH_PERF 0x40 // ODR 300 Hz when FODR is set
#define XY_ULTRA_PERF 0x60 // ODR 155 Hz when FODR is set

// Output data rate 
#define ODR_0_625 0x00
#define ODR_1_25	0x04
#define ODR_2_5	0x08
#define ODR_5	0x0C
#define ODR_10	0x10
#define ODR_20	0x14
#define ODR_40	0x18
#define ODR_80	0x1C
#define FODR 0x02

enum FAST_ODR {ODR_155 = 0x1D, ODR_300 , ODR_560, ODR_1000};


/*** CTRL_REG2 Setting ***/

//Full scale

#define SCALE_4G	0x00
#define SCALE_8G	0x20
#define SCALE_12G 0x40
#define SCALE_16G	0x60


/*** CTRL_REG3 Setting ***/

// Measurement mode
#define CONTINUOUS_MEAS	0x00
#define SINGLE_MEAS	0x01
#define IDLE_MODE	0x02


/*** CTRL_REG4 Setting ***/

// Z Operating Mode
#define Z_LOW_POWER 0x00
#define Z_MED_PERF 0x04
#define Z_HIGH_PERF 0x08
#define Z_ULTRA_PERF 0x0C


//Big Little Endian Setting
#define LITTLE_ENDIAN 0x00
#define BIG_ENDIAN 0x02

/*** CTRL_REG5 Setting ***/

#define BDU		0x40 // Use when reading rate is too slow 
#define FAST_READ	0x80 //Only high part is valid and low part can be disregard 


/*** STATUS_REG ***/

#define ZYXDA 0x08 //Data ready
#define ZYXOR	0x80 //Data overwritten 


/*** Data Status ***/

uint8_t isAN4602Ready(void);
uint8_t isAN4602Overun(void);


/*** Configure settings ***/
void setAN4602Scale(uint8_t scaleSet); // reg1
void setAN4602OPowerMode(uint8_t xySet, uint8_t zSet); //reg1 and reg4
void setAN4602DOR(uint8_t opSet); // reg1 
void setAN4602MeasMode(uint8_t measMode); // reg3

void configN4602(void);


/*** Read data ***/
void readAN4602Axes(void);
void readAN4602Temp(void);

#endif

