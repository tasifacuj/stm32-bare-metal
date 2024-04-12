#include "stm32l4xx.h"
#include "uart.h"
#include <stdio.h>
#include "adc.h"
#include "systick.h"

#define GPIOA_EN	( 1U << 0 )
#define GPIOA_5		( 1U << 5 )
#define LED_PIN		GPIOA_5



static void test_adc2_ch2(){
	uart2_tx_init();
	uint32_t val;

	PC1_adc2_ch2_init();
	printf( ">> bare-metal adc\r\n" );

	while( 1 ){
		adc2_ch2_start_conversion();
		val = adc2_ch2_read();
		printf( "adc value %d\r\n",(int) val );
	}
}

int main(void){
// PA5 led
   RCC->AHB2ENR |= GPIOA_EN;

   // set PA5 as output
   GPIOA->MODER |= ( 1U << 10 );
   GPIOA->MODER &= ~( 1U << 11 );
   uart2_tx_init();

   while( 1 ){
	   systick_delay_ms( 500 * 2 );
	   GPIOA->ODR ^= LED_PIN;
	   printf( ">>blink\r\n" );
   }

	return 0;
}

