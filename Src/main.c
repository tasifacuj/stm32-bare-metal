#include "stm32l4xx.h"
#include "uart.h"
#include <stdio.h>

int main(void){
	uart2_tx_init();
	int idx = 0;

	printf( ">> bare-metal uart tx\r\n" );

	while( 1 ){
		printf( "Y %i\r\n", idx ++ );
		for( int i = 0; i < 100000; i ++ );
	}
	return 0;
}

