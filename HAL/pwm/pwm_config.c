#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "TM4C123.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/gpt/gpt_interface.h"
#include "pwm_interface.h"
#define  PERIOD_REQUIRED_IN_MS   500

str_pinConfig_t str_g_pwmPin = {
	.port_index 			= PORTF_INDEX,
	.pin_index  			= GPIO_PIN3,
	.pin_state  			= GPIO_LOW,
	.pin_direction			= GPIO_DIRECTION_OUTPUT,
	.pin_MADrive			= GPIO_FOUR_MA_DRIVE, 
	.pin_connection			= GPIO_PULL_UP ,
	.enable_interrupt		= GPIO_DISABLE_INTERRUPT ,
};

str_pwm_t str_g_pwm = {
	.duty_cycle 	= DUTY_0 ,
	.period_in_ms 	= PERIOD_REQUIRED_IN_MS ,
	.pwm_pin 		= &(str_g_pwmPin) ,
	.pwm_timer 		= PWM_TIMER_0
	
};

