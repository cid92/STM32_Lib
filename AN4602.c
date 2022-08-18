#include "AN4602.h"


static uint8_t ctrl_Reg [5], reg_stat;
static int16_t x, y, z;

imu magno = {&ctrl_Reg[0], &reg_stat, &x, &y, &z, 0};
/*** Data Status ***/

uint8_t isAN4602Ready(void){
	return (i2cReadAByte(COMPASS_ADDR, STATUS_REG)&ZYXDA);
	
}

uint8_t isAN4602Overun(void){
	return (i2cReadAByte(COMPASS_ADDR, STATUS_REG)&ZYXOR);
}

/*** Configure settings ***/

void setAN4602Scale(uint8_t scaleSet){
	*(magno.ctrlReg+1) |= scaleSet;
}

void setAN4602OPMode(uint8_t xySet, uint8_t zSet){
	*magno.ctrlReg |= xySet;
	*(magno.ctrlReg+3) |= zSet;
}

void setAN4602DOR(uint8_t opSet){
	//Fast output data rate 
	if (opSet == ODR_155 || opSet == ODR_300 || opSet == ODR_560 || opSet == ODR_1000){
		*magno.ctrlReg |= FODR;
		switch (opSet){ 
			case ODR_155:
				setAN4602OPMode(XY_ULTRA_PERF, Z_ULTRA_PERF);
				break;
			case ODR_300:
				setAN4602OPMode(XY_HIGH_PERF, Z_HIGH_PERF);
				break;
			case ODR_560:
				setAN4602OPMode(XY_MED_PERF, Z_MED_PERF);
				break;
			case ODR_1000:
				setAN4602OPMode(XY_LOW_POWER, Z_LOW_POWER);
				break;
		}
	}
	//Standard output rate up to 80Hz
	else {
		*magno.ctrlReg |= opSet;
	}
}

void setAN4602MM(uint8_t measMode){
	*(magno.ctrlReg+2) |= measMode;
}


void configN4602(void){
	for (uint8_t i = 0; i < 5; i++){
		i2cWriteSingle(COMPASS_ADDR, CTRL_REG1+i, *(magno.ctrlReg+i));
	}
}


/*** Read data ***/
void readAN4602Axes(void){
	i2cReadBytes(COMPASS_ADDR, OUT_X_L, 6);
	*magno.dataX = (int16_t)((i2cOutput[1]<<8|i2cOutput[0]));
	*magno.dataY = (int16_t)((i2cOutput[3]<<8|i2cOutput[2]));
	*magno.dataZ = (int16_t)((i2cOutput[5]<<8|i2cOutput[4]));
}

void readAN4602Temp(void){
	i2cReadBytes(COMPASS_ADDR, TEMP_OUT_L, 2);
	magno.temp = (int16_t)((i2cOutput[1]<<8|i2cOutput[0]));
}

