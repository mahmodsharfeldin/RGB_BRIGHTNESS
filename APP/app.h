#include "../HAL/led/led.h"
#include "../HAL/button/button.h"
#include "../HAL/pwm/pwm_interface.h"
#define STATE_1    1
#define STATE_2    2
#define STATE_3    3
#define STATE_4    4
#define ZERO_INIT  				0
#define ONE_INIT  				1
#define MINUS_ONE_INIT  		-1
#define DEBOUNCING_THRESHOLD     100 
#define NUMBER_OF_STATES		 5

void app_init();
void app_run();