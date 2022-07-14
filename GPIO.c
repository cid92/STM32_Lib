#include "GPIO.h"
#include <stdint.h>

//The bit register for each pib
static uint32_t PINPOS[16] = {
	(0x00),
	(0x04),
	(0x08),
	(0x0C),
	(0x10),
	(0x14),
	(0x18),
	(0x1C),
	(0x00), //pin 8 at register high
	(0x04), //pin 9 
	(0x08),
	(0x0C),
	(0x10),
	(0x14),
	(0x18),
	(0x1C),
	
};
// Configure the mode type of a pin 
static void config_pin (GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type){
	//Configure the mode type for pin at register high (pin 8 and above)
	if (pinNumber >= 8){ 
		switch(mode_type){
			case OUTPUT_GEN_PURPOSE | INPUT_ANALOG:
				port->CRH &= ~( (1<<CNF_POS_BIT1	) | (1<<CNF_POS_BIT2	) );
			break;
			case OUTPUT_OD | INPUT_FLOATING:
				port->CRH &=  ~(1<<CNF_POS_BIT2	);
				port->CRH |=  (1<<CNF_POS_BIT1	);
			break;
			case OUTPUT_ALT_FUNCTION | INPUT_PU_PD:
				port->CRH &=  ~(1<<CNF_POS_BIT1	);
				port->CRH |=  (1<<CNF_POS_BIT2	);
				//port->ODR |= (1<<pinNumber); // for pullup input 
			break;
			case OUTPUT_ALT_FUNCTION_OD:
						port->CRH |= ( OUTPUT_ALT_FUNCTION_OD<<CNF_POS_BIT1 );
			break;
		}
		
	}
	//Configure the mode type for pin at register low (up to pin 7)
	else{
			switch(mode_type){
			case OUTPUT_GEN_PURPOSE | INPUT_ANALOG:
				port->CRL &= ~( (1<<CNF_POS_BIT1	) | (1<<CNF_POS_BIT2	) );
			break;
			case OUTPUT_OD | INPUT_FLOATING:
				port->CRL |=  (1<<CNF_POS_BIT1	);
				port->CRL &=  (1<<CNF_POS_BIT2	);
			break;
			case OUTPUT_ALT_FUNCTION | INPUT_PU_PD:
				port->CRL &=  ~(1<<CNF_POS_BIT1	);
				port->CRL |=  (1<<CNF_POS_BIT2	);
				//port->ODR |= (1<<pinNumber); // for pullup input 
			break;
			case OUTPUT_ALT_FUNCTION_OD:
						port->CRL |= ( OUTPUT_ALT_FUNCTION_OD<<CNF_POS_BIT1 );
			break;
		}
		
	}
}

//Configure the pin mode and speed
static void pin_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed)
{
		if (pinNumber >= 8){
			port->CRH |= (pinSpeed << MODE_POS_BIT1);
			
		}
		else {
			port->CRL |= (pinSpeed << MODE_POS_BIT1);
			
		}
}

uint8_t gpio_read(GPIO_TypeDef *port, uint32_t pinNumber){
	
	return (uint8_t) ((port->IDR&(1<<pinNumber))>>pinNumber);
}

void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t state){
		
	if (state){
		port->BSRR =  (1<<pinNumber);
	}
	else {
	
		port->BSRR = (1<< (pinNumber+16) );
	}

                                                                                                                                        }

void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber){
		port->ODR ^= (1<<pinNumber);

}

void gpio_init(GPIO_TYPE PinType){
	if (PinType.port == GPIOA){
		GPIO_CLOCK_ENABLE_PORTA;
	}
	else if (PinType.port == GPIOB){
		GPIO_CLOCK_ENABLE_PORTB;
	}
	else if (PinType.port == GPIOC){
		GPIO_CLOCK_ENABLE_PORTC;
	}
	else if (PinType.port == GPIOD){
		GPIO_CLOCK_ENABLE_PORTD;
	}
	config_pin (PinType.port, PinType.pin, PinType.mode_type);
	pin_speed(PinType.port, PinType.pin, PinType.speed);
}

// Configure external interrupt for a GPIO pin 

void configure_gpio_interrupt(GPIO_TypeDef *port, uint32_t pinNumber, edge_type edgeSet){
	GPIO_CLOCK_ENABLE_ALT_FUCN;
	if (port == PORTA) {
		switch (pinNumber) {
			case 0:
					AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI0_PA;
			break;
			case 1:
				  AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI1_PA;
			break;
			case 2:
					AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI2_PA;
			break;
			case 3:
					AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI3_PA;
			break;
			case 4:
					AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI4_PA;
			break;
			case 5:
				  AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI5_PA;
			break;
			case 6:
					AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI6_PA;
			break;
			case 7:
					AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI7_PA;
			break;
			case 8:
					AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI8_PA;
			break;
			case 9:
				  AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI9_PA;
			break;
			case 10:
					AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI10_PA;
			break;
			case 11:
					AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI11_PA;
			break;
			case 12:
					AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI12_PA;
			break;
			case 13:
				  AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI13_PA;
			break;
			case 14:
					AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI14_PA;
			break;
			case 15:
					AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI15_PA;
			break;
		}	
	}		
	if (port == PORTB) {
		switch (pinNumber) {
			case 0:
					AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI0_PB;
			break;
			case 1:
				  AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI1_PB;
			break;
			case 2:
					AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI2_PB;
			break;
			case 3:
					AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI3_PB;
			break;
			case 4:
					AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI4_PB;
			break;
			case 5:
				  AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI5_PB;
			break;
			case 6:
					AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI6_PB;
			break;
			case 7:
					AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI7_PB;
			break;
			case 8:
					AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI8_PB;
			break;
			case 9:
				  AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI9_PB;
			break;
			case 10:
					AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI10_PB;
			break;
			case 11:
					AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI11_PB;
			break;
			case 12:
					AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI12_PB;
			break;
			case 13:
				  AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI13_PB;
			break;
			case 14:
					AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI14_PB;
			break;
			case 15:
					AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI15_PB;
			break;
		}	
	}	
	if (port == PORTC) {
		switch (pinNumber) {
			case 0:
					AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PC;
			break;
			case 1:
				  AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI1_PC;
			break;
			case 2:
					AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI2_PC;
			break;
			case 3:
					AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI3_PC;
			break;
			case 4:
					AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI4_PC;
			break;
			case 5:
				  AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI5_PC;
			break;
			case 6:
					AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI6_PC;
			break;
			case 7:
					AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI7_PC;
			break;
			case 8:
					AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI8_PC;
			break;
			case 9:
				  AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI9_PC;
			break;
			case 10:
					AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI10_PC;
			break;
			case 11:
					AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI11_PC;
			break;
			case 12:
					AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI12_PC;
			break;
			case 13:
				  AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI13_PC;
			break;
			case 14:
					AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI14_PC;
			break;
			case 15:
					AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI15_PC;
			break;
		}	
	}		
	if (port == PORTD) {
		switch (pinNumber) {
			case 0:
					AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PD;
			break;
			case 1:
				  AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI1_PD;
			break;
			case 2:
					AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI2_PD;
			break;
			case 3:
					AFIO->EXTICR[0]|= AFIO_EXTICR1_EXTI3_PD;
			break;
			case 4:
					AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI4_PD;
			break;
			case 5:
				  AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI5_PD;
			break;
			case 6:
					AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI6_PD;
			break;
			case 7:
					AFIO->EXTICR[1]|= AFIO_EXTICR2_EXTI7_PD;
			break;
			case 8:
					AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI8_PD;
			break;
			case 9:
				  AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI9_PD;
			break;
			case 10:
					AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI10_PD;
			break;
			case 11:
					AFIO->EXTICR[2]|= AFIO_EXTICR3_EXTI11_PD;
			break;
			case 12:
					AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI12_PD;
			break;
			case 13:
				  AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI13_PD;
			break;
			case 14:
					AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI14_PD;
			break;
			case 15:
					AFIO->EXTICR[3]|= AFIO_EXTICR4_EXTI15_PD;
			break;
		}	
	}
	switch (edgeSet) {
		case RISING_EDGE:
			EXTI->RTSR |= (1 << pinNumber);
			break;
		case FALLING_EDGE:
			EXTI->FTSR |= (1 << pinNumber);
			break;
		case RISE_FALL_EDGE:
			EXTI->RTSR |= (1 << pinNumber);
			EXTI->FTSR |= (1 << pinNumber);
			break;
		}
}

void enable_gpio_interrupt(uint32_t pinNumber, IRQn_Type irqNumber) {
	EXTI->IMR |= (1 << pinNumber);
	NVIC_EnableIRQ(irqNumber);

}

void clear_gpio_interrupt(uint32_t pinNumber) {
	EXTI->PR = (1 << pinNumber);
}
