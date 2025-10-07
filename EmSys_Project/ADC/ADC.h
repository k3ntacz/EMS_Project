#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define CS_PIN     PC3               // Chip select pin for MAX156 ADC
#define CS_PORT    PORTC
#define CS_DDR     DDRC

#define WR_PIN     PD6               // Write pulse pin
#define WR_PORT    PORTD
#define WR_DDR     DDRD

#define RD_PIN     PD7               // Read pulse pin
#define RD_PORT    PORTD
#define RD_DDR     DDRD

// ADC clock output on PD5 (OC1A)
#define BUSY_INIT	PD4
#define ADC_CLK_PIN PD5

// Timing margins
#define T_WR_PULSE_US      1         // Write pulse width in microseconds
#define T_CONVERSION_US    5         // Conversion delay in microseconds
#define T_RD_PULSE_US      1         // Read pulse width in microseconds

void max156_init(void);

void adc_clk_init(void);

//---------- Read single channel ----------
//uint8_t max156_read_channel(void);

#endif
