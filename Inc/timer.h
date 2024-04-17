/*
 * timer.h
 *
 *  Created on: Apr 16, 2024
 *      Author: t.shypytiak
 */

#ifndef TIMER_H_
#define TIMER_H_

#define SR_UIF 		( 1U << 0 )
#define SR_CC1IF	( 1U << 1 )

void tim2_1hz_init(void);

void tim2_ch1_PA5_OC_init(void);

void tim3_pa6_input_capture( void );

#endif /* TIMER_H_ */
