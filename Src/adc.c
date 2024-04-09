/*
 * adc.c
 *
 *  Created on: Apr 9, 2024
 *      Author: tasifacij
 */
#include "adc.h"
#include "stm32l4xx.h"

#define ADC_EN			( 1U << 13 )
#define GPIOC_EN		( 1U << 2 )
#define ADC_CH1			( 1U << 6 )
#define ADC_SEQ_LEN1	0x00
#define ADC_CR_EN		( 1U << 0 )
#define ADC_CR_ADSTART_pos	(1U << 2)
#define ISR_EOC			( 1U << 2 )

void PC0_adc1_ch1_init(void){
		/* configure ADC pin */
	// enable clock access to adc pin port GPIOC
	RCC->AHB2ENR |= GPIOC_EN;

	// set mode of PC0 to analog mode
	GPIOC->MODER |= ( 1U << 0 );
	GPIOC->MODER |= ( 1U << 1 );

		/*configure ADC module*/
	// enable clock access to ADC
	RCC->AHB2ENR |= ADC_EN;

	/* configure adc parameters*/
	// conversion sequence start
	ADC1->SQR1 |= ADC_CH1;
	// conversion sequence len is ZERO, 18.7.11 ADC regular sequence register 1 (ADC_SQR1)
	// 0000: 1 conversion
	// 0001: 2 conversions, etc

	// enable adc
	ADC1->CR = ADC_CR_EN;
}

void adc1_ch1_start_conversion( void ){
/* start conversion */
	ADC1->CR |= ADC_CR_ADSTART_pos;
}

uint32_t adc1_ch1_read( void ){
	// wait for the conversion is complete
	while( !(ADC1->ISR & ISR_EOC) );

	// read converted result
	return ADC1->DR;
}
