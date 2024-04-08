#include "stm32l4xx.h"
#include "uart.h"
#include <stdio.h>

#define GPIOA_EN	( 1U << 0 )
#define GPIOA_5		( 1U << 5 )
#define LED_PIN		GPIOA_5

char key;

int main(void){
	RCC->AHB2ENR |= GPIOA_EN;

	// set PA5 as output
	GPIOA->MODER |= ( 1U << 10 );
	GPIOA->MODER &= ~( 1U << 11 );

	uart2_rxtx_init();

	printf( ">> bare-metal uart tx\r\n" );

	while( 1 ){
		key = uart2_read();
		printf( ">> received %c\r\n", key );

		if( key == '1' )
			GPIOA->ODR |= LED_PIN;
		else
			GPIOA->ODR &= ~LED_PIN;
	}
	return 0;
}

