#define F_CPU 4915200UL              // Define CPU clock frequency for delay routines
#include <avr/io.h>                 // Include AVR I/O definitions
#include <util/delay.h>             // Include delay routines (_delay_ms, _delay_us)
#include <stdio.h>                  // Include standard I/O (printf)
#include <stdint.h>                 // Include standard integer types (uint8_t, etc.)
#include <avr/pgmspace.h>           // Include program memory access (PROGMEM)
#include <avr/interrupt.h>

#include "ADC.h"
#include "OLED.h"
#include "SPI.h"
#include "SRAM.h"
#include "UART.h"
#include "UTILS_IO.h"
#include "UTILS_JOY.h"

/* ----------------- MAIN ----------------- */
int main(void) {
	//uint8_t x_val, y_val, x_s, y_s;

	USART0_Init(MYUBRR);                    // Initialize UART
	stdout = &uart0_str;                 // Redirect printf to UART
	//SRAM_init();
	
	spi_init();                             // Initialize SPI
	//oled_init();                            // Initialize OLED

	//max156_init();                           // Initialize ADC
	//adc_clk_init();                          // Initialize ADC clock

	//oled_goto(0,0);                          // Go to first column, first page
	//oled_puts("Joystick:");                  // Display "Joystick:"
	printf("Init");
	
	
	sei();
	
	slave_select(IO_CS);
	spi_write_display_command(0x05);
	_delay_us(50);
	spi_write(0x00);
	_delay_us(50);
	spi_write(0x00);
	_delay_us(50);
	slave_reset(IO_CS);
	
	
	while (1) {
		_delay_ms(1000);
		slave_select(IO_CS);
		spi_write(0x0f);
		slave_reset(IO_CS);
		
		flashing_light();

		
	}
}
