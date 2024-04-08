#include "stm32l4xx.h"
#include "uart.h"
#include <stdio.h>

#define GPIOA_EN	( 1U << 0 )
#define GPIOA_5		( 1U << 5 )
#define LED_PIN		GPIOA_5

char key;

int main(void){
	uart2_rxtx_init();
	int idx = 0;

	printf( ">> bare-metal uart tx\r\n" );

	while( 1 ){
		key = uart2_read();
	}
	return 0;
}

