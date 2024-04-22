/*
 * adc.c
 *
 *  Created on: Apr 9, 2024
 *      Author: tasifacij
 */
#include "adc.h"
#include "stm32l4xx.h"

#define ADC123_EN			( 1U << 13 )/*AHB2 bus*/
#define GPIOC_EN			( 1U << 2 )/*6.4.17 referrence manual*/

#define ADC_CH2_SQ1			( 1U << 7 )/* reference manual 18.7.11*/
#define ADC_SEQ_LEN1		0x00

#define ADC_CR_EN		( 1U << 0 )
#define ADC_CR_ADSTART_pos	(1U << 2)

#define IER_EOCIE_R		( 1U << 2 )// 18.7.2 ADC interrupt enable register ADC_IER

void PC1_adc2_ch2_init(void){

		/* configure ADC pin */
	// 1. enable clock access to adc pin port GPIOC
	RCC->AHB2ENR |= GPIOC_EN;

	// 2. set mode of PC1 to analog mode
	// 8.5.1 moder reference manual
	GPIOC->MODER |= ( 1U << 1 );
	GPIOC->MODER |= ( 1U << 0 );
	GPIOC->ASCR |= 0x2;      //Connect analog switch to the ADC input(PORT C input 1), only necessary on STM32L47x/L48x devices


		/*** configure ADC module ***/
	// enable clock access to ADC
	RCC->AHB2ENR |= ADC123_EN;

	// https://stackoverflow.com/questions/54856078/stm32l476-adc-not-ready
	RCC->CCIPR |= ( 1U << 28 );
	RCC->CCIPR |= ( 1U << 29 );



	/*** configure adc parameters ***/
	// 1. conversion sequence start, set ch 2 into sq1

	ADC2->SQR1 = ADC_CH2_SQ1;
	// 2. conversion sequence len is ZERO, 18.7.11 ADC regular sequence register 1 (ADC_SQR1)
	// 0000: 1 conversion
	// 0001: 2 conversions, etc
	ADC2->SQR1 &= ~( 1U << 0 );
	ADC2->SQR1 &= ~( 1U << 1 );
	ADC2->SQR1 &= ~( 1U << 2 );
	ADC2->SQR1 &= ~( 1U << 3 );


	// 3. enable adc
	ADC2->CR = 0x00000000;//Disable deep-power-down by setting DEEPPWD to 0
	ADC1->CR |= 0x2;//ADDIS(ADC disable command); disable the ADC
	ADC2->CR |= ( 1U<< 28 );//Enable ADC voltage regulator by setting ADVREGEN to 1
	for( int i = 0; i < 50000; i ++ );

	ADC2->ISR    |= 1;		 //Clear ADC ready by setting ADRDY to 1
	ADC2->CR |= ADC_CR_EN;	//Enable ADC by setting ADEN to 1
	for( int i = 0; i < 50000; i ++ );
}

void adc2_ch2_start_conversion( void ){
/* start conversion */
	ADC2->CR |= ADC_CR_ADSTART_pos;
}

uint32_t adc2_ch2_read( void ){
	// wait for the conversion is complete
	while( !(ADC2->ISR & SR_EOC) ){}

	// read converted result
	return ( ADC2->DR );
}

void PC1_adc2_ch2_interrupt_init(void){

		/* configure ADC pin */
	// 1. enable clock access to adc pin port GPIOC
	RCC->AHB2ENR |= GPIOC_EN;

	// 2. set mode of PC1 to analog mode
	// 8.5.1 moder reference manual
	GPIOC->MODER |= ( 1U << 1 );
	GPIOC->MODER |= ( 1U << 0 );
	GPIOC->ASCR |= 0x2;      //Connect analog switch to the ADC input(PORT C input 1), only necessary on STM32L47x/L48x devices


		/*** configure ADC module ***/
	// enable clock access to ADC
	RCC->AHB2ENR |= ADC123_EN;

	// https://stackoverflow.com/questions/54856078/stm32l476-adc-not-ready
	RCC->CCIPR |= ( 1U << 28 );
	RCC->CCIPR |= ( 1U << 29 );



	/*** configure adc parameters ***/
	// 1. conversion sequence start, set ch 2 into sq1

	ADC2->SQR1 = ADC_CH2_SQ1;
	// 2. conversion sequence len is ZERO, 18.7.11 ADC regular sequence register 1 (ADC_SQR1)
	// 0000: 1 conversion
	// 0001: 2 conversions, etc
	ADC2->SQR1 &= ~( 1U << 0 );
	ADC2->SQR1 &= ~( 1U << 1 );
	ADC2->SQR1 &= ~( 1U << 2 );
	ADC2->SQR1 &= ~( 1U << 3 );

	// enable interupt of regular conversion
	ADC2->IER |= IER_EOCIE_R;
	// enable in NVIC
	NVIC_EnableIRQ( ADC1_2_IRQn );

	// 3. enable adc
	ADC2->CR = 0x00000000;//Disable deep-power-down by setting DEEPPWD to 0
	ADC1->CR |= 0x2;//ADDIS(ADC disable command); disable the ADC
	ADC2->CR |= ( 1U<< 28 );//Enable ADC voltage regulator by setting ADVREGEN to 1
	for( int i = 0; i < 50000; i ++ );

	ADC2->ISR    |= 1;		 //Clear ADC ready by setting ADRDY to 1
	ADC2->CR |= ADC_CR_EN;	//Enable ADC by setting ADEN to 1
	for( int i = 0; i < 50000; i ++ );
}
