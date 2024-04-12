#include "stm32l4xx.h"
#include "uart.h"
#include <stdio.h>
#include "adc.h"

#define GPIOA_EN	( 1U << 0 )
#define GPIOA_5		( 1U << 5 )
#define LED_PIN		GPIOA_5

uint32_t val;

int main(void){
	RCC->AHB2ENR |= GPIOA_EN;

	// set PA5 as output
	GPIOA->MODER |= ( 1U << 10 );
	GPIOA->MODER &= ~( 1U << 11 );

	uart2_tx_init();
	PC1_adc2_ch2_init();
	printf( ">> bare-metal adc\r\n" );


	while( 1 ){
		adc2_ch2_start_conversion();
		val = adc2_ch2_read();
		printf( "adc value %d\r\n",(int) val );
	}
	return 0;
}

