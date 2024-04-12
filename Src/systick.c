/*
 * systick.c
 *
 *  Created on: Apr 12, 2024
 *      Author: t.shypytiak
 */
#include "systick.h"
#include "stm32l4xx.h"

#define SYSTICK_LOAD_VALUE	4000
#define CTRL_ENABLE			( 1U << 0 )
#define CTRL_CLKSRC			( 1U << 2 )
#define CTRL_COUNTFLAG		( 1U << 16 )


void systick_delay_ms( int ms ){
	/*** configure systick **/
	SysTick->LOAD = SYSTICK_LOAD_VALUE;
	// clear systick
	SysTick->VAL = 0;
	//	enable systick and select clk source
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for( int i = 0; i < ms; i ++ ){
		// wait until countflag is set
		while( ( SysTick->CTRL & CTRL_COUNTFLAG ) == 0 );
	}

	SysTick->CTRL = 0;
}
