#include "stm32l4xx.h"

#define GPIOAEN	(1u << 0)
#define PIN5 	( 1u << 5 )
#define LED_PIN	PIN5


int main(void){
	RCC->AHB2ENR |= GPIOAEN;
	GPIOA->MODER |= ( 1U << 10 );
	GPIOA->MODER &= ~( 1U << 11 );

	while( 1 ){
		GPIOA-> ODR ^= LED_PIN;
		for( int i = 0; i < 10000; i ++ );
	}
	return 0;
}
