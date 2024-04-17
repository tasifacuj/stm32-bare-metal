#include "stm32l4xx.h"
#include "uart.h"
#include <stdio.h>
#include "adc.h"
#include "systick.h"
#include "timer.h"

#define GPIOA_EN	( 1U << 0 )
#define GPIOA_5		( 1U << 5 )
#define LED_PIN		GPIOA_5


#if 0
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

static void test_systick_delay( void ){
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
}

static void test_timer_delay(){
	// PA5 led
	   RCC->AHB2ENR |= GPIOA_EN;

	   // set PA5 as output
	   GPIOA->MODER |= ( 1U << 10 );
	   GPIOA->MODER &= ~( 1U << 11 );
	   uart2_tx_init();
	   tim2_1hz_init();

	   while( 1 ){
		   // wait for update event
		   while( ( TIM2->SR & SR_UIF ) == 0 );

		   // clear update event
		   TIM2->SR &= ~SR_UIF;

		   GPIOA->ODR ^= LED_PIN;
		   printf( ">>blink tim2\r\n" );
	   }
}
#endif


int timestamp = 0;

int main(void){

//	uart2_tx_init();
	tim3_pa6_input_capture();// connect PA5 and PA6
   tim2_ch1_PA5_OC_init();



   while( 1 ){
	   // wait for capture event
	   while( ( TIM3->SR & SR_CC1IF ) == 0 );

	   // read value
	   timestamp = TIM3->CCR1;
   }

	return 0;
}

