/*
* ATMEGA32_TEST.c
*
* Created: 4/17/2020 1:42:10 AM
* Author : Hassan
*/
#include "f_cpu.h"
#include <avr/io.h>
#include <util/delay.h>
#include "f_cpu.h"
#include "macros.h"
#include "types.h"
#include "dio.h"
#include "lcd.h"
#include "keypad.h"
#include "adc.h"
#include "uart.h"

#define SERVO_SIGNAL_PORT 2
#define SERVO_SIGNAL_PIN 0
#define RIGHT_DURATION 1200
#define LEFT_DURATION 2400
#define FRONT_DURATION 1900
void setServoDuty(u16 duartion) {
	u8 i;
	for (i=0; i<5; i++) {
		dio_vid_set_pin_value(SERVO_SIGNAL_PORT, SERVO_SIGNAL_PIN, HIGH_PIN);
		_delay_us(duartion);
		dio_vid_set_pin_value(SERVO_SIGNAL_PORT, SERVO_SIGNAL_PIN, LOW_PIN);
		_delay_us(20000-duartion);
	}
}



int main(void)
{
	dio_vid_set_pin_direction(SERVO_SIGNAL_PORT, SERVO_SIGNAL_PIN, OUTPUT_PIN);
	while (1) {
		setServoDuty(RIGHT_DURATION);
		_delay_ms(1000);
				setServoDuty(LEFT_DURATION);
						_delay_ms(1000);
		setServoDuty(FRONT_DURATION);
				_delay_ms(1000);


	}
	

	
	
}

