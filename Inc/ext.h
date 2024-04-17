/*
 * ext.h
 *
 *  Created on: Apr 17, 2024
 *      Author: t.shypytiak
 */

#ifndef EXT_H_
#define EXT_H_
#include "stm32l4xx.h"

#define LINE_13	( 1U << 13 )

void pc13_exti_init( void );

#endif /* EXT_H_ */
