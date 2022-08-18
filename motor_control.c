#include "motor_control.h"
#include <stdlib.h>

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

#define PINx 0
#define MOTx 1

#define LEFT_PWM 0
#define LEFT_ENCA 0
#define LEFT_ENCB 1
#define LEFT_FWD 4
#define LEFT_BWD 5

#define RIGHT_PWM 1
#define RIGHT_ENCA 2
#define RIGHT_ENCB 3
#define RIGHT_FWD 12
#define RIGHT_BWD 13


motor Wheel[2]; //Left wheel at index 0 and Right wheel at index 1
static enc encPin[4];
static dir dirPin[2];

GPIO_TYPE pwm_port[] = {	[0].port = PORTA,
													[0].pin = 11,
													[0].mode = OUTPUT_MODE,
													[0].mode_type = OUTPUT_ALT_FUNCTION,
													[0].speed = SPEED_50MHZ,
	
													[1].port = PORTA,
													[1].pin = 8,
													[1].mode = OUTPUT_MODE,
													[1].mode_type = OUTPUT_ALT_FUNCTION,
													[1].speed = SPEED_50MHZ,
};

GPIO_TYPE dir_port[] = {	//Direction control pin 1
													[0].port = PORTB,
													[0].pin = 4,
													[0].mode = OUTPUT_MODE,
													[0].mode_type = OUTPUT_GEN_PURPOSE,
													[0].speed = SPEED_50MHZ,
													
													//Direction control pin 2
													[1].port = PORTB,
													[1].pin = 5,
													[1].mode = OUTPUT_MODE,
													[1].mode_type = OUTPUT_GEN_PURPOSE,
													[1].speed = SPEED_50MHZ,
	
													//Direction control pin 3
													[2].port = PORTB,
													[2].pin = 12,
													[2].mode = OUTPUT_MODE,
													[2].mode_type = OUTPUT_GEN_PURPOSE,
													[2].speed = SPEED_50MHZ,

													//Direction control pin 4
													[3].port = PORTB,
													[3].pin = 13,
													[3].mode = OUTPUT_MODE,
													[3].mode_type = OUTPUT_GEN_PURPOSE,
													[3].speed = SPEED_50MHZ,

};


GPIO_TYPE enc_port[] = {	[0].port = PORTA,
													[0].pin = 0,
													[0].mode = INPUT_MODE,
													[0].mode_type = INPUT_PU_PD,
													[0].speed = NIL,

													[1].port = PORTA,
													[1].pin = 1,
													[1].mode = INPUT_MODE,
													[1].mode_type = INPUT_PU_PD,
													[1].speed = NIL,
	
													[2].port = PORTA,
													[2].pin = 2,
													[2].mode = INPUT_MODE,
													[2].mode_type = INPUT_PU_PD,
													[2].speed = NIL,
	
													[3].port = PORTA,
													[3].pin = 3,
													[3].mode = INPUT_MODE,
													[3].mode_type = INPUT_PU_PD,
													[3].speed = NIL,
};


motor Wheel[] = {
	// Left Motor
	[LEFT_MOTOR].pwm_chan = 1,
	[LEFT_MOTOR].speed = 0,
	[LEFT_MOTOR].pos = 0,
	[LEFT_MOTOR].p = 10,
	[LEFT_MOTOR].i = 1,
	[LEFT_MOTOR].d = 0,
	[LEFT_MOTOR].enc_count = 0,
	[LEFT_MOTOR].duty_cycle = 0,
  // Right Motor
	[RIGHT_MOTOR].pwm_chan = 4,
	[RIGHT_MOTOR].speed = 0,
	[RIGHT_MOTOR].pos = 0,
	[RIGHT_MOTOR].p = 10,
	[RIGHT_MOTOR].i = 1,
	[RIGHT_MOTOR].d = 0,
	[RIGHT_MOTOR].enc_count = 0,
	[RIGHT_MOTOR].duty_cycle = 0,
};



void EXTI0_IRQHandler(void){
	//Compare the encoder A and B outputs at rising and falling edge of the encoder A
	if (EXTI->PR & EXTI_PR_PR0){
		uint8_t pin = gpio_read(PORTA,0);
		uint8_t pinX = gpio_read(PORTA,encPin[0].noX);
		if (pin == 1 && pinX== 0){
			Wheel[encPin[0].motorX].enc_count++;
		}
		else if (pin == 1 && pinX == 1){
			Wheel[encPin[0].motorX].enc_count--;
		}
		else if (pin == 0 && pinX == 1){
			Wheel[encPin[0].motorX].enc_count++;
		}
		else if (pin == 0 && pinX == 0){
			Wheel[encPin[0].motorX].enc_count--;
		}
	}
	clear_gpio_interrupt(0);
}
void EXTI1_IRQHandler(void){
	//Compare the encoder A and B outputs at rising and falling edge of the encoder B
	if (EXTI->PR & EXTI_PR_PR1){
		uint8_t pin = gpio_read(PORTA,0);
		uint8_t pinX = gpio_read(PORTA,encPin[1].noX);
		if (pin == 1 && pinX == 1){
			Wheel[encPin[1].motorX].enc_count++;
		}
		else if (pin == 1 && pinX == 0){
			Wheel[encPin[1].motorX].enc_count--;
		}
		else if (pin == 0 && pinX == 0){
			Wheel[encPin[1].motorX].enc_count++;
		}
		else if (pin == 0 && pinX == 1){
			Wheel[encPin[1].motorX].enc_count--;
		}
	}
	clear_gpio_interrupt(1);
	
}

void EXTI2_IRQHandler(void){
	if (EXTI->PR & EXTI_PR_PR2){
		uint8_t pin = gpio_read(PORTA,2);
		uint8_t pinX = gpio_read(PORTA,encPin[2].noX);
		if (pin == 1 && pinX == 0){
			Wheel[encPin[2].motorX].enc_count++;
		}
		else if (pin == 1 && pinX == 1){
			Wheel[encPin[2].motorX].enc_count--;
		}
		else if (pin == 0 && pinX == 1){
			Wheel[encPin[2].motorX].enc_count++;
		}
		else if (pin == 0 && pinX == 0){
			Wheel[encPin[2].motorX].enc_count--;
		}
	}
	clear_gpio_interrupt(2);
}
void EXTI3_IRQHandler(void){
	if (EXTI->PR & EXTI_PR_PR3){
		uint8_t pin = gpio_read(PORTA,2);
		uint8_t pinX = gpio_read(PORTA,encPin[3].noX);
		if (pin == 1 && pinX == 1){ //maybe change to pin == pinX and pin != pinX
			Wheel[encPin[2].motorX].enc_count++;
		}
		else if (pin == 0 && pinX == 0){
			Wheel[encPin[2].motorX].enc_count++;
		}
		else if (pin == 0 && pinX == 1){
			Wheel[encPin[2].motorX].enc_count--;
		}
		else if (pin == 1 && pinX == 0){
			Wheel[encPin[2].motorX].enc_count--;
		}
	}
	clear_gpio_interrupt(3);
	
}





void configMotor(void){
	
	//Pair up A and B encoder pins for each motor
	encPin[LEFT_ENCA].noX = LEFT_ENCB;
	encPin[LEFT_ENCA].motorX = LEFT_MOTOR;
	encPin[LEFT_ENCB].noX = LEFT_ENCA;
	encPin[LEFT_ENCB].motorX = LEFT_MOTOR;
	
	encPin[RIGHT_ENCA].noX = LEFT_ENCB;
	encPin[RIGHT_ENCA].motorX = RIGHT_MOTOR;
	encPin[RIGHT_ENCB].noX = RIGHT_ENCA;
	encPin[RIGHT_ENCB].motorX = RIGHT_MOTOR;
	
	// Configure the directom pin for each wheels
	dirPin[LEFT_MOTOR].fwd = LEFT_FWD;
	dirPin[LEFT_MOTOR].bwd = LEFT_BWD;
	dirPin[RIGHT_MOTOR].fwd = RIGHT_FWD;
	dirPin[RIGHT_MOTOR].bwd = RIGHT_BWD;
	
	// Configure the PWM for each wheel   
	Wheel[LEFT_MOTOR].pwm_chan = LEFT_PWM;
	Wheel[RIGHT_MOTOR].pwm_chan = RIGHT_PWM;
	
}


void jtagDisable(void){ // run before initialising the motor
	AFIO->MAPR |=AFIO_MAPR_SWJ_CFG_1; //disable JTAG for Port B pin4
	AFIO->MAPR &= ~(AFIO_MAPR_SWJ_CFG_0|AFIO_MAPR_SWJ_CFG_2);
}
	
void initMotor(void){
	//Initialise all the IO for pwm generation, direction set and encoder reading 
	for (uint8_t i = 0; i < 2; i++){
		gpio_init(pwm_port[i]);
		gpio_init(dir_port[i]);
		gpio_init(dir_port[2*i+1]);
		gpio_init(enc_port[i]);
		gpio_init(enc_port[2*i+1]);

	}
	initPWM(TIMER1, CHANNEL1, 2000);
	initPWM(TIMER1, CHANNEL4, 2000);
	setPwmDuty(TIMER1, CHANNEL1,0);
	setPwmDuty(TIMER1, CHANNEL4,0);
	// Enable gpio interrupt handler for pins 0,1,2 and 3
	configure_gpio_interrupt(PORTA,0,RISE_FALL_EDGE);
	enable_gpio_interrupt(0, EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 0);
	configure_gpio_interrupt(PORTA,1,RISE_FALL_EDGE);
	enable_gpio_interrupt(1, EXTI1_IRQn);
	NVIC_SetPriority(EXTI1_IRQn, 0);
	configure_gpio_interrupt(PORTA,2,RISE_FALL_EDGE);
	enable_gpio_interrupt(2, EXTI2_IRQn);
	NVIC_SetPriority(EXTI2_IRQn, 0);
	configure_gpio_interrupt(PORTA,3,RISE_FALL_EDGE);
	enable_gpio_interrupt(3, EXTI3_IRQn);
	NVIC_SetPriority(EXTI3_IRQn, 0);
}

void setMotorPWM(void){
	gpio_write(PORTB, dirPin[LEFT_MOTOR].fwd, 0);
	gpio_write(PORTB, dirPin[LEFT_MOTOR].bwd, 1);
	Wheel[LEFT_MOTOR].duty_cycle = (uint16_t)abs(Wheel[LEFT_MOTOR].speed) ;
	setPwmDuty(TIMER1,Wheel[LEFT_MOTOR].pwm_chan ,Wheel[LEFT_MOTOR].duty_cycle);
}
