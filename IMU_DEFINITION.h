#ifndef IMU_DEF
#define IMU_DEF

#include <stdint.h>

typedef struct imu{
	
	uint8_t *ctrlReg;
	uint8_t *regStatus;
	int16_t	*dataX;
	int16_t	*dataY;
	int16_t	*dataZ;
	int16_t temp;
	
} imu;
#endif 
