
#ifndef GPT_INTERFACE_H_
#define GPT_INTERFACE_H_

#include "gpt_private.h"

typedef enum {
	GPT_ORDINARY_TIMER =0 ,
	GPT_WIDE_TIMER 
} enu_timerSize_t;

typedef enum {
	GPT_OK =0 ,
	GPT_NOK   ,
	GPT_INVALID_INPUT
} enu_GPTErrorStatus_t;
typedef enum {
	GPT_TIMER_0 =0 ,
	GPT_TIMER_1    ,
	GPT_TIMER_2    ,
	GPT_TIMER_3    ,
	GPT_TIMER_4    ,
	GPT_TIMER_5    ,
} enu_timerIndex_t;

typedef enum {
	GPT_ENABLE_INTERRUPT =0 ,
	GPT_DISABLE_INTERRUPT 
} enu_GPTInterrupt_t;

typedef enum {
	GPT_ON_SHOT_MODE =0 ,
	GPT_PERIODIC_MODE   ,       
} enu_timerMode_t;
typedef struct {
	enu_timerIndex_t 	timerIndex;
	enu_timerSize_t 	timerSize;
	enu_timerMode_t		timerMode; 
	enu_GPTInterrupt_t  interruptEnable;
	uint8_t				interruptProirity;
	uint32_t 			timerPeriod;
	void ( * ptr_func_timeoutInterruptHandler)();
	
}str_GPT_t;
extern str_GPT_t str_g_timer;

// Function prototypes

/**
 * @brief Initializes the General-Purpose Timer (GPT) module based on the provided configuration.
 *
 * @return enu_GPTErrorStatus_t Error status after initialization.
 */
enu_GPTErrorStatus_t GPT_init();

/**
 * @brief Starts the GPT with the specified period in microseconds.
 *
 * @param uint32_a_periodInMicoSeconds Period in microseconds.
 * @return enu_GPTErrorStatus_t Error status after starting the timer.
 */
enu_GPTErrorStatus_t GPT_startTimerMicroSeconds(uint32_t uint32_a_periodInMicoSeconds);

/**
 * @brief Starts the GPT with the specified period in milliseconds.
 *
 * @param uint16_a_timeInMilliSeconds Period in milliseconds.
 * @return enu_GPTErrorStatus_t Error status after starting the timer.
 */
enu_GPTErrorStatus_t GPT_startTimerMilliSeconds(uint16_t uint16_a_timeInMilliSeconds);

/**
 * @brief Starts the GPT with the specified period in seconds.
 *
 * @param uint8_a_timeInSeconds Period in seconds.
 * @return enu_GPTErrorStatus_t Error status after starting the timer.
 */
enu_GPTErrorStatus_t GPT_startTimerSeconds(uint8_t uint8_a_timeInSeconds);

/**
 * @brief Stops the GPT.
 *
 * @return enu_GPTErrorStatus_t Error status after stopping the timer.
 */
enu_GPTErrorStatus_t GPT_stopTimer();

/**
 * @brief Gets the elapsed time since the GPT started.
 *
 * @param ptr_unit16_a_timeValue Pointer to store the elapsed time.
 * @return enu_GPTErrorStatus_t Error status after getting the elapsed time.
 */
enu_GPTErrorStatus_t GPT_getElapsedTime(uint16_t * ptr_unit16_a_timeValue);

/**
 * @brief Gets the remaining time until the GPT timeout.
 *
 * @param ptr_unit16_a_timeValue Pointer to store the remaining time.
 * @return enu_GPTErrorStatus_t Error status after getting the remaining time.
 */
enu_GPTErrorStatus_t GPT_getRemainingTime(uint16_t * ptr_unit16_a_timeValue);

/**
 * @brief Enables the GPT interrupt.
 *
 * @return enu_GPTErrorStatus_t Error status after enabling the interrupt.
 */
enu_GPTErrorStatus_t GPT_enableInterrupt();

/**
 * @brief Disables the GPT interrupt.
 * @return enu_GPTErrorStatus_t Error status after disabling the interrupt.
 */
enu_GPTErrorStatus_t GPT_disableInterrupt();

/**
 * @brief Passes callback functions for GPT timeout interrupts.
 *
 * @param ptr_func_timeout Pointer to the callback function.
 * @return enu_GPTErrorStatus_t Error status after passing the callback function.
 */
enu_GPTErrorStatus_t GPT_passCallBackFuncs(void * ptr_func_timeout);

#endif /*GPT_INTERFACE_H_*/