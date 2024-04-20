#include "stm32l4xx.h"
#include "uart.h"
#include <stdio.h>
#include "adc.h"
#include "systick.h"
#include "timer.h"
#include "ext.h"


#define GPIOA_EN	( 1U << 0 )
#define GPIOA_5		( 1U << 5 )
#define LED_PIN		GPIOA_5

static void exti_callback( void );

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

static void test_exti_interrupt( void ){
	// PA5 led
	RCC->AHB2ENR |= GPIOA_EN;

   // set PA5 as output
   GPIOA->MODER |= ( 1U << 10 );
   GPIOA->MODER &= ~( 1U << 11 );
   uart2_tx_init();
   pc13_exti_init();

	while( 1 ){

	}

}

#endif

static void init_led_PA5(void){
	// PA5 led
	RCC->AHB2ENR |= GPIOA_EN;

	// set PA5 as output
	GPIOA->MODER |= ( 1U << 10 );
	GPIOA->MODER &= ~( 1U << 11 );
}

int main(void){
	init_led_PA5();
	uart2_rxtx_interrupt_init();

	while( 1 ){

	}

	return 0;
}


void EXTI15_10_IRQHandler( void ){
	if( ( EXTI->PR1 & LINE_13 ) != 0 ) {
		// clear pr flag
		EXTI->PR1 |= LINE_13;
		// do smth
		exti_callback();
	}
}

void USART2_IRQHandler( void ){
	if( USART2->ISR & ISR_RXNE){
		char ch = USART2->RDR;

		if( ch == '1' )
			GPIOA->ODR |= LED_PIN;
		else
			GPIOA->ODR &= ~LED_PIN;
	}
}


static void exti_callback( void ){
	printf( ">> pc13\r\n" );
	GPIOA->ODR ^= LED_PIN;
}
