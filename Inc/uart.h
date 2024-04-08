/*
 * uart.h
 *
 *  Created on: Apr 8, 2024
 *      Author: tasifacij
 */

#ifndef UART_H_
#define UART_H_

void uart2_tx_init( void );
void uart2_rxtx_init( void );
void uart2_write( int data );
char uart2_read( void );

#endif /* UART_H_ */
