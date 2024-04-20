/*
 * ext.c
 *
 *  Created on: Apr 17, 2024
 *      Author: t.shypytiak
 */
#include "ext.h"

#define GPIOC_EN			( 1U << 2 )/*6.4.17 referrence manual*/
#define SYSCFG_EN			( 1U << 0 )//6.4.21 APB2 peripheral clock enable register
#define MR13 				( 1U << 13 )
#define FT13				( 1U << 13 )

void pc13_exti_init( void ){
	// disable global interrupt
	__disable_irq();

	// enable clock access for GPIOC
	RCC->AHB2ENR |= GPIOC_EN;

	// enable clock access to SYSCFG
	RCC->APB2ENR |= SYSCFG_EN;

	// set PORT C as input func type
	GPIOC->MODER &= ( 1U << 26 );
	GPIOC->MODER &= ( 1U << 27 );

	// select PORT C for EXTI13
	SYSCFG->EXTICR[ 3 ] |= ( 1U << 5 );

	// Unmask EXTI13
	EXTI->IMR1 |= MR13;

	// select falling edge trigger
	EXTI->FTSR1 |= FT13;

	// enable EXTI13 line in NVIC
	NVIC_EnableIRQ( EXTI15_10_IRQn );

	// enable global interrupt
	__enable_irq();
}

