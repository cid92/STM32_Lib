#ifndef HMC5883L
#define HMC5883L
#include "stm32f10x.h"
#include <stdint.h>

/*** Register A Configuration	***/													

/* Average Sampling	*/ 
#define SAMPLE_1	0x00
#define SAMPLE_2	0x20
#define SAMPLE_4	0x40
#define SAMPLE_8	0x60


/*	Data Output Rate	*/
#define	OUTPUT_RATE_0_75 0x00
#define	OUTPUT_RATE_1_5	0x04	// 000100
#define	OUTPUT_RATE_3		0x08  // 001000
#define	OUTPUT_RATE_7_5	0x0C	// 001100
#define	OUTPUT_RATE_15	0x10	// 010000
#define	OUTPUT_RATE_30  0x14	// 010100
#define OUTPUT_RATE_75	0x18	// 011000

/*	Measurement Mode	*/
#define NORMAL_MEAS 0x00
#define POSITIVE_BIAS	0x01
#define NEGATIVE_BIAS 0x02

/*** Register B Configuration ***/

/* Gain */
#define GAIN_1370 0x00
#define GAIN_1090 0x20
#define GAIN_820 0x40
#define GAIN_660 0x60
#define GAIN_440 0x80
#define GAIN_390 0xA0
#define GAIN_330 0xC0
#define GAIN_230 0xE0


/*** Mode Register ***/

/* Set to enable high speed I2C , 3400kHz */
#define HIGH_SPEED	 0x80

/* Operation mode */
#define CONTINUOUS_MEASUREMENT 0x00
#define SINGLE_MEASUREMENT	0x01
#define IDLE	0x02


uint8_t isDataReady(void);


#endif