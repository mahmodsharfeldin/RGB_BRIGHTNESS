#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "TM4C123.h"
#include "gpt_interface.h"

static uint8_t irqs[TIMER_TYPES_COUNT][TIMERS_COUNT] ={		
		{TIMER0_IRQ,TIMER1_IRQ,TIMER2_IRQ,TIMER3_IRQ,TIMER4_IRQ,TIMER5_IRQ},
		{WTIMER0_IRQ,WTIMER1_IRQ,WTIMER2_IRQ,WTIMER3_IRQ,WTIMER4_IRQ,WTIMER5_IRQ}
};
typedef void (*ptr_func_callbackTimeoutTimer)(void);

static ptr_func_callbackTimeoutTimer arr_ptr_func_callbackTimeoutTimer[TIMER_TYPES_COUNT][TIMERS_COUNT] = {NULL };

/**
 * @brief Initializes the General-Purpose Timer (GPT) module based on the provided configuration.
 *
 * @return enu_GPTErrorStatus_t Error status after initialization.
 */
enu_GPTErrorStatus_t GPT_init()
{
	//config on-shot and periodic for the first step
	enu_GPTErrorStatus_t enu_a_funcRet = GPT_OK;
	

	if(str_g_timer.timerSize == GPT_ORDINARY_TIMER)
	{
		SET_BIT(RCG_CTIMER,str_g_timer.timerIndex);
	}
	else if(str_g_timer.timerSize == GPT_ORDINARY_TIMER)
	{
		SET_BIT(RCG_CWTIMER,str_g_timer.timerIndex);
	}
	else
	{
		enu_a_funcRet = GPT_INVALID_INPUT;
	}
		
	GPT_DISABLE_TIMER_A(str_g_timer.timerIndex,str_g_timer.timerSize);
	GPT_FRESH_CONFIG_REGISTER(str_g_timer.timerIndex,str_g_timer.timerSize);
	
	if(str_g_timer.timerMode == GPT_ON_SHOT_MODE)
	{
		GPT_CONFIG_ONE_SHOT_TIMER_MODE(str_g_timer.timerIndex,str_g_timer.timerSize);
		
	}
	else if(str_g_timer.timerMode == GPT_PERIODIC_MODE)
	{
		GPT_CONFIG_PERIODIC_TIMER_MODE(str_g_timer.timerIndex,str_g_timer.timerSize);
	}
	else
	{
		enu_a_funcRet = GPT_INVALID_INPUT;
	}
	
	if(str_g_timer.interruptEnable == GPT_ENABLE_INTERRUPT)
	{
		GPT_ENABLE_ON_MATCH_INTERRUPT(str_g_timer.timerIndex,str_g_timer.timerSize);
		GPT_ENABLE_TIMERA_TIMEOUT_INTERRUPT(str_g_timer.timerIndex,str_g_timer.timerSize);
		arr_ptr_func_callbackTimeoutTimer[str_g_timer.timerSize][str_g_timer.timerIndex] = str_g_timer.ptr_func_timeoutInterruptHandler;
		NVIC_EnableIRQ(irqs[str_g_timer.timerSize][str_g_timer.timerIndex]);
		__enable_irq();
	}
	else if(str_g_timer.interruptEnable == GPT_DISABLE_INTERRUPT)
	{
		GPT_DISABLE_ON_MATCH_INTERRUPT(str_g_timer.timerIndex,str_g_timer.timerSize);
		GPT_DISABLE_TIMERA_TIMEOUT_INTERRUPT(str_g_timer.timerIndex,str_g_timer.timerSize);
		NVIC_DisableIRQ(irqs[str_g_timer.timerSize][str_g_timer.timerIndex]);
	}
	else
	{
		enu_a_funcRet = GPT_INVALID_INPUT;
	}
	GPT_COUNTING_DOWN_MODE(str_g_timer.timerIndex,str_g_timer.timerSize);
	GPT_DISABLE_SNAP_SHOT_MODE(str_g_timer.timerIndex,str_g_timer.timerSize);
	GPT_DISABLE_WAIT_ON_TRIGGER_FEATURE(str_g_timer.timerIndex,str_g_timer.timerSize);
	GPT_CONCATENATE_TIMER_CONFIG(str_g_timer.timerIndex,str_g_timer.timerSize);
	GPT_ENABLE_TIMER_A(str_g_timer.timerIndex,str_g_timer.timerSize);
	
	return enu_a_funcRet;
}
/**
 * @brief Starts the GPT with the specified period in microseconds.
 *
 * @param uint32_a_periodInMicoSeconds Period in microseconds.
 * @return enu_GPTErrorStatus_t Error status after starting the timer.
 */
enu_GPTErrorStatus_t GPT_startTimerMicroSeconds(uint32_t uint32_a_periodInMicoSeconds)
{
	enu_GPTErrorStatus_t enu_a_funcRet = GPT_OK;
	uint32_t uint32_a_timeoutValue = ZERO_INIT;
	uint32_a_timeoutValue = (uint32_t) (SystemCoreClock / MICRO_SECOND_DIVIDER * uint32_a_periodInMicoSeconds) ;
	GPT_TIMER_A_LOAD_INTERVAL(str_g_timer.timerIndex,str_g_timer.timerSize,uint32_a_timeoutValue);
	GPT_ENABLE_TIMER_A(str_g_timer.timerIndex,str_g_timer.timerSize);
	return enu_a_funcRet;
}
/**
 * @brief Starts the GPT with the specified period in milliseconds.
 *
 * @param uint16_a_timeInMilliSeconds Period in milliseconds.
 * @return enu_GPTErrorStatus_t Error status after starting the timer.
 */
enu_GPTErrorStatus_t GPT_startTimerMilliSeconds(uint16_t uint16_a_timeInMilliSeconds)
{
	enu_GPTErrorStatus_t enu_a_funcRet = GPT_OK;
	uint32_t uint32_a_timeoutValue = ZERO_INIT;
	uint32_a_timeoutValue = (uint32_t) (SystemCoreClock / MILLI_SECOND_DIVIDER * uint16_a_timeInMilliSeconds) ;
	GPT_TIMER_A_LOAD_INTERVAL(str_g_timer.timerIndex,str_g_timer.timerSize,uint32_a_timeoutValue);
	GPT_ENABLE_TIMER_A(str_g_timer.timerIndex,str_g_timer.timerSize);
	return enu_a_funcRet;
}
 
/**
 * @brief Starts the GPT with the specified period in seconds.
 *
 * @param uint8_a_timeInSeconds Period in seconds.
 * @return enu_GPTErrorStatus_t Error status after starting the timer.
 */
enu_GPTErrorStatus_t GPT_startTimerSeconds(uint8_t uint8_a_timeInSeconds)
{
	enu_GPTErrorStatus_t enu_a_funcRet = GPT_OK;
	uint32_t uint32_a_tempValue = ZERO_INIT;
	if(uint8_a_timeInSeconds < MAX_ALLOW_SECONDS)
	{
		uint32_t uint32_a_tempValue = (uint32_t) (SystemCoreClock * uint8_a_timeInSeconds) ;
		GPT_TIMER_A_LOAD_INTERVAL(str_g_timer.timerIndex,str_g_timer.timerSize,uint32_a_tempValue);			
	}
	return enu_a_funcRet;
}
/**
 * @brief Stops the GPT.
 *
 * @return enu_GPTErrorStatus_t Error status after stopping the timer.
 */
enu_GPTErrorStatus_t GPT_stopTimer()
{
	enu_GPTErrorStatus_t enu_a_funcRet = GPT_OK;
	GPT_DISABLE_TIMER_A(str_g_timer.timerIndex,str_g_timer.timerSize);
	return enu_a_funcRet;
}
/**
 * @brief Gets the elapsed time since the GPT started.
 *
 * @param ptr_unit16_a_timeValue Pointer to store the elapsed time.
 * @return enu_GPTErrorStatus_t Error status after getting the elapsed time.
 */
enu_GPTErrorStatus_t GPT_getElapsedTime(uint16_t * ptr_unit16_a_timeValue)
{
	enu_GPTErrorStatus_t enu_a_funcRet = GPT_OK;
	if(ptr_unit16_a_timeValue == NULL)
	{
		enu_a_funcRet = GPT_NOK;
	}
	else
	{
		*ptr_unit16_a_timeValue = (uint16_t)(str_g_timer.timerPeriod * (ONE_INIT - ( GPT_TIMER_A_GET_VALUE(str_g_timer.timerIndex,str_g_timer.timerSize) / GPT_TIMER_A_GET_INTERVAL(str_g_timer.timerIndex,str_g_timer.timerSize))));

	}
	return enu_a_funcRet;
}

/**
 * @brief Gets the remaining time until the GPT timeout.
 *
 * @param ptr_unit16_a_timeValue Pointer to store the remaining time.
 * @return enu_GPTErrorStatus_t Error status after getting the remaining time.
 */
enu_GPTErrorStatus_t GPT_getRemainingTime(uint16_t * ptr_unit16_a_timeValue)
{
	enu_GPTErrorStatus_t enu_a_funcRet = GPT_OK;
	if(ptr_unit16_a_timeValue == NULL)
	{
		enu_a_funcRet = GPT_NOK;
	}
	else
	{
		*ptr_unit16_a_timeValue = (uint16_t)(str_g_timer.timerPeriod * ( GPT_TIMER_A_GET_VALUE(str_g_timer.timerIndex,str_g_timer.timerSize) / GPT_TIMER_A_GET_INTERVAL(str_g_timer.timerIndex,str_g_timer.timerSize)));
	}
	return enu_a_funcRet;
}
/**
 * @brief Enables the GPT interrupt.
 *
 * @return enu_GPTErrorStatus_t Error status after enabling the interrupt.
 */
enu_GPTErrorStatus_t GPT_enableInterrupt()
{
	enu_GPTErrorStatus_t enu_a_funcRet = GPT_OK;
	GPT_ENABLE_TIMERA_TIMEOUT_INTERRUPT(str_g_timer.timerIndex,str_g_timer.timerSize);
	arr_ptr_func_callbackTimeoutTimer[str_g_timer.timerSize][str_g_timer.timerIndex] = str_g_timer.ptr_func_timeoutInterruptHandler;
	NVIC_EnableIRQ(irqs[str_g_timer.timerSize][str_g_timer.timerIndex]);
	__enable_irq();
	return enu_a_funcRet;
}
/**
 * @brief Disables the GPT interrupt.
 * @return enu_GPTErrorStatus_t Error status after disabling the interrupt.
 */
enu_GPTErrorStatus_t GPT_disableInterrupt()
{
	enu_GPTErrorStatus_t enu_a_funcRet = GPT_OK;
	if(str_g_timer.interruptEnable == GPT_DISABLE_INTERRUPT)
	{
		GPT_DISABLE_TIMERA_TIMEOUT_INTERRUPT(str_g_timer.timerIndex,str_g_timer.timerSize);
		NVIC_DisableIRQ(irqs[str_g_timer.timerSize][str_g_timer.timerIndex]);
	}
	else
	{
		enu_a_funcRet = GPT_INVALID_INPUT;
	}	
	return enu_a_funcRet;
}
/**
 * @brief Passes callback functions for GPT timeout interrupts.
 *
 * @param ptr_func_timeout Pointer to the callback function.
 * @return enu_GPTErrorStatus_t Error status after passing the callback function.
 */
enu_GPTErrorStatus_t GPT_passCallBackFuncs(void * ptr_func_timeout)
{
	enu_GPTErrorStatus_t enu_a_funcRet = GPT_OK;
	str_g_timer.ptr_func_timeoutInterruptHandler = ptr_func_timeout;
	arr_ptr_func_callbackTimeoutTimer[str_g_timer.timerSize][str_g_timer.timerIndex] = ptr_func_timeout;
	return enu_a_funcRet;
}
void TIMER0A_Handler(void)
{
	if(arr_ptr_func_callbackTimeoutTimer[str_g_timer.timerSize][str_g_timer.timerIndex] != NULL && GPT_IS_TIMERA_TIMEOUT(str_g_timer.timerIndex,str_g_timer.timerSize))	
	{
		arr_ptr_func_callbackTimeoutTimer[str_g_timer.timerSize][str_g_timer.timerIndex]();
		GPT_CLEAR_TIMERA_TIMEOUT_FLAG();
	}
	else
	{
		
	}	
}
