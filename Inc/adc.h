/*
 * adc.h
 *
 *  Created on: Apr 9, 2024
 *      Author: tasifacij
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void PC0_adc1_ch1_init(void);
uint32_t adc1_ch1_read( void );
void adc1_ch1_start_conversion( void );

#endif /* ADC_H_ */
