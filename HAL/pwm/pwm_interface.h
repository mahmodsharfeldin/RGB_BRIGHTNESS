#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

#include "../../MCAL/gpio/gpio.h"
// Duty cycle values
#define DUTY_0    0
#define DUTY_30   30
#define DUTY_60   60
#define DUTY_90   90

// Enumeration for PWM error status
typedef enum {
    PWM_OK = 0,
    PWM_NOK,
    PWM_INVALID_INPUT
} enu_PWMErrorStatus_t;

// Enumeration for PWM timers
typedef enum {
    PWM_TIMER_0,
    PWM_TIMER_1,
    PWM_TIMER_2,
    PWM_TIMER_3,
    PWM_TIMER_4,
    PWM_TIMER_5
} enu_PWMTimer_t;

// Structure to hold PWM configuration
typedef struct {
    uint8_t             duty_cycle;
    uint16_t            period_in_ms;
    str_pinConfig_t*    pwm_pin;
    enu_PWMTimer_t*     pwm_timer;
} str_pwm_t;

// Function prototypes
/**
 * @brief Initializes the PWM module.
 *
 * @return enu_PWMErrorStatus_t Error status after initialization.
 */
enu_PWMErrorStatus_t PWM_init();
/**
 * @brief Sets the duty cycle for PWM.
 *
 * @param uint8_a_duty Duty cycle value in percentage.
 * @return enu_PWMErrorStatus_t Error status after setting the duty cycle.
 */
enu_PWMErrorStatus_t PWM_setDutyCycle(uint8_t uint8_a_duty);
#endif /*PWM_INTERFACE_H_*/