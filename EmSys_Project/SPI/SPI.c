#define F_CPU 4915200UL              // Define CPU clock frequency for delay routines
#include <avr/io.h>                 // Include AVR I/O definitions
#include <stdio.h>                  // Include standard I/O (printf)
#include <stdint.h>                 // Include standard integer types (uint8_t, etc.)
#include <avr/pgmspace.h>           // Include program memory access (PROGMEM)
#include <avr/interrupt.h>

#include "SPI.h"

void spi_init(void)
{
	//Sets MOSI, SCK, CS as output, while MISO is input
	DDRB |= (1 << IO_CS) | (1 << DISP_CS) | (1 << CAN_CS) | (1 << SPI_MOSI) | (1 << SPI_CLK);
	
	// Enable SPI and select this device as master
	SPCR |= (1 << SPE) | (1 << MSTR);
	
	// Drive CS high initially
	PORTB |= (1 << IO_CS) | (1 << DISP_CS) | (1 << CAN_CS);
}


static inline void spi_write_display_command(uint8_t data){
   (PORTB &= ~(1<<DISP_DC)); //command
   SPDR = data;
   while (!(SPSR & (1 << SPIF))) {};
   (PORTB |=  (1<<DISP_DC)); //data
}


static inline void spi_write(uint8_t data){
   SPDR = data;
   while (!(SPSR & (1 << SPIF))) {};
}

void spi_write_n_bytes(uint8_t slave_pin, uint8_t cmd, const uint8_t *data, uint8_t n){    // write n bytes !!! I did not check it !!!!! I am not sure it is working !!!
	slave_select(slave_pin);
	_delay_us(5);
	
	spi_write(cmd);
	_delay_us(10);
	
	for(int i=0;i<n;i++){
		spi_write(data[i]);
		_delay_us(5);
	}
	
	slave_reset(slave_pin);
	_delay_us(5);
}

static inline uint8_t spi_read(void){                                                               // read  byte
	SPDR = 0x00;
	while (!(SPSR & (1 << SPIF))) {};
	return SPDR;
}

void spi_read_n_bytes_io_and_save_in_array(uint8_t cs, uint8_t n, uint8_t cmd, uint8_t *buffer){       // read n bytes
	slave_select(cs);
	_delay_us(5);
	spi_write(cmd);
	_delay_us(40);
	
	for(int i = 0;i<n;i++){
		buffer[i]=spi_read();
		_delay_us(10);
	}
	slave_reset(cs);
}

static inline void slave_select(uint8_t slave_pin){
   PORTB |= (1 << DISP_CS) | (1 << IO_CS);
   
   PORTB &= ~(1 << slave_pin);
}

static inline void slave_reset(uint8_t slave_pin){
   PORTB |= (1 << slave_pin);
}
