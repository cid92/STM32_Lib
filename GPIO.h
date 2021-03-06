#ifndef GPIO
#define GPIO

#include "stm32f10x.h"

//Port names

#define PORTA	GPIOA
#define PORTB	GPIOB
#define PORTC	GPIOC
#define PORTD	GPIOD

//Pin Mode
#define OUTPUT_MODE ((uint32_t) 0x01)
#define INPUT_MODE ((uint32_t) 0x02)

//Input Mode Type
#define INPUT_ANALOG ((uint32_t) 0x00)
#define INPUT_FLOATING ((uint32_t) 0x01)
#define INPUT_PU_PD ((uint32_t) 0x02)

//Output Mode Type
#define OUTPUT_GEN_PURPOSE ((uint32_t) 0x00)
#define OUTPUT_OD ((uint32_t) 0x01)
#define OUTPUT_ALT_FUNCTION ((uint32_t) 0x02)
#define OUTPUT_ALT_FUNCTION_OD ((uint32_t) 0x03)

//Pin speed/slew rate
#define NIL ((uint32_t) 0x00)
#define SPEED_2MHZ ((uint32_t) 0x02)
#define SPEED_10MHZ ((uint32_t) 0x01)
#define SPEED_50MHZ ((uint32_t) 0x03)

//clock enable
#define GPIO_CLOCK_ENABLE_ALT_FUCN (RCC->APB2ENR |= (1<<0))
#define GPIO_CLOCK_ENABLE_PORTA	(RCC->APB2ENR |= (1<<2))
#define GPIO_CLOCK_ENABLE_PORTB	(RCC->APB2ENR |= (1<<3))
#define GPIO_CLOCK_ENABLE_PORTC	(RCC->APB2ENR |= (1<<4))
#define GPIO_CLOCK_ENABLE_PORTD	(RCC->APB2ENR |= (1<<5))



//CNF Shift 
#define CNF_POS_BIT1	(PINPOS[pinNumber] +2)
#define CNF_POS_BIT2	(PINPOS[pinNumber] +3)


//Mode Shift 
#define MODE_POS_BIT1 PINPOS[pinNumber]
#define MODE_POS_BIT2 (PINPOS[pinNumber] +1)

typedef enum {
RISING_EDGE, FALLING_EDGE, RISE_FALL_EDGE
}edge_type;

typedef struct
{
	GPIO_TypeDef *port;
	uint32_t pin;
	uint32_t mode;
	uint32_t mode_type;
	uint32_t pull;
	uint32_t speed;
	uint32_t alt_func;
	
} GPIO_TYPE;

//GPIO Functions 
//*************************************
//GPIO Configuration 
static void config_pin (GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type);
static void pin_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed);

//GPIO User Pin Functions 
uint8_t gpio_read(GPIO_TypeDef *port, uint32_t pinNumber);
void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t state);
void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber);
void gpio_init(GPIO_TYPE PinType);


//Interrupt Function 
//**********************************
void configure_gpio_interrupt(GPIO_TypeDef *port, uint32_t pinNumber, edge_type edgeSet);
void enable_gpio_interrupt(uint32_t pinNumber, IRQn_Type irqNumber);
void clear_gpio_interrupt(uint32_t pinNumber);
#endif

