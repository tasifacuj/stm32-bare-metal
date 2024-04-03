#include "stm32l4xx.h"

#include <stdio.h>

#define GPIOA_EN		( 1u << 0 )
#define USART2_EN		( 1u << 17 )
#define SYS_FRQ 		4000000// without clock conf default freq is 4Mhz, reference manual 6.2 Clocks, The MSI is used as system clock source after startup from Reset, configured at 4 MHz
#define APB1_CLK		SYS_FRQ
#define UART_BAUDRATE	115200
#define CR1_TE			( 1U << 3 )
#define CR1_UE			( 1U << 0 )
#define ISR_TXE			( 1U << 7 )

// forward declarations
static uint16_t uart2_compute_uart_div( uint32_t clk, uint32_t baud_rate );
static void uart2_set_baudrate( USART_TypeDef* uartx, uint32_t clk, uint32_t baud_rate );
static void uart2_tx_init( void );
static void uart2_write( int data );

int __io_putchar( int ch ){
	uart2_write( ch );
	return ch;
}

int main(void){
	uart2_tx_init();
	uint32_t idx = 0;

	printf( ">> bare-metal uart tx\r\n" );

	while( 1 ){
		printf( "Y %i\r\n", idx ++ );
		for( int i = 0; i < 50000; i ++ );
	}
	return 0;
}


static void uart2_tx_init( void ){
	/* configure uart gpio pin */
	// 1. enablr clock access to gpioa AHB2
	RCC->AHB2ENR |=  GPIOA_EN;

	// 2. set PA2 mode to alternate func mode, GPIOx_MODER, bits 4,5
	GPIOA->MODER &= ~( 1u << 4 );
	GPIOA->MODER |= ( 1u << 5 );

	// 3. set PA2 alternate func type to UART_TX(AF7)
	GPIOA->AFR[ 0 ] |= ( 1U << 8 );
	GPIOA->AFR[ 0 ] |= ( 1U << 9 );
	GPIOA->AFR[ 0 ] |= ( 1U << 10 );
	GPIOA->AFR[ 0 ] &= ~( 1U << 11 );

	/*  configure uart*/
	// 1. enable clock access to uart 2
	RCC->APB1ENR1 |= USART2_EN;

	// 2. configure baudrate
	uart2_set_baudrate( USART2, APB1_CLK, UART_BAUDRATE );

	// 3. configure transfer direction
	USART2->CR1 = CR1_TE;

	// 4. enable uart module
	USART2->CR1 |= CR1_UE;
}

static void uart2_set_baudrate( USART_TypeDef* uartx, uint32_t clk, uint32_t baud_rate ){
	uartx->BRR = uart2_compute_uart_div(clk, baud_rate);
}

static uint16_t uart2_compute_uart_div( uint32_t clk, uint32_t baud_rate ){
	return ( ( clk + ( baud_rate / 2U ) ) / baud_rate );
}

static void uart2_write( int data ){
	// (((__HANDLE__)->Instance->ISR & (__FLAG__)) == (__FLAG__))
	while( ( USART2->ISR & ISR_TXE )  == 0 );

	USART2->TDR = data;
}


