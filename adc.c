/*
 * adc.c
 *
 *  Created on: Oct 5, 2019
 *  Author: Ahmed Hassan
 */
#include <avr/io.h>
#include "types.h"
#include "macros.h"

void adc_start(void) {
	setBit(ADCSRA, ADSC);
}

void adc_vid_init (u8 pin) {
	//Voltage Reference Selection : AVCC with external capacitor at AREF pin
	setBit(ADMUX, REFS0);
	clrBit(ADMUX, REFS1);
	
	//NO LEFT ADJ
	clrBit(ADMUX, ADLAR);
	
	//CHANNEL SELECT WITH Single Ended Input
	ADMUX = ADMUX | pin;
	
	//PRESCALAR 128
	setBit(ADCSRA, ADPS0);
	setBit(ADCSRA, ADPS1);
	setBit(ADCSRA, ADPS2);
	
	//DISABLE INTERUPT
	clrBit(ADCSRA, ADIE);
	
	//ENABLE ADC
	setBit(ADCSRA, ADEN);
	
	//ADC START CONVERSION
	adc_start();
}

u8 adc_u8_get_result(u16* result) {
	if (getBit(ADCSRA,4)) {
		ADCW&=(0b0000001111111111);
		*result = ADCW;
		setBit(ADCSRA,4);
		adc_start();
		return 1; /*Flag indicates that ADC completed conversion*/
	}
	return 0; /*Flag indicates that ADC not completed yet*/
}

