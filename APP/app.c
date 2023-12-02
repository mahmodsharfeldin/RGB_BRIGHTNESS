#include "app.h"
#define  step_1  30
#define  step_2  60
#define  step_3  90
#define  step_4  0
static str_led_t str_gs_greenLed;
static uint32_t uint32_gs_counter 		= ZERO_INIT;
static uint8_t uint8_gs_state 			= MINUS_ONE_INIT;
static uint8_t uint8_gs_change_state 	= ZERO_INIT;
static str_button_t str_gs_button;
void preesed_button()
{
	uint32_gs_counter++;
}

void app_init()
{
	str_gs_button.port = BUTTON_PORTF;
	str_gs_button.pin   = BUTTON_PIN4;
	str_gs_button.connection = BUTTON_PULL_UP;
	str_gs_button.enable_interrupt = BUTTON_ENABLE_INTERRUPT;
	str_gs_button.interrupt_trigger = BUTTON_LOW_LEVEL_TRIGGER;
	str_gs_button.btnInterruptHandler = preesed_button;
	str_gs_button.interrupt_priority = BUTTON_INT_PRIORITY_0;
	str_gs_greenLed.port  = LED_PORTF;
	str_gs_greenLed.pin   = LED_PIN3;
	str_gs_greenLed.state = LED_OFF;
	LED_init(&str_gs_greenLed);
	PWM_init();
	BUTTON_init(&str_gs_button);
	LED_off(&str_gs_greenLed);
}
void app_run()
{
	if(uint32_gs_counter >= DEBOUNCING_THRESHOLD)
	{
		uint8_gs_state = (uint8_gs_state+ONE_INIT)% NUMBER_OF_STATES;
		uint32_gs_counter=ZERO_INIT;
		uint8_gs_change_state =ONE_INIT;
	}
	if(uint8_gs_change_state){
		uint8_gs_change_state =ZERO_INIT;
		switch(uint8_gs_state)
		{
			case STATE_1 :
				PWM_setDutyCycle(step_1);
				break;
			case STATE_2 :
				PWM_setDutyCycle(step_2);
				break;
			case STATE_3 :
				PWM_setDutyCycle(step_3);
				break;
			case STATE_4 :
				PWM_setDutyCycle(step_4);
				break;
			default : break;
				
		}
	}
	
}