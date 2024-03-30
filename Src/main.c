#include "stm32l4xx.h"

#define GPIOAEN		(1u << 0)
#define GPIOC_EN	( 1u << 2 )

#define PIN5 		( 1u << 5 )
#define PIN13		( 1u << 13 )
#define LED_PIN		PIN5
#define BTN_PIN		PIN13



int main(void){
	// turn on clocking for gpioa and gpioc
	RCC->AHB2ENR |= GPIOAEN;
	RCC->AHB2ENR |= GPIOC_EN;

	// set PA5 as output
	GPIOA->MODER |= ( 1U << 10 );
	GPIOA->MODER &= ~( 1U << 11 );

	// set PC13 as input pin
	GPIOC->MODER &= ~( 1u << 26 );
	GPIOC->MODER &= ~( 1u << 27 );

	while( 1 ){
		if( 0 == ( GPIOC->IDR & BTN_PIN ) )
			GPIOA->BSRR = LED_PIN;
		else
			GPIOA->BSRR = ( 1U << 21 );
	}
	return 0;
}
