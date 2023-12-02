
#ifndef GPT_PRIVATE_H_
#define GPT_PRIVATE_H_


#include "gpt_config.h"
#include "../../LIB/BIT_MATH.h"

#define ORDINARY_TIMER 	0
#define WIDE_TIMER 		1
#define MICRO_SECOND_DIVIDER  1000000
#define MILLI_SECOND_DIVIDER  1000
#define TIMER0_IRQ				19
#define TIMER1_IRQ				21
#define TIMER2_IRQ				23
#define TIMER3_IRQ				35
#define TIMER4_IRQ				70
#define TIMER5_IRQ				92
#define WTIMER0_IRQ				94
#define WTIMER1_IRQ				96
#define WTIMER2_IRQ				98
#define WTIMER3_IRQ				100
#define WTIMER4_IRQ				102
#define WTIMER5_IRQ				104

#define TIMER_TYPES_COUNT		2
#define TIMERS_COUNT			6
#define ZERO_INIT  				0
#define ONE_INIT  				1
#define MAX_ALLOW_SECONDS  		86		


#define TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE) ((TIMER_TYPE == ORDINARY_TIMER) ?  (0X40030000 + (TIMER_INDEX * 0X1000)): (0X40030000 + ((TIMER_INDEX <2) ? 0X1000 : 0X1A000)))
#define TIMER_CFG(TIMER_OFFSET)             		(*((volatile unsigned long *)(TIMER_OFFSET + 0x000)))
#define TIMER_TAMR(TIMER_OFFSET)			        (*((volatile unsigned long *)(TIMER_OFFSET + 0x004)))
#define TIMER_TBMR(TIMER_OFFSET)           			(*((volatile unsigned long *)(TIMER_OFFSET + 0x008)))
#define TIMER_CTL(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x00C)))
#define TIMER_SYNC(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x010)))
#define TIMER_IMR(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x018)))
#define TIMER_RIS(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x01C)))
#define TIMER_MIS(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x020)))
#define TIMER_ICR(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x024)))
#define TIMER_TAILR(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x028)))
#define TIMER_TBILR(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x02C)))
#define TIMER_TAMATCHR(TIMER_OFFSET)     			(*((volatile unsigned long *)(TIMER_OFFSET + 0x030)))
#define TIMER_TBMATCHR(TIMER_OFFSET)     			(*((volatile unsigned long *)(TIMER_OFFSET + 0x034)))
#define TIMER_TAPR(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x038)))
#define TIMER_TBPR(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x03C)))
#define TIMER_TAPMR(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x040)))
#define TIMER_TBPMR(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x044)))
#define TIMER_TAR(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x048)))
#define TIMER_TBR(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x04C)))
#define TIMER_TAV(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x050)))
#define TIMER_TBV(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x054)))
#define TIMER_RTCPD(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x058)))
#define TIMER_TAPS(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x05C)))
#define TIMER_TBPS(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x060)))
#define TIMER_TAPV(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x064)))
#define TIMER_TBPV(TIMER_OFFSET)     				(*((volatile unsigned long *)(TIMER_OFFSET + 0x068)))
#define TIMER_PP(TIMER_OFFSET)     					(*((volatile unsigned long *)(TIMER_OFFSET + 0xFC0)))
#define RCG_CTIMER     				                (*((volatile unsigned long *)(0x400FE604)))
#define RCG_CWTIMER     					        (*((volatile unsigned long *)(0x400FE65C)))	

/*--------------------------------------------------- config register ---------------------------------------------------------------*/
#define GPT_CONCATENATE_TIMER_CONFIG(TIMER_INDEX,TIMER_TYPE)  				(TIMER_CFG(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = 0X00)
#define GPT_INDIVIDUAL_TIMER_CONFIG(TIMER_INDEX,TIMER_TYPE)					((TIMER_CFG(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = 0X04)
#define GPT_REAL_TIME_CLOCK_CONFIG(TIMER_INDEX,TIMER_TYPE)					(TIMER_CFG(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = 0X01)
#define GPT_FRESH_CONFIG_REGISTER(TIMER_INDEX,TIMER_TYPE)					(TIMER_CFG(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = 0X00)

/*---------------------------------------------------------------------------------------------------------------------------------------*/

//FIRST CONFIGURE IN CONCATENATE MODE THEN WE WILL CONFIGURE THE INDVIDUAL

/*--------------------------------------------------- mode register ---------------------------------------------------------------*/

#define GPT_CONFIG_ONE_SHOT_TIMER_MODE(TIMER_INDEX,TIMER_TYPE)       do{ \
																		SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),0); \
																		CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),1); \
																	}while(0)
#define GPT_CONFIG_PERIODIC_TIMER_MODE(TIMER_INDEX,TIMER_TYPE)       do{ \
																		SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),1); \
																		CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),0); \
																	}while(0)

#define GPT_CONFIG_EDGE_COUNT_MODE(TIMER_INDEX,TIMER_TYPE)   (CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),2))
#define GPT_CONFIG_EDGE_TIME_MODE(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),2))
									
#define GPT_ENABLE_CCP_MODE(TIMER_INDEX,TIMER_TYPE)    (CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),3))
#define GPT_ENABLE_PWM_MODE(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),3))	

#define GPT_COUNTING_DOWN_MODE(TIMER_INDEX,TIMER_TYPE)       (CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),4))
#define GPT_COUNTING_UP_MODE(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),4))	

#define GPT_ENABLE_ON_MATCH_INTERRUPT(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),5))
#define GPT_DISABLE_ON_MATCH_INTERRUPT(TIMER_INDEX,TIMER_TYPE)    (CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),5))										

#define GPT_ENABLE_WAIT_ON_TRIGGER_FEATURE(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),6))
#define GPT_DISABLE_WAIT_ON_TRIGGER_FEATURE(TIMER_INDEX,TIMER_TYPE)    (CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),6))

#define GPT_ENABLE_SNAP_SHOT_MODE(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),7))
#define GPT_DISABLE_SNAP_SHOT_MODE(TIMER_INDEX,TIMER_TYPE)    (CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),7))

#define GPT_RELOAD_ON_NEXT_TIMEOUT(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),8))
#define GPT_RELOAD_ON_NEXT_CLOCK_CYCLE(TIMER_INDEX,TIMER_TYPE)    (CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),8))	

#define GPT_RELOAD_MACTH_REGISTER_ON_NEXT_TIMEOUT(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),10))
#define GPT_RELOAD_MACTH_REGISTER_ON_NEXT_CLOCK_CYCLE(TIMER_INDEX,TIMER_TYPE)    (CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),10))		

#define GPT_ENABLE_PWM_INTERRUPT(TIMER_INDEX,TIMER_TYPE)     (SET_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),9))
#define GPT_DISABLE_PWM_INTERRUPT(TIMER_INDEX,TIMER_TYPE)    (CLEAR_BIT(TIMER_TAMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),9))	

/*---------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------- control register -------------------------------------------------------------------*/


#define GPT_ENABLE_TIMER_A(TIMER_INDEX,TIMER_TYPE)       (SET_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),0))
#define GPT_DISABLE_TIMER_A(TIMER_INDEX,TIMER_TYPE)      (CLEAR_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),0))


#define GPT_TIMER_A_FROZE_COUNTING_WHILE_DEBUG(TIMER_INDEX,TIMER_TYPE)       (SET_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),1))
#define GPT_TIMER_A_COUNTING_WHILE_DEBUG(TIMER_INDEX,TIMER_TYPE)             (CLEAR_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),1))


#define GPT_CONFIG_TIMERA_EVENT_MODE_POSITIVE_EDGE(TIMER_INDEX,TIMER_TYPE)  do{ \
										CLEAR_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),2); \
										CLEAR_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),3); \
									}while(0)

#define GPT_CONFIG_TIMERA_EVENT_MODE_NEGATIVE_EDGE(TIMER_INDEX,TIMER_TYPE)  do{ \
										SET_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),2); \
										CLEAR_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),3); \
									}while(0)

#define GPT_CONFIG_TIMERA_EVENT_MODE_BOTH_EDGES(TIMER_INDEX,TIMER_TYPE)  do{ \
										SET_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),2); \
										SET_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),3); \
									}while(0)

#define GPT_RTC_FROZE_COUNTING_WHILE_DEBUG(TIMER_INDEX,TIMER_TYPE)       (SET_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),4))
#define GPT_RTC_COUNTING_WHILE_DEBUG(TIMER_INDEX,TIMER_TYPE)             (CLEAR_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),4))	
									
#define GPT_ENABLE_TIMERA_TRIGGER_ADC(TIMER_INDEX,TIMER_TYPE)       (SET_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),5))
#define GPT_DISABLE_TIMERA_TRIGGER_ADC(TIMER_INDEX,TIMER_TYPE)      (CLEAR_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),5))
									
#define GPT_INVERT_PWM_OUTPUT(TIMER_INDEX,TIMER_TYPE)       (SET_BIT(TIMER_CTL(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),6))

									
/*---------------------------------------------------------------------------------------------------------------------------------------*/
									
/*--------------------------------------------------- INTERRUPT REGISTERS -------------------------------------------------------------------*/

#define GPT_ENABLE_TIMERA_TIMEOUT_INTERRUPT(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),0))
#define GPT_DISABLE_TIMERA_TIMEOUT_INTERRUPT(TIMER_INDEX,TIMER_TYPE)   (CLEAR_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),0))	

#define GPT_ENABLE_TIMERA_CAPTURE_MATCH_INTERRUPT(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),1))
#define GPT_DISABLE_TIMERA_CAPTURE_MATCH_INTERRUPT(TIMER_INDEX,TIMER_TYPE)   (CLEAR_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),1))

#define GPT_ENABLE_TIMERA_CAPTURE_EVENT_INTERRUPT(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),2))
#define GPT_DISABLE_TIMERA_CAPTURE_EVENT_INTERRUPT(TIMER_INDEX,TIMER_TYPE)   (CLEAR_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),2))

#define GPT_ENABLE_TIMER_RTC_INTERRUPT(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),3))
#define GPT_DISABLE_TIMER_RTC_INTERRUPT(TIMER_INDEX,TIMER_TYPE)   (CLEAR_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),3))


#define GPT_ENABLE_TIMERA_MATCH_INTERRUPT(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),4))
#define GPT_DISABLE_TIMERA_MATCH_INTERRUPT(TIMER_INDEX,TIMER_TYPE)   (CLEAR_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),4))


#define GPT_ENABLE_WRITE_UPDATE_ERROR_INTERRUPT(TIMER_INDEX,TIMER_TYPE)    (SET_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),16))
#define GPT_DISABLE_WRITE_UPDATE_ERROR_INTERRUPT(TIMER_INDEX,TIMER_TYPE)   (CLEAR_BIT(TIMER_IMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),16))


#define GPT_IS_TIMERA_TIMEOUT(TIMER_INDEX,TIMER_TYPE)    				(GET_BIT(TIMER_RIS(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),0) == 1)
#define GPT_IS_TIMERA_CAPTURE_MATCHING(TIMER_INDEX,TIMER_TYPE)    		(GET_BIT(TIMER_RIS(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),1) == 1)
#define GPT_IS_TIMERA_CAPTURE_EVENT_OCCURED(TIMER_INDEX,TIMER_TYPE)    	(GET_BIT(TIMER_RIS(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),2) == 1)
#define GPT_IS_RTC_EVENT_OCCURED(TIMER_INDEX,TIMER_TYPE)    			(GET_BIT(TIMER_RIS(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),3) == 1)
#define GPT_IS_TIMERA_MATCHING(TIMER_INDEX,TIMER_TYPE)    				(GET_BIT(TIMER_RIS(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),4) == 1)
#define GPT_IS_WRITE_UPDATE_ERROR_MATCHING(TIMER_INDEX,TIMER_TYPE)    	(GET_BIT(TIMER_RIS(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),16) == 1)

#define GPT_CLEAR_TIMERA_TIMEOUT_FLAG()                					(SET_BIT(TIMER_ICR(TIMER_OFFSET(0,0)),0))
#define GPT_CLEAR_TIMERA_TIMEOUT_INTERRUPT_FLAG(TIMER_INDEX,TIMER_TYPE)    					(SET_BIT(TIMER_ICR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),0))
#define GPT_CLEAR_TIMERA_CAPTURE_MATCHING_INTERRUPT_FLAG(TIMER_INDEX,TIMER_TYPE)    		(SET_BIT(TIMER_ICR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),1))
#define GPT_CLEAR_TIMERA_CAPTURE_EVENT_INTERRUPT_FLAG(TIMER_INDEX,TIMER_TYPE)    			(SET_BIT(TIMER_ICR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),2))
#define GPT_CLEAR_RTC_EVENT_INTERRUPT_FLAG(TIMER_INDEX,TIMER_TYPE)    						(SET_BIT(TIMER_ICR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),3))
#define GPT_CLEAR_TIMERA_MATCHING_INTERRUPT_FLAG(TIMER_INDEX,TIMER_TYPE)    				(SET_BIT(TIMER_ICR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),4))
#define GPT_CLEAR_WRITE_UPDATE_ERROR_MATCHING_INTERRUPT_FLAG(TIMER_INDEX,TIMER_TYPE)    	(SET_BIT(TIMER_ICR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)),16))

									
/*---------------------------------------------------------------------------------------------------------------------------------------*/

#define GPT_TIMER_A_LOAD_INTERVAL(TIMER_INDEX,TIMER_TYPE,VALUE)               (TIMER_TAILR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = VALUE)
#define GPT_TIMER_B_LOAD_INTERVAL(TIMER_INDEX,TIMER_TYPE,VALUE)               (TIMER_TBILR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = VALUE)

#define GPT_TIMER_A_GET_INTERVAL(TIMER_INDEX,TIMER_TYPE)               (TIMER_TAILR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)))

#define GPT_TIMER_A_GET_VALUE(TIMER_INDEX,TIMER_TYPE)               (TIMER_TAR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)))

#define GPT_TIMER_A_LOAD_MATCH_VALUE(TIMER_INDEX,TIMER_TYPE,VALUE)               (TIMER_TAMATCHR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = VALUE)
#define GPT_TIMER_B_LOAD_MATCH_VALUE(TIMER_INDEX,TIMER_TYPE,VALUE)               (TIMER_TBMATCHR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = VALUE)


#define GPT_LOAD_PRESCALER_FOR_ORDINARY_TIMER(TIMER_INDEX,TIMER_TYPE,VALUE)               	(TIMER_TAPR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = VALUE)
#define GPT_LOAD_PRESCALER_FOR_WIDE_TIMER(TIMER_INDEX,TIMER_TYPE,VALUE)         			(TIMER_TAPR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = VALUE)

#define GPT_LOAD_MATCH_PRESCALER_FOR_ORDINARY_TIMER(TIMER_INDEX,TIMER_TYPE,VALUE)               (TIMER_TAPMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = VALUE)
#define GPT_LOAD_MATCH_PRESCALER_FOR_WIDE_TIMER(TIMER_INDEX,TIMER_TYPE,VALUE)         			(TIMER_TAPMR(TIMER_OFFSET(TIMER_INDEX,TIMER_TYPE)) = VALUE)
 
 #endif /*GPT_PRIVATE_H_*/