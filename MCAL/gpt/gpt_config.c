#include "TM4C123.h"
#include "gpt_interface.h"
#define PERIOD_OF_INTERRUPT     1000

str_GPT_t str_g_timer = {
	.interruptEnable = GPT_DISABLE_INTERRUPT,
	.timerIndex = GPT_TIMER_0,
	.timerMode = GPT_PERIODIC_MODE,
	.timerPeriod = PERIOD_OF_INTERRUPT,
	.timerSize =GPT_ORDINARY_TIMER,
};