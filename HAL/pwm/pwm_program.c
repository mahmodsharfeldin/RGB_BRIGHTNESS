#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "TM4C123.h"
#include "../../MCAL/gpio/gpio.h"
#include "../../MCAL/gpt/gpt_interface.h"
#include "pwm_interface.h"
#include "../led/led.h"
// Constants for initialization
#define ZERO_INIT                 0
#define ONE_INIT                  1
#define ZERO_PERCENT              0
#define ONE_HUNDRED_PERCENT       100

// Global variables
extern str_pwm_t str_g_pwm;
static uint8_t uint8_gs_handlerFlag = ONE_INIT;

// Handler function for PWM
static void PWM_handler()
{
    if (uint8_gs_handlerFlag)
    {
        uint8_gs_handlerFlag = ZERO_INIT;
        GPIO_setPinStatus(str_g_pwm.pwm_pin, GPIO_LOW);
        GPT_startTimerMilliSeconds(((ONE_HUNDRED_PERCENT - str_g_pwm.duty_cycle) * str_g_pwm.period_in_ms) / ONE_HUNDRED_PERCENT);
    }
    else
    {
        uint8_gs_handlerFlag = ONE_INIT;
        GPIO_setPinStatus(str_g_pwm.pwm_pin, GPIO_HIGH);
        GPT_startTimerMilliSeconds((str_g_pwm.duty_cycle * str_g_pwm.period_in_ms) / ONE_HUNDRED_PERCENT);
    }
}

/**
 * @brief Initializes the PWM module.
 *
 * @return enu_PWMErrorStatus_t Error status after initialization.
 */
enu_PWMErrorStatus_t PWM_init()
{
    enu_PWMErrorStatus_t enu_retFunc = PWM_OK;

    enu_retFunc |= GPIO_init(str_g_pwm.pwm_pin);
    enu_retFunc |= GPT_init();
    enu_retFunc |= GPT_passCallBackFuncs(PWM_handler);
    enu_retFunc |= GPT_enableInterrupt();

    return enu_retFunc;
}

/**
 * @brief Sets the duty cycle for PWM 
 *
 * @param uint8_a_duty Duty cycle value in percentage.
 * @return enu_PWMErrorStatus_t Error status after setting the duty cycle.
 */
enu_PWMErrorStatus_t PWM_setDutyCycle(uint8_t uint8_a_duty)
{
    enu_PWMErrorStatus_t enu_retFunc = PWM_OK;

    if (uint8_a_duty <= ONE_HUNDRED_PERCENT)
    {
        if (uint8_a_duty == ZERO_PERCENT)
        {
            GPT_stopTimer();
            GPIO_outputLow(str_g_pwm.pwm_pin);
        }
        else if (uint8_a_duty == ONE_HUNDRED_PERCENT)
        {
            GPT_stopTimer();
            GPIO_outputHigh(str_g_pwm.pwm_pin);
        }
        else
        {
            str_g_pwm.duty_cycle = uint8_a_duty;
            GPT_startTimerMilliSeconds((str_g_pwm.duty_cycle * str_g_pwm.period_in_ms) / ONE_HUNDRED_PERCENT);
            uint8_gs_handlerFlag = ONE_INIT;
        }
    }
    else
    {
        enu_retFunc = PWM_INVALID_INPUT;
    }

    return enu_retFunc;
}





