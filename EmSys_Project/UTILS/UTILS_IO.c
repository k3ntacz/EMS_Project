#define F_CPU 4915200UL              // Define CPU clock frequency for delay routines
#include <avr/io.h>                 // Include AVR I/O definitions
#include <stdio.h>                  // Include standard I/O (printf)
#include <stdint.h>                 // Include standard integer types (uint8_t, etc.)
#include <avr/pgmspace.h>           // Include program memory access (PROGMEM)
#include <avr/interrupt.h>

#include "UTILS_IO.h"
#include "SPI.h"

void light_on(uint8_t LED_N){
	slave_select(IO_CS);
	_delay_us(50);
	
	spi_write_display_command(0x05);
	_delay_us(50);
	
	spi_write((uint8_t) LED_N);
	_delay_us(50);
	spi_write(0x01);
	_delay_us(50);
	
	slave_reset(IO_CS);
	//_delay_us(2000);
}

void light_off(uint8_t LED_N){
	slave_select(IO_CS);
	_delay_us(50);
	
	spi_write_display_command(0x05);
	_delay_us(50);
		
	spi_write((uint8_t) LED_N);
	_delay_us(50);
	spi_write(0x00);
	_delay_us(50);
		
	slave_reset(IO_CS);
		
	//_delay_us(2000);
}

void flashing_light(void){
	while (1){
		for (int i = 0; i < 6; i++){
			light_on(i);
			 _delay_ms(250);
			 printf("Light on ");
		}
		
		for (int j = 0; j < 6; j++){
			light_off(j);
			_delay_ms(250);
			printf("Light off ");
		}
	}
}
