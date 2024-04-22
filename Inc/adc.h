/*
 * adc.h
 *
 *  Created on: Apr 9, 2024
 *      Author: tasifacij
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>


#define SR_EOC			( 1U << 2 )

void PC1_adc2_ch2_init(void);
uint32_t adc2_ch2_read( void );
void adc2_ch2_start_conversion( void );
void PC1_adc2_ch2_interrupt_init(void);
#endif /* ADC_H_ */
