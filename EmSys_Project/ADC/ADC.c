#define F_CPU 4915200UL              // Define CPU clock frequency for delay routines
#include <avr/io.h>                 // Include AVR I/O definitions
#include <stdio.h>                  // Include standard I/O (printf)
#include <stdint.h>                 // Include standard integer types (uint8_t, etc.)
#include <avr/pgmspace.h>           // Include program memory access (PROGMEM)
#include <avr/interrupt.h>

#include "ADC.h"

void max156_init(void) {
	DDRA = 0x00;                           // Set PORTA as input (ADC data)
	PORTA = 0x00;                          // Disable pull-ups
	CS_DDR |= (1 << CS_PIN);  CS_PORT |= (1 << CS_PIN); // Set CS as output, idle high
	WR_DDR |= (1 << WR_PIN);  WR_PORT |= (1 << WR_PIN); // Set WR as output, idle high
	RD_DDR |= (1 << RD_PIN);  RD_PORT |= (1 << RD_PIN); // Set RD as output, idle high
}

void adc_clk_init(void) {
	// Set PD5 (OC1A) as output
	DDRD |= (1 << ADC_CLK_PIN);
	DDRD |= (0 << BUSY_INIT); 		//busy init
	

	// Set the square signal
	TCCR1A = (1 << COM1A0) | (1 << WGM10) | (1 << WGM11);	// 1.2048MHz
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
	OCR1A = 0;
}

/* //---------- Read single channel ----------
uint8_t max156_read_channel(void) {
	uint8_t val;

	volatile uint8_t* adcMem = (uint8_t*)0x1000;
	adcMem[0] = 1;
	_delay_us(T_CONVERSION_US);
	val = adcMem[0];
	return val;
}*/
