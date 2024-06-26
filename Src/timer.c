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
#define OC_TOGGLE_CH1 ( ( 1U << 4 ) | ( 1U << 5 ) )
#define CCER_CC1E	( 1U << 0 )

#define GPIOA_EN	( 1U << 0 )
#define GPIOA_5		( 1U << 5 )

#define AFR5_TIM	( 1U << 20 )
#define AFR6_TIM	( 1U << 25 )
#define TIM3_EN 	( 1U << 1 )

#define CCER_CC1S	( 1U < 0 )


#define DIER_UI	( 1U << 0 )
// without clock conf default freq is 4Mhz,
// reference manual 6.2 Clocks.
// The MSI is used as system clock source after startup from Reset, configured at 4 MHz

void tim2_1hz_init(void){
	/* enable clock 6.4.19 APB1 peripheral clock enable register 1 (RCC_APB1ENR1) */
	RCC->APB1ENR1 |= TIM2_EN;

	// set prescaler
	TIM2->PSC = 400 - 1;// 4 000 000 / 400 == 10 000

	// set ARR
	TIM2->ARR = 10000 - 1;// 100000 / 10000 == 10Hz

	// clear counter
	TIM2->CNT = 0;

	// enable timer
	TIM2->CR1 = CR1_CEN;
}

void tim2_ch1_PA5_OC_init(void){
	//  configure PA5
	RCC->AHB2ENR |= GPIOA_EN;
	// set PA5 to alt func type
	// // 8.5.1 moder reference manual, bits 11:10, MODER5
	GPIOA->MODER &= ~( 1U << 10 );
	GPIOA->MODER |= ( 1U << 11 );

	// set PA5 alt func TIM2_CH1
	// 8.5.9 GPIO alternate function low register (GPIOx_AFRL
	// set AFSEL5, PA5 to AF1, AF1=0b0001
	GPIOA->AFR[ 0 ] |= AFR5_TIM;

	// base stuff
	/* enable clock 6.4.19 APB1 peripheral clock enable register 1 (RCC_APB1ENR1) */
	RCC->APB1ENR1 |= TIM2_EN;

	// set prescaler
	TIM2->PSC = 400 - 1;// 4 000 000 / 400 == 10 000

	// set ARR
//	TIM2->ARR = 1000 - 1;// 100000 / 1000 == 10Hz
	TIM2->ARR = 10000 - 1;// 100000 / 1000 == 1Hz

	{// base + OC stuff
		// set output compare toggle mode, enable OCM1 mode
		TIM2->CCMR1 = OC_TOGGLE_CH1;

		// enable ch1 in compare mode, 31.4.11 TIMx capture/compare enable register
		TIM2->CCER |= CCER_CC1E;
	}

	// clear counter
	TIM2->CNT = 0;

	// enable timer
	TIM2->CR1 = CR1_CEN;
}

void tim3_pa6_input_capture( void ){
	// enable clock access to GPIOA
	RCC->AHB2ENR |= GPIOA_EN;

	// set pa6 mode to alt func mode
	// 8.5.1 moder reference manual, PA6 bits 13:12, MODER6
	GPIOA->MODER &= ~( 1U << 12 );
	GPIOA->MODER |= ( 1U << 13 );

	// set PA6 alt func type to TIM3_CH1 - AF2
	GPIOA->AFR[ 0 ] |= AFR6_TIM;

	/* enable clock access to TIM3*/
	/* enable clock 6.4.19 APB1 peripheral clock enable register 1 (RCC_APB1ENR1) */
	RCC->APB1ENR1 |= TIM3_EN;

	// set prescaler
//	TIM3->PSC = 400 - 1;// 4 000 000 / 400 == 10 000
//	TIM3->ARR = 65536 - 1;

	// set CH1 capture to input mode
	TIM3->CCMR1 = CCER_CC1S;

	// set CH1 capture at rising edge
	TIM3->CCER |= CCER_CC1E;

	// enable TIM3
//	TIM3->CNT = 0;
	TIM3->CR1 = CR1_CEN;
}

void tim2_1hz_interrupt_init(void){
	/* enable clock 6.4.19 APB1 peripheral clock enable register 1 (RCC_APB1ENR1) */
	RCC->APB1ENR1 |= TIM2_EN;

	// set prescaler
	TIM2->PSC = 400 - 1;// 4 000 000 / 400 == 10 000

	// set ARR
	TIM2->ARR = 10000 - 1;// 100000 / 10000 == 10Hz

	// clear counter
	TIM2->CNT = 0;

	// enable timer
	TIM2->CR1 = CR1_CEN;

	// enable interrupt
	TIM2->DIER |= DIER_UI;
	NVIC_EnableIRQ( TIM2_IRQn );
}


