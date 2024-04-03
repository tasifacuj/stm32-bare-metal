#include "stm32l4xx.h"

#define GPIOAEN			( 1u << 0 )
#define USART1_EN		( 1U << 14 )
#define SYS_FREQ 		4000000
#define APB2_CLK 		SYS_FREQ
#define UART_BAUDRATE	115200
#define CR1_TE			( 1U << 3 )
#define CR1_UE			( 1U << 0 )
#define SR_TXE			( 1U << 7 )

// forward declarations
static uint16_t uart_compute_div( uint32_t periphClock, uint32_t baud_rate );
static void uart_set_baudrate( USART_TypeDef* usartx, uint32_t clk, uint32_t baudrate );
void uart1_tx_init( void );
static void uart1_write( int ch );

int main(void){
	uart1_tx_init();

	while( 1 ){
		uart1_write( 'Y' );
	}
	return 0;
}

void uart1_tx_init( void ){
	/* configure gpio pin */

	// enable clock access to gpioa
	RCC->AHB2ENR |= GPIOAEN;

	// set pa9 to alternate mode
	GPIOA->MODER &= ~( 1U << 18 );
	GPIOA->MODER |= ( 1U << 19 );

	// set pa9 type as uart tx(AF7)
	GPIOA->AFR[ 1 ] |= ( 1U << 4 );
	GPIOA->AFR[ 1 ] |= ( 1U << 5 );
	GPIOA->AFR[ 1 ] |= ( 1U << 6 );
	GPIOA->AFR[ 1 ] &= ~( 1U << 7 );

	/* configure USART */
	// enable clock access to uart1
	RCC->APB2ENR |= USART1_EN;

	// set baudrate
	uart_set_baudrate( USART1, APB2_CLK, UART_BAUDRATE );
	// set transfer dir
	USART1->CR1 = CR1_TE;
	// enable uart
	USART1->CR1 |= CR1_UE;
}

static void uart1_write( int ch ){
	while( !( USART1->ISR & SR_TXE ) );
	USART1->TDR = ( ch & 0xff );
}

static void uart_set_baudrate( USART_TypeDef* usartx, uint32_t clk, uint32_t baudrate ){
	usartx->BRR = uart_compute_div(clk, baudrate);
}

static uint16_t uart_compute_div( uint32_t periphClock, uint32_t baud_rate ){
	return ( periphClock + ( baud_rate / 2U ) ) / baud_rate;
}



