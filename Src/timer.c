/*
 * timer.c
 *
 *  Created on: Apr 16, 2024
 *      Author: t.shypytiak
 */
#include "stm32l4xx.h"
#include "timer.h"

#define TIM2_EN ( 1U << 0 )
#define CR1_CEN	TIM2_EN

// without clock conf default freq is 4Mhz,
// reference manual 6.2 Clocks.
// The MSI is used as system clock source after startup from Reset, configured at 4 MHz

void tim2_1hz_init(void){
	/* enable clock 6.4.19 APB1 peripheral clock enable register 1 (RCC_APB1ENR1) */
	RCC->APB1ENR1 |= TIM2_EN;

	// set prescaler
	TIM2->PSC = 400 - 1;// 4 000 000 / 400 == 10 000

	// set ARR
	TIM2->ARR = 10000 - 1;// 100000 / 10000 == 1Hz

	// clear counter
	TIM2->CNT = 0;

	// enable timer
	TIM2->CR1 = CR1_CEN;
}
