#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL
#include "stm32f10x.h"
#include "GPIO.h"
#include "PWM.h"

typedef struct {
	uint8_t pwm_chan;
	int16_t speed;
	int16_t pos;
	uint16_t p;
	uint16_t i;
	uint16_t d;
	int32_t  enc_count;
	uint16_t duty_cycle;
}motor;

typedef struct {
	uint8_t noX;
	uint8_t motorX;
}enc;

typedef struct {
	uint8_t fwd;
	uint8_t bwd;
}dir;

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);

extern GPIO_TYPE pwm_port[2];
extern GPIO_TYPE dir_port[4];
extern GPIO_TYPE enc_port[4];

extern motor Wheel[2];


	//Configure quadrature encoder reading for right wheel
	
void jtagDisable(void);
void configMotor(void);
void initMotor(void);
void setMotorPWM(void);


#endif